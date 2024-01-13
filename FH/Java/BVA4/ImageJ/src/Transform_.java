import ij.*;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

public class Transform_ implements PlugInFilter {

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about"))
        {showAbout(); return DONE;}
        return DOES_8G+DOES_STACKS+SUPPORTS_MASKING;
    } //setup


    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[])ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();
        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);

        double transX = 9.721;
        double transY = -30.0;
        double rotAngle = 21.1111;

        int[][] resultImg = getTransformedImage(inDataArrInt, width, height, transX, transY, rotAngle);

        ImageJUtility.showNewImage(resultImg,width,height,"Transformed image, Tx="+transX+", Ty="+transY+", rot="+rotAngle);
    } //run

    public static int[][] getTransformedImage(int[][] inImg, int width, int height, double transX, double transY, double rotAngle) {
        int[][] retImg = new int[width][height];

        double cosVal = Math.cos(-rotAngle * Math.PI / 180.0);
        double sinVal = Math.sin(-rotAngle * Math.PI / 180.0);

        double widthHalf = width/2;
        double heightHalf = height/2;

        // use backward mapping -- iterate over all pixels of result image
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                double xPos = x;
                double yPos = y;

                // step 1) center image
                xPos -= widthHalf;
                yPos -= heightHalf;

                // step 2) rotation
                double rotatedX = xPos * cosVal + yPos * sinVal;
                double rotatedY = xPos * -sinVal + yPos * cosVal;
                xPos = rotatedX;
                yPos = rotatedY;

                // step 3) translation
                xPos -= transX;
                yPos -= transY;

                // step 4) revert to old origin/center
                xPos += widthHalf;
                yPos += heightHalf;

                // step 5) get NN-interpolated value
                int resVal = Utility.getNNinterpolation(inImg,width,height,xPos,yPos);
                retImg[x][y] = resVal;
            }
        }

        return retImg;
    }

    public static float[][] getTransformedImageF(float[][] inImg, int width, int height, double transX, double transY, double rotAngle) {
        float[][] retImg = new float[width][height];

        double cosVal = Math.cos(-rotAngle * Math.PI / 180.0);
        double sinVal = Math.sin(-rotAngle * Math.PI / 180.0);

        double widthHalf = width/2;
        double heightHalf = height/2;

        // use backward mapping -- iterate over all pixels of result image
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                double xPos = x;
                double yPos = y;

                // step 1) center image
                xPos -= widthHalf;
                yPos -= heightHalf;

                // step 2) rotation
                double rotatedX = xPos * cosVal + yPos * sinVal;
                double rotatedY = xPos * -sinVal + yPos * cosVal;
                xPos = rotatedX;
                yPos = rotatedY;

                // step 3) translation
                xPos -= transX;
                yPos -= transY;

                // step 4) revert to old origin/center
                xPos += widthHalf;
                yPos += heightHalf;

                // step 5) get Bilinear-interpolated value
                float resVal = Utility.getBilinearInterpolationF(inImg,width,height,xPos,yPos);
                retImg[x][y] = resVal;
            }
        }

        return retImg;
    }

    void showAbout() {
        IJ.showMessage("About Transform_...",
                "this Plugin allows the transformation of images. (translation and rotation)\n");
    } //showAbout

} //class FilterTemplate_

