
import ij.*;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

import java.util.Arrays;

public class Median_ implements PlugInFilter {

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about")) {
            showAbout();
            return DONE;
        }
        return DOES_8G;
    } //setup

    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[]) ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();
        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        //radius of windowing
        int maskRadius = 1;
        //user can enter radius
        GenericDialog gd = new GenericDialog("median filter config");
        gd.addNumericField("radius", maskRadius, 0);
        gd.showDialog();
        if (!gd.wasCanceled()) {
            maskRadius = (int) gd.getNextNumber();
        }

        int size = 2 * maskRadius + 1; // radius left right and the pixel in the middle
        int[][] outputImg = new int[width][height];
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {

                int medianValues = 0;
                int[] values = new int[size * size];
                //iterate all yellow mask elements in range [-radius;radius]
                for (int xOffset = -maskRadius; xOffset <= maskRadius; xOffset++) {
                    for (int yOffset = -maskRadius; yOffset <= maskRadius; yOffset++) {


                        int nbX = x + xOffset;
                        int nbY = y + yOffset;
                        //check if inside image
                        if ((nbX >= 0) && (nbY >= 0) && (nbX < width) && (nbY < height)) {
                            values[medianValues] = inDataArrInt[nbX][nbY];
                            medianValues++;
                        }
                    }
                }

                Arrays.sort(values);
                int median = 0;
                if (medianValues % 2 == 0) { // if array length is even (only important for corners and edges of the image)
                    int idx = values.length - (medianValues / 2);
                    int idx2 = idx - 1;
                    median = (values[idx] + values[idx2]) / 2; // even length results in two values that is why we add them and /2
                } else { // uneven length is easier to find the median
                    int idx = values.length - (medianValues / 2) - 1;
                    median = values[idx];
                }

                outputImg[x][y] = median; // all newly calculated pixels got placed on the new image
            } //for y
        } //for x
        //show Image Result
        ImageJUtility.showNewImage(outputImg, width, height,
                "median with radius = " + maskRadius);

        int[][] newImg = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                if (x < (width / 2) && y < (height / 2) || x > (width / 2) && y > (height / 2)) {
                    newImg[x][y] = outputImg[x][y]; // shows old image for comparison (4x4 Segments)
                }
            }
        }
        ImageJUtility.showNewImage(newImg, width, height,
                "Noise & Median with radius = " + maskRadius);
    }//run

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is a median filter\n");
    } //showAbout

} //class Median_

