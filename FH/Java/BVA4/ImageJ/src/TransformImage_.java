import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

public class TransformImage_ implements PlugInFilter {
    // The rotation angle in degrees
    private double angle;
    // The translation deltaX in pixels
    private int deltaX;
    // The translation deltaY in pixels
    private int deltaY;

    public int setup(String arg, ImagePlus im) {
        // Display a dialog box to get the angle, deltaX, and deltaY values from the user
        GenericDialog gd = new GenericDialog("Transform Image");
        gd.addNumericField("Rotation Angle (degrees):", 0, 1);
        gd.addNumericField("Translation Delta X (pixels):", 0, 0);
        gd.addNumericField("Translation Delta Y (pixels):", 0, 0);
        gd.showDialog();
        if (gd.wasCanceled()) {
            return DONE;
        }

        // Get the user-entered values from the dialog box
        angle = gd.getNextNumber();
        deltaX = (int) gd.getNextNumber();
        deltaY = (int) gd.getNextNumber();

        return DOES_ALL;
    }

    public void run(ImageProcessor ip) {
        // Convert the angle to radians
        double radians = Math.toRadians(angle);
        // Calculate the sine and cosine of the angle
        double cosine = Math.cos(radians);
        double sine = Math.sin(radians);

        // Get the width and height of the image
        int width = ip.getWidth();
        int height = ip.getHeight();

        // Create a new image processor for the transformed image
        ImageProcessor transformedIp = ip.createProcessor(width, height);

        // Loop through each pixel in the image
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                // Calculate the transformed x and y coordinates using nearest neighbor interpolation
                int transformedX = (int) Math.round(x * cosine - y * sine) + deltaX;
                int transformedY = (int) Math.round(x * sine + y * cosine) + deltaY;

                // Check if the transformed coordinates are within the bounds of the image
                if (transformedX >= 0 && transformedX < width && transformedY >= 0 && transformedY < height) {
                    // Get the pixel value at the original position
                    int pixel = ip.getPixel(x, y);
                    // Set the pixel value in the transformed image
                    transformedIp.putPixel(transformedX, transformedY, pixel);
                }
            }
        }

        // Use bilinear interpolation to get the final result
        transformedIp = transformedIp.resize(width, height, true);

        // Create a new ImagePlus object for the transformed image
        ImagePlus transformedIm = new ImagePlus("Transformed Image", transformedIp);

        // Show the transformed image in ImageJ
        transformedIm.show();
    }}
