import ij.*;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

import java.util.ArrayList;
import java.util.List;

public class BitSplit_ implements PlugInFilter {

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

        List<int[][]> resultImages = bitSplitImg(inDataArrInt,width,height);
        int idx = 0;
        for(int[][] img : resultImages) {
            ImageJUtility.showNewImage(img, width, height, "bit plane " + idx++);
        }
    } //run

    public List<int[][]> bitSplitImg(int[][] inImg, int width, int height) {
        List<int[][]> returnImages = new ArrayList<>();

        for(int i = 0; i < 8; i++) {
            returnImages.add(new int[width][height]);
        }

        int[] bitArray = new int[] {128, 64, 32, 16, 8, 4, 2, 1};

        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                int actVal = inImg[x][y];

                for(int bitIDX = 0; bitIDX <= 7; bitIDX++) {
                    int resultVal = 0;
                    if(actVal >= bitArray[bitIDX]) {
                        resultVal = 255;
                        actVal -= bitArray[bitIDX];
                    }

                    returnImages.get(bitIDX)[x][y] = resultVal;
                }
            }
        }

        return returnImages;
    }

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is a PluginFilter template\n");
    } //showAbout

} //class FilterTemplate_

