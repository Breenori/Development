import ij.IJ;
import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

public class Register_ implements PlugInFilter {

    int BG_VAL = 255; // background

    public int setup(String arg, ImagePlus imp) {
        if(arg.equals("about")){
            showAbout();
            return DONE;
        } //if
        return DOES_8G+DOES_STACKS+SUPPORTS_MASKING;
    } //setup

    //TODO-DONE
    public double getEntropyOfImg(double[][] imgData, int width, int height) {
        int maxValue = 255;
        int[] greyValueCounts = new int[maxValue + 1];
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int val = (int) imgData[x][y];
                greyValueCounts[val]++;
            }
        }
        double[] probabilities = new double[maxValue + 1];
        double pixels = width * height;
        for (int i = 0; i < probabilities.length; i++) {
            probabilities[i] = greyValueCounts[i] / pixels;
        }
        // calc Entropy: sum(p * log_2 p)
        double entropy = 0;
        double logBase2 = Math.log(2);
        for (int i = 0; i < probabilities.length; i++) {
            double p = probabilities[i];
            if (p > 0.0) {
                //double newP = p * (Math.log(p) / logBase2);
                double newP = p * Math.log(p);
                entropy += newP;
            }
        }
        return -entropy;
    } //getEntropyOfImg

    //TODO-DONE
    public double getEntropyOfImages(double[][] imgA, double[][] imgB, int width, int height) {
        int maxValue = 255;
        int[][] greyValueCounts = new int[maxValue + 1][maxValue + 1];
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int valA = (int) imgA[x][y];
                int valB = (int) imgB[x][y];
                greyValueCounts[valA][valB]++;
            }
        }
        double[][] probabilities = new double[maxValue + 1][maxValue + 1];
        double pixels = width * height;
        for (int i = 0; i < maxValue + 1; i++) {
            for (int j = 0; j < maxValue + 1; j++) {
                probabilities[i][j] = greyValueCounts[i][j] / pixels;
            }
        }
        // calc Entropy: sum(p * log_2 p)
        double entropy = 0;
        double logBase2 = Math.log(2);
        for (int i = 0; i < maxValue + 1; i++) {
            for (int j = 0; j < maxValue + 1; j++) {
                double p = probabilities[i][j];
                if (p > 0.0) {
                    //double newP = p * (Math.log(p) / logBase2);
                    double newP = p * Math.log(p);
                    entropy += newP;
                }
            }
        }
        return -entropy;
    }

    //TODO-DONE
    public double getBilinearInterpolatedValue(double[][] imgData, int width, int height, double idxX, double idxY) {
        int posXint = (int) (idxX);
        int posYint = (int) (idxY);
        double deltaX = idxX - posXint;
        double deltaY = idxY - posYint;

        if((posXint >= 0) && (posYint >= 0) && (posXint < width - 1) && (posYint < height - 1)) {
            double result = (1 - deltaX) * (1 - deltaY) * imgData[posXint][posYint]
                    + deltaX * (1 - deltaY) * imgData[posXint + 1][posYint]
                    + (1 - deltaX) * deltaY * imgData[posXint][posYint + 1]
                    + deltaX * deltaY * imgData[posXint + 1][posYint + 1];
            return result;
        }
        return 255; // out of range default value
    } //getBilinearInterpolatedValue

    public double getNNInterpolatedValue(double[][] imgData, int width, int height, double idxX, double idxY) {
        int x1 = (int) (idxX + 0.5);
        int y1 = (int) (idxY + 0.5);

        if((x1 >= 0) && (y1 >= 0) && (x1 < width) && (y1 < height)) {
            double actVal = imgData[x1][y1];
            return actVal;
        } //if
        else {
            return 255;
        } //else ==> outside mask
    } //getNN

    public double[][] getDiffImg(double[][] imgA, double[][] imgB, int width, int height) {
        double[][] returnImg = new double[width][height];
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                returnImg[x][y] = Math.abs(imgA[x][y] - imgB[x][y]);
            }
        }
        return returnImg;
    } //getDiffImg


    //TODO-DONE: exercise 3d - error detection with mutual information
    public double getImgDiffMI(double[][] imgData1, double[][] imgData2, int width, int height) {
        // Slides registration 5 - Slide 32: I(A,B)=H(B)-H(B|A)=H(B)+H(A)-H(A,B)
        double hA = getEntropyOfImg(imgData1, width, height);
        double hB = getEntropyOfImg(imgData2, width, height);
        double hAB = getEntropyOfImages(imgData1, imgData2, width, height);
        return hB + hA - hAB;
    } //getImgDiffMI

    public double getImgDiffSSE(double[][] imgData1, double[][] imgData2, int width, int height) {
        double currentError = 0.0;
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                double diff = imgData1[x][y] - imgData2[x][y];
                currentError += diff * diff;
            }
        }
        return currentError;
    } //getImageDiffSSE

    private double getOptimizedThreshold(int[][] inImg, int width, int height, int guess) {
        double sumLower = 0;
        double countLower = 0;
        double sumHigher = 0;
        double countHigher = 0;

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                if (inImg[x][y] <= guess) {
                    sumLower += inImg[x][y];
                    countLower++;
                } else {
                    sumHigher += inImg[x][y];
                    countHigher++;
                }
            }
        }
        if (countLower > 0.0) sumLower = sumLower / countLower;
        if (countHigher > 0.0) sumHigher = sumHigher / countHigher;
        return (sumLower + sumHigher) / 2;
    }

    //TODO
    public double getImgDiffBinary(double[][] imgData1, double[][] imgData2, int width, int height) {
        return -1;
    } //getImgDiffBinary

    //TODO-DONE: exercise 3b - method for translation and rotation (nn or bilinear)
    /*
    * rotAngle... angle in degree
    * */
    public double[][] transformImg(double[][] inImg, int width, int height, double transX, double transY, double rotAngle, boolean bilinear) {
        double[][] retArr = new double[width][height];

        //ATTENTION: change direction due to backward mapping
        double radAngle = -rotAngle * Math.PI /180.0; // Math.toRadians is more expensive
        double cosTheta = Math.cos(radAngle);
        double sinTheta = Math.sin(radAngle);
        double midX = width/2.0;
        double midY = height/2.0;

        //backproject all pixels of result image B
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                //1) move coordinate to center
                double posX = x - midX;
                double posY = y - midY;
                //2) rotate
                double newX = posX * cosTheta + posY * sinTheta;
                double newY = -posX * sinTheta + posY * cosTheta;
                //3) move coordinate back from center
                newX = newX + midX;
                newY = newY + midY;
                //4) translate
                posX = newX - transX;
                posY = newY - transY;

                double scalarVal;
                if (bilinear) {
                    scalarVal = getBilinearInterpolatedValue(inImg, width, height, posX, posY);
                } else {
                    scalarVal = getNNInterpolatedValue(inImg, width, height, posX, posY);
                }
                retArr[x][y] = scalarVal;
            }
        }

        return retArr;
    } //transformImg

    private double[][][] getSplitedImage(double[][] inImg, int width, int height) {
        double[][][] resultImages = new double[2][][];
        int halfWidth = width / 2;
        double[][] leftImg = new double[halfWidth][height];
        // right image is one pixel wider if width is odd
        int oddWidth = width % 2 == 0 ? halfWidth : halfWidth + 1;
        double[][] rightImg = new double[oddWidth][height];
        resultImages[0] = leftImg;
        resultImages[1] = rightImg;

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                if (x < halfWidth) {
                    leftImg[x][y] = inImg[x][y];
                } else {
                    rightImg[x - halfWidth][y] = inImg[x][y];
                }
            }
        }
        return resultImages;
    }

    //TODO-DONE: exercise 3c: automatic registration to find the best parameters
    private double[] applyRegistration(double[][] inDataArrDbl, double[][] unregisteredImg, int width, int height, double[] registrationParams, String method) {
//        int numOfStepsTx = 10; // 11 solutions ==> 2 *5 +1 (for  0) cf. radius ==> -5;5 (-5, -4, ... 5)
//        int numOfStepsTy = 10;
//        int numOfStepsRot = 10;
//        double stepWidthTx = 2.0; // multiply steps ==> (-10, -8, -6, ...)
//        double stepWidthTy = 2.0;
//        double stepWidthRot = 2.0;

        int numOfStepsTx = (int) registrationParams[0];
        int numOfStepsTy = (int) registrationParams[1];
        int numOfStepsRot = (int) registrationParams[2];
        double stepWidthTx = registrationParams[3];
        double stepWidthTy = registrationParams[4];
        double stepWidthRot = registrationParams[5];

        // size of search space: 11 x 11 x 11 ==> 1331 solutions
        // one possible search candidate is (-4, 2.0, -8.0) for(Tx, Ty, Rot)
        double minERR = 0.0;
        if (method == "MI") {
            minERR = getImgDiffMI(inDataArrDbl, unregisteredImg, width, height);
        } else if (method == "SSE") {
            minERR = getImgDiffSSE(inDataArrDbl, unregisteredImg, width, height);
        }

        double bestTx = 0.0;
        double bestTy = 0.0;
        double bestRot = 0.0;

        double currTx = 0.0;
        double currTy = 0.0;
        double currRot = 0.0;

        for (int txStep = -numOfStepsTx; txStep <= numOfStepsTx; txStep++) {
            currTx = txStep * stepWidthTx;

            for (int tyStep = -numOfStepsTy; tyStep <= numOfStepsTy; tyStep++) {
                currTy = tyStep * stepWidthTy;

                for (int rotStep = -numOfStepsRot; rotStep <= numOfStepsRot; rotStep++) {
                    currRot = rotStep * stepWidthRot;
                    double[][] registeredImg = transformImg(unregisteredImg, width, height, currTx, currTy, currRot, false);
                    double currErr = 0.0;
                    if (method == "MI") {
                        currErr = getImgDiffMI(inDataArrDbl, registeredImg, width, height);
                    } else if (method == "SSE") {
                        currErr = getImgDiffSSE(inDataArrDbl, registeredImg, width, height);
                    }

                    if ((method == "SSE" && currErr < minERR) || (method == "MI" && currErr > minERR)) { // check if better solution was found? if YES - replace the old solution
                        minERR = currErr;
                        bestTx = currTx;
                        bestTy = currTy;
                        bestRot = currRot;
                        System.out.println(method + ": NEW best solution found with " + bestTx + ", " + bestTy + ", " + bestRot + " at ERR = " + minERR);
                    }
                }
            }
        }
        double[] bestParams = {bestTx, bestTy, bestRot};
        return bestParams;
    }

    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[])ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();

        int[][] inDataArr = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        double[][] inDataArrDbl = ImageJUtility.convertToDoubleArr2D(inDataArr, width, height);

        // Parameters: [0]:numOfStepsTx, [1]:numOfStepsTy, [2]:numOfStepsRot,
        //             [3]:stepWidthTx, [4]:stepWidthTy, [5]:stepWidthRot
        double[] registrationParams = {10.0, 10.0, 5.0, 4.0, 4.0, 4.0};

        GenericDialog gd = new GenericDialog("register config");
        gd.addNumericField("Delta X", registrationParams[0], 0);
        gd.addNumericField("Delta Y", registrationParams[1], 0);
        gd.addNumericField("Rotations", registrationParams[2], 0);
        gd.addNumericField("Step Width X", registrationParams[3], 2);
        gd.addNumericField("Step Width Y", registrationParams[4], 2);
        gd.addNumericField("Step Width Rotation", registrationParams[5], 2);
        String[] methods = {"SSE", "MI"};
        gd.addRadioButtonGroup("Methods", methods, 3, 1, "SSE");
        String selectedMethod = "";
        gd.showDialog();
        if (!gd.wasCanceled()) {
            registrationParams[0] = gd.getNextNumber();
            registrationParams[1] = gd.getNextNumber();
            registrationParams[2] = gd.getNextNumber();
            registrationParams[3] = gd.getNextNumber();
            registrationParams[4] = gd.getNextNumber();
            registrationParams[5] = gd.getNextNumber();
            selectedMethod = gd.getNextRadioButton();
        } else {
            return;
        }
        //TODO-DONE: Exercise 3a: Split Image horizontal in the middle
        double[][][] splitImages = getSplitedImage(inDataArrDbl, width, height);
        width = width / 2; // override width after split
