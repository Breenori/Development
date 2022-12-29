import ij.*;
import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

public class ResampleNnBi_ implements PlugInFilter {


    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about")) {
            showAbout();
            return DONE;
        }
        return DOES_8G + DOES_STACKS + SUPPORTS_MASKING;
    }


    public int[][] getnearestNeighbour(int[][] inImg, int width, int height, double factor) {
        int[][] returnImage = new int[(int) ((double) width * factor + 1.0)][(int) ((double) height * factor + 1.0)];

//        double tgtWidth = (int) Math.round(width * factor);
//        //diese Methode verwendet keine math. run dung
//        double tgtHeight = (int) (height * factor + 0.5);
//        double scaleFactorW = (tgtWidth - 1.0) / (width - 1.0);
//        double scaleFactorH = (tgtHeight - 1.0) / (height - 1.0);
//        double posX = 0;
//        double posY = 0;
//        for (int x = 0; x < tgtWidth; x++) {
//            for (int y = 0; y < tgtHeight; y++) {
//                posX = x / scaleFactorW;
//                posY = y / scaleFactorH;

        for (int w = 0; w < (int) ((double) width * factor); ++w) {
            for (int h = 0; h < (int) ((double) height * factor); ++h) {
                int posXint = (int) ((double) w / factor + 0.5);
                int posYint = (int) ((double) h / factor + 0.5);

                if (posXint < 0)
                    posXint = 0;
                if (posYint < 0)
                    posYint = 0;
                if (posXint >= width)
                    posXint = width - 1;
                if (posYint >= height)
                    posYint = height - 1;

                returnImage[w][h] = inImg[posXint][posYint];
            }
        }
//            }
//        }
        return returnImage;
    }
    public int[][] getBilinear(int[][] inImg, int width, int height, double factor) {
        int[][] returnImage = new int[(int) ((double) width * factor + 1.0)][(int) ((double) height * factor + 1.0)];
        for (int w = 0; w < (int) ((double) width * factor); ++w) {
            for (int h = 0; h < (int) ((double) height * factor); ++h) {
                int x = (int) ((double) h / factor);
                int y = (int) ((double) w / factor);
                int x1 = (int) Math.ceil((double) h / factor);
                int y1 = (int) Math.ceil((double) w / factor);
                if (y1 < width && x1 < height) {
                    double x_weight = (double) h / factor - (double) x;
                    double y_weight = (double) w / factor - (double) y;
                    int a = inImg[y][x];
                    int b = inImg[y][x1];
                    int c = inImg[y1][x];
                    int d = inImg[y1][x1];
                    int pixel = (int) ((double) a * (1.0 - x_weight) * (1.0 - y_weight) + (double) b * x_weight * (1.0 - y_weight) +
                            (double) c * y_weight * (1.0 - x_weight) + (double) d * x_weight * y_weight);
                    returnImage[w][h] = pixel;
                }
            }
        }
        return returnImage;
    }

    public int[][] getDifferentialImage(int[][] nnImg, int[][] biImg, int width, int height, double factor) {
        int[][] differentialImage = new int[(int) ((double) width * factor + 1.0)][(int) ((double) height * factor + 1.0)];
        for (int w = 0; w < (int) ((double) width * factor); ++w) {
            for (int h = 0; h < (int) ((double) height * factor); ++h) {
                if ((nnImg[w][h] - biImg[w][h]) < 0) {
                    differentialImage[w][h] = (nnImg[w][h] - biImg[w][h]) * (-1);
                } else {
                    differentialImage[w][h] = nnImg[w][h] - biImg[w][h];
                }
            }
        }
        return differentialImage;
    }

    public int[][] getCheckerImage(int[][] nnImg, int[][] biImg, int width, int height, double factor) {
        int[][] checkerImg = new int[(int) ((double) width * factor + 1.0)][(int) ((double) height * factor + 1.0)];
        for (int w = 0; w < (int) ((double) width * factor); ++w) {
            for (int h = 0; h < (int) ((double) height * factor); ++h) {
                if (w < (((int) ((double) width * factor)) / 2) && h < (((int) ((double) height * factor)) / 2)
                        || w >= (((int) ((double) width * factor)) / 2) && h >= (((int) ((double) height * factor)) / 2)) {
                    checkerImg[w][h] = nnImg[w][h];
                } else {
                    checkerImg[w][h] = biImg[w][h];
                }
            }
        }
        return checkerImg;
    }
    public void run (ImageProcessor ip){
        byte[] pixels = (byte[]) ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();
        double resizeScale = 2.5;
        boolean useBilinear = false;
        boolean useNN = false;
        boolean useDif = false;
        boolean useCB = false;
        GenericDialog gd = new GenericDialog("Borders");
        gd.addSlider("Factor:", -10.0, 10.0, 1.0, 0.1);
        gd.addCheckbox("show Bilinear Interpolation", true);
        gd.addCheckbox("show NearestNeighbour Interpolation", true);
        gd.addCheckbox("show Differential of Interpolations", true);
        gd.addCheckbox("show Checker-Board", true);
        gd.showDialog();
        resizeScale = gd.getNextNumber();
        useBilinear = gd.getNextBoolean();
        useNN = gd.getNextBoolean();
        useDif = gd.getNextBoolean();
        useCB = gd.getNextBoolean();
        if (resizeScale < 0.0) {
            resizeScale = 1.0 / (0.0 - resizeScale);
        }

        int[][] resampledImg = new int[(int) ((double) width * resizeScale + 1.0)][(int) ((double) height * resizeScale + 1.0)];
        resampledImg = ImageJUtility.convertFrom1DByteArr(pixels, width, height);
        double f = resizeScale;
        int w = width;
        int h = height;


        int[][] bilinearImg = this.getBilinear(resampledImg, w, h, f);
        int[][] nnImg = this.getnearestNeighbour(resampledImg, w, h, f);
        int[][] differentialImg = this.getDifferentialImage(getnearestNeighbour(resampledImg, w, h, f), getBilinear(resampledImg, w, h, f), w, h, f);
        int[][] checkerImg =this.getCheckerImage(getnearestNeighbour(resampledImg, w, h, f), getBilinear(resampledImg, w, h, f), w, h, f);
        w = (int) ((double) w * f + 1.0);
        h = (int) ((double) h * f + 1.0);

        if (useBilinear == true) {
            ImageJUtility.showNewImage(bilinearImg, (int) ((double) width * resizeScale), (int) ((double) height * resizeScale), "Bilinear image");
        }
        if (useNN == true) {
            ImageJUtility.showNewImage(nnImg, (int) ((double) width * resizeScale), (int) ((double) height * resizeScale), "Nearest Neighbour image");
        }
        if (useDif == true) {
            ImageJUtility.showNewImage(differentialImg, (int) ((double) width * resizeScale), (int) ((double) height * resizeScale), "Differential image");
        }
        if (useCB == true) {
            ImageJUtility.showNewImage(checkerImg, (int) ((double) width * resizeScale), (int) ((double) height * resizeScale), "Checker-Board image");
        }


    }

    void showAbout () {
        IJ.showMessage("Invert Picture", "Inverts all pixel values from picture\n");
    }
}