import ij.IJ;
import ij.ImagePlus;
import ij.WindowManager;
import ij.gui.GenericDialog;
import ij.gui.HistogramWindow;
import ij.gui.Plot;
import ij.gui.PlotDialog;
import ij.plugin.Histogram;
import ij.plugin.ImageCalculator;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

/**
 * Simple implementation of a registration using nearest neighbor interpolation and sum of squared error distance
 * metric. (Lab 8)
 */
public class Registration_ implements PlugInFilter {
    private static String[] operators = new String[]{"Add", "Subtract", "Multiply", "Divide", "AND", "OR", "XOR", "Min", "Max", "Average", "Difference", "Copy", "Transparent-zero"};
    private static String[] lcOperators = new String[]{"add", "sub", "mul", "div", "and", "or", "xor", "min", "max", "ave", "diff", "copy", "zero"};
    private static int operator;
    private static String title1 = "";
    private static String title2 = "";
    private static boolean createWindow = true;
    private static boolean floatResult;
    private boolean processStack;

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about")) {
            showAbout();
            return DONE;
        }
        return DOES_8G;
    } //setup

    /**
     * @param xIdx   double x-image coordinate
     * @param yIdx   double y-image coordinate
     * @param width  the width of the input image
     * @param height the height of the image image
     * @param img    input image
     * @return the interpolated value for x and y.
     */
    public double getNNinterpolatedValue(double xIdx, double yIdx, int width, int height,
                                         double[][] img) {
        int xA = (int)(xIdx + 0.5);
        int yA = (int)(yIdx + 0.5);
        //restrict to [0;width-1] ==> check if inside the image!
        if(xA < 0) return 0;
        if(yA < 0) return 0;
        if(xA >= width) return 0;
        if(yA >= height) return 0;

        return img[xA][yA];
    }

    /**
     * @param inImg    input image
     * @param width    the width of the input image
     * @param height   the height of the input image
     * @param transX   translation in x-direction
     * @param transY   translation in y-direction
     * @param rotAngle rotation angle in degrees
     * @return transformed image
     */
    public double[][] transformImg(double[][] inImg, int width, int height, double transX, double transY, double rotAngle) {
        //due to backward mapping the direction for translation and rotation changes
        double rotAngleRad = -rotAngle * Math.PI / 180.0; //Math.toRadians(rot);
        double cosTheta = Math.cos(rotAngleRad);
        double sinTheta = Math.sin(rotAngleRad);
        double widthHalf = width / 2.0;
        double heightHalf = height / 2.0;

        //now calculate the image with backward mapping
        double[][] resultImg = new double[width][height];

        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                double xInA = x;
                double yInA = y;

                //step 1) move origin to center of the image
                xInA -= widthHalf;
                yInA -= heightHalf;

                //step 2) apply rotation!
                double rotatedX = xInA * cosTheta + yInA * sinTheta;
                double rotatedY = -xInA * sinTheta + yInA * cosTheta;

                xInA = rotatedX;
                yInA = rotatedY;

                //step 3) move origin back from center
                xInA += widthHalf;
                yInA += heightHalf;

                //step 4) apply translation (negative sign due to backward mapping)
                xInA -= transX;
                yInA -= transY;

                //apply interpolation
                double resVal = getNNinterpolatedValue(xInA, yInA ,width, height, inImg);
                resultImg[x][y] = resVal;

            } //for y in B!!!
        } //for x in B!!!

        return resultImg;
    }

    /**
     * @param refImg  - static reference image
     * @param testImg - moving image getting transformed
     * @param width   the width of the input image
     * @param height  the height of the input image
     * @return error metric
     */
    public double getImgDiffSSE(int[][] refImg, double[][] testImg, int width, int height) {
        double totalError = 0.0;

        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                double pixelDiff = refImg[x][y] - testImg[x][y];
                totalError += pixelDiff * pixelDiff;
            } //for y
        } //for x

        return totalError;
    }

    /**
     * @param refImg  - static reference image
     * @param testImg - moving image getting transformed
     * @param width   the width of the input image
     * @param height  the height of the input image
     * @return difference image
     */
    public double[][] getDiffImg(int[][] refImg, double[][] testImg, int width, int height) {
        double[][] res = new double[width][height];
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                res[x][y] = Math.abs(refImg[x][y] - testImg[x][y]);
            } //for y
        } //for x

        return res;
    }

    /**
     * method for automated registration utilizing 11x11x11 permutations for the transformation parameters
     *
     * @param refImg  The reference image
     * @param testImg the image to test with.
     * @param width   the width of the input image
     * @param height  the height of the input image
     * @return returns the registered image
     */
    public double[][] getRegisteredImage(int[][] refImg, double[][] testImg, int width, int height) {
        //best parameters
        double bestTx = 0.0;
        double bestTy = 0.0;
        double bestRot = 0.0;
        double currMinError = getImgDiffSSE(refImg, testImg, width, height);

        //apply registration, i.e. checking many permutations such as (4, -8, 2) for (Tx, Ty, Rot)
        int searchRadius = 5; //TODO use larger search radius for translation in exercise
        //due to search radius, we have 11 steps per dimension (2 * radius + 1)
        double stepWidth = 2.0; //init search space for Tx (from -radius to + radius) [-10;10], namely (-10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10)

        //check all possible permutations, e.g. (4, -8, 2) - around 1,300 permutations
        for(int xPos = -searchRadius; xPos <= searchRadius; xPos++) {
            for(int yPos = -searchRadius; yPos <= searchRadius; yPos++) {
                for(int rPos = -searchRadius; rPos <= searchRadius; rPos++) { //e.g. (2, -4, 1)
                    double Tx = xPos * stepWidth;
                    double Ty = yPos * stepWidth;
                    double Rot = rPos * stepWidth;
                    //for our example we get (4.0, -8.0, 2.0)

                    double[][] transformedImg = transformImg(testImg, width, height, Tx, Ty, Rot);
                    double actError = getImgDiffSSE(refImg, transformedImg, width, height);
                    //now check if actError indicates a new overall best solution
                    if(actError < currMinError) {
                        IJ.log("new best solution, ERR = " + actError);
                        currMinError = actError;
                        bestTx = Tx;
                        bestTy = Ty;
                        bestRot = Rot;
                    } //if

                } //for Rot
            } //for Ty
        } //for Tx

        //for exercise: use NN interpolation above (thousands and millions of times)
        //here: once Bilinear for quality of results!!
        double[][] registeredImg = transformImg(testImg, width, height, bestTx, bestTy, bestRot);

        System.out.println("final params, Tx=" + bestTx + ", Ty=" + bestTy + ", Rot=" + bestRot);

        return registeredImg;
    }


    public void run(ImageProcessor ip) {
        ImagePlus img1 = null;
        ImagePlus img2 = null;
        int[] wList = WindowManager.getIDList();
        if (wList == null) {
            IJ.noImage();
        } else {
            IJ.register(ImageCalculator.class);
            String[] titles = new String[wList.length];

            for(int i = 0; i < wList.length; ++i) {
                ImagePlus imp = WindowManager.getImage(wList[i]);
                if (imp != null) {
                    titles[i] = imp.getTitle();
                } else {
                    titles[i] = "";
                }
            }


            GenericDialog gd = new GenericDialog("Image Calculator");
            String defaultItem;
            if (title1.equals("")) {
                defaultItem = titles[0];
            } else {
                defaultItem = title1;
            }

            gd.addChoice("Image1:", titles, defaultItem);
            if (title2.equals("")) {
                defaultItem = titles[0];
            } else {
                defaultItem = title2;
            }

            gd.addChoice("Image2:", titles, defaultItem);
            gd.showDialog();
            if (!gd.wasCanceled()) {
                int index1 = gd.getNextChoiceIndex();
                title1 = titles[index1];
                int index2 = gd.getNextChoiceIndex();
                title2 = titles[index2];
                img1 = WindowManager.getImage(wList[index1]);
                img2 = WindowManager.getImage(wList[index2]);
            }
        }
        ImageProcessor ip1 = img1.getProcessor();
        ImageProcessor ip2 = img2.getProcessor();
        byte[] pixels1 = (byte[]) ip1.getPixels();
        int width1 = ip1.getWidth();
        int height1 = ip1.getHeight();
        int[][] inDataArrInt1 = ImageJUtility.convertFrom1DByteArr(pixels1, width1, height1);
        double[][] inDataArrDbl1 = ImageJUtility.convertToDoubleArr2D(inDataArrInt1, width1, height1);
        byte[] pixels2 = (byte[]) ip2.getPixels();
        int width2 = ip2.getWidth();
        int height2 = ip2.getHeight();
        int[][] inDataArrInt2 = ImageJUtility.convertFrom1DByteArr(pixels2, width2, height2);
        double[][] inDataArrDbl2 = ImageJUtility.convertToDoubleArr2D(inDataArrInt2, width2, height2);


        if(width1 != width2 && height1 != height2){
            try {
                throw new Exception("Images need same height and width!");
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }

        //initially transform input image to get a registration task
        double transX = 9.78;
        double transY = -1.99;
        double rot = 2.14;
        //with the first run, we expect to get (10.0, -2.0, 2.0) due to backward mapping, we get inverted values!!

        double[][] transformedImage = transformImg(inDataArrDbl1, width1, height1, transX, transY, rot);
        double initError = getImgDiffSSE(inDataArrInt2, transformedImage, width2, height2);
        IJ.log("init error = " + initError);
        ImageJUtility.showNewImage(transformedImage, width1, height1, "transformed img");
        double[][] initDiffImg = getDiffImg(inDataArrInt2, transformedImage,width2, height2);
        ImageJUtility.showNewImage(initDiffImg, width1, height1, "init diff image prior to registration");

        double[][] registeredImg = getRegisteredImage(inDataArrInt2, transformedImage, width2, height2);
        ImageJUtility.showNewImage(registeredImg, width2, height2, "registered img");
        double[][] finalDiffImg = getDiffImg(inDataArrInt2, registeredImg,width2, height2);
        ImageJUtility.showNewImage(finalDiffImg, width2, height2, "final diff image");


    } //run

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is a PluginFilter template\n");
    } //showAbout

    int[] calculateHistogram (int[][] inDataArrInt, int width, int height){
        int histo[] = new int[256];
        int pixel;
        for(int x = 0; x < width; x++){
            for(int y = 0; y < height; y++){
                pixel = inDataArrInt[x][y];
                histo[pixel]++;
            }
        }
        return histo;
    }

} //class Registration_
