import ij.IJ;
import ij.ImagePlus;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

public class HistogramEqualization_ implements PlugInFilter {
    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about")) {
            showAbout();
            return DONE;
        }
        return DOES_8G + DOES_STACKS + SUPPORTS_MASKING;
    } //setup

    public void run(ImageProcessor ip) {
        //read in the data of the original photo
        byte[] pixels = (byte[]) ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();
        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);

        //create a array for the color values, per pixel
        int[] histogram = new int[256];
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int z = inDataArrInt[x][y];
                histogram[z] += 1;
            }
        }

        //adding up all the color values of the histogram, per pixel
        int[] pixelsum = new int[256];
        for (int i = 1; i < 256; i++) {
            pixelsum[i] = pixelsum[i - 1] + histogram[i];
        }

        //creating a new histogram for the grey value equalization
        int[] histogramEqualization = new int[256];
        // dividing the average grey color for each pixel
        int averageColor = (width * height / 255);
        for (int i = 0; i <= 255 ; i++) {
            histogramEqualization[i] = (int)(pixelsum[i] / averageColor);
        }

        //returns the new histogram equalization to the output photo
        int[][] returnImg = new int[width][height];
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                returnImg[x][y] = histogramEqualization[inDataArrInt[x][y]];
            }
        }
        ImageJUtility.showNewImage(returnImg, width, height, "histogramEqualization");

} //run

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is a histogram equalization filter\n");
    } //showAbout
}
