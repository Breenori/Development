import ij.*;
import ij.text.*;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

import java.awt.*;
import java.lang.reflect.Array;

import ij.gui.GenericDialog;

public class Register2_ implements PlugInFilter {

    int BG_VAL = 255; //background

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about")) {
            showAbout();
            return DONE;
        } //if
        return DOES_8G;
    } //setup

    public double getEntropyOfImg(double[][] imgData, int width, int height) {

        double[] histogram = histogram(imgData, width, height);
        int pixels = width * height;

        double result = 0.0;
        for (int i = 0; i < histogram.length; i++) {
            double p = histogram[i] / (double) pixels;
            if (p > 0) result += p * (Math.log10(p) / (double) Math.log10(2));

        }
        return -result;
    } //getEntropyOfImg

    public double getEntropyOfImages(double[][] imgA, double[][] imgB, int width, int height) {

        double[][] histogramOfTwo = histogram(imgA, imgB, width, height);
        int pixels = width * height;

        double result = 0.0;

        for (int i = 0; i < histogramOfTwo.length; i++) {
            for (int j = 0; j < histogramOfTwo.length; j++) {
                double p = (histogramOfTwo[i][j]) / (double) pixels;
                if (p > 0) result += p * (Math.log10(p) / (double) Math.log10(2));
            }

        }
        return -result;
    } //getEntropyOfImages


    public static double[] histogram(double[][] image, int width, int height){

        double[] histogram = new double[256];
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int img = (int)image[x][y];
                histogram[img]++;
            }
        }

        return histogram;
    }

    public static double[][] histogram(double[][] image1, double[][] image2, int width, int height){
        double[][] histogram = new double[256][256];

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int img1 = (int)image1[x][y];
                int img2 = (int)image2[x][y];
                histogram[img1][img2]++;
            }
        }

        return histogram;
    }

    public int getBilinearInterpolatedValue(double[][] imgData, int width, int height, double idxX, double idxY) {
        double saveX = idxX - (int) (idxX);
        double saveY = idxY - (int) (idxY);

        int x1 = (int) (idxX);
        int x2 = (int) (idxX + 0.5);
        int y1 = (int) (idxY);
        int y2 = (int) (idxY + 0.5);

        if (x1 >= 0 && x1 < width && x2 >= 0 && x2 < width && y1 >= 0 && y1 < height && y2 >= 0 && y2 < height) {
            double interimResult1 = calculatePointForBilineareInterpolation(imgData[x1][y1], imgData[x2][y1], saveX);
            double interimResult2 = calculatePointForBilineareInterpolation(imgData[x1][y2], imgData[x2][y2], saveX);
            return (int) (calculatePointForBilineareInterpolation(interimResult1, interimResult2, saveY));
    }
        return 0;
    }   //getBilinearInterpolatedValue

    public double calculatePointForBilineareInterpolation(double point1, double point2, double storagedPoint){
            double pointDifference = Math.abs(point1-point2);
            double minPoint = Math.min(point1, point2);

            double result = minPoint + storagedPoint * pointDifference;
            return result;

        }

    public double getNNInterpolatedValue(double[][] imgData, int width, int height, double idxX, double idxY) {
        int x1 = (int) (idxX + 0.5);
        int y1 = (int) (idxY + 0.5);

        if ((x1 >= 0) && (y1 >= 0) && (x1 < width) && (y1 < height)) {
            double actVal = imgData[x1][y1];
            return actVal;
        } //if
        else {
            return 255.0;
        } //else ==> outside mask
    } //getNN

    public double[][] getDiffImg(double[][] imgA, double[][] imgB, int width, int height) {
        double[][] returnImg = new double[width][height];
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                returnImg[x][y] = Math.abs(imgA[x][y] - imgB[x][y]);
            }
        }

        return returnImg;
    } //getDiffImg


    public double getImgDiffMI(double[][] imgData1, double[][] imgData2, int width, int height) {
        return getEntropyOfImg(imgData1, width, height) +
                getEntropyOfImg(imgData2, width, height) -
                getEntropyOfImages(imgData1, imgData2, width, height);
    } //getImgDiffMI

    public double getImgDiffSSE(double[][] imgData1, double[][] imgData2, int width, int height) {
        double currentError = 0.0;
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                double diff = imgData1[x][y] - imgData2[x][y];
                currentError += diff * diff;
            }
        }

        return currentError;
    } //getImageDiffSSE

    public double getImgDiffBinary(int[][] imgData1, int[][] imgData2, int width, int height) {
        //TODO
        return -1;
    } //getImgDiffBinary


    public double[][] transformImg(double[][] inImg, int width, int height, double transX, double transY, double rotAngle) {

        double[][] retArr = new double[width][height];


        double radAngle = -rotAngle * Math.PI / 180.0; //Attenstion "-" for changing direction due tp backward mapping
        //double radAngle = Math.toRadians(rotAngle);
        double cosTheta = Math.cos(radAngle);
        double sinTheta = Math.sin(radAngle);

        double widthHalf = width / 2.0;
        double heightHalf = height / 2.0;


        //backproject all pixels of result image B
        //iterate all pixels and calculate the new value
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {

                //1) move coordinate to center
                double posX = x - widthHalf;
                double posY = y - heightHalf;

                //2) rotate
                double rotatedX = posX * cosTheta + posY * sinTheta;
                double rotatedY = -posX * sinTheta + posY * cosTheta;

                //3) move coordinate back from center
                rotatedX = rotatedX + widthHalf;
                rotatedY = rotatedY + heightHalf;

                //4) translate
                posX = rotatedX - transX;
                posY = rotatedY - transY;

                //finally geht the interpolated pixel value
                double scalarVal = getNNInterpolatedValue(inImg, width, height, posX, posY);

                retArr[x][y] = scalarVal;

            }
        }


        return retArr;
    } //transformImg





    /*
   a)
     */
    public double[][][] splitImage(double[][] image, int width, int height) {
        int halfWidth = (int) width/2;

        //second image
        //look if width is odd or even
        int startSecondImage = halfWidth + 1;
        if(width%2==0)
            startSecondImage = halfWidth - 1;


        double[][] retArrA = new double[halfWidth][height];
        double[][] retArrB = new double[halfWidth][height];

        for (int x = 0; x < halfWidth; x++) {
            for (int y = 0; y < height; y++) {
                retArrA[x][y] = image[x][y];
                retArrB[x][y] = image[startSecondImage+x][y];
            }
        }

        double [][][] imagePair = new double [2][width][height];
        imagePair[0] = retArrA;
        imagePair[1] = retArrB;

        return imagePair;

    }

    //b)
    public double[][] moveImage(double[][] inImg, int width, int height, double transX, double transY, double rotAngle, String methode) {

        double[][] retArr = new double[width][height];

        double radAngle = -rotAngle * Math.PI / 180.0; //Attention "-" for changing direction due tp backward mapping
        double cosTheta = Math.cos(radAngle);
        double sinTheta = Math.sin(radAngle);

        double widthHalf = width / 2.0;
        double heightHalf = height / 2.0;


        //backproject all pixels of result image B
        //iterate all pixels and calculate the new value
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {

                //1) move coordinate to center
                double posX = x - widthHalf;
                double posY = y - heightHalf;

                //2) rotate
                double rotatedX = posX * cosTheta + posY * sinTheta;
                double rotatedY = -posX * sinTheta + posY * cosTheta;

                //3) move coordinate back from center
                rotatedX = rotatedX + widthHalf;
                rotatedY = rotatedY + heightHalf;

                //4) translate
                posX = rotatedX - transX;
                posY = rotatedY - transY;

                //finally geht the interpolated pixel value
                double scalarVal = 0.0;
                if(methode.equals("N")){
                    scalarVal = getNNInterpolatedValue(inImg, width, height, posX, posY);
                }
                else {
                    scalarVal = getBilinearInterpolatedValue(inImg, width, height, posX, posY);
                }

                retArr[x][y] = scalarVal;
            }
        }

        return retArr;
    } //moveImage


    //c)
    public double [][] applyAutomaticRegistration( double[][] imageA, double[][] unregisteredImg, double initError, int width, int height){
        double[][] registeredImg = new double[width][height];
        double[][] diffImg = getDiffImg(imageA, unregisteredImg, (int)width/2, height);


        //cf. radius ==> 11 solutions = 2*5+1 (for 0)// -5;5 (-5, -4, -3, ..., 0, 1, 3, ... 5);
        int numOfStepsTx = 10;
        int numOfStepsTy = 10;
        int numOfStepsRot = 10;

        //multiply steps ==> (-10, -8, -6, ..., 0, 2, 6, ... 10);
        double stepWidthTx = 5.0;
        double stepWidthTy = 5.0;
        double stepWidthRot = 5.0;

        //size of search space is: 11 x 11 x 11 ==> 1,331 solutions
        //one possible search candidate is (-4, 2.0, -8.0) for (Tx, Ty, Rot);

        double minERR = initError;
        double bestTx = 0.0;
        double bestTy = 0.0;
        double bestRot = 0.0;

        //permutate all possible solutions
        for (int txStep = -numOfStepsTx; txStep <= numOfStepsTx; txStep++) {
            double currTx = txStep * stepWidthTx; //e.g. -4.0 for example above

            for (int tyStep = -numOfStepsTy; tyStep <= numOfStepsTy; tyStep++) {
                double currTy = tyStep * stepWidthTy;

                for (int rotStep = -numOfStepsRot; rotStep <= numOfStepsRot; rotStep++) {
                    double currRot = rotStep * stepWidthRot;

                    ///what is the error now?
                    registeredImg = transformImg(unregisteredImg, width, height, currTx, currTy, currRot);

                    //Gut oder schlechter Wert? Neuer Fehler ausrechnen!
                    //if we found a new best solution we replace the other
                    double currErr = getImgDiffMI(imageA, registeredImg, width, height);
                    if (currErr > minERR) {
                        minERR = currErr;
                        bestTx = currTx;
                        bestTy = currTy;
                        bestRot = currRot;
                        System.out.println("New best solution found with " + bestTx + ", " + bestTy + " , " + bestRot + " at ERR = " + minERR);

                        //find best solutions
                        registeredImg = transformImg(unregisteredImg, width, height, bestTx, bestTy, bestRot);
                        diffImg = getDiffImg(imageA, registeredImg, width, height);

                    }


                }
            }
        }
        ImageJUtility.showNewImage(registeredImg, width, height, "Registered Image = " + minERR);
        ImageJUtility.showNewImage(diffImg, width, height, "Differenz; ERR = " + minERR);

        return registeredImg;
    }


    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[]) ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();

        int[][] inDataArr = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        double[][] inDataArrDbl = ImageJUtility.convertToDoubleArr2D(inDataArr, width, height);


        //split the image into two images
        double[][][] imagepair = splitImage(inDataArrDbl, width, height);
        double[][] imageA = imagepair[0];
        double[][] imageB = imagepair[1];

        ImageJUtility.showNewImage(imageA, (int)width/2, height, "image A");
        ImageJUtility.showNewImage(imageB, (int)width/2, height, "image B");


        //transform or/and rotate image
        /*double[][] image1 = moveImage(inDataArrDbl, width, height, 50, 60, 0, "N");
        double[][] image2 = moveImage(inDataArrDbl, width, height, 2, 70, 0 ,"N");
        double[][] image3 = moveImage(inDataArrDbl, width, height, 0, 0, 90,"N");
        double[][] image4 = moveImage(inDataArrDbl, width, height, 20, 45, 178,"B");
        double[][] image5 = moveImage(inDataArrDbl, width, height, 0, 60, 150, "B");
        double[][] image6 = moveImage(inDataArrDbl, width, height, 55, 2, 77, "B");

        ImageJUtility.showNewImage(image1, width, height, "image1");
        ImageJUtility.showNewImage(image2, width, height, "image2");
        ImageJUtility.showNewImage(image3, width, height, "image3");
        ImageJUtility.showNewImage(image4, width, height, "image4");
        ImageJUtility.showNewImage(image5, width, height, "image5");
        ImageJUtility.showNewImage(image6, width, height, "image6");
*/


        //create registration task
        double transX = -43.0;
        double transY = -20.0;
        double rot = -2;

        double[][] unregisteredImg = transformImg(imageA, (int)width/2, height, transX, transY, rot);
        double initError = getImgDiffMI(imageA, unregisteredImg, (int)width/2, height);
        double[][] diffImg = getDiffImg(imageA, unregisteredImg, (int)width/2, height);

        ImageJUtility.showNewImage(diffImg, (int)width/2, height, "Differenz; ERR = " + initError);
        ImageJUtility.showNewImage(unregisteredImg, (int)width/2, height, "unregistered Image");



        //Bild 1
      double[][] registered1 = transformImg(unregisteredImg, (int)width/2, height, 15.0, -10, 5.0);
        diffImg = getDiffImg(imageA, registered1, (int)width/2, height);
        double newError = getImgDiffMI(imageA, registered1, (int)width/2, height);
        ImageJUtility.showNewImage(registered1, (int)width/2, height, "Err after reg = " + newError);
        ImageJUtility.showNewImage(diffImg, (int)width/2, height, "diff image; ERR = " + newError);

        //Bild2
        //double[][] registered2 = transformImg(unregisteredImg, (int)width/2, height, -10.0, 20.0, -15.0);
        //diffImg = getDiffImg(imageA, registered2, (int)width/2, height);
        //newError = getImgDiffSSE(imageA, registered2, (int)width/2, height);
        //ImageJUtility.showNewImage(registered2, (int)width/2, height, "Err after reg = " + newError);




        //TODO: put that into a proper methode ------ applyRegistration();

       double[][] registeredImage = applyAutomaticRegistration(imageA, unregisteredImg, initError, width/2, height);
       ImageJUtility.showNewImage(registeredImage, width/2, height, "Automatic Registered!");



        //-----------------------------------------------------------------


    } //run

    void showAbout() {
        IJ.showMessage("About Register_ ...", "core registration functionality ");
    } //showAbout


} //class Register_