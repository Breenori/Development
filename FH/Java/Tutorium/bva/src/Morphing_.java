import ij.*;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

import java.awt.*;
//import ImageJUtility;
//import ImageTransformationFilter;
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

        //TODO //load from File path or utilizing a dialogue (see ImageCalculator)
        ImagePlus inImg2 = IJ.openImage();
        int[][] secondImg = inImg2.getProcessor().getIntArray();        // convert the input image into a "inDataArrInt2"

        //TODO: check if both images of same size



        double alphaMinVal = 0.0;
        double alphaMaxVal = 1.0;
        double alphaVal = 0.5; //start value

        GenericDialog gd = new GenericDialog("Morphing");
        gd.addDialogListener(new MorphingListener(inDataArrInt1, secondImg, width, height, ip, imagePlus));
        gd.addSlider("alpha val", alphaMinVal, alphaMaxVal, alphaVal);
        gd.showDialog();
        if(gd.wasCanceled()) {
            return;
        } //if

        alphaVal = gd.getNextNumber();

        int[][] morphedImgArr = ImageTransformationFilter_.MorphImages(inDataArrInt1, secondImg, width, height, alphaVal);

        ImageJUtility.showNewImage(morphedImgArr, width, height, "morphed image at alpha = " + alphaVal);
    } //run



    void showAbout() {
        IJ.showMessage("About Morphing_...",
                "this is a plugin to morph 2 images\n");
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

            int[][] morphedImgArr = ImageTransformationFilter_.MorphImages(inDataArrInt1, inDataArrInt2, width, height, alphaVal);
            byte[] pixels = ImageJUtility.convertFrom2DIntArr(morphedImgArr, width, height);
            ip.reset();
            ip.setPixels(pixels);
            imp.setProcessor(ip);
            genDialog.repaint();

            return true;
        }

    }


} //class Morphing_



