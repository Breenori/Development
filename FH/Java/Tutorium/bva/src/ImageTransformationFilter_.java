public class ImageTransformationFilter_ {

    /**
     * get morphed image
     *
     * @param inImg1           The first input image.
     * @param inImg2           The second input image.
     * @param width            The width of the first image image.
     * @param height           The height of the first input image.
     * @param alphaVal         The value of overlapping from the second image
     * @return The resulting image.
     */


    public static int[][] MorphImages(int[][] inImg1, int[][] inImg2, int width,
                                      int height, double alphaVal) {

        int[][] morphedImg = new int[width][height];

        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                morphedImg[x][y] = (int)(inImg1[x][y]*alphaVal) + (int)(inImg2[x][y]*(1-alphaVal));
            } //y
        } //x
        return morphedImg;
    }

    /**
     * apply scalar transformation
     *
     * @param inImg            The input image.
     * @param width            The width of the image image.
     * @param height           The height of the input image.
     * @param transferFunction The transferFunction where the index corresponds to a input color and the value to the
     *                         output color in which it should be transferred.
     * @return The resulting image.
     */

    public static int[][] getTransformedImage(int[][] inImg, int width,
                                              int height, int[] transferFunction) {
        int[][] returnImg = new int[width][height];
        //iterate all pixels
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                int currValInA = inImg[x][y];
                int newValInB = transferFunction[currValInA];
                returnImg[x][y] = newValInB;
            } //y
        } //x
        return returnImg;
    }

    /**
     * get transfer function for contrast inversion
     *
     * @param maxVal the max value of the image space (note: this is 255 for most of the images)
     * @return The resulting transfer function.
     */

    public static int[] getInversionTF(int maxVal) {
        int[] transferFunction = new int[maxVal + 1];
        for(int idx = 0; idx <= maxVal; idx++) {
            //idx == scalar value of A
            transferFunction[idx] = maxVal - idx; //new value in B
        } //for

        return transferFunction;
    }



    public static int[] getBinaryThreshTF(int lowerThresh, int upperThresh, int maxVal) {
        int[] transferFunction = new int[maxVal + 1]; //we think everywhere 0

        for(int i = lowerThresh; i<= upperThresh; i++) {
            transferFunction[i] = maxVal;
        } //for

        return transferFunction;
    } //getBinaryThreshTF


}



