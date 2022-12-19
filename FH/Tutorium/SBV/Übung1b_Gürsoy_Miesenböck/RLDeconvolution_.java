import ij.IJ;
import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

public class RLDeconvolution_ implements PlugInFilter {

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
        double[][] inDataArrDbl = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        // get filter kernel for convolution
        int tgtRadius = 2;    //5x5 ==> 25 Elements --> size always 2x Radius + 1
        int iterations = 5;

        //let the user enter the parameters
        GenericDialog gd = new GenericDialog("mean filter config");
        gd.addNumericField("radius", tgtRadius, 0);
        gd.addNumericField("iterations", iterations, 0);

        gd.showDialog();
        if (!gd.wasCanceled()) {
            tgtRadius = (int) gd.getNextNumber();
            iterations = (int) gd.getNextNumber();
        }

        double[][] meanKernel = ConvolutionFilter.getMeanMask(tgtRadius);

        //apply the filter kernel
        double[][] resultImg = ConvolutionFilter.RLD(inDataArrDbl, meanKernel, width, height, tgtRadius, iterations);


        // finally show the result image
        ImageJUtility.showNewImage(resultImg, width, height, "RL Deconvolution Filter");



    } //run

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is a RLD template\n");
    } //showAbout


}