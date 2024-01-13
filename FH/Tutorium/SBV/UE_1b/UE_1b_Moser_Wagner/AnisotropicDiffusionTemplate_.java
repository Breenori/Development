import ij.*;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;
import ij.gui.GenericDialog;

public class AnisotropicDiffusionTemplate_ implements PlugInFilter {

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
        int convMaskRadius = 1;
        double kappa = 100.0;
        int diffFunctOption = 1; //mode 1 or mode 2
        double normFactor;

        GenericDialog gd = new GenericDialog("anisotrope diffusion filter config");
        gd.addNumericField("numberOfIterations", numOfIterations, 0);
        gd.addNumericField("kappa", kappa, 0);
        gd.addNumericField("diffFuctionOption: 1 or 2", diffFunctOption, 0);

        gd.showDialog();
        if (!gd.wasCanceled()) {
            numOfIterations = (int) gd.getNextNumber();
            kappa = (int) gd.getNextNumber();
            diffFunctOption = (int) gd.getNextNumber();
        }

        //Center pixel distances ==> to ensure lower weight for diagonal neighbours
        double direct = 1.0;
        double diagonal = Math.sqrt(2.0);

        double weightD = direct;
        double weightDD = 1 / diagonal;
        normFactor = 1 / (4 * direct + 4 * diagonal);

