import ij.*;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

public class GaussFilter_ implements PlugInFilter {

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

        int radius = 0;
        GenericDialog gd = new GenericDialog("Gaussian blur");
        gd.addNumericField("radius=",2);

        gd.showDialog();
        if(!gd.wasCanceled()) {
            radius = (int)gd.getNextNumber();
        }

        // get the kernel
        double[][] kernel = getGaussKernel(radius);
        // delegate to convolveDouble using the kernel
        double[][] resultImg = ConvolutionFilter.convolveDouble(inDataArrDbl, width, height,kernel,radius);

        ImageJUtility.showNewImage(resultImg,width,height,"Gauss filtered image, radius="+radius);
    } //run

    private double[][] getGaussKernel(int radius) {
        double[][] kernel = new double[1+2*radius][1+2*radius];
        // Calculate gauss relevant values
        double sigma = (float)(2*radius/3);
        double fixedPart = 1/(2 * Math.PI * Math.pow(sigma,2));
        double sum = 0;
        double max = 0;

        // calculate filtermask
        for(int x=radius*-1; x<=radius; x++)
        {
            for(int y=radius*-1; y<=radius; y++)
            {
                // calculate value with given formula for each value and sum them up
                double pixelValue = fixedPart * Math.pow(Math.E,-1*(Math.pow(x,2)+Math.pow(y,2))/(2*Math.pow(sigma,2)));
                kernel[x+radius][y+radius] = pixelValue;
                sum += pixelValue;

                // determine the maximum value, to normalize the output image of the mask later
                if(Math.abs(pixelValue) > max) {
                    max = pixelValue;
                }
            }
        }

        double scaleGaussImg = 255 / max;

        double[][] kernelImg = new double[1+2*radius][1+2*radius];
        for(int x=radius*-1; x<=radius; x++)
        {
            for(int y=radius*-1; y<=radius; y++)
            {
                // normalize the image to 0-255 and the kernel values to get a sum of 1.
                kernelImg[x+radius][y+radius] = kernel[x+radius][y+radius] * scaleGaussImg;
                kernel[x+radius][y+radius] /= sum;
            }
        }
        // show the visualized mask
        ImageJUtility.showNewImage(kernelImg,1+2*radius,1+2*radius,"Gauss Kernel, radius="+radius);

        return kernel;
    }

    void showAbout() {
        IJ.showMessage("About GaussFilter_...",
                "this is a filter implementing Gaussian blur.\n");
    } //showAbout

} //class FilterTemplate_

