import ij.IJ;
import ij.ImagePlus;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

import javax.imageio.ImageTranscoder;

/**
 * Plugin that inverts a given greyscale image. (Lab 5)
 */
public class Invert_ implements PlugInFilter {

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

		// transfer function array (version 2)
		int[] invertTF = ImageTransformationFilter.getInversionTF(255);

		// apply transformation (transfer function)
		int[][] returnImg = ImageTransformationFilter.getTransformedImage(inDataArrInt,width,height,invertTF);


		// finally visualize the result image
		ImageJUtility.showNewImage(returnImg, width, height, "first plugin, invert");


	} //run

	void showAbout() {
		IJ.showMessage("About Template_...",
			"this is a PluginFilter template\n");
	} //showAbout

} //class Invert_

