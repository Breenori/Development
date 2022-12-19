import ij.*;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

public class RichardsonLucyDeconvolution_ implements PlugInFilter {

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
        double[][] inDataArrDouble = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);
        double[][] guessImg = ConvolutionFilter.GetGuessImage(inDataArrDouble, width, height, 1);

        int radius = 1;
        // get number of iterations and radius
        int iterations = 1;
        GenericDialog gd = new GenericDialog("RLD config");
        gd.addNumericField("Iterations", iterations, 0);
        gd.addNumericField("Radius", radius, 0);
        gd.showDialog();
        if (gd.wasCanceled()) {
            return;
        }
        iterations = (int)gd.getNextNumber();
        radius = (int)gd.getNextNumber();

        // point spread function
        double kernel[][] = ConvolutionFilter.getMeanMask(radius);

        // apply median filter
        double[][] resultImg = ConvolutionFilter.RLD(inDataArrDouble, guessImg, kernel, width, height, radius, iterations);

        // show the result
        ImageJUtility.showNewImage(resultImg, width, height, "RLD edited image");

    } //run

    void showAbout() {
        IJ.showMessage("RLD",
                "this is a PluginFilter RLD\n");
    } //showAbout

} //class RichardsonLucyDeconvolution_

