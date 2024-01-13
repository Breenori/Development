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


    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[])ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();
        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);

        double maxScale = 10.0;
        double minScale = 0.1;
        double scaleToUse = 2.0;

        GenericDialog gd = new GenericDialog("Resample");
        gd.addNumericField("scale s=", scaleToUse, 2);
        gd.showDialog();

        if(!gd.wasCanceled()) {
            scaleToUse = gd.getNextNumber();
        }

        if(scaleToUse < minScale || scaleToUse > maxScale)
        {
            return; // on invalid scale
        }

        int newWidth = (int)(width * scaleToUse);
        int newHeight = (int)(height * scaleToUse);

        // aquire the result image
        int[][] resultImg = new int[newWidth][newHeight];

        // backward mapping tgt ==> src
        for(int x = 0; x < newWidth; x++)
        {
            for (int y = 0; y < newHeight; y++)
            {
                double posX = x / scaleToUse;
                double posY = y / scaleToUse;
                resultImg[x][y] = getNNInterpolation(inDataArrInt, width, height, posX,posY);
            } // y
        } // x

        // show image
        ImageJUtility.showNewImage(resultImg, newWidth, newHeight, "scaled by s=" +scaleToUse);

    } //run

    int getNNInterpolation(int[][] inImg, int width, int height, double posX, double posY)
    {
        int x = (int) (posX + 0.5);
        int y = (int) (posY + 0.5);

        if(x >= 0 && x < width && y >= 0 && y < height)
        {
            return inImg[x][y];
        }

        return 0;
    }

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is a PluginFilter to resize the input image\n");
    } //showAbout

} //class FilterTemplate_
