import ij.*;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

public class Resample_ implements PlugInFilter {

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about"))
        {showAbout(); return DONE;}
        return DOES_8G;  // DOES_8G for greyscale pictures and DOES_RGB for colored pictures
    } //setup


    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[])ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();
        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        double[][] inDataArrDbl = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        double scaleFactor = 2.0;
        // let the user enter factor
        GenericDialog gd = new GenericDialog("median filter config");
        gd.addNumericField("scale factor (max 10)", scaleFactor, 4);
        String[] choices = {"Nearest Neighbour", "Bilinear", "Checkerboard", "Difference"};
        gd.addChoice("Method", choices, choices[1]);
        String choice;
        gd.showDialog();
        if (!gd.wasCanceled()) {
            scaleFactor = gd.getNextNumber();
            choice = gd.getNextChoice();
        } else {
            return;
        }
        if (scaleFactor > 10.0) scaleFactor = 10.0;

        int tgtWidth = (int) Math.round(width * scaleFactor);
        int tgtHeight = (int) Math.round(height * scaleFactor);

        double[][] resampledImage = getResampledImage(inDataArrDbl, width, height, tgtWidth, tgtHeight, false);
        double[][] resampledBilinearImage = getResampledImage(inDataArrDbl, width, height, tgtWidth, tgtHeight, true);

        if (choice == "Nearest Neighbour") {
            ImageJUtility.showNewImage(resampledImage, tgtWidth, tgtHeight, "resized with factor " + scaleFactor);
        } else if (choice == "Bilinear") {
            ImageJUtility.showNewImage(resampledBilinearImage, tgtWidth, tgtHeight, "resized bilinear with factor " + scaleFactor);
        } else if (choice == "Checkerboard") {
            ResizedImage checkerBoard = ImageTransformationFilter.getCheckerBoard(
                    ImageJUtility.convertToIntArr2D(resampledImage, tgtWidth, tgtHeight),
                    ImageJUtility.convertToIntArr2D(resampledBilinearImage, tgtWidth, tgtHeight),
                    tgtWidth, tgtHeight, 2);
            ImageJUtility.showNewImage(checkerBoard.getImage(), tgtWidth, tgtHeight, "Checkerboard with 2 resized images with " + scaleFactor);
        } else if (choice == "Difference") {
            double[][] differenceImage = getDifferenceOfImages(resampledImage, resampledBilinearImage, tgtWidth, tgtHeight);
            ImageJUtility.showNewImage(differenceImage, tgtWidth, tgtHeight, "difference between NN and Bilinear ");
        }
    } //run

    private double[][] getDifferenceOfImages(double[][] firstImage, double[][] secondImage, int width, int height) {
        double[][] resultImage = new double[width][height];
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                resultImage[i][j] = firstImage[i][j] - secondImage[i][j];
            }
        }
        return resultImage;
    }

    public double getNNInterpolatedValue(double[][] inImg, int width, int height, double posX, double posY) {
        // e.g. get value of inImg at position (posX, posY) (2.2, 3.7) => inImg[2][4]
        int posXint = (int) (posX + 0.5); // method to round a double value without Math library
        int posYint = (int) (posY + 0.5);

        if (posXint < 0) posXint = 0;
        if (posYint < 0) posYint = 0;
        if (posXint >= width) posXint = width - 1;
        if (posYint >= height) posYint = height - 1;

        return inImg[posXint][posYint];
    }

    public double getBilinearInterpolatedValue(double[][] inImg, int width, int height, double posX, double posY) {
        //Exercise 2.1b
        int posXint = (int) (posX);
        int posYint = (int) (posY);

        if (posXint < 0) posXint = 0;
        if (posYint < 0) posYint = 0;
        if (posXint >= width - 1) posXint = width - 2;
        if (posYint >= height - 1) posYint = height - 2;

        double deltaX = posX - posXint;
        double deltaY = posY - posYint;

        double result = (1 - deltaX) * (1 - deltaY) * inImg[posXint][posYint]
                + deltaX * (1 - deltaY) * inImg[posXint + 1][posYint]
                + (1 - deltaX) * deltaY * inImg[posXint][posYint + 1]
                + deltaX * deltaY * inImg[posXint + 1][posYint + 1];

        return result;
    }

    private double[][] getResampledImage(double[][] inImg, int width, int height, int tgtWidth, int tgtHeight, boolean b) {
        double[][] returnImg = new double[tgtWidth][tgtHeight];

        //this is strategy A
        //double scaleFactorW = tgtWidth / ((double)width);
        //double scaleFactorH = tgtHeight / ((double)height);

        //this is strategy B
        double scaleFactorW = (tgtWidth - 1.0) / (width - 1.0);
        double scaleFactorH = (tgtHeight -1.0) / (height - 1.0);

        //move all pixels FORWARD MAPPING from A ==> B
        /*for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
              double posX = x * scaleFactorW;
              double posY = y * scaleFactorH;
              //example, pos I(2,3) with scale factor 4.0 ==> I'(8, 12)
              returnImg[(int)Math.round(posX)][(int)Math.round(posY)] =
                      getNNInterpolatedValue(inImg, width, height, x, y);

            }
        } */

        //get all resulting pixel in B from any position in A, from B ==> A, BACKWARD MAPPING
        for(int x = 0; x < tgtWidth; x++) {
            for (int y = 0; y < tgtHeight; y++) {
                double posX = x / scaleFactorW;
                double posY = y / scaleFactorH;
                returnImg[x][y] = getNNInterpolatedValue(inImg, width, height, posX, posY);
            }
        }

        // this is strategy C - doesn't work yet
//        double scaleFactorW = tgtWidth / (double) width;
//        double scaleFactorH = tgtWidth / (double) height;
//        for (int x = 0; x < tgtWidth; x++) {
//            for (int y = 0; y < tgtHeight; y++) {
//                int aX = (int)(x / scaleFactorW);
//                int aY = (int)(y / scaleFactorH);
//                double offsetX = aX / (double) width;
//                double offsetY = aY / (double) height;
//                double rX = (1.0 / (2.0 * width)) + offsetX;
//                double rY = (1.0 / (2.0 * height)) + offsetY;
//                double posX = (2.0 * rX * (double) tgtWidth - 1.0) / 2.0;
//                double posY = (2.0 * rY * (double) tgtHeight - 1.0) / 2.0;
//                if (b) {
//                    returnImg[x][y] = getBilinearInterpolatedValue(inImg, width, height, posX, posY);
//                } else {
//                    returnImg[x][y] = getNNInterpolatedValue(inImg, width, height, posX, posY);
//                }
//            }
//        }

        return returnImg;
    }



    void showAbout() {
        IJ.showMessage("About Resample_...",
                "this is a PluginFilter to resize the input images\n");
    } //showAbout

} //class Resample_

