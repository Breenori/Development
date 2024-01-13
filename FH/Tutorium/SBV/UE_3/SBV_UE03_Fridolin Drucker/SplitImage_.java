import ij.ImagePlus;
import ij.gui.NewImage;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

public class SplitImage_ implements PlugInFilter {

    @Override
    public int setup(String arg, ImagePlus imp) {
        // This method is called once when the plugin is loaded.
        // "arg" is the argument specified for this plugin in ImageJ's Plugins menu,
        // and "imp" is the currently active image.
        // Return flags indicating the capabilities of the plugin.
        // In this case, we just say that we accept any type of image.
        return DOES_ALL;
    }

    @Override
    public void run(ImageProcessor ip) {
        // This method is called once for each slice in a stack, or once for
        // each image in a collection of images.
        // "ip" is the image processor for the current image.

        // Get the width and height of the image
        int width = ip.getWidth();
        int height = ip.getHeight();

        // Create two new image processors for the two halves of the image
        ImageProcessor leftIp = ip.createProcessor(width / 2, height);
        ImageProcessor rightIp = ip.createProcessor(width / 2, height);

        // Loop through all the pixels in the image
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                // Get the value of the pixel at (x, y)
                int value = ip.getPixel(x, y);

                // Set the pixel value in the appropriate half of the image
                if (x < width / 2) {
                    leftIp.putPixel(x, y, value);
                } else {
                    rightIp.putPixel(x - width / 2, y, value);
                }
            }
        }

        // Create two new image plus objects from the image processors
        ImagePlus leftImp = new ImagePlus("Left Half", leftIp);
        ImagePlus rightImp = new ImagePlus("Right Half", rightIp);

        // Show the images
        leftImp.show();
        rightImp.show();
    }
}