        // all directions
        double[][] hNW = new double[][]{{1.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hN = new double[][]{{0.0, 1.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hNE = new double[][]{{0.0, 0.0, 1.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};

        double[][] hW = new double[][]{{0.0, 0.0, 0.0}, {1.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hE = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 1.0}, {0.0, 0.0, 0.0}};

        double[][] hSW = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {1.0, 0.0, 0.0}};
        double[][] hS = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 1.0, 0.0}};
        double[][] hSE = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}};

        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        double[][] outImg = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        //now do some iterations
        for (int iter = 0; iter < numOfIterations; iter++) {
            //do convolutions in all directions; nabla == gradient symbol (triangle with top-down);
            double[][] nablaNW = ConvolutionFilter.convolveDouble(outImg, width, height, hNW, convMaskRadius); //gradient compass
            double[][] nablaN = ConvolutionFilter.convolveDouble(outImg, width, height, hN, convMaskRadius);
            double[][] nablaNE = ConvolutionFilter.convolveDouble(outImg, width, height, hNE, convMaskRadius);

            double[][] nablaW = ConvolutionFilter.convolveDouble(outImg, width, height, hW, convMaskRadius);
            double[][] nablaE = ConvolutionFilter.convolveDouble(outImg, width, height, hE, convMaskRadius);

            double[][] nablaSW = ConvolutionFilter.convolveDouble(outImg, width, height, hSW, convMaskRadius);
            double[][] nablaS = ConvolutionFilter.convolveDouble(outImg, width, height, hS, convMaskRadius);
            double[][] nablaSE = ConvolutionFilter.convolveDouble(outImg, width, height, hSE, convMaskRadius);

            /*
            ImageJUtility.showNewImage(nablaNW, width, height, "nablaNW");
            ImageJUtility.showNewImage(nablaN, width, height, "nablaN");
            ImageJUtility.showNewImage(nablaNE, width, height, "nablaNE");

            ImageJUtility.showNewImage(nablaW, width, height, "nablaW");
            ImageJUtility.showNewImage(nablaNE, width, height, "nablaE");

            ImageJUtility.showNewImage(nablaSW, width, height, "nablaSW");
            ImageJUtility.showNewImage(nablaS, width, height, "nablaS");
            ImageJUtility.showNewImage(nablaSE, width, height, "nablaSE");
            */

            //coefficient from gradient derived as
            //   (a)  cN = exp(-(-nablaN[x_i][y_i]/kappa)^2)  MODE 1
            // OR more precisely
            //    (b) cN = 1.0/(1.0 + (nablaN[x_i][y_i]/kappa)^2) MODE 2
            double[][] cNW = new double[width][height];
            double[][] cN = new double[width][height];
            double[][] cNE = new double[width][height];

            double[][] cW = new double[width][height];
            double[][] cE = new double[width][height];

            double[][] cSW = new double[width][height];
            double[][] cS = new double[width][height];
            double[][] cSE = new double[width][height];

            //diffuse
            if (diffFunctOption == 1) { //MODE 1
                for (int x = 0; x < width; x++) {
                    for (int y = 0; y < height; y++) {

                        cNW[x][y] = Math.exp(-(Math.pow((-nablaN[x][y] / kappa), 2))); //diff constant
                        cN[x][y] = Math.exp(-(Math.pow((-nablaN[x][y] / kappa), 2))); //diff constant
                        cNE[x][y] = Math.exp(-(Math.pow((-nablaNE[x][y] / kappa), 2))); //diff constant
                        cW[x][y] = Math.exp(-(Math.pow((-nablaW[x][y] / kappa), 2))); //diff constant
                        cE[x][y] = Math.exp(-(Math.pow((-nablaE[x][y] / kappa), 2))); //diff constant
                        cSW[x][y] = Math.exp(-(Math.pow((-nablaSW[x][y] / kappa), 2))); //diff constant
                        cS[x][y] = Math.exp(-(Math.pow((-nablaS[x][y] / kappa), 2))); //diff constant
                        cSE[x][y] = Math.exp(-(Math.pow((-nablaSE[x][y] / kappa), 2))); //diff constant
                    }
                }
            } else if (diffFunctOption == 2) { //MODE 2
                for (int x = 0; x < width; x++) {
                    for (int y = 0; y < height; y++) {
                        cNW[x][y] = 1.0 / (1.0 + (Math.pow((nablaNW[x][y] / kappa), 2))); //diff constant
                        cN[x][y] = 1.0 / (1.0 + (Math.pow((nablaN[x][y] / kappa), 2))); //diff constant
                        cNE[x][y] = 1.0 / (1.0 + (Math.pow((nablaNE[x][y] / kappa), 2))); //diff constant
                        cW[x][y] = 1.0 / (1.0 + (Math.pow((nablaW[x][y] / kappa), 2))); //diff constant
                        cE[x][y] = 1.0 / (1.0 + (Math.pow((nablaE[x][y] / kappa), 2))); //diff constant
                        cSW[x][y] = 1.0 / (1.0 + (Math.pow((nablaSW[x][y] / kappa), 2))); //diff constant
                        cS[x][y] = 1.0 / (1.0 + (Math.pow((nablaS[x][y] / kappa), 2))); //diff constant
                        cSE[x][y] = 1.0 / (1.0 + (Math.pow((nablaSE[x][y] / kappa), 2))); //diff constant
                    }
                }
            }

            double[][] skaled = new double[width][height];

            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    skaled[x][y] = cNW[x][y] * 255;
                }
            }

            ImageJUtility.showNewImage(skaled, width, height, "cNW");

            //now finally diffuse all pixels: aggregate weighted Cn * nablaN, aso.
            //outImg[x_i][y_i] = outImg[x_i][y_i] + normFactor * (weightN * cN[x_i][y_i] * nablaN[x_i][y_i] + weightS * ....)
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    outImg[x][y] = outImg[x][y] + normFactor *
                            (weightD * cN[x][y] * nablaN[x][y] + weightD * cS[x][y] * nablaS[x][y] +
                                    weightDD * cNE[x][y] * nablaNE[x][y] + weightDD * cSW[x][y] * nablaSW[x][y] +
                                    weightDD * cNW[x][y] * nablaNW[x][y] + weightDD * cSE[x][y] * nablaSE[x][y] +
                                    weightD * cW[x][y] * nablaW[x][y] + weightD * cE[x][y] * nablaE[x][y]);//update
                }
            }
        }
        ImageJUtility.showNewImage(outImg, width, height, "anisotropic diffusion");


    } //run

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is a anisotropic diffusion template\n");
    } //showAbout
} //class AnisotropicDiffusionTemplate_
