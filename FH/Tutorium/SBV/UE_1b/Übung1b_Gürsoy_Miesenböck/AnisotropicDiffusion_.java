import ij.IJ;
import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

public class AnisotropicDiffusion_ implements PlugInFilter {

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about"))
        {showAbout(); return DONE;}
        return DOES_8G;
    } //setup


    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[])ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();

        int numOfIterations = 15;
        int convMaskRadius = 1;
        double kappa = 30.0;
        int diffFunctOption = 2; //mode 1 or mode 2

        //user enters kappa & n
        GenericDialog gd = new GenericDialog("Anisotropic Diffusion Config");
        gd.addNumericField("kappa", kappa, 0);
        gd.addNumericField("iterations",numOfIterations, 0);

        gd.showDialog();
        if (!gd.wasCanceled()) {
            kappa = (int) gd.getNextNumber();
            numOfIterations = (int) gd.getNextNumber();
        }

        //Center pixel distances ==> to ensure lower weight for diagonal neighbours
        double dx = 1.0;
        double dy = 1.0;
        double dd = Math.sqrt(2.0);
        double normFactor = 1.0/6.8;

        double[][] hN = new double[][]{{0.0, 1.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hNW = new double[][]{{1.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hW = new double[][]{{0.0, 0.0, 0.0}, {1.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hSW = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {1.0, 0.0, 0.0}};
        double[][] hS = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 1.0, 0.0}};
        double[][] hSO = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}};
        double[][] hO = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 1.0}, {0.0, 0.0, 0.0}};
        double[][] hNO = new double[][]{{0.0, 0.0, 1.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};

        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        double[][] outImg = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        //now do some iterations
        for(int iter = 0; iter < numOfIterations; iter++) {
            //do convolutions in all directions; nabla == gradient symbol (triangle with top-down);
            double[][] nablaN = ConvolutionFilter.convolveDouble(outImg, width, height, hN, convMaskRadius);
            double[][] nablaNW = ConvolutionFilter.convolveDouble(outImg, width, height, hNW, convMaskRadius);
            double[][] nablaW = ConvolutionFilter.convolveDouble(outImg, width, height, hW, convMaskRadius);
            double[][] nablaSW = ConvolutionFilter.convolveDouble(outImg, width, height, hSW, convMaskRadius);
            double[][] nablaS = ConvolutionFilter.convolveDouble(outImg, width, height, hS, convMaskRadius);
            double[][] nablaSO = ConvolutionFilter.convolveDouble(outImg, width, height, hSO, convMaskRadius);
            double[][] nablaO = ConvolutionFilter.convolveDouble(outImg, width, height, hO, convMaskRadius);
            double[][] nablaNO = ConvolutionFilter.convolveDouble(outImg, width, height, hNO, convMaskRadius);

            double[][] cN = new double[width][height];
            double[][] cNW = new double[width][height];
            double[][] cW = new double[width][height];
            double[][] cSW = new double[width][height];
            double[][] cS = new double[width][height];
            double[][] cSO = new double[width][height];
            double[][] cO = new double[width][height];
            double[][] cNO = new double[width][height];

            //coefficient from gradient
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {

                    //diffuse
                    if(diffFunctOption == 1) { //MODE 1
                        //TODO for all pixels and all gradient directions
                        cN[x][y] = Math.exp(-Math.pow((-nablaN[x][y]/kappa),2));
                        cNW[x][y] = Math.exp(-Math.pow((-nablaNW[x][y]/kappa),2));
                        cW[x][y] = Math.exp(-Math.pow((-nablaW[x][y]/kappa),2));
                        cSW[x][y] = Math.exp(-Math.pow((-nablaSW[x][y]/kappa),2));
                        cS[x][y] = Math.exp(-Math.pow((-nablaS[x][y]/kappa),2));
                        cSO[x][y] = Math.exp(-Math.pow((-nablaSO[x][y]/kappa),2));
                        cO[x][y] = Math.exp(-Math.pow((-nablaO[x][y]/kappa),2));
                        cNO[x][y] = Math.exp(-Math.pow((-nablaNO[x][y]/kappa),2));
                    }
                    else if(diffFunctOption == 2) { //MODE 2
                        cN[x][y] = 1.0/(1.0 + Math.pow((nablaN[x][y]/kappa),2));
                        cNW[x][y] = 1.0/(1.0 + Math.pow((nablaNW[x][y]/kappa),2));
                        cW[x][y] = 1.0/(1.0 + Math.pow((nablaW[x][y]/kappa),2));
                        cSW[x][y] = 1.0/(1.0 + Math.pow((nablaSW[x][y]/kappa),2));
                        cS[x][y] = 1.0/(1.0 + Math.pow((nablaS[x][y]/kappa),2));
                        cSO[x][y] = 1.0/(1.0 + Math.pow((nablaSO[x][y]/kappa),2));
                        cO[x][y] = 1.0/(1.0 + Math.pow((nablaO[x][y]/kappa),2));
                        cNO[x][y] = 1.0/(1.0 + Math.pow((nablaNO[x][y]/kappa),2));
                    }
                }
            }


            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    //now finally diffuse all pixels: aggregate weighted Cn * nablaN, aso.
                    double result = outImg[x][y] + normFactor * (
                                    Math.pow(1/dy,2) * cN[x][y] * nablaN[x][y] +
                                    Math.pow(1/dy,2) * cS[x][y] * nablaS[x][y] +
                                    Math.pow(1/dx,2) * cW[x][y] * nablaW[x][y] +
                                    Math.pow(1/dx,2) * cO[x][y] * nablaO[x][y] +
                                            (1/dd) * cNO[x][y] * nablaNO[x][y] +
                                            (1/dd) * cSO[x][y] * nablaSO[x][y] +
                                            (1/dd) * cNW[x][y] * nablaNW[x][y] +
                                            (1/dd) * cSW[x][y] * nablaSW[x][y]
                    );

                    outImg[x][y] = result;
                }
            }
        }

        ImageJUtility.showNewImage(outImg, width, height, "anisotropic diffusion with kappa: " + kappa + " & n: " + numOfIterations);
    }

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is a PluginFilter template\n");
    } //showAbout


}