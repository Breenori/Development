import ij.*;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

public class BinaryIntervalThresh_ implements PlugInFilter {

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

        int lowerThresh = 80;
        int upperThresh = 140;

        GenericDialog gd = new GenericDialog("binary interval thresh");
        gd.addSlider("Tlow=", 0, 255, lowerThresh);
        gd.addSlider("Tup=", 0, 255, upperThresh);
        gd.showDialog();

        if(!gd.wasCanceled()){
            lowerThresh = (int)gd.getNextNumber();
            upperThresh = (int)gd.getNextNumber();
        }

        // transfer function array
        int[] binaryThreshTF = ImageTransformationFilter.getBinaryIntervalThresh(255,lowerThresh,upperThresh);

        //apply transformation (transfer function)
        int[][] returnImg = ImageTransformationFilter.getTransformedImage(inDataArrInt, width, height,binaryThreshTF);

        // finally, visualize the image
        ImageJUtility.showNewImage(returnImg, width, height, "segmentation, Thresh = ["+lowerThresh+";"+upperThresh+"]");

    } //run

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is a PluginFilter template\n");
    } //showAbout

} //class FilterTemplate_

