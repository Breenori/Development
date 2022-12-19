import ij.IJ;
import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

import java.util.Random;

public class RLD_ implements PlugInFilter {

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about")) {
            showAbout();
            return DONE;
        }
        return DOES_8G + DOES_STACKS + SUPPORTS_MASKING;
    } //setup

    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[]) ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();

        int numOfIterations = 5;
        int radius = 1;

        GenericDialog gd = new GenericDialog("RDL deconvolution config");
        gd.addNumericField("numberOfIterations", numOfIterations, 0);

        gd.showDialog();
        if (!gd.wasCanceled()) {
            numOfIterations = (int) gd.getNextNumber();

        }

        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        double[][] initialImg = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        double[][] meanKernel = ConvolutionFilter.getMeanMask(radius);
        double[][] resultImg = RDL(initialImg, meanKernel, width, height, radius, numOfIterations);

        ImageJUtility.showNewImage(resultImg, width, height, "Richardson-Lucy Deconvolution");
    } //run

    private double[][] RDL(double[][] original, double[][] kernel, int width, int height, int radius, int iterations) {
        double[][] guess = monoImage(width, height, 0);
        //monoImage(width, height, 127);
        //randomImage(width, height);<
        //inputImage();
        //initialImage(original, width, height, kernel, radius);

        double[][] ct;
        double[][] mt = new double[width][height];
        double[][] help;

        for (int iter = 0; iter < iterations; iter++) {

            ct = ConvolutionFilter.convolveDoubleNorm(guess, width, height, kernel, radius);

            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    mt[x][y] = (original[x][y] +1) / (ct[x][y] + 1);
                    System.out.println(mt[x][y] + " = " + (original[x][y] + 1) + " / " + (ct[x][y] + 1));
                }
            }
            help = ConvolutionFilter.convolveDoubleNorm(mt, width, height, kernel, radius);
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    guess[x][y] = (guess[x][y] + 1) * help[x][y];
                    System.out.println(guess[x][y] + " = " + guess[x][y] + " * " + help[x][y]);
                }
            }
        }
        return guess;
    }

    private double[][] monoImage(int width, int height, int value) {
        double[][] monoImage = new double[width][height];
        for (int i = 0; i < width; i++) {
            for (int y = 0; y < height; y++) {
                monoImage[i][y] = value;
            }
        }
        return monoImage;
    }

    private double[][] randomImage(int width, int height) {
        double[][] randomImage = new double[width][height];
        Random rn = new Random();

        for (int i = 0; i < width; i++) {
            for (int y = 0; y < height; y++) {
                randomImage[i][y] = rn.nextInt(255);
            }
        }
        return randomImage;
    }

    private double[][] inputImage() {
        ImagePlus imp = new ImagePlus("C:\\Users\\carol\\Documents\\Master\\SignalBildverarbeitung\\UE_1b\\1.8\\clown.png");
        ImageProcessor ipL = imp.getProcessor();
        byte[] pixels = (byte[]) ipL.getPixels();
        int width = ipL.getWidth();
        int height = ipL.getHeight();

        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        double[][] lenaImg = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        return lenaImg;
    }

    private double[][] initialImage(double[][] original, int width, int height, double[][] kernel, int radius) {
        double[][] result = ConvolutionFilter.convolveDoubleNorm(original, width, height, kernel, radius);
        return result;
    }

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is the RLD template\n");
    } //showAbout
} //class AnisotropicDiffusionTemplate_
