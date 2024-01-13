import ij.*;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

public class Mean_ implements PlugInFilter {

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
        double[][] inDataArrDbl = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        int radius = 1;

        GenericDialog gd = new GenericDialog("mean");
        gd.addSlider("radius=",0,20,radius);
        gd.showDialog();

        if(!gd.wasCanceled()) {
            radius = (int)gd.getNextNumber();
        }


        double[][] filterKernel = ConvolutionFilter.getMeanMask(radius);
        double[][] resImg = ConvolutionFilter.convolveDoubleNorm(inDataArrDbl,width,height,filterKernel,radius);


        ImageJUtility.showNewImage(resImg,width,height,"mean, kernel radius r="+radius);
    } //run

    void showAbout() {
        IJ.showMessage("About Mean_...",
                "smoothing filter\n");
    } //showAbout

} //class FilterTemplate_

