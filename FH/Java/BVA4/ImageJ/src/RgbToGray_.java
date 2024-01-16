import ij.IJ;
import ij.ImagePlus;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

public class RgbToGray_ implements PlugInFilter {
    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about")) {
            showAbout();
            return DONE;
        }
        return DOES_RGB + DOES_STACKS + SUPPORTS_MASKING;
    } //setup

    public void run(ImageProcessor ip) {
        int width = ip.getWidth();
        int height = ip.getHeight();

        // getChannelImageFromIP delivers the 3 color values of RGB
        int[][][] inDataArrInt = ImageJUtility.getChannelImageFromIP(ip, width, height, 3);

        // two arrays: one per output photo
        int[][] greyPicture = new int[width][height];
        int[][] greyPicture2 = new int[width][height];
        // running through two for loops to access the 3 color values per pixel
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int red = inDataArrInt[x][y][0];
                int green = inDataArrInt[x][y][1];
                int blue = inDataArrInt[x][y][2];

                // modifying the color values into grey values
                int grey = (red + green + blue) / 3; //average
                int grey2 = (int) (red * 0.21 + green * 0.72 + blue * 0.07); //lumosity

                greyPicture[x][y] = grey;
                greyPicture2[x][y] = grey2;

            }
        }

        ImageJUtility.showNewImage(greyPicture, width, height, "RGB to grey");
        ImageJUtility.showNewImage(greyPicture2, width, height, "RGB to grey with weighted Filters");

    } //run

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this transforms RGB to gray pictures\n");
    } //showAbout

}
