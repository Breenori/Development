import ij.IJ;
import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

/**
 * Applies a sobel edge detection (high-pass filter) onto a given image. (Lab 6)
 */
public class SobelFilter_ implements PlugInFilter {

   public int setup(String arg, ImagePlus imp) {
		if (arg.equals("about"))
			{showAbout(); return DONE;}
		return DOES_8G+DOES_STACKS+SUPPORTS_MASKING;
	} //setup



	public void run(ImageProcessor ip) {
		byte[] pixels = (byte[])ip.getPixels();
		int width = ip.getWidth();
		int height = ip.getHeight();
		int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        double[][] inDataArrDbl =
        		ImageJUtility.convertToDoubleArr2D(inDataArrInt, width, height);

		GenericDialog gd = new GenericDialog("Sobel filter");
		gd.addCheckbox("Horizontal", true);
		gd.addCheckbox("Vertical", true);
		gd.addCheckbox("Diagonal 1 (Top Left to Bottom Right)", true);
		gd.addCheckbox("Diagonal 2 (Bottom Left to Top Right)", true);

		boolean horCb = false;
		boolean verCb = false;
		boolean dia1Cb = false;
		boolean dia2Cb = false;

		// let the user select which sobel filter to execute
		gd.showDialog();
		if(!gd.wasCanceled()) {
			horCb = gd.getNextBoolean();
			verCb = gd.getNextBoolean();
			dia1Cb = gd.getNextBoolean();
			dia2Cb = gd.getNextBoolean();
		}



        double maxmag = 0;
        double minmag = Double.MAX_VALUE;
        // define sobel-masks
        int[][] sobelKernelX = {{1,0,-1},
								{2,0,-2},
								{1,0,-1}};
		int[][] sobelKernelY = {{1,2,1},
								{0,0,0},
								{-1,-2,-1}};

		int[][] sobelKernelD1 = {	{0,1,2},
									{-1,0,1},
									{-2,-1,0}};
		int[][] sobelKernelD2 = {	{-2,-1,0},
									{-1,0,1},
									{0,1,2}};

		double[][] resultImg = new double[width][height];
		for(int x=0; x < width; x++) {
			for(int y=0; y < height; y++) {
				double sx=0;
				double sy=0;
				double sd1=0;
				double sd2=0;

				// depending on the user input, calculate the sobel-values
				if(horCb) { sx = applyMaskToPixel(inDataArrDbl, sobelKernelX, x, y); }
				if(verCb) { sy = applyMaskToPixel(inDataArrDbl, sobelKernelY, x, y); }
				if(dia1Cb) { sd1 = applyMaskToPixel(inDataArrDbl, sobelKernelD1, x, y); }
				if(dia2Cb) { sd2=applyMaskToPixel(inDataArrDbl, sobelKernelD2, x, y); }
				// then, using the sobel values, calculate the magnitude
				double mag = Math.sqrt(sx * sx + sy * sy + sd1 * sd1 + sd2 * sd2);
				resultImg[x][y] = mag;

				// determine maximum and minimum magnitude for normalizing
				if(mag > maxmag) {
					maxmag = mag;
				}
				if(mag < minmag) {
					minmag = mag;
				}
			}
		}
		maxmag -= minmag;
		double scale = maxmag/255;
		// normalize the image for valid constraints
		for(int x=0; x < width; x++) {
			for(int y=0; y < height; y++) {
				resultImg[x][y] = (resultImg[x][y]-minmag)/scale;
			}
		}

        ImageJUtility.showNewImage(resultImg, width, height, "Sobel filtered image");
	} //run

	private double applyMaskToPixel(double[][] inImg,  int[][] mask, int x, int y) {
   		int sum = 0;
		for(int xoff=0; xoff < mask.length; xoff++) {
			for(int yoff=0; yoff < mask[0].length; yoff++) {
				try {
					// for each pixel, multiply its value with the corresponding mask value and sum it up
					sum += inImg[x + xoff - 1][y + yoff - 1] * mask[xoff][yoff];
				} catch(Exception e) {

				}
			}
		}
		return sum;
	}

	void showAbout() {
		IJ.showMessage("About Sobel_...",
			"this is an edge detection algorithm using sobel filters.\n");
	} //showAbout

} //class Mean_

