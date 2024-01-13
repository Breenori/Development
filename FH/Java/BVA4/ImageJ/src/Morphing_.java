import ij.*;
import ij.plugin.ImageCalculator;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

import java.awt.*;
import java.nio.file.Files;

import ij.gui.DialogListener;
import ij.gui.GenericDialog;


public class Morphing_ implements PlugInFilter {

    ImagePlus imagePlus = null;

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about"))
        {showAbout(); return DONE;}

        imagePlus = imp;

        return DOES_8G+DOES_STACKS+SUPPORTS_MASKING;
    } //setup


    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[])ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();
        int[][] inDataArrInt1 = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        int[][] inDataArrInt2 = null;

        //load from File path or utilizing a dialogue (see ImageCalculator)
        GenericDialog gd1 = new GenericDialog("please pick a second image to morph with");
		// Newest version of imageJ was downloaded to allow use of this function
        gd1.addImageChoice("second image ", ".");

        gd1.showDialog();
        if(gd1.wasCanceled())
        {
            return;
        }

		// Use Dialog to fetch Image, get array and dimensions
        ImagePlus tmpImg = gd1.getNextImage();
        ImageProcessor ip2 = tmpImg.getProcessor();
        int width2 = ip2.getWidth();
        int height2 = ip2.getHeight();
        inDataArrInt2 = ImageJUtility.convertFrom1DByteArr((byte[])ip2.getPixels(),width2, height2);

        //check if both images of same size, if not, set size of image2 to size of image1
        if(width!=width2 || height!=height2) {
            inDataArrInt2 = Utility.rescaleImage(inDataArrInt2,width2,height2,width,height,true);
        }

        double alphaMinVal = 0.0;
        double alphaMaxVal = 1.0;
        double alphaVal = 0.5; //start value

        GenericDialog gd = new GenericDialog("Morphing");

		// allow instantaneous display of the result
        gd.addDialogListener(new MorphingListener(inDataArrInt1, inDataArrInt2, width, height, ip, imagePlus));
        gd.addSlider("alpha val", alphaMinVal, alphaMaxVal, alphaVal);
        gd.showDialog();
        if(gd.wasCanceled()) {
            return;
        } //if

        alphaVal = gd.getNextNumber();

        int[][] morphedImgArr = ImageTransformationFilter.MorphImages(inDataArrInt1, inDataArrInt2, width, height, alphaVal);

        ImageJUtility.showNewImage(morphedImgArr, width, height, "morphed image at alpha = " + alphaVal);
    } //run



    void showAbout() {
        IJ.showMessage("About Morphing_...",
                "morphs two images using the given alpha value.\n");
    } //showAbout

    private class MorphingListener implements DialogListener  {
        int[][] inDataArrInt1;
        int[][] inDataArrInt2;
        ImageProcessor ip;
        ImagePlus imp;
        int width;
        int height;

        public MorphingListener(int[][] inDataArrInt1, int[][] inDataArrInt2, int width, int height, ImageProcessor ip, ImagePlus imp) {
            this.inDataArrInt1= inDataArrInt1;
            this.inDataArrInt2= inDataArrInt2;
            this.width = width;
            this.height = height;
            this.ip = ip;
            this.imp = imp;
        }

        public boolean dialogItemChanged(GenericDialog genDialog, AWTEvent arg1) {
            double alphaVal = genDialog.getNextNumber();

            int[][] morphedImgArr = ImageTransformationFilter.MorphImages(inDataArrInt1, inDataArrInt2, width, height, alphaVal);
            byte[] pixels = ImageJUtility.convertFrom2DIntArr(morphedImgArr, width, height);
            ip.reset();
            ip.setPixels(pixels);
            imp.setProcessor(ip);
            genDialog.repaint();

            return true;
        }

    }


} //class Morphing_



