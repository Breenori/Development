/**
 * Utility class that supports various convolution filters
 */
public class ConvolutionFilter {

    /**
     * convolution of input image with kernel, normalization to kernel sum 1.0 only use for low-pass filters
     *
     * @param inputImg The input image on which the kernel should be applied.
     * @param width    The width of the image.
     * @param height   The height of the image.
     * @param kernel   The kernel that should be applied on the image.
     * @param radius   The radius of the kernel.
     * @return The image with the applied kernel.
     */
    public static double[][] convolveDoubleNorm(double[][] inputImg, int width, int height, double[][] kernel, int radius) {
        double[][] returnImg = new double[width][height];

        // place yellow filter kernel at all possible hot-spot positions
        for(int x=0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                double sum = 0.0;
                double coefSum = 0.0; // should be 1.0

                for(int xOffset=-radius; xOffset <= radius; xOffset++) {
                    for(int yOffset=-radius; yOffset <= radius; yOffset++) {
                        int newX = x+xOffset;
                        int newY = y+yOffset;
                        if(newX>0 && newX<width && newY>0 && newY<height) {
                            sum+=inputImg[newX][newY]*kernel[xOffset+radius][yOffset+radius];
                            coefSum += kernel[xOffset+radius][yOffset+radius];
                        }
                    }
                }

                returnImg[x][y] = sum / coefSum;
            }
        }

        return returnImg;
    }

    /**
     * convolution of input image with kernel
     *
     * @param inputImg The input image on which the kernel should be applied.
     * @param width    The width of the image.
     * @param height   The height of the image.
     * @param kernel   The kernel that should be applied on the image.
     * @param radius   The radius of the kernel.
     * @return The image with the applied kernel.
     */

    public static double[][] convolveDouble(double[][] inputImg, int width, int height, double[][] kernel, int radius) {
        double[][] returnImg = new double[width][height];

        // place yellow filter kernel at all possible hot-spot positions
        for(int x=0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                double sum = 0.0;

                for(int xOffset=-radius; xOffset <= radius; xOffset++) {
                    for(int yOffset=-radius; yOffset <= radius; yOffset++) {
                            int newX = x+xOffset;
                            int newY = y+yOffset;
                            if(newX>0 && newX<width && newY>0 && newY<height) {
                                sum+=inputImg[newX][newY]*kernel[xOffset+radius][yOffset+radius];
                            }
                    }
                }

                returnImg[x][y] = sum;
            }
        }

        return returnImg;
    }

    /**
     * returns kernel image according to specified radius for mean low-pass filtering
     *
     * @param tgtRadius the radius that the mean mask should have.
     * @return The resulting mean mask.
     */
    public static double[][] getMeanMask(int tgtRadius) {
        int size = 2 * tgtRadius + 1;
        double[][] kernelImg = new double[size][size];

        double coeff = 1.0 / (size * size);

        for(int x=0; x<size; x++) {
            for(int y=0; y<size; y++) {
                kernelImg[x][y] = coeff;
            }
        }

        return kernelImg;
    }

}
