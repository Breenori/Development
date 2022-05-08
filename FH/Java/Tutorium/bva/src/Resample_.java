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

    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[])ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();
        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);

        GenericDialog gd = new GenericDialog("target scale factor");
        int newWidth = width;
        int newHeight = height;
        //user enters new width
        gd.addNumericField("Width", width, 0);
        //user enters new height
        gd.addNumericField("Height", height, 0);
        gd.showDialog(); //blocking
        if(!gd.wasCanceled()) {
            //save entered numbers in variables
            newWidth = (int)gd.getNextNumber();
            newHeight = (int)gd.getNextNumber();
        } //if

        //calculate scale factors
        double scaleFactorX = (newWidth -1) / ((double) width -1);
        double scaleFactorY = (newHeight -1) / ((double) height -1);

        //allocate result image
        int[][] returnImg = new int[newWidth][newHeight];

        //SOLVED: change from forward to backward mapping (B ==> A)
        //forward mapping A ==> B, obsolete
        for(int x = 0; x < newWidth; x++) { //in result image B
            for(int y = 0; y < newHeight; y++) {
                double xA = (x / scaleFactorX);
                double yA = (y / scaleFactorY);
                int resVal = getBilinearinterpolatedValue(inDataArrInt, width, height, xA, yA);
                returnImg[x][y] = resVal;
            } //for y
        } //for x

        ImageJUtility.showNewImage(returnImg, newWidth, newHeight,
                "resized to " + newWidth + "x" + newHeight);
    } //run

    /*
    in, out
     */
    int getNNinterpolatedValue(int[][] inImg, int width, int height,
                               double idxX, double idxY) {
        int xA = (int)(idxX + 0.5);
        int yA = (int)(idxY + 0.5);
        //restrict to [0;width-1] ==> check if inside the image!
        if(xA < 0) return 0;
        if(yA < 0) return 0;
        if(xA >= width) return 0;
        if(yA >= height) return 0;
        return inImg[xA][yA];
    }

    int getBilinearinterpolatedValue(int[][] inImg, int width, int height, double idxX, double idxY) {
        //get values from corner pixels
        int leftLower = inImg[(int)idxX][(int)idxY];
        int rightLower = inImg[(int)(idxX)][(int)idxY];
        if (idxX < width-1){
            rightLower = inImg[(int)(idxX+1)][(int)idxY];
        }
        int leftUpper = inImg[(int)idxX][(int)(idxY)];
        if (idxY < height-1){
            leftUpper = inImg[(int)idxX][(int)(idxY+1)];
        }
        int rightUpper = inImg[(int)(idxX)][(int)(idxY)];
        if (idxX < width-1 && idxY < height-1){
            rightUpper = inImg[(int)(idxX+1)][(int)(idxY+1)];
        }
        //calculate horizontal and vertical distances
        double distanceLeftLowerHori = idxX%1;
        double distanceRightLowerHori = 1-distanceLeftLowerHori;
        double distanceLeftUpperVerti = idxY%1;
        double distanceRightUpperVerti = 1-distanceLeftUpperVerti;
        //calculate new pixel value
        double resultLower = (rightLower*distanceLeftLowerHori + leftLower*distanceRightLowerHori) * distanceRightUpperVerti;
        double resultUpper = (rightUpper*distanceLeftLowerHori + leftUpper*distanceRightLowerHori) * distanceLeftUpperVerti;

        return (int)(resultLower+resultUpper);
    }

    void showAbout() {
        IJ.showMessage("About Resample_...",
                "this is a plugin to change the size of the input image\n");
    } //showAbout

}