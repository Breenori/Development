
import ij.*;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;
import ij.io.FileSaver;

public class sample32bit_ implements PlugInFilter {

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about"))
        {showAbout(); return DONE;}
        return DOES_32; //float 4byte
    } //setup


    public void run(ImageProcessor ip) {
        float[] pixels = (float[])ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();

        //vonvert from float[] to float[][]
        float[][] inDataArrFloat = convertFrom1DByteArrF(pixels, width, height);
        float minVal = Long.MAX_VALUE;
        float maxVal = Long.MIN_VALUE;
        double sum = 0.0;
        //calc min, max, avg
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                float actVal = inDataArrFloat[x][y];
                if(actVal < minVal)
                    minVal = actVal;
                if(actVal > maxVal)
                    maxVal = actVal;
                sum += actVal;
            }
        }
        sum /= (width * height);
        IJ.log("min= " + minVal + " max= " + maxVal + " avg = " + sum);

        //save image as 32bit float
        float[] pixelsOut = convertFrom2DFloatArr(inDataArrFloat,  width,  height);
        ImageProcessor outImgProc = new FloatProcessor(width, height);
        outImgProc.setPixels(pixelsOut);
        ImagePlus ip2 = new ImagePlus("", outImgProc);
        FileSaver fs = new FileSaver(ip2);
        boolean saved = fs.saveAsTiff("C:\\public\\out.tiff");
        IJ.log("image saved as tiff::" + saved);

        ImagePlus ip3 = IJ.openImage("C:\\public\\out.tiff");
        ImageProcessor iproc3 = ip3.getProcessor();
        float[] pixels3 = (float[])iproc3.getPixels();

    } //run

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is a PluginFilter template\n");
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

