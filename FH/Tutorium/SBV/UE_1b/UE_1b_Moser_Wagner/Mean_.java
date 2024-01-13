import ij.*;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

public class Mean_ implements PlugInFilter {

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about"))
        {showAbout(); return DONE;}
        return DOES_8G;
    } //setup


    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[])ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();
        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        double[][] inDataArrDouble= ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        // get filter kernel for convolution
        int tgtRadius = 2; // 5x5 ==> 25 (size always 2* radius +1)

        // let the user enter the parameters
        GenericDialog gd = new GenericDialog("mean filter config");
        gd.addNumericField("radius", tgtRadius, 0);
        gd.showDialog();
        if(!gd.wasCanceled()){
            tgtRadius = (int) gd.getNextNumber();
        }

        double[][] meanKernel = ConvolutionFilter.getMeanMask(tgtRadius);

        // apply the filter kernel
        //double[][] resultImg = ConvolutionFilter.convolveDouble(inDataArrDouble, width, height, meanKernel, tgtRadius);
        double[][] resultImg = ConvolutionFilter.convolveDoubleNorm(inDataArrDouble, width, height, meanKernel, tgtRadius);
        // finally show the result image
        ImageJUtility.showNewImage(resultImg, width, height, "mean with kernel r = " + tgtRadius);

    } //run

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is a mean filter\n");
    } //showAbout

}

