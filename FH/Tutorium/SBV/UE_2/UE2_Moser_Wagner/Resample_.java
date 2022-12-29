import ij.*;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

public class Resample_ implements PlugInFilter {

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about"))
        {showAbout(); return DONE;}
        return DOES_8G+DOES_STACKS+SUPPORTS_MASKING;
    } //setup

    double[][] getResampledImage(double[][] inImg, int width, int height, int tgtWidth, int tgtHeight, boolean useBilinear){
        double[][] returnImg = new double[tgtWidth][tgtHeight];
        // this is strategy A
        double scaleFactorW = (double) tgtWidth  / width;
        double scaleFactorH = (double) tgtHeight / height;

        // get all resulting pixels in B from any position in A, from B ==> A, Backward mapping
        for (int x = 0; x < tgtWidth; x++){
            for (int y = 0; y < tgtHeight; y++){
                // example pos I(2, 3) with scaleFactor 4.0 ==> I'(8,12)
                double posX = Math.round((x / scaleFactorW) * 10.0) / 10.0;
                double posY = Math.round((y / scaleFactorH) * 10.0) / 10.0;

                if(useBilinear){
                    returnImg[x][y] = getBilinearInterpolateValue(inImg, width, height, posX, posY);
                } else {
                    returnImg[x][y] = getNNInterpolatedValue(inImg, width, height, posX, posY);
                }
            }
        }

        // this is strategy B
        /*
        double scaleFactorW = (tgtWidth - 1.0)  / (width -1.0);
        double scaleFactorH = (tgtHeight -1.0) / (height -1.0);

        for (int x = 0; x < width; x++){
            for (int y = 0; y < height; y++){
                // example pos I(2, 3) with scaleFactor 4.0 ==> I'(8,12)
                int posX = (int) Math.round(x * scaleFactorW);
                int posY = (int) Math.round(y * scaleFactorH);

                if(useBilinear){
                    returnImg[posX][posY] = getBilinearInterpolateValue(inImg, width, height, x, y);
                } else {
                    returnImg[posX][posY] = getNNInterpolatedValue(inImg, width, height, x, y);
                }
            }
        }
        */

        return returnImg;
    }

    public double getNNInterpolatedValue(double[][] inImg, int width, int height, double posX, double posY){
        // e.g. get value of inImg at position (posX, posY)(2.2, 3.7) ==> inImg[2][4]
        int posXint = (int) Math.round(posX);
        int posYint = (int) Math.round(posY);

        //Let's check the range
        if(posXint < 0){
            posXint = 0;
        }
        if(posYint < 0){
            posYint = 0;
        }
        if (posXint >= width){
            posXint = width-1;
        }
        if (posYint >= height){
            posYint = height -1;
        }
        return inImg[posXint][posYint];
    }

    public double getBilinearInterpolateValue(double[][] inImg, int width, int height, double posX, double posY){
        double result;
        int posXA = (int) posX;
        int posYA = (int) posY;

        int posXB = (int) posX + 1;
        int posYB = (int) posY + 1;

        if(posXA < 0){
            posXA = 0;
        }
        if(posYA < 0){
            posYA = 0;
        }
        if (posXA >= width){
            posXA = width-1;
        }
        if (posYA >= height){
            posYA = height -1;
        }

        if(posXB < 0){
            posXB = 0;
        }
        if(posYB < 0){
            posYB = 0;
        }
        if (posXB >= width){
            posXB = width-1;
        }
        if (posYB >= height){
            posYB = height -1;
        }

        double resultA = (((inImg[posXB][posYA] - inImg[posXA][posYA]) / 100) * Math.round((posX % 1) * 100)) +  inImg[posXA][posYA];

        double resultB = (((inImg[posXB][posYB] - inImg[posXA][posYB]) / 100) * Math.round((posX % 1) * 100)) +  inImg[posXA][posYB];

        result = (((resultB - resultA) / 100) * Math.round((posY % 1) * 100)) + resultA;

        return Math.round(result);
    }

    double[][] differencePicture(double[][] NN, double[][] BI, int tgtWidth, int tgtHeight){

        double[][] result = new double[tgtWidth][tgtHeight];

        for (int x = 0; x < tgtWidth; x++) {
            for (int y = 0; y < tgtHeight; y++) {

                result[x][y] = Math.abs(NN[x][y] - BI[x][y]);
            }
        }
        return result;
    }


    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[])ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();
        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        double[][] inDataDbl = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        double scaleFactor = 2.11;
        double min = 0.0;
        double max = 10.0;

        GenericDialog gd = new GenericDialog("resample");
        gd.addSlider("scaleFactor", min, max, scaleFactor,0.01);
        gd.showDialog();
        if(!gd.wasCanceled()){
            scaleFactor = gd.getNextNumber();
        }

        int tgtWidth = (int) Math.round(width * scaleFactor);
        int tgtHeight = (int) Math.round(height * scaleFactor);

        double[][]  resampledImgNN = getResampledImage(inDataDbl, width, height, tgtWidth, tgtHeight, false);
        double[][]  resampledImgBilinear = getResampledImage(inDataDbl, width, height, tgtWidth, tgtHeight, true);

        double[][] diff = differencePicture(resampledImgNN, resampledImgBilinear, tgtWidth, tgtHeight);

        double[][] checkerboard = ImageTransformationFilter.checkerboard(resampledImgNN, resampledImgBilinear, tgtWidth, tgtHeight);

        ImageJUtility.showNewImage(resampledImgNN, tgtWidth, tgtHeight, "resized with factor " + scaleFactor + " NN");
        ImageJUtility.showNewImage(resampledImgBilinear, tgtWidth, tgtHeight, "resized with factor " + scaleFactor + " Bilinear");

        ImageJUtility.showNewImage(checkerboard, tgtWidth, tgtHeight, "checkerboard NN and bilinear Interpolation");
        ImageJUtility.showNewImage(diff, tgtWidth, tgtHeight, "difference picture");
    } //run

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is a PluginFilter to resize input images\n");
    } //showAbout

} //class FilterTemplate_

