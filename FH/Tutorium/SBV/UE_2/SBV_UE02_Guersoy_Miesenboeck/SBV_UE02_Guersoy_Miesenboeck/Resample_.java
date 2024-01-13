import com.sun.xml.internal.bind.v2.runtime.output.StAXExStreamWriterOutput;
import ij.IJ;
import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

public class Resample_ implements PlugInFilter {

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about"))
        {showAbout(); return DONE;}
        return DOES_8G;
    } //setup



    public double getNNinternpolatedValue(double[][] inImg, int width, int height, double posX, double posY) {

        //e.g. get value of inImg at position (posX, posY)(2.2, 3.7) ==> inImg[2][4]
        int posXint = (int)(posX + 0.5);
        int posYint = (int)(posY + 0.5);

        //check the range
        if (posXint < 0) posXint = 0;
        if (posYint < 0) posYint = 0;
        if (posXint >= width) posXint = width - 1;
        if (posYint >= height) posYint = height - 1;

        return inImg[posXint][posYint];
    }

    public double getBilinearinternpolatedValue(double[][] inImg, int width, int height, double posX, double posY) {

        // get 4 coordinate points
        int xPos0 = (int) (posX);
        int yPos0 = (int) (posY);
        int xPos1 = xPos0+1;
        int yPos1 = yPos0;
        int yPos2 = yPos0+1;
        int xPos2 = xPos0;
        int xPos3 = (int)(Math.round(posX +0.5));
        int yPos3 = (int)(Math.round(posY +0.5));

        double valueA = inImg[xPos0][yPos0];
        double valueB = valueA;
        double valueC = valueA;
        double valueD = valueA;

        if (xPos1 < width) valueB = inImg[xPos1][yPos1];
        if (yPos2 < height) valueC = inImg[xPos2][yPos2];
        if (xPos3 < width && yPos3 < height) valueD = inImg[xPos3][yPos3];

        double xRatio = posX - (int) (posX);
        double yRatio = posY - (int) (posY);
        int xPos = (int) (posX + 0.5);
        int yPos = (int) (posY + 0.5);

        if (xPos >= 0 && xPos < width && yPos >= 0 && yPos < height) {
            int x1Interpol = (int) (valueA + xRatio * (valueB-valueC));
            int x2Interpol = (int) (valueC + xRatio * (valueD-valueC));
            int yInterpol = (int) (x1Interpol + yRatio * (x2Interpol - x1Interpol));

            return yInterpol;
        }
        return 0;
    }

    double[][] getResampledImage(double[][] inImg, int width, int height, int tgtWidth, int tgtHeight, boolean useBilinearInterpolation) {
        double[][] returnImg = new double[tgtWidth][tgtHeight];


        //this is strategy A
        //double scaleFactorW = tgtWidth / (double)(width);
        //double scaleFactorH = tgtHeight / (double)(height);

        //this is strategy B
        double scaleFactorW = (tgtWidth -1.0 ) / (width - 1.0);
        double scaleFactorH = (tgtHeight - 1.0) / (height - 1.0);

        System.out.println("scale X = " + scaleFactorW + " scale Y = " + scaleFactorH);

        //move all pixels FORWARD MAPPING from A ==> B only works when making img smaller
        /*for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                double posX = x * scaleFactorW;
                double posY = y * scaleFactorH;

                returnImg[(int)Math.round(posX)][(int)Math.round(posY)] = getNNinternpolatedValue(inImg, width, height, x, y);
            }
        }*/

        //get all resulting pixel in B from any position in A, from B ==> A, BACKWARD MAPPING
        for (int x = 0; x < tgtWidth; x++) {
            for (int y = 0; y < tgtHeight; y++) {

                double posX = x / scaleFactorW;
                double posY = y / scaleFactorH;

                if (!useBilinearInterpolation)
                    returnImg[x][y] = getNNinternpolatedValue(inImg, width, height, posX, posY);
                else
                    returnImg[x][y] = getBilinearinternpolatedValue(inImg, width, height, posX, posY);
            }
        }
        return returnImg;
    }

    public double[][] checkerboard(int width, int height, double[][]NNimg, double[][]BLimg){
        double[][] checkerboard = new double[width][height];
        int halfWidth = width/2;
        int halfHeight = height/2;

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if(i < halfWidth && j < halfHeight ){
                    checkerboard[i][j] = NNimg[i][j];
                }
                else if(i>halfWidth && j > halfHeight){
                    checkerboard[i][j] = NNimg[i][j];
                }
                else{
                    checkerboard[i][j] = BLimg[i][j];
                }

            }
        }
        return checkerboard;
    }

    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[])ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();
        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        double[][] inDataArrDbl = ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

        double scaleFactor = 2.11;
        //let the user enter the parameters
        GenericDialog gd = new GenericDialog("resample");
        gd.addNumericField("scale factor", scaleFactor, 4);
        gd.showDialog();
        if (!gd.wasCanceled()) scaleFactor = gd.getNextNumber();
        else return;


        if (scaleFactor < 0.01 || scaleFactor > 10) {
            return;
        }

        int tgtWidth = (int)Math.round(width*scaleFactor);
        int tgtHeight = (int)(height*scaleFactor + 0.5);
        double[][] resampledImage = getResampledImage(inDataArrDbl, width, height, tgtWidth, tgtHeight, false);
        double[][] resampledImage2 = getResampledImage(inDataArrDbl, width, height, tgtWidth, tgtHeight, true);

        double[][] checkerboardImg = checkerboard(tgtWidth, tgtHeight, resampledImage, resampledImage2);

        ImageJUtility.showNewImage(resampledImage, tgtWidth, tgtHeight, "Nearest Neighbor with scale factor:  " + scaleFactor);
        ImageJUtility.showNewImage(resampledImage2, tgtWidth, tgtHeight, "Bilinear with scale factor:  " + scaleFactor);
        ImageJUtility.showNewImage(checkerboardImg, tgtWidth, tgtHeight, "Checkerboard presentation");


    } //run

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is a PluginFilter to resize the input images\n");
    } //showAbout


}