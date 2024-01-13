public class Utility {

    static int getNNinterpolation(int[][] inImg, int width, int height, double posX, double posY) {
		// backward mapping
        int x = (int)(posX + 0.5);
        int y = (int)(posY + 0.5);

        //range check
        if(x >= 0 && x < width && y >= 0 && y < height) {
            return inImg[x][y];
        } //if valid range

        return 0;
    }

    static int getBilinearInterpolation(int[][] inImg, int width, int height, double posX, double posY) {
		// calculate coordinates of left-upper pixel
        int left = (int)Math.floor(posX);
        int top = (int)Math.floor(posY);
		// calculate deviation (delta) of new position to reference point (top-left)
        double dX = posX - left;
        double dY = posY - top;

		// range-check and insert into formula for calculation of bilinear interpolated values.
        if(left > 0 && left+1 < width && top > 0 && top + 1 < height) {
            return (int) ((1 - dX) * (1 - dY) * inImg[left][top] + dX * (1 - dY) * inImg[left + 1][top] + (1 - dX) * dY * inImg[left][top + 1] + dX * dY * inImg[left + 1][top + 1]);
        }

        return 0;
    }

    static float getBilinearInterpolationF(float[][] inImg, int width, int height, double posX, double posY) {
        // calculate coordinates of left-upper pixel
        int left = (int)Math.floor(posX);
        int top = (int)Math.floor(posY);
        // calculate deviation (delta) of new position to reference point (top-left)
        double dX = posX - left;
        double dY = posY - top;

        // range-check and insert into formula for calculation of bilinear interpolated values.
        if(left > 0 && left+1 < width && top > 0 && top + 1 < height) {
            return (float)((1 - dX) * (1 - dY) * inImg[left][top] + dX * (1 - dY) * inImg[left + 1][top] + (1 - dX) * dY * inImg[left][top + 1] + dX * dY * inImg[left + 1][top + 1]);
        }

        return 0;
    }

    static int[][] rescaleImage(int[][] inImg, int width, int height, int newWidth, int newHeight, boolean useBilinear) {
        int[][] returnImg = new int[newWidth][newHeight];

        //calculate resampled image ==> iterate over result image and get values from input img by backward mapping
        for(int x = 0; x < newWidth; x++) {
            for(int y = 0; y < newHeight; y++) {
				// calculate new position based on target width and height
                double xPos = x / ((double)newWidth/width);
                double yPos = y / ((double)newHeight/height);
				// based on the boolean, delegate to the right function
                if(useBilinear)
                {
                    returnImg[x][y] = Utility.getBilinearInterpolation(inImg, width, height, xPos, yPos);
                }
                else {
                    returnImg[x][y] = Utility.getNNinterpolation(inImg, width, height, xPos, yPos);
                }
            } //for y
        } //for x

        return returnImg;
    }

    static int[][] normalizeF(float[][] inImg, int width, int height, int newMax) {
        int[][] resultImg = new int[width][height];

        float minVal = Long.MAX_VALUE;
        float maxVal = Long.MIN_VALUE;
        //calc min, max
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                float actVal = inImg[x][y];
                if(actVal < minVal)
                    minVal = actVal;
                if(actVal > maxVal)
                    maxVal = actVal;
            }
        }
        maxVal = maxVal - minVal;
        float scale = maxVal/255;

        // set new values based on the previously calculated scaled
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                resultImg[x][y] = (int)((inImg[x][y]-minVal)/scale);
            }
        }

        return resultImg;
    }
}
