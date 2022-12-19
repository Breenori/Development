import ij.*;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

public class AnisotropicDiffusion_ implements PlugInFilter {

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
        //Convert image values from integer to double for further processing
        double[][] outImg = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        //Radius of mask
        int radius = 1;

        //Weight based on pixel distance from center
        double dx = 1.0;
        double dy = 1.0;
        double dd = 1.0 / Math.sqrt(2.0);

        //Initiate variables for user input
        int numOfIterations = 10;
        double kappa = 10.0;
        boolean dgimages = false;

        //Get values in dialog from user
        GenericDialog gd = new GenericDialog("Enter # of iterations and kappa");
        gd.addNumericField("Iterations (n)", numOfIterations, 0);
        gd.addNumericField("Kappa (k)", kappa, 0);
        gd.addCheckbox("Show diffusion and gradient images", dgimages);
        gd.showDialog();
        if (gd.wasCanceled()) {
            return;
        }

        //Set values to variables
        numOfIterations = (int) gd.getNextNumber();
        kappa = (int) gd.getNextNumber();
        dgimages = gd.getNextBoolean();

        //Initiate directional filter masks
        double[][] hNO = new double[][] {{0.0, 0.0, 1.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hO = new double[][] {{0.0, 0.0, 0.0}, {0.0, -1.0, 1.0}, {0.0, 0.0, 0.0}};
        double[][] hN = new double[][] {{0.0, 1.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hSO = new double[][] {{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}};
        double[][] hS = new double[][] {{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 1.0, 0.0}};
        double[][] hSW = new double[][] {{0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {1.0, 0.0, 0.0}};
        double[][] hW = new double[][] {{0.0, 0.0, 0.0}, {1.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};
        double[][] hNW = new double[][] {{1.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, 0.0}};

        //Initiate arrays for gradients
        double[][] nablaN = new double[width][height];
        double[][] nablaNO = new double[width][height];
        double[][] nablaO = new double[width][height];
        double[][] nablaSO = new double[width][height];
        double[][] nablaS = new double[width][height];
        double[][] nablaSW = new double[width][height];
        double[][] nablaW = new double[width][height];
        double[][] nablaNW = new double[width][height];

        //Initiate arrays for coefficients
        double[][] cN = new double[width][height];
        double[][] cNO = new double[width][height];
        double[][] cO = new double[width][height];
        double[][] cSO = new double[width][height];
        double[][] cS = new double[width][height];
        double[][] cSW = new double[width][height];
        double[][] cW = new double[width][height];
        double[][] cNW = new double[width][height];

        //Apply anisotrophic diffusion n times
        for (int iter  = 0; iter < numOfIterations; iter++) {

            //Do convolutions in all directions
            nablaN = ConvolutionFilter.convolveDouble(outImg, width, height, hN, radius);
            nablaNO = ConvolutionFilter.convolveDouble(outImg, width, height, hNO, radius);
            nablaO = ConvolutionFilter.convolveDouble(outImg, width, height, hO, radius);
            nablaSO = ConvolutionFilter.convolveDouble(outImg, width, height, hSO, radius);
            nablaS = ConvolutionFilter.convolveDouble(outImg, width, height, hS, radius);
            nablaSW = ConvolutionFilter.convolveDouble(outImg, width, height, hSW, radius);
            nablaW = ConvolutionFilter.convolveDouble(outImg, width, height, hW, radius);
            nablaNW = ConvolutionFilter.convolveDouble(outImg, width, height, hNW, radius);

            //Get coefficients from gradients
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    cN[x][y] = Math.exp(-0.5 * (Math.pow((nablaN[x][y] / kappa), 2.0)));
                    cNO[x][y] = Math.exp(-0.5 * (Math.pow((nablaNO[x][y] / kappa), 2.0)));
                    cO[x][y] = Math.exp(-0.5 * (Math.pow((nablaO[x][y] / kappa), 2.0)));
                    cSO[x][y] = Math.exp(-0.5 * (Math.pow((nablaSO[x][y] / kappa), 2.0)));
                    cS[x][y] = Math.exp(-0.5 * (Math.pow((nablaS[x][y] / kappa), 2.0)));
                    cSW[x][y] = Math.exp(-0.5 * (Math.pow((nablaSW[x][y] / kappa), 2.0)));
                    cW[x][y] = Math.exp(-0.5 * (Math.pow((nablaW[x][y] / kappa), 2.0)));
                    cNW[x][y] = Math.exp(-0.5 * (Math.pow((nablaNW[x][y] / kappa), 2.0)));
                } //Height
            } //Width

            //Iterate through every pixel of outImg
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    //Perform anisotropic diffusion
                    outImg[x][y] = outImg[x][y] + ((1/6.8) * ((dx * ((cO[x][y] * nablaO[x][y]) + (cW[x][y] * nablaW[x][y]))) + (dy * ((cN[x][y] * nablaN[x][y]) + (cS[x][y] * nablaS[x][y]))) + (dd * ((cNO[x][y] * nablaNO[x][y]) + (cSO[x][y] * nablaSO[x][y]) + (cSW[x][y] * nablaSW[x][y]) + (cNW[x][y] * nablaNW[x][y])))));
                } //Height
            } //Width

        } //Iterations

        //Append naming of generated image by n and k values
        String nstr = new String("n: " + numOfIterations + ", ");
        String kappastr = new String("k: " + (int) kappa);

        //Generate and output final image
        ImageJUtility.showNewImage(outImg, width, height, "anisotropic diffusion, " + nstr + kappastr);

        //If user wants to get diffusion and gradient images
        if (dgimages) {

            //Get gradient images for all directions
            getGradientImage(nablaN, width, height, "Gradient N");
            getGradientImage(nablaO, width, height, "Gradient O");
            getGradientImage(nablaS, width, height, "Gradient S");
            getGradientImage(nablaW, width, height, "Gradient W");
            getGradientImage(nablaNO, width, height, "Gradient NO");
            getGradientImage(nablaNW, width, height, "Gradient NW");
            getGradientImage(nablaSW, width, height, "Gradient SW");
            getGradientImage(nablaSO, width, height, "Gradient SO");

            //Get diffusion images for all directions
            getDiffusionImage(cN, width, height, "Diffusion N");
            getDiffusionImage(cO, width, height, "Diffusion O");
            getDiffusionImage(cS, width, height, "Diffusion S");
            getDiffusionImage(cW, width, height, "Diffusion W");
            getDiffusionImage(cNO, width, height, "Diffusion NO");
            getDiffusionImage(cNW, width, height, "Diffusion NW");
            getDiffusionImage(cSW, width, height, "Diffusion SW");
            getDiffusionImage(cSO, width, height, "Diffusion SO");
        } //If
    } //Run

    public void getGradientImage(double[][] gradientArray, int width, int height, String name) {
        // Initiate new array
        double[][] gradient = new double[width][height];

        // Iterate through all pixels of image
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                //Make sure every pixel value is positive
                gradient[x][y] = Math.abs(gradientArray[x][y]);
            } //Height
        } //Width

        //Generate and output gradient image
        ImageJUtility.showNewImage(gradient, width, height, name);
    } //getGradientImage

    public void getDiffusionImage(double[][] diffusionArray, int width, int height, String name) {
        // Initiate new array
        double[][] diffusion = new double[width][height];

        // Iterate through all pixels of image
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                //Multiply diffusion values by 255
                diffusion[x][y] = diffusionArray[x][y] * 255;
            } //Height
        } //Width

        //Generate and output diffusion image
        ImageJUtility.showNewImage(diffusion, width, height, name);
    } //getDiffusionImage

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is a PluginFilter template\n");
    } //showAbout

} //Class AnisotropicDiffusion_