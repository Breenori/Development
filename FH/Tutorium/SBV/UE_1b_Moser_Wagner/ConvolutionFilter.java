import java.util.Arrays;

public class ConvolutionFilter {


	/**
	 * convolution of input image with kernel, normalization to kernel sum 1.0
	 * only use for low-pass filters
	 *
	 * @param inputImg
	 * @param width
	 * @param height
	 * @param kernel   double[][] kernel image
	 * @param radius   kernel radius
	 * @return
	 */
	public static double[][] convolveDoubleNorm(double[][] inputImg, int width, int height, double[][] kernel, int radius) {

		double[][] returnImg = new double[width][height];

		// move over all pixels ==> once, hot-spot at I(3,3), cf. slide 18
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				// e.g. I with size 100*100 ==> 10.000 pixels. One position of them is I(3,3)
				double sum = 0;
				double sumCoef = 0.0; // we expect 1.0 for low-pass filters (Tiefpass)

				// now iterate all yellow mask elements in range [-radius, +radius]
				for (int xOffset = -radius; xOffset <= radius; xOffset++) {
					for (int yOffset = -radius; yOffset <= radius; yOffset++) {
						//e.g. position M with (1,0) for x/y offset
						int nbx = x + xOffset;
						int nby = y + yOffset; // for our example we get (4,3) at M

						// first check if nbx, nby valid coordinates, inside the image
						if ((nbx >= 0) && (nby >= 0) && (nbx < width) && (nby < height)) {
							sum = sum + inputImg[nbx][nby] * kernel[xOffset + radius][yOffset + radius];
							sumCoef = sumCoef + kernel[xOffset + radius][yOffset + radius];
						}
					}
				}
				returnImg[x][y] = (sum / sumCoef); // apply normalization
			}
		}
		return returnImg;
	}

	public static double[][] convolveDoubleMedian(double[][] inputImg, int width, int height, int radius) {
		int size = 2 * radius + 1; // width or height
		double[] kernel = new double[size * size];
		double median;

		double[][] returnImg = new double[width][height];
		int count = 0;
		// move over all pixels ==> once, hot-spot at I(3,3), cf. slide 18
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {

				// now iterate all yellow mask elements in range [-radius, +radius]
				for (int xOffset = -radius; xOffset <= radius; xOffset++) {
					for (int yOffset = -radius; yOffset <= radius; yOffset++) {
						//e.g. position M with (1,0) for x/y offset
						int nbx = x + xOffset;
						int nby = y + yOffset; // for our example we get (4,3) at M

						// first check if nbx, nby valid coordinates, inside the image
						if ((nbx >= 0) && (nby >= 0) && (nbx < width) && (nby < height)) {
							kernel[count] = inputImg[nbx][nby];
							count++;
						}
					}
				}
				count = 0;
				median = getMedianMask(kernel);
				returnImg[x][y] = median; // apply normalization
			}
		}
		return returnImg;
	}

	public static double[][] getSobelVerticalKernel() {
		return new double[][]{{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
	} //getVerticalSobel

	public static double[][] getGradientHorizontalKernel() {
		return new double[][]{{0, 0, 0}, {0, 1, -1}, {0, 0, 0}};
	} //getGradientHorizontalKernel

	/**
	 * convolution of input image with kernel
	 *
	 * @param inputImg
	 * @param width
	 * @param height
	 * @param kernel   double[][] kernel image
	 * @param radius   kernel radius
	 * @return
	 */
	public static double[][] convolveDouble(double[][] inputImg, int width, int height, double[][] kernel, int radius) {
		double[][] returnImg = new double[width][height];

		// move over all pixels ==> once, hot-spot at I(3,3), cf. slide 18
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				// e.g. I with size 100*100 ==> 10.000 pixels. One position of them is I(3,3)
				double sum = 0;

				// now iterate all yellow mask elements in range [-radius, +radius]
				for (int xOffset = -radius; xOffset <= radius; xOffset++) {
					for (int yOffset = -radius; yOffset <= radius; yOffset++) {
						//e.g. position M with (1,0) for x/y offset
						int nbx = x + xOffset;
						int nby = y + yOffset; // for our example we get (4,3) at M

						// first check if nbx, nby valid coordinates, inside the image
						if ((nbx >= 0) && (nby >= 0) && (nbx < width) && (nby < height)) {
							sum = sum + inputImg[nbx][nby] * kernel[xOffset + radius][yOffset + radius];
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
	 * @param tgtRadius
	 * @return
	 */
	public static double[][] getMeanMask(int tgtRadius) {
		int size = 2 * tgtRadius + 1; // width or height
		double[][] kernelImg = new double[size][size];

		double meanCoef = 1.0 / (size * size);

		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				kernelImg[x][y] = meanCoef;
			}
		}

		return kernelImg;
	}

	public static double getMedianMask(double[] kernelArray) {
		Arrays.sort(kernelArray);
		double median;

		if (kernelArray.length % 2 == 0) {
			median = ((kernelArray.length / 2 + 0.5) + (kernelArray.length / 2 - 0.5));
		} else {
			median = kernelArray[kernelArray.length / 2];
		}
		return median;
	}
}
