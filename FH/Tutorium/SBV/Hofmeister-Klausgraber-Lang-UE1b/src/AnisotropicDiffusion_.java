import ij.*;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

public class AnisotropicDiffusion_ implements PlugInFilter {

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

        // let the user enter the parameters
        int n = 5;
        double kappa = 5.0;
        GenericDialog gd = new GenericDialog("mean filter config");
        gd.addNumericField("Iterations", n, 0);
        gd.addNumericField("Kappa", kappa, 0);
        gd.showDialog();
        if (!gd.wasCanceled()) {
            n = (int) gd.getNextNumber();
            kappa = gd.getNextNumber();
        }

        if (kappa == 0) kappa = 0.000001; // prevent division by zero
        int radius = 1;

//        double[][] hN   = new double[][]{{0.0, 1.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
//        double[][] hNW  = new double[][]{{1.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
//        double[][] hW   = new double[][]{{0.0, 0.0, 0.0}, {1.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
//        double[][] hSW  = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {1.0, 0.0, 0.0}};
//        double[][] hS   = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 1.0, 0.0}};
//        double[][] hSE  = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}};
//        double[][] hE   = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 1.0}, {0.0, 0.0, 0.0}};
//        double[][] hNE  = new double[][]{{0.0, 0.0, 1.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};

        // rotated arrays for column major order
        double[][] hN   = new double[][]{{0.0, 0.0, 0.0}, {1.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hNW  = new double[][]{{1.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hW   = new double[][]{{0.0, 1.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hSW  = new double[][]{{0.0, 0.0, 1.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hS   = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 1.0}, {0.0, 0.0, 0.0}};
        double[][] hSE  = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}};
        double[][] hE   = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 1.0, 0.0}};
        double[][] hNE  = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {1.0, 0.0, 0.0}};

        for (int iter = 0; iter < n; iter++) {
            // convolution for each compass gradient
            double[][] nablaN   = ConvolutionFilter.convolveDouble(inDataArrayDbl, width, height, hN, radius);
            double[][] nablaNW  = ConvolutionFilter.convolveDouble(inDataArrayDbl, width, height, hNW, radius);
            double[][] nablaW   = ConvolutionFilter.convolveDouble(inDataArrayDbl, width, height, hW, radius);
            double[][] nablaSW  = ConvolutionFilter.convolveDouble(inDataArrayDbl, width, height, hSW, radius);
            double[][] nablaS   = ConvolutionFilter.convolveDouble(inDataArrayDbl, width, height, hS, radius);
            double[][] nablaSE  = ConvolutionFilter.convolveDouble(inDataArrayDbl, width, height, hSE, radius);
            double[][] nablaE   = ConvolutionFilter.convolveDouble(inDataArrayDbl, width, height, hE, radius);
            double[][] nablaNE  = ConvolutionFilter.convolveDouble(inDataArrayDbl, width, height, hNE, radius);

//            ImageJUtility.showNewImage(nablaN, width, height, "N");
//            ImageJUtility.showNewImage(nablaNW, width, height, "NW");
//            ImageJUtility.showNewImage(nablaW, width, height, "W");
//            ImageJUtility.showNewImage(nablaSW, width, height, "SW");
//            ImageJUtility.showNewImage(nablaS, width, height, "S");
//            ImageJUtility.showNewImage(nablaSE, width, height, "SE");
//            ImageJUtility.showNewImage(nablaE, width, height, "E");
//            ImageJUtility.showNewImage(nablaNE, width, height, "NE");

            double[][] cN   = new double[width][height];
            double[][] cNW  = new double[width][height];
            double[][] cW   = new double[width][height];
            double[][] cSW  = new double[width][height];
            double[][] cS   = new double[width][height];
            double[][] cSE  = new double[width][height];
            double[][] cE   = new double[width][height];
            double[][] cNE  = new double[width][height];
            // Calculation from slide 33 Anisotropic Diffusion V
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    cN[x][y] = Math.exp(-0.5 * (Math.pow((nablaN[x][y] / kappa), 2.0)));
                    cNW[x][y] = Math.exp(-0.5 * (Math.pow((nablaNW[x][y] / kappa), 2.0)));
                    cW[x][y] = Math.exp(-0.5 * (Math.pow((nablaW[x][y] / kappa), 2.0)));
                    cSW[x][y] = Math.exp(-0.5 * (Math.pow((nablaSW[x][y] / kappa), 2.0)));
                    cS[x][y] = Math.exp(-0.5 * (Math.pow((nablaS[x][y] / kappa), 2.0)));
                    cSE[x][y] = Math.exp(-0.5 * (Math.pow((nablaSE[x][y] / kappa), 2.0)));
                    cE[x][y] = Math.exp(-0.5 * (Math.pow((nablaE[x][y] / kappa), 2.0)));
                    cNE[x][y] = Math.exp(-0.5 * (Math.pow((nablaNE[x][y] / kappa), 2.0)));
                }
            }

//            ImageJUtility.showNewImage(cN, width, height, "cN");
//            ImageJUtility.showNewImage(cNW, width, height, "cNW");
//            ImageJUtility.showNewImage(cW, width, height, "cW");
//            ImageJUtility.showNewImage(cSW, width, height, "cSW");
//            ImageJUtility.showNewImage(cS, width, height, "cS");
//            ImageJUtility.showNewImage(cSE, width, height, "cSE");
//            ImageJUtility.showNewImage(cE, width, height, "cE");
//            ImageJUtility.showNewImage(cNE, width, height, "cNE");

            double dw = 1.0 / Math.sqrt(2.0); // diagonal distance weight
            double normFactor = 1.0 / (4 + 4 * dw); // 4 * 1 + 4 * sqrt(2) - sum of distances

            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    double newVal =
                            // old pixel value
                            inDataArrayDbl[x][y] + normFactor * (
                            // straight compass directions north, west, south, east
                            cN[x][y] * nablaN[x][y]
                            + cW[x][y] * nablaW[x][y]
                            + cS[x][y] * nablaS[x][y]
                            + cE[x][y] * nablaE[x][y]
                            // diagonal compass directions north-west, south-west, south-east, north-east
                            // multiplied with diagonal distance weight
                            + dw * cNW[x][y] * nablaNW[x][y]
                            + dw * cSW[x][y] * nablaSW[x][y]
                            + dw * cSE[x][y] * nablaSE[x][y]
                            + dw * cNE[x][y] * nablaNE[x][y]);

                    inDataArrayDbl[x][y] = newVal;
                }
            }
        }
        ImageJUtility.showNewImage(inDataArrayDbl, width, height,
                "anisotropic diffusion, n=" + n + ", kappa=" + kappa);
    } //run

    void showAbout() {
        IJ.showMessage("Anisotropic Diffusion...",
                "this is a PluginFilter smooth the image without losing edges\n");
    } //showAbout

} //class AnisotropicDiffusion_