//        ImageJUtility.showNewImage(splitImages[0], width, height, "left image");
//        ImageJUtility.showNewImage(splitImages[1], width, height, "right image");

        // Translation Tests:
//        double tX, tY, rot;
//        GenericDialog gdTest1 = new GenericDialog("translation config");
//        gdTest1.addNumericField("Trans X", registrationParams[0], 0);
//        gdTest1.addNumericField("Trans Y", registrationParams[1], 0);
//        gdTest1.addNumericField("Rotation Angle", registrationParams[2], 0);
//        gdTest1.showDialog();
//        if (!gd.wasCanceled()) {
//            tX = gdTest1.getNextNumber();
//            tY = gdTest1.getNextNumber();
//            rot = gdTest1.getNextNumber();
//        } else {
//            return;
//        }
//        double[][] image = transformImg(inDataArrDbl,width, height, tX, tY, rot, true);
//        ImageJUtility.showNewImage(image, width, height, "tX:" + tX + ", tY:" + tY + ", rot:" + rot);


        GenericDialog output = new GenericDialog("Output");
        output.addMessage("Entropy of Image: " + getEntropyOfImg(inDataArrDbl, width, height));

        inDataArrDbl = splitImages[0]; // override inDataArrDbl with left image
        double[][] unregisteredImg = splitImages[1]; // right image
        double initError = getImgDiffSSE(inDataArrDbl, unregisteredImg, width, height);
        output.addMessage("Initial Error: " + initError);

        //ImageJUtility.showNewImage(unregisteredImg, width, height, "unregistered image with error = " + initError);

        //TODO-DONE: put that into a proper method - applyRegistrations(params...)
        double[] autoParams = applyRegistration(inDataArrDbl, unregisteredImg, width, height, registrationParams, selectedMethod);
        double[][] appliedReg = transformImg(unregisteredImg, width, height, autoParams[0], autoParams[1], autoParams[2], true);
        double currError = getImgDiffMI(inDataArrDbl, appliedReg, width, height);

        output.addMessage( selectedMethod + " best automatic parameters found with error: " + currError);
        output.addMessage("Best Translation-X: " + autoParams[0]);
        output.addMessage("Best Translation-Y: " + autoParams[1]);
        output.addMessage("Best Rotation: " + autoParams[2]);

        //ImageJUtility.showNewImage(appliedReg, width, height, "applied with " + selectedMethod + " error " + currError);

        double[][] diffImg = getDiffImg(inDataArrDbl, appliedReg, width, height);
        ImageJUtility.showNewImage(diffImg, width, height, "diff applied " + currError);

        output.showDialog();
    } //run



    void showAbout() {
        IJ.showMessage("About Register_ ...", "core registration functionality ");
    } //showAbout


} //class Register_ 