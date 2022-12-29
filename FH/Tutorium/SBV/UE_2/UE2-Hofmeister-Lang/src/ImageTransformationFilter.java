public class ImageTransformationFilter {

    /**
     * apply scalar transformation
     *
     * @param inImg
     * @param width
     * @param height
     * @param transferFunction
     * @return
     */
    public static int[][] getTransformedImage(int[][] inImg, int width, int height, int[] transferFunction) {
        int[][] returnImg = new int[width][height]; // result image B

        // visit every pixel
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int oldVal_ai = inImg[x][y]; // input value
                int newVal_bi = transferFunction[oldVal_ai];
                returnImg[x][y] = newVal_bi;
            }
        }
        return returnImg;
    }

    /**
     * apply rgb channel transformation to a greyscale image
     *
     * @param inImgChannels
     * @param width
     * @param height
     * @param transferFunction
     * @return
     */
    public static int[][] getTransformedImageRgbChannelsToGrayscale(int[][][] inImgChannels, int width, int height, int[][][] transferFunction) {
        int[][] returnImg = new int[width][height]; // result image B

        // visit every pixel
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int[] rgbValues = new int[3];
                for (int z = 0; z < 3; z++) {
                    rgbValues[z] = inImgChannels[x][y][z]; // input value
                }
                int newVal_bi = transferFunction[rgbValues[0]][rgbValues[1]][rgbValues[2]];
                returnImg[x][y] = newVal_bi;
            }
        }
        return returnImg;
    }

    /**
     * get transfer function for contrast inversion
     *
     * @param maxVal
     * @return
     */
    public static int[] getInversionTF(int maxVal) {
        int[] transferFunction = new int[maxVal + 1];

        for (int i = 0; i < maxVal; i++) {
            transferFunction[i] = maxVal - i;
        }
        return transferFunction;
    }

    /**
     * get transfer function for binary (black/white) filtering with minimal and maximal values
     *
     * @param lowerThresh
     * @param upperThresh
     * @param maxVal
     * @return
     */
    public static int[] getBinaryThreshTF(int lowerThresh, int upperThresh, int maxVal) {
        int[] transferFunction = new int[maxVal + 1];

        for (int i = 0; i < maxVal; i++) {
            if (i >= lowerThresh && i <= upperThresh) {
                transferFunction[i] = maxVal;
            } else {
                transferFunction[i] = 0;
            }
        }
        return transferFunction;
    }

    /**
     * get transfer function for RGB pictures to greyscale pictures.
     * Transfer algorithm: Average
     *
     * @param maxVal
     * @return
     */
    public static int[][][] getRgbToGreyscaleTfAvg(int maxVal) {
        int[][][] transferFunction = new int[maxVal + 1][maxVal + 1][maxVal + 1];

        for (int i = 0; i < maxVal; i++) {
            for (int j = 0; j < maxVal; j++) {
                for (int k = 0; k < maxVal; k++) {
                    transferFunction[i][j][k] = (i + j + k) / 3;
                }
            }
        }
        return transferFunction;
    }

    /**
     * get transfer function for RGB pictures to greyscale pictures.
     * Transfer algorithm: Lightness
     *
     * @param maxVal
     * @return
     */
    public static int[][][] getRgbToGreyscaleTfLight(int maxVal) {
        int[][][] transferFunction = new int[maxVal + 1][maxVal + 1][maxVal + 1];

        for (int r = 0; r < maxVal; r++) {
            for (int g = 0; g < maxVal; g++) {
                for (int b = 0; b < maxVal; b++) {
                    int max = Math.max(r, g);
                    max = Math.max(max, b);
                    int min = Math.min(r, g);
                    min = Math.min(min, b);
                    transferFunction[r][g][b] = (min + max) / 2;
                }
            }
        }
        return transferFunction;
    }

    /**
     * get transfer function for RGB pictures to greyscale pictures.
     * Transfer algorithm: Luminosity
     *
     * @param maxVal
     * @return
     */
    public static int[][][] getRgbToGreyscaleTfLum(int maxVal) {
        int[][][] transferFunction = new int[maxVal + 1][maxVal + 1][maxVal + 1];

        for (int r = 0; r < maxVal; r++) {
            for (int g = 0; g < maxVal; g++) {
                for (int b = 0; b < maxVal; b++) {
                    transferFunction[r][g][b] = (int) (0.21 * r + 0.72 * g + 0.07 * b);
                }
            }
        }
        return transferFunction;
    }

    /**
     * get transfer function for contrast strengthening with histogram equalization.
     *
     * @param inArr
     * @param width
     * @param height
     * @param maxVal
     * @return
     */
    public static int[] getHistogramEqualTF(int[][] inArr, int width, int height, int maxVal) {
        int length = maxVal + 1;
        int[] transferFunction = new int[length];
        int[] histogram = new int[length];
        int[] cumulativeHistogram = new int[length];
        int sum = 0;

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                int greyVal = inArr[i][j];
                histogram[greyVal] = histogram[greyVal] + 1;
            }
        }
        for (int i = 0; i < length; i++) {
            sum = sum + histogram[i];
            cumulativeHistogram[i] = sum;
        }
        for (int i = 0; i < length; i++) {
            int ti = (cumulativeHistogram[i] * maxVal) / (width * height);
            transferFunction[i] = ti;
        }
        return transferFunction;
    }

    /**
     * Merges two images to one checkerboard by chosen divider.
     * Result Images will be resized by a multiple of the divider.
     *
     * @param imageA
     * @param imageB
     * @param width
     * @param height
     * @param divider
     * @return ResizedImage
     */
    public static ResizedImage getCheckerBoard(int[][] imageA, int[][] imageB, int width, int height, int divider) {
        if (divider == 0) return null;

        int tileWidth = width / divider;
        int tileHeight = height / divider;
        boolean isOnImageA = true;
        width = tileWidth * divider;
        height = tileHeight * divider;
        int[][] resultImg = new int[width][height];
        ResizedImage ri = new ResizedImage(width, height);

        for (int i = 0; i < width; i++) {
            if (i % tileWidth == 0) isOnImageA = !isOnImageA;

            for (int j = 0; j < height; j++) {
                if (j % tileHeight == 0) isOnImageA = !isOnImageA;

                if (isOnImageA) {
                    resultImg[i][j] = imageA[i][j];
                } else {
                    resultImg[i][j] = imageB[i][j];
                }
            }

            if (divider % 2 == 1) isOnImageA = !isOnImageA;
        }
        ri.setImage(resultImg);
        return ri;
    }

    /**
     * Get new image within defined values (Window)
     *
     * @param inDataArrInt
     * @param width
     * @param height
     * @param aMin
     * @param aMax
     * @param tMin
     * @param tMax
     *
     * @return
     */
    public static int[][] getWindowedImage(int[][] inDataArrInt, int width, int height, int aMin, int aMax, int tMin, int tMax) {
        int[][] resultImg = new int[width][height];

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (inDataArrInt[i][j] < tMin){
                    resultImg[i][j] = aMin;
                } else if (inDataArrInt[i][j] > tMax) {
                    resultImg[i][j] = aMax;
                } else {
                    int newVal = ((aMax - aMin) / (tMax - tMin)) * (inDataArrInt[i][j] - tMin);
                    resultImg[i][j] = newVal;
                }
            }
        }
        return resultImg;
    }
}