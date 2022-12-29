import java.awt.*;
import java.awt.image.BufferedImage;
import java.awt.image.DirectColorModel;
import java.util.ArrayList;
import java.util.Arrays;

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
		int[][] returnImg = new int[width][height];

		//visit every pixel
		for (int x = 0; x < width; x++){
			for (int y = 0; y < height; y++){
				int oldVal_ai = inImg[x][y]; // used as input value / index for transfer function
				int newVal_bi = transferFunction[oldVal_ai]; // b = T(a)

				returnImg[x][y] = newVal_bi;
			}
		}
		return returnImg;
	}

	public static int[][] getTransformedImageAverage(BufferedImage bfi, int width, int height) {
		int[][] returnImg = new int[width][height];
		Color c;

		for (int i = 0; i < width; i++){
			for (int j = 0; j < height; j++){
				c = new Color(bfi.getRGB(i, j));
				returnImg[i][j] = (c.getRed() + c.getGreen() + c.getBlue()) / 3;
			}
		}
		return returnImg;
	}

	public static int[][] getTransformedImageLuminosity(BufferedImage bfi, int width, int height) {
		int[][] returnImg = new int[width][height];
		Color c;
		float rFactor = 0.21f;
		float gFactor = 0.72f;
		float bFactor = 0.07f;

		for (int i = 0; i < width; i++){
			for (int j = 0; j < height; j++){
				c = new Color(bfi.getRGB(i, j));
				returnImg[i][j] = ((int) (c.getRed() * rFactor)) + ((int)(c.getGreen() * gFactor)) + ((int)(c.getBlue() * bFactor));
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
		int[] transferFunction = new int[maxVal + 1]; // due to index 0 as first element

		for (int i = 0; i <= maxVal; i++){ // loop all posisble a_i
			transferFunction[i] = maxVal - i;
		}
		return transferFunction;
	}

	public static int[] getBinaryThreshTF(int lowerThresh, int upperThresh, int maxVal, int minVal){
		int[] transferFunction = new int[maxVal +1];

		for (int i = 0; i <= maxVal; i++){
			if (i > lowerThresh && i < upperThresh){
				transferFunction[i] =minVal;
			} else {
				transferFunction[i] = maxVal;
			}
		}
		return transferFunction;
	}

	public static int[] getHistoTF(int maxVal, int[] histo, int width, int height){

		int[] transferFunction = new int[maxVal + 1];
		int ew = (width * height) / maxVal;
		int sum = 0;

		for (int i = 0; i <= maxVal; i++){
			sum = sum + histo[i];
			transferFunction[i] = Math.round(sum / ew);
		}
		return transferFunction;
	}

	public static int[] getHistoTFImproved(int maxVal, int[] histo, int width, int height){
		int[] transferFunction = new int[maxVal + 1];
		int ew = (width * height) / maxVal;
		int sum = 0;
		double ninetyPercent = (width * height) * 0.9; // 90% off all pixels

		for (int i = 0; i <= maxVal; i++){

			sum = sum + histo[i];
			int change = Math.round(sum / ew);

			if (sum < ninetyPercent){ // the last 10% percent stay the same
				transferFunction[i] = change;
			} else {
				transferFunction[i] = i;
			}
		}
		return transferFunction;
	}

	public static double[][] checkerboard(double [][] oldImg, double[][] newImg, int width, int height){

		double[][] returnImg = new double[width][height];

		for (int x = 0; x < width; x++){
			for (int y = 0; y < height; y++){
				if(x == Math.round(width / 2) || y == Math.round(height /2)){
					returnImg[x][y] = 255;
				} else if (x < Math.round(width / 2) && y < Math.round(height /2) || x > Math.round(width / 2) && y > Math.round(height /2) ){
					returnImg[x][y] = oldImg[x][y];
				} else {
					returnImg[x][y] = newImg[x][y];
				}
			}
		}
		return returnImg;
	}
}
