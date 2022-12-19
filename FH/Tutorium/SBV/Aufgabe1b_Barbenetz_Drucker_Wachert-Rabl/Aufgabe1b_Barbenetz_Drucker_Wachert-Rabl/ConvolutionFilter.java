

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

		//move over all pixels ==> once, hot-spot at I(3,3), cf. slide 18
		for(int x = 0; x < width; x++) {
			for(int y = 0; y < height; y++) {
				//e.g. I with size 100x100 ==> 10,000 pixel. One position of them is I(3,3)
				double sum = 0;
				double coeffSum = 0.0; //we expect 1.0 for low-pass filters (Tiefpass)

				//now iterate all yellow mask elements in range [-radius;radius]
				for(int xOffset = -radius; xOffset <= radius; xOffset++) {
					for(int yOffset = -radius; yOffset <= radius; yOffset++) {
						//e.g. position M with (1,0) for x/y offset
						int nbX = x + xOffset;
						int nbY = y + yOffset; //for our example we get (4,3) at M

						//first check if nbX, nbY valid coordinates!!! check if inside the image
						if((nbX >= 0) && (nbY >= 0) && (nbX < width) && (nbY < height)) {
							sum += inputImg[nbX][nbY] * kernel[xOffset + radius][yOffset + radius];
							coeffSum += kernel[xOffset + radius][yOffset + radius];
						} //valid pos

					} //for yOffset
				} //for xOffset

				returnImg[x][y] = (sum / coeffSum); //apply normalization

			} //for y
		} //for x


		return returnImg;
	}

	public static double[][] getSobelVerticalKernel() {
		return new double[][]{{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
	} //getVerticalSobelKernel

	public static double[][] getGradientHorizontalKernel() {
		return new double[][]{{0, 0, 0}, {0, 1, -1}, {0, 0, 0}};
	} //getGradientHorizontalKernel

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
	public static double[][] convolveDouble(double[][] inputImg, int width, int height,
											double[][] kernel, int radius) {
		double[][] returnImg = new double[width][height];
		
		//move over all pixels ==> once, hot-spot at I(3,3), cf. slide 18
		for(int x = 0; x < width; x++) {
			for(int y = 0; y < height; y++) {
              //e.g. I with size 100x100 ==> 10,000 pixel. One position of them is I(3,3)
			  double sum = 0;

			  //now iterate all yellow mask elements in range [-radius;radius]
			  for(int xOffset = -radius; xOffset <= radius; xOffset++) {
				  for(int yOffset = -radius; yOffset <= radius; yOffset++) {
                     //e.g. position M with (1,0) for x/y offset
					 int nbX = x + xOffset;
					 int nbY = y + yOffset; //for our example we get (4,3) at M

					 //first check if nbX, nbY valid coordinates!!! check if inside the image
					 if((nbX >= 0) && (nbY >= 0) && (nbX < width) && (nbY < height)) {
						 sum += inputImg[nbX][nbY] * kernel[xOffset + radius][yOffset + radius];
					 } //valid pos

				  } //for yOffset
			  } //for xOffset

			  returnImg[x][y] = sum;
			} //for y
		} //for x

		return returnImg;
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

		double meanCoef = 1.0 / (size * size);
		for(int x = 0; x < size; x++) {
			for(int y = 0; y < size; y++) {
				kernelImg[x][y] = meanCoef;
			} //for y
		} //for x
		
		return kernelImg;
	}
		
}
