import java.sql.Array;
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



		//move over all pixels -> once , hot-spot at I (3,3), cf. slide 18

		for(int x = 0; x < width; x++){
			for (int y = 0; y < height; y++){
				//e.g. I with size 100x100 ->10.000 Pixels. One position if them is I(3,3)
				double sum = 0;
				double coeffsum = 0.0; //we expect 1.0 for low-pass filter (Tiefpass)

				//now iteratre all yellow mask elements in range [-radius; radius]
				for(int xOffset = -radius; xOffset <= radius; xOffset++){
					for(int yOffset = -radius; yOffset <= radius; yOffset++){
						//e.g. position M with (1,0) for (x/y) offset
						int nbX = x + xOffset;
						int nbY = y + yOffset; //for our example we get (4,3) at M

						//first check if nbX, nbY valid coordinates - check if inside the image
						if((nbX>0) && (nbY>0) && (nbX < width) && (nbY < height)){
							sum += inputImg[nbX][nbY] * kernel[xOffset + radius][yOffset + radius];
							coeffsum += kernel[xOffset + radius][yOffset + radius];
						}//
					}//for yOffset
				}//for xOffset

				returnImg [x][y] = (sum / coeffsum) ; //apply normalisation

			}
		}

		return returnImg;

	}
	
	/**
	 * convolution of input image with kernel
	 * wendet die Faltung an
	 * @param inputImg
	 * @param width
	 * @param height
	 * @param kernel double[][] kernel image
	 * @param radius kernel radius
	 * @return
	 */
	public static double[][] convolveDouble(double[][] inputImg, int width, int height, double[][] kernel, int radius) {
		double[][] returnImg = new double[width][height];

		//move over all pixels -> once , hot-spot at I (3,3), cf. slide 18

		for(int x = 0; x < width; x++){
			for (int y = 0; y < height; y++){
				//e.g. I with size 100x100 ->10.000 Pixels. One position if them is I(3,3)
				double sum = 0;

				//now iteratre all yellow mask elements in range [-radius; radius]
				for(int xOffset = -radius; xOffset <= radius; xOffset++){
					for(int yOffset = -radius; yOffset <= radius; yOffset++){
						//e.g. position M with (1,0) for (x/y) offset
						int nbX = x + xOffset;
						int nbY = y + yOffset; //for our example we get (4,3) at M


						//first check if nbX, nbY valid coordinates - check if inside the image
						if((nbX>0) && (nbY>0) && (nbX < width) && (nbY < height)){
							sum += inputImg[nbX][nbY] * kernel[xOffset + radius][yOffset + radius];
						}//
					}//for yOffset
				}//for xOffset

				returnImg [x][y] = sum;
			}
		}

		return returnImg;
	}


	public static double[][] convolveMedian(double[][] inputImg, int width, int height, double[][] kernel, int radius) {
		double[][] returnImg = new double[width][height];

			for(int x = 0; x < width; x++){
			for (int y = 0; y < height; y++){
				//e.g. I with size 100x100 ->10.000 Pixels. One position if them is I(3,3)
				double sum = 0;
				double [] values;
				 double[] array = new double[255];
				 int counter = 0;


				//now iteratre all yellow mask elements in range [-radius; radius]
				for(int xOffset = -radius; xOffset <= radius; xOffset++){
					for(int yOffset = -radius; yOffset <= radius; yOffset++){
						//e.g. position M with (1,0) for (x/y) offset
						int nbX = x + xOffset;
						int nbY = y + yOffset; //for our example we get (4,3) at M

						//first check if nbX, nbY valid coordinates - check if inside the image
						if((nbX>0) && (nbY>0) && (nbX < width) && (nbY < height)){
							array[counter] = inputImg[nbX][nbY];
							counter++;
						}

					}//for yOffset
				}//for xOffset

				values = new double[counter];
				for (int i = 0; i < counter; i++) {
					values[i] = array[i];
				}

				Arrays.sort(values);

				if((counter)%2==1){
					returnImg [x][y] = values[counter/2];
				}
				else{
					returnImg[x][y] = (values[counter/2-1]+values[counter/2])/2;
				}
			}
		}
		return returnImg;
	}

	public static double[][] getSobelVerticalKernel(){
		return new double[][]{{-1,0,1}, {-2,0,2}, {-1,0,1}};
	}

	public static double[][] getGradientHorizontalKernel(){
		return new double[][]{{0,0,0}, {0,1,-1}, {0,0,0}};
	}


	
	/**
	 * returns kernel image according to specified radius for mean low-pass filtering
	 * 
	 * @param tgtRadius
	 * @return
	 */
	public static double[][] getMeanMask(int tgtRadius) {
		int size = 2 * tgtRadius + 1; //width or height
		double[][] kernelImg = new double[size][size];

		//bei Kostanten eher mit 1.0 auf double bringen
		double meanCoef = 1.0 / (size*size);

		for(int x = 0; x<size; x++){
			for (int y = 0; y<size;  y++){
				kernelImg[x][y] = meanCoef;
			}
		}
		return kernelImg;
	}

	public static double[][] getMedianMask(int tgtRadius) {
		int size = 2 * tgtRadius + 1; //width or height
		double[][] kernelImg = new double[size][size];

		//bei Kostanten eher mit 1.0 auf double bringen
		double meanCoef = 1.0 / (size*size);

		for(int x = 0; x<size; x++){
			for (int y = 0; y<size;  y++){
				kernelImg[x][y] = meanCoef;
			}
		}

		return kernelImg;
	}


	public static double[][] RLD (double[][] original, double[][] kernel, int width, int height, int radius, int iterations){
		double[][] guess = new double[width][height];
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				guess[x][y] = 100;
				//guess[x][y] = (Math.random()%255)+1;
				//guess[x][y] = (Math.random()%255)+1;
			}
		}
		guess = convolveDoubleNorm(guess, width ,height, kernel, radius);

		double[][] mt = new double[width][height];

		for (int i = 0; i < iterations; i++) {
			//1. Schritt
			double[][] ct = convolveDoubleNorm(guess, width ,height, kernel, radius);
			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++) {
					//Division durch 0 abfangen
					if(ct[x][y] == 0.0)
						ct[x][y] = 1.0;
					mt[x][y] = original[x][y] / ct[x][y];
				}
			}

			//mt*h
			double[][] actual = convolveDoubleNorm(mt, width, height, kernel, radius);
			for (int x = 0; x < width ; x++) {
				for (int y = 0; y < height; y++) {
					//Schwarze Artefakte abfangen
					if(guess[x][y] * actual[x][y] >=255.0)
						guess[x][y] = 255.0;
					else
						guess[x][y] = guess[x][y] * actual[x][y];
				}
			}
		}
		return guess;
	}



}
