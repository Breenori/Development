import ij.*;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

public class Rescale_ implements PlugInFilter {

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

        //scale factor limits
        double maxScale = 10.0;
        double minScale = 0.1;
        int tgtWidth = width;
        int tgtHeight = height;
        boolean bilinearCb = false;

        //instead of asking for a scale, ask for 2 values width and height
        GenericDialog gd = new GenericDialog("enter scale fro resampling");
        gd.addNumericField("width = ", tgtWidth, 2);
        gd.addNumericField("height = ", tgtHeight, 2);
		// added a checkbox to switch between NN and bilinear interpolation
        gd.addCheckbox("Bilinear ",false);

        gd.showDialog();
        if(!gd.wasCanceled()) {
			// fetch numbers from dialog
            tgtWidth = (int)gd.getNextNumber();
            tgtHeight = (int)gd.getNextNumber();
            bilinearCb = gd.getNextBoolean();
        } //if

        //range check
        if(tgtWidth < minScale*width || tgtWidth > maxScale*width || tgtHeight < minScale*height || tgtHeight > maxScale*width) {
            return; //invalid scale
        }

        int[][] returnImg = Utility.rescaleImage(inDataArrInt,width,height,tgtWidth,tgtHeight,bilinearCb);

        ImageJUtility.showNewImage(returnImg, tgtWidth, tgtHeight, "image rescaled to width = " + tgtWidth + " and height = " + tgtHeight);
    } //run

    void showAbout() {
        IJ.showMessage("About Rescale_...",
                "this is a PluginFilter to rescale input image to the dimensions provided \n");
    } //showAbout

} //class Resample_

