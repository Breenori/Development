
import ij.*;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;
import ij.io.FileSaver;

public class Sinogram_ implements PlugInFilter {

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about"))
        {showAbout(); return DONE;}
        return DOES_32; //float 4byte
    } //setup


    public void run(ImageProcessor ip) {
        float[] pixels = (float[])ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();

        // this filter should only work for 512x512 images
        if(width != 512 || height != 512) {
            return;
        }

        // convert from float[] to float[][]
        float[][] inDataArrFloat = convertFrom1DByteArrF(pixels, width, height);
        int sinoWidth = 512;
        int sinoHeight = 180; // = 180 degrees

        float sinoImg[][] = new float[sinoWidth][sinoHeight];
        // iterate over the image.
        for(int actDeg=0; actDeg < sinoHeight; actDeg++) {
            float[][] rotImg = Transform_.getTransformedImageF(inDataArrFloat,width,height,0,0,actDeg);
            // calculate sums for every angle (1° increments, up to 180° degrees)
            for(int x=0; x < sinoWidth; x++)
            {
                for(int y=0; y < sinoWidth; y++)
                {
                    // calculate sum of the values of the same y-coordinate
                    sinoImg[y][actDeg] += rotImg[x][y];
                }
            }
        }

        //save image as 32bit float
        float[] pixelsOut = convertFrom2DFloatArr(sinoImg,  sinoWidth,  sinoHeight);
        ImageProcessor outImgProc = new FloatProcessor(sinoWidth, sinoHeight);
        outImgProc.setPixels(pixelsOut);
        ImagePlus ip2 = new ImagePlus("", outImgProc);
        FileSaver fs = new FileSaver(ip2);
        boolean saved = fs.saveAsTiff("C:\\public\\out.tiff");
        IJ.log("image saved as tiff::" + saved);

        // normalize the image to 8bit values depending on the maximum and minimum values inside of the sinogram.
        int[][] sinoImg8bit = Utility.normalizeF(sinoImg, sinoWidth, sinoHeight, 255);
        ImageJUtility.showNewImage(sinoImg8bit, sinoWidth, sinoHeight, "Sinogram of image");

    } //run

    void showAbout() {
        IJ.showMessage("About Sinogram_...",
                "this filter creates a sinogram based on the image.\n");
    } //showAbout


    public static float[] convertFrom2DFloatArr(float[][] inArr, int width, int height) {
        int pixelIdx1D = 0;
        float[] outArray2D = new float[width * height];

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                float resultVal = inArr[x][y];
                outArray2D[pixelIdx1D] = resultVal;
                pixelIdx1D++;
            }
        }

        return outArray2D;
    }

    public static float[][] convertFrom1DByteArrF(float[] pixels, int width, int height) {

        float[][] fArray2D = new float[width][height];

        int pixelIdx1D = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                fArray2D[x][y] = (float) pixels[pixelIdx1D];
                pixelIdx1D++;
            }
        }

        return fArray2D;
    }

} //class sample32bit_

