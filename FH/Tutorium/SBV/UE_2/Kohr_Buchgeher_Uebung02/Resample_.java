import ij.*;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

import javax.swing.*;
import java.awt.*;

public class Resample_ implements PlugInFilter {

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about"))
        {showAbout(); return DONE;}
        return DOES_8G;
    } //setup

    public static double[][] getResampledImage(double[][] inImg, int width, int height, int tgtWidth, int tgtHeight, boolean useBilinearInterpolation) {

        //initiate array for return image
        double[][] returnImg = new double[tgtWidth][tgtHeight];

        //this is strategy A)
        //double scaleFactorW = tgtWidth / ((double)width);
        //double scaleFactorH = tgtHeight / ((double)height);

        //this is strategy B)
        //calculate scale factor for width and height as of operation on slide 15 in the script
        double scaleFactorW = (tgtWidth - 1.0) / (width - 1.0);
        double scaleFactorH = (tgtHeight - 1.0) / (height - 1.0);

        System.out.println("scale X = " + scaleFactorW + "scale Y = " + scaleFactorH);

        //move all pixels FORWARD MAPPING from A == > B
        /*for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                double posX = x * scaleFactorW;
                double posY = y * scaleFactorH;
                //example, pos I(2,3) with scale factor 4.0 ==> I'(8,12)
                returnImg[(int)Math.round(posX)][(int)Math.round(posY)] = getNNinterpolatedValue(inImg, width, height, x, y)

            }//for y
        } //for x */

        //get all resulting pixel in B from any position in A, from B ==> A, BACKWARD MAPPING
        for(int x = 0; x < tgtWidth; x++) {
            for(int y = 0; y < tgtHeight; y++) {
                double posX = x / scaleFactorW;
                double posY = y / scaleFactorH;
                if(useBilinearInterpolation){
                    returnImg[x][y] = getBilinearinterpolatedValue(inImg, width, height, posX, posY);
                }
                else {
                    returnImg[x][y] = getNNinterpolatedValue(inImg, width, height, posX, posY);
                }
            } //for y
        } //for x

        //return array of return image
        return returnImg;
    }

    public static double getNNinterpolatedValue(double[][] inImg, int width, int height, double posX, double posY) {
        //e.g. get value of inImg at position (posX, posY)(2.2, 3.7) ==> inImg[2][4]

        //mechanism to round values to the nearest integer without Math.round
        int posXint = (int)(posX + 0.5);
        int posYint = (int)(posY + 0.5);

        //let's check the range
        if (posXint < 0)
            posXint = 0;
        if (posYint < 0)
            posYint = 0;
        if (posXint >= width)
            posXint = width - 1;
        if (posYint >= height)
            posYint = height - 1;

        //return value from input image that got calculated for output image
        return  inImg[posXint][posYint];
    }

    public static double getBilinearinterpolatedValue(double[][] inImg, int width, int height, double posX, double posY) {

        //rounding down positions
        int posXint_0 = (int) posX;
        int posYint_0 = (int) posY;

        //get offset positions
        int posXint_1 = posXint_0 + 1;
        int posYint_1 = posYint_0 + 1;

        //prevent getting out of bound
        if (posXint_1 >= width)
            posXint_1 = width - 1;
        if (posYint_1 >= height)
            posYint_1 = height - 1;

        //get position delta as weight for value delta
        double posXdelta = posX - posXint_0;
        double posYdelta = posY - posYint_0;

        //getting values of surrounding pixels
        int value_0_0 = (int) inImg[posXint_0][posYint_0];
        int value_1_0 = (int) inImg[posXint_1][posYint_0];
        int value_0_1 = (int) inImg[posXint_0][posYint_1];
        int value_1_1 = (int) inImg[posXint_1][posYint_1];

        //get bilinear interpolated value as seen on slide 9 from script
        int valueBIint = (int) Math.round(((1 - posXdelta) * (1 - posYdelta) * value_0_0) + (posXdelta * (1 - posYdelta) * value_1_0) + ((1 - posXdelta) * posYdelta * value_0_1) + (posXdelta * posYdelta * value_1_1));

        //return value from input image that got calculated for output image
        return valueBIint;
    }

    public static double[][] getDifference(double[][] NN, double[][] BI, int tgtWidth, int tgtHeight) {

        //initiate array for return image
        double[][] returnImg = new double[tgtWidth][tgtHeight];

        //get all resulting delta pixel values by subtracting bilinear interpolated and nearest neighbor interpolated value
        for(int x = 0; x < tgtWidth; x++) {
            for(int y = 0; y < tgtHeight; y++) {
                returnImg[x][y] = NN[x][y] - BI[x][y];

                //if the value is negative add the positive value to it twice
                if(returnImg[x][y] < 0){
                    returnImg[x][y] += (returnImg[x][y] * (-1)) * 2;
                } //if
            } //for y
        } //for x

        //return array of return image
        return returnImg;
    }

    public static double[][] getCheckerboard(double[][] NN, double[][] BI, int tgtWidth, int tgtHeight) {

        //initiate array for return image
        double[][] returnImg = new double[tgtWidth][tgtHeight];

        //generate a 2x2 checkerboard with nearest neighbor values in quadrant 1 and 4
        for(int x = 0; x < tgtWidth; x++) {
            for(int y = 0; y < tgtHeight; y++){

                //for all pixels placed inside the first and fourth quadrant use values of nearest neighbor interpolation
                if(((x < tgtWidth / 2) && (y < tgtHeight / 2)) || ((x > tgtWidth / 2) && (y > tgtHeight/ 2))) {
                    returnImg[x][y] = NN[x][y];
                } //if

                //else use values of bilinear interpolation
                else {
                    returnImg[x][y] = BI[x][y];
                } //else
            } //for y
        } //for x

        //return array of return image
        return returnImg;
    }

    public void run(ImageProcessor ip) {

        //initiate image data in arrays
        byte[] pixels = (byte[])ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();
        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        double[][] inDataArrDbl = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        //set default values for dialog variables
        double scaleFactor = 2.11;
        boolean useBilinearInterpolation = false;
        boolean showDifference = false;
        boolean showCheckerboard = false;

        //generate dialog with input field for scale factor and checkbox for usage of bilinear interpolation
        GenericDialog gd = new GenericDialog("resample");
        gd.addNumericField("scale factor (between 0.1 & 10)", scaleFactor, 4);
        gd.addCheckbox("use bilinear interpolation", useBilinearInterpolation);
        gd.addCheckbox("show difference between NN and BI", showDifference);
        gd.addCheckbox("show checkerboard (only available with show difference activated)", showCheckerboard);
        gd.showDialog();

        //set user input for scale factor as variable sF
        double sF = gd.getNextNumber();

        //set scale factor to 10 for both, up and down scaling
        if(sF <= 10 && sF >= 0.1) {
            if(!gd.wasCanceled()) {
                scaleFactor = sF;
                useBilinearInterpolation = gd.getNextBoolean();
                showDifference = gd.getNextBoolean();
                showCheckerboard = gd.getNextBoolean();
            } //if

            else {
                return;
            } //else
        } //if

        //if user input exceeds range for scale factor, show text dialog
        else {
            GenericDialog wn = new GenericDialog("scale factor out of range");
            wn.addMessage("scale factor out of range");
            wn.showDialog();
            return;
        } //else

        //calculate and round target size based on the scale factor
        //two different rounding methods:
        double tgtWidth = (int)Math.round(width * scaleFactor); //either this
        double tgtHeight = (int)(height * scaleFactor + 0.5); //or that

        if(showDifference){
            //generate resampled images in NN and BI + show difference between them
            double[][] resampledImageNN = getResampledImage(inDataArrDbl, width, height, (int)tgtWidth, (int)tgtHeight, false);
            double[][] resampledImageBI = getResampledImage(inDataArrDbl, width, height, (int)tgtWidth, (int)tgtHeight, true);
            double[][] difference = getDifference(resampledImageNN, resampledImageBI, (int)tgtWidth, (int)tgtHeight);

            //show images
            ImageJUtility.showNewImage(resampledImageNN, (int)tgtWidth, (int)tgtHeight, "NN resized with factor " + scaleFactor);
            ImageJUtility.showNewImage(resampledImageBI, (int)tgtWidth, (int)tgtHeight, "BI resized with factor " + scaleFactor);
            ImageJUtility.showNewImage(difference, (int)tgtWidth, (int)tgtHeight, "difference");

            if(showCheckerboard){
                //generate checkerboard image with nearest neighbor in quadrant 1 and 4
                double[][] checkerboard = getCheckerboard(resampledImageNN, resampledImageBI, (int)tgtWidth, (int)tgtHeight);

                //show image
                ImageJUtility.showNewImage(checkerboard, (int)tgtWidth, (int)tgtHeight, "checkerboard");
            }
        } //if

        else {
            //write resampled image into array
            double[][] resampledImage = getResampledImage(inDataArrDbl, width, height, (int) tgtWidth, (int) tgtHeight, useBilinearInterpolation);

            //show image
            if(useBilinearInterpolation) {
                ImageJUtility.showNewImage(resampledImage, (int) tgtWidth, (int) tgtHeight, "BI resized with factor " + scaleFactor);
            } //if
            else {
                ImageJUtility.showNewImage(resampledImage, (int) tgtWidth, (int) tgtHeight, "NN resized with factor " + scaleFactor);
            } //else
        } //else
    } //run

    void showAbout() {
        IJ.showMessage("About Resample_...",
                "this is a PluginFilter to resize input images\n");
    } //showAbout

} //class Resample_