import ij.ImagePlus;
import ij.io.Opener;
import ij.process.ImageProcessor;

import java.util.Arrays;

public class ConvolutionFilter {


	/**
	 * convolution of input image with kernel, normalization to kernel sum 1.0
	 * only use for low-pass filters
	 *
	 * @param inputImg
	 * @param width
	 * @param height
	 * @param kernel double[][] kernel image
	 * @param radius kernel radius
	 * @return
	 */
	public static double[][] convolveDoubleNorm(double[][] inputImg, int width, int height, double[][] kernel, int radius) {
		double[][] returnImg = new double[width][height];

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				double sum = 0;
				double coeffSum = 0.0; // should always be 1.0
				// iterate through all mask elements
				for (int xOffset = -radius; xOffset <= radius; xOffset++) {
					for (int yOffset = -radius; yOffset <= radius; yOffset++) {
						int nbX = x + xOffset;
						int nbY = y + yOffset;
						if ((nbX >= 0) && (nbY >= 0) && (nbX < width) && (nbY < height)) {
							sum += inputImg[nbX][nbY] * kernel[xOffset + radius][yOffset + radius];
							coeffSum += kernel[xOffset + radius][yOffset + radius];
						}
					}
				}
				returnImg[x][y] = sum / coeffSum; // apply normalization
			}
		}
		return returnImg;
	}

	/**
	 * convolution of input image with kernel
	 *
	 * @param inputImg
	 * @param width
	 * @param height
	 * @param kernel double[][] kernel image
	 * @param radius kernel radius
	 * @return
	 */
	public static double[][] convolveDouble(double[][] inputImg, int width, int height, double[][] kernel, int radius) {
		double[][] returnImg = new double[width][height];

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				double sum = 0;
				// iterate through all mask elements
				for (int xOffset = -radius; xOffset <= radius; xOffset++) {
					for (int yOffset = -radius; yOffset <= radius; yOffset++) {
						int nbX = x + xOffset;
						int nbY = y + yOffset;
						if ((nbX >= 0) && (nbY >= 0) && (nbX < width) && (nbY < height)) {
							sum += inputImg[nbX][nbY] * kernel[xOffset + radius][yOffset + radius];
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
		int size = 2 * tgtRadius + 1;
		double[][] kernelImg = new double[size][size];

		double meanCoef = 1.0 / (size * size);

		for (int x = 0; x < size; ++x) {
			for(int y = 0; y < size; ++y) {
				kernelImg[x][y] = meanCoef;
			}
		}
		return kernelImg;
	}

	public static double[][] getSobelVerticalKernel() {
		return new double[][] {{-1, 0, 1},{-2, 0, 2},{-1, 0, 1}};
	}

	public static double[][] getGradientHorizontalKernel() {
		return new double[][] {{0, 0, 0},{0, 1, -1},{0, 0, 0}};
	}

	public static int[][] convolveMedian(int[][] inputImg, int width, int height, int radius) {
		int[][] resultImg = new int[width][height];
		int size = 2 * radius + 1;
		int numberOfPixels = size * size;
		int idx = 0;

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				int[] valuesForMedian = new int[numberOfPixels];
				idx = 0;
				for (int xOffset = -radius; xOffset <= radius; xOffset++) {
					for (int yOffset = -radius; yOffset <= radius; yOffset++) {
						int nbX = x + xOffset;
						int nbY = y + yOffset;
						if ((nbX >= 0) && (nbY >= 0) && (nbX < width) && (nbY < height)) {
							valuesForMedian[idx++] = inputImg[nbX][nbY];
						}
					}
				}
				Arrays.sort(valuesForMedian);
				int medianIndex = (numberOfPixels + numberOfPixels - idx) / 2;
				if (idx % 2 == 0) {
					resultImg[x][y] = (valuesForMedian[medianIndex] + valuesForMedian[medianIndex + 1]) / 2;
				} else {
					resultImg[x][y] = valuesForMedian[medianIndex];
				}
			}
		}
		return resultImg;
	}

	public static double[][] GetGuessImage(double[][] originalImg, int width, int height, int mode) {
			double[][] guessImage = new double[width][height];

			//uses the folded original image
			if (mode == 0) {
				for (int x = 0; x < width; x++) {
					for (int y = 0; y < height; y++) {
						guessImage[x][y] = originalImg[x][y];
					}
				}
				return guessImage;
			}

			//generates an image with a random value between 1 and 255 for each pixel
			else if (mode == 1) {
				for (int x = 0; x < width; x++) {
					for (int y = 0; y < height; y++) {
						guessImage[x][y] = (int) ((Math.random() * (255 - 1)) + 1);
					}
				}
				return guessImage;
			}

			//generates a monotonous grey image
			else if (mode == 2) {
				for (int x = 0; x < width; x++) {
					for (int y = 0; y < height; y++) {
						guessImage[x][y] = 127.0;
					}
				}
				return guessImage;
			}

			else if (mode == 3) {
				Opener opener = new Opener();
				String imageFilePath = "clown.png";
				ImagePlus imp = opener.openImage(imageFilePath);
				ImageProcessor clown = imp.getProcessor();

				byte[] pixels = (byte[])clown.getPixels();
				int c_width = clown.getWidth();
				int c_height = clown.getHeight();
				int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, c_width, c_height);
				double[][] inDataArrDbl = ImageJUtility.convertToDoubleArr2D(inDataArrInt, c_width, c_height);

				double[][] resampledImage = Resample_.getResampledImage(inDataArrDbl, c_width, c_height, width, height, false);

				for (int x = 0; x < width; x++) {
					for (int y = 0; y < height; y++) {
						guessImage[x][y] = resampledImage[x][y];
					}
				}
				return guessImage;
			}

			else {
				return guessImage;
			}
		}

	public static double[][] RLD(double[][] originalImg, double[][] guessImg, double[][] kernel, int width, int height, int radius, int iterations) {
		double[][] newGuess = new double[width][height];
		double[][] cT = new double[width][height];
		double[][] mT = new double[width][height];

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				double pixelRes = 0;
				for (int xOffset = -radius; xOffset <= radius; xOffset++) {
					for (int yOffset = -radius; yOffset <= radius; yOffset++) {
						int nbX = x + xOffset;
						int nbY = y + yOffset;
						if ((nbX >= 0) && (nbY >= 0) && (nbX < width) && (nbY < height)) {
							pixelRes += kernel[xOffset + radius][yOffset + radius] * guessImg[nbX][nbY];
						}
					}
				}
				if (pixelRes == 0) {
					pixelRes = 1;
				} else if (pixelRes > 255) {
					pixelRes = 255;
				}
				mT[x][y] = originalImg[x][y] / pixelRes;
			}
		}
		newGuess = convolveDoubleNorm(mT, width, height, kernel, radius);

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				if (guessImg[x][y] != 0) {
					newGuess[x][y] *= guessImg[x][y];
				}
				if (newGuess[x][y] > 255) { // no value above maximum
					newGuess[x][y] = 255;
				}
			}
		}
		if (iterations == 0) {
			return newGuess;
		} else {
			return RLD(originalImg, newGuess, kernel, width, height, radius, iterations - 1);
		}
	}
}
