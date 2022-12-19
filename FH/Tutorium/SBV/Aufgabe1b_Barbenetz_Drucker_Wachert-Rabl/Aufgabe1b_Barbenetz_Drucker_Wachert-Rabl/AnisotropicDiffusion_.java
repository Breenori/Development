import ij.*;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

import static java.lang.Math.exp;


public class AnisotropicDiffusion_ implements PlugInFilter {

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about"))
        {showAbout(); return DONE;}
        return DOES_8G+DOES_STACKS+SUPPORTS_MASKING;
    } //setup

    // kappa soll eingegeben werden
    // n soll eingegeben werden

    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[])ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();

        int numOfIterations = 1;
        int convMaskRadius = 1;
        double kappa = 1;
        int diffFunctOption = 1; //mode 1 or mode 2

        GenericDialog gd = new GenericDialog("Kappa & number of iterations");
        gd.addNumericField("kappa", kappa, 0);
        gd.addNumericField("n", numOfIterations, 0);
        gd.showDialog();
        if(!gd.wasCanceled()){
            kappa = (int) gd.getNextNumber();
            numOfIterations = (int) gd.getNextNumber();
        }

        //Center pixel distances ==> to ensure lower weight for diagonal neighbours
        double dx = 1.0;
        double dy = 1.0;
        double dd = Math.sqrt(2.0);

        double[][] hN = new double[][]{{0.0, 1.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hS = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 1.0, 0.0}};
        double[][] hE = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 1.0}, {0.0, 0.0, 0.0}};
        double[][] hW = new double[][]{{0.0, 0.0, 0.0}, {1.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hNE = new double[][]{{0.0, 0.0, 1.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hSE = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}};
        double[][] hSW = new double[][]{{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {1.0, 0.0, 0.0}};
        double[][] hNW = new double[][]{{1.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        //TODO: other directions

        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        double[][] outImg =ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        double[][] outImgCN =ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);
        double[][] outImgCS =ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);
        double[][] outImgCE =ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);
        double[][] outImgCW =ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);
        double[][] outImgCNE =ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);
        double[][] outImgCSE =ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);
        double[][] outImgCSW =ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);
        double[][] outImgCNW =ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        double[][] outImgNablaN = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);
        double[][] outImgNablaS = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);
        double[][] outImgNablaE = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);
        double[][] outImgNablaW = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);
        double[][] outImgNablaNE = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);
        double[][] outImgNablaSE = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);
        double[][] outImgNablaSW = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);
        double[][] outImgNablaNW = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        //now do some iterations
        for(int iter = 0; iter < numOfIterations; iter++) {
            //do convolutions in all directions; nabla == gradient symbol (triangle with top-down);
            double[][] nablaN = ConvolutionFilter.convolveDouble(outImg, width, height, hN, convMaskRadius);
            double[][] nablaS = ConvolutionFilter.convolveDouble(outImg, width, height, hS, convMaskRadius);
            double[][] nablaE = ConvolutionFilter.convolveDouble(outImg, width, height, hE, convMaskRadius);
            double[][] nablaW = ConvolutionFilter.convolveDouble(outImg, width, height, hW, convMaskRadius);
            double[][] nablaNE = ConvolutionFilter.convolveDouble(outImg, width, height, hNE, convMaskRadius);
            double[][] nablaSE = ConvolutionFilter.convolveDouble(outImg, width, height, hSE, convMaskRadius);
            double[][] nablaSW = ConvolutionFilter.convolveDouble(outImg, width, height, hSW, convMaskRadius);
            double[][] nablaNW = ConvolutionFilter.convolveDouble(outImg, width, height, hNW, convMaskRadius);
            //TODO: filter in all directions
            //coefficient from gradient derived as
            //   (a)  cN = exp(-(-nablaN[x_i][y_i]/kappa)^2)  MODE 1
            // OR more precisely
            //    (b) cN = 1.0/(1.0 + (nablaN[x_i][y_i]/kappa)^2) MODE 2
            double[][] cN = new double[width][height];
            double[][] cS = new double[width][height];
            double[][] cE = new double[width][height];
            double[][] cW = new double[width][height];
            double[][] cNE = new double[width][height];
            double[][] cSE = new double[width][height];
            double[][] cSW = new double[width][height];
            double[][] cNW = new double[width][height];

            //TODO: for all directions
            for(int x = 0; x < width; x++ ) {
                for (int y = 0; y < height; y++) {

                    //diffuse
                    if (diffFunctOption == 1) { //MODE 1
                        cN[x][y] = exp(-Math.pow((-nablaN[x][y] / kappa),2));
                        cS[x][y] = exp(-Math.pow((-nablaS[x][y] / kappa),2));
                        cE[x][y] = exp(-Math.pow((-nablaE[x][y] / kappa),2));
                        cW[x][y] = exp(-Math.pow((-nablaW[x][y] / kappa),2));
                        cNE[x][y] = exp(-Math.pow((-nablaNE[x][y] / kappa),2));
                        cSE[x][y] = exp(-Math.pow((-nablaSE[x][y] / kappa),2));
                        cSW[x][y] = exp(-Math.pow((-nablaSW[x][y] / kappa),2));
                        cNW[x][y] = exp(-Math.pow((-nablaNW[x][y] / kappa),2));

                        //TODO for all pixels and all gradient directions
                    } else if (diffFunctOption == 2) { //MODE 2
                        cN[x][y] = 1.0 / (1.0 + Math.pow((nablaN[x][y] / kappa),2));
                        cS[x][y] = 1.0 / (1.0 + Math.pow((nablaS[x][y] / kappa),2));
                        cE[x][y] = 1.0 / (1.0 + Math.pow((nablaE[x][y] / kappa),2));
                        cW[x][y] = 1.0 / (1.0 + Math.pow((nablaW[x][y] / kappa),2));
                        cNE[x][y] = 1.0 / (1.0 + Math.pow((nablaNE[x][y] / kappa),2));
                        cSE[x][y] = 1.0 / (1.0 + Math.pow((nablaSE[x][y] / kappa),2));
                        cSW[x][y] = 1.0 / (1.0 + Math.pow((nablaSW[x][y] / kappa),2));
                        cNW[x][y] = 1.0 / (1.0 + Math.pow((nablaNW[x][y] / kappa),2));

                        //TODO for all pixels and all gradient directions
                    }

                    //now finally diffuse all pixels: aggregate weighted Cn * nablaN, aso.
                    outImg[x][y] = outImg[x][y] + (1/6.8) * (1.0 * cN[x][y] * nablaN[x][y] + 1.0 * cS[x][y] * nablaS[x][y]
                            + 1.0 * cE[x][y] * nablaE[x][y] + 1.0 * cW[x][y] * nablaW[x][y] + 0.7 * cNE[x][y] * nablaNE[x][y]
                            + 0.7 * cSE[x][y] * nablaSE[x][y] + 0.7 * cSW[x][y] * nablaSW[x][y] + 0.7 * cNW[x][y] * nablaNW[x][y]);

                    outImgCN[x][y] = outImgCN[x][y] + cN[x][y];
                    outImgCS[x][y] = outImgCS[x][y] + cS[x][y];
                    outImgCE[x][y] = outImgCE[x][y] + cE[x][y];
                    outImgCW[x][y] = outImgCW[x][y] + cW[x][y];
                    outImgCNE[x][y] = outImgCNE[x][y] + cNE[x][y];
                    outImgCSE[x][y] = outImgCSE[x][y] + cSE[x][y];
                    outImgCSW[x][y] = outImgCSW[x][y] + cSW[x][y];
                    outImgCNW[x][y] = outImgCNW[x][y] + cNW[x][y];

                    outImgNablaN[x][y] = outImgNablaN[x][y] + nablaN[x][y];
                    outImgNablaS[x][y] = outImgNablaS[x][y] + nablaS[x][y];
                    outImgNablaE[x][y] = outImgNablaE[x][y] + nablaE[x][y];
                    outImgNablaW[x][y] = outImgNablaW[x][y] + nablaW[x][y];
                    outImgNablaNE[x][y] = outImgNablaNE[x][y] + nablaNE[x][y];
                    outImgNablaSE[x][y] = outImgNablaSE[x][y] + nablaSE[x][y];
                    outImgNablaSW[x][y] = outImgNablaSW[x][y] + nablaSW[x][y];
                    outImgNablaNW[x][y] = outImgNablaNW[x][y] + nablaNW[x][y];

                }
            }
        }

        ImageJUtility.showNewImage(outImg, width, height, "anisotropic diffusion");


        /* ImageJUtility.showNewImage(outImgCN, width, height, "cN");
        ImageJUtility.showNewImage(outImgCS, width, height, "cS");
        ImageJUtility.showNewImage(outImgCE, width, height, "cE");
        ImageJUtility.showNewImage(outImgCW, width, height, "cW");
        ImageJUtility.showNewImage(outImgCNE, width, height, "cNE");
        ImageJUtility.showNewImage(outImgCSE, width, height, "cSE");
        ImageJUtility.showNewImage(outImgCSW, width, height, "cSW");
        ImageJUtility.showNewImage(outImgCNW, width, height, "cNW");

        ImageJUtility.showNewImage(outImgNablaN, width, height, "nablaN");
        ImageJUtility.showNewImage(outImgNablaS, width, height, "nablaS");
        ImageJUtility.showNewImage(outImgNablaE, width, height, "nablaE");
        ImageJUtility.showNewImage(outImgNablaW, width, height, "nablaW");
        ImageJUtility.showNewImage(outImgNablaNE, width, height, "nablaNE");
        ImageJUtility.showNewImage(outImgNablaSE, width, height, "nablaSE");
        ImageJUtility.showNewImage(outImgNablaSW, width, height, "nablaSW");
        ImageJUtility.showNewImage(outImgNablaNW, width, height, "nablaNW");
        */


    } //run

    void showAbout() {
        IJ.showMessage("This Filter implements Anisotropic Diffusion",
                "this is a AnisotropicDiffusion_ PluginFilter \n");
    } //showAbout

} //class AnisotropicDiffusion_