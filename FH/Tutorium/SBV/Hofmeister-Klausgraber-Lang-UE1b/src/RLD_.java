import ij.IJ;
import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

import java.util.Random;

public class RLD_ implements PlugInFilter {

    private double[][] image;

    public double[][] getImage() {
        return this.image;
    }

    public void setImage(double[][] image) {
        this.image = image;
    }

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about"))
        {showAbout(); return DONE;}
        return DOES_8G+DOES_STACKS+SUPPORTS_MASKING;  // DOES_8G for greyscale pictures and DOES_RGB for colored pictures
    } //setup

    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[])ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();
        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        double[][] inDataArrayDbl = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        int radius = 3;
        int iterations = 5;
        GenericDialog gd = new GenericDialog("mean filter config");
        gd.addNumericField("Iterations", iterations, 0);
        gd.addNumericField("Radius", radius, 0);
        gd.showDialog();
        if (!gd.wasCanceled()) {
            iterations = (int) gd.getNextNumber();
            radius = (int) gd.getNextNumber();

        }
        double[][] meanKernel = ConvolutionFilter.getMeanMask(radius);
        double[][] gaussianKernel = {{0.05, 0.1, 0.05}, {0.1, 0.4, 0.1}, {0.05, 0.1, 0.05}};
        double[][] estimatedImg = RDL(inDataArrayDbl, meanKernel, width, height, radius, iterations);
        ImageJUtility.showNewImage(estimatedImg, width, height,
                "RLD, iterations=" + iterations + ", radius=" + radius);
    } //run

    private double[][] RDL(double[][] original, double[][] kernel, int width, int height, int radius, int iterations) {
        double[][] guess = new double[width][height];
        boolean guessIsAnImage = true;

        if (guessIsAnImage) {
            // import lena as guess
            ImagePlus imp = new ImagePlus("C:\\OneDrive\\HCC 1. Semester\\SBV\\Projects\\lena-8bit.png");
            ImageProcessor ip = imp.getProcessor();
            byte[] pixels = (byte[])ip.getPixels();
            int widthGuess = ip.getWidth();
            int heightGuess = ip.getHeight();
            int[][] inDataArrIn = ImageJUtility.convertFrom1DByteArr(pixels, widthGuess, heightGuess);
            double[][] inDataArrayDbl = ImageJUtility.convertToDoubleArr2D(inDataArrIn, widthGuess, heightGuess);
            guess = inDataArrayDbl;
        } else {
            Random random  = new Random();
            // create grey image as guess
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    guess[i][j] = 128.0; // monotone
                    // guess[i][j] = random.nextDouble() % 255 + 1; // Random Values
                    // guess[i][j] = original[i][j]; // Original
                }
            }
        }
        //ImageJUtility.showNewImage(guess, width, height, "initial guess image");

        double[][] mt = new double[width][height];
        for (int iter = 0; iter < iterations; iter++) {
            // init - c^t = h * g^t
            double[][] ct = ConvolutionFilter.convolveDoubleNorm(guess, width, height, kernel, radius);
            // start new iteration
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    // prevent division by zero
                    double divisor = ct[i][j] == 0.0 ? 0.0001 : ct[i][j];
                    // calculate the quotient between original and new guess
                    mt[i][j] = original[i][j] / divisor;
                }
            }
            // update guess for next iteration: g^(t+1) = g^t . (m^t * h)
            double[][] mth = ConvolutionFilter.convolveDoubleNorm(mt, width, height, kernel, radius);
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    double res = guess[i][j] * mth[i][j];
                    // correct black artefacts caused by value overrun
                    if (res > 255.0) {
                        // System.out.println("x=" + i + " y=" + j + " val=" + res);
                        guess[i][j] = 255.0;
                    } else {
                        guess[i][j] = guess[i][j] * mth[i][j];
                    }
                }
            }
        }
        return guess;
    }

    void showAbout() {
        IJ.showMessage("Richardson-Lucy Deconvolution...",
                "this is a PluginFilter to sharpen a blurred image\n");
    } //showAbout

} //class RLD_

