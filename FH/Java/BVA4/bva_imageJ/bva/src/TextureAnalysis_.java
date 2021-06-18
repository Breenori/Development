import ij.*;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class TextureAnalysis_ implements PlugInFilter {

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

        // TODO
        int scalarRange = 64; // quantization: 128: every 2nd pixel ==> [0,1,2,3] --> [0,0,1,1]
        // TODO: solve with scalar transformation
        int[] quantizationTF = ImageTransformationFilter.getQuantization(scalarRange, 256);
        int[][] quantizisedImg = ImageTransformationFilter.transformImage(inDataArrInt, quantizationTF, width, height);

        //int[][] quantizisedImg = inDataArrInt; // TODO: replace by quant.
        List<Point> translationElements = new ArrayList<>();
        translationElements.add(new Point(1,0));
        translationElements.add(new Point(0,-1));
        translationElements.add(new Point(1,1));

        // calc co-occurrence-matrix as p_i,j
        double[][] cMatrix = calcCooccurrenceMatrix(quantizisedImg, width, height, translationElements, scalarRange);

        double[][] scaledCMatrix = getScaledImage(cMatrix,scalarRange,scalarRange,scalarRange);
        ImageJUtility.showNewImage(scaledCMatrix, scalarRange, scalarRange, "scaled Co-oc Matrix");

        //calculated entropy
        double entropy = getEntropy(cMatrix, scalarRange);
        IJ.log("entropy = "+entropy);

        //calculated homogenity
        double homogenity = getHomogenity(cMatrix, scalarRange);
        IJ.log("homogenity = "+homogenity);
    } //run

    public static double[][] calcCooccurrenceMatrix(int[][] inImg, int width, int height, List<Point> translationElements, int scalarRange) {
        double[][] cMatrix = new double[scalarRange][scalarRange];

        int numOfEntries = 0;
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                int actVal = inImg[x][y];

                // now calc all the neighbors
                for(Point nbPos : translationElements) {
                    int nbX = x + nbPos.x;
                    int nbY = y + nbPos.y;
                    // check if neighbor inside image
                    if(nbX >= 0 && nbX < width && nbY>=0 && nbY < height) {
                        int nbVal = inImg[nbX][nbY];
                        cMatrix[actVal][nbVal]++;
                        numOfEntries++;
                    }
                }
            }
        }

        // finally scale the cMatrix to percentage values in [0;1]
        for(int x = 0; x < scalarRange; x++) {
            for(int y = 0; y < scalarRange; y++) {
                cMatrix[x][y] /= numOfEntries;
            }
        }

        IJ.log("final sum of entries = "+numOfEntries);
        return cMatrix;
    }

    double[][] getScaledImage(double[][] inImgDbl, int width, int height, int maxScalarVal) {
        // target: get all values into range [0;maxVal]
        double minVal = Double.MAX_VALUE;
        double maxVal = Double.MIN_VALUE;
        double[][] resImg = new double[width][height];

        for(int x=0; x < width; x++) {
            for(int y=0; y < height; y++) {
                double currVal = inImgDbl[x][y];
                if(currVal < minVal) {
                    minVal = currVal;
                }
                if(currVal > maxVal) {
                    maxVal = currVal;
                }
            }
        }

        double scaleFactor = (maxVal - minVal) / ((double)maxScalarVal);
        for(int x=0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                double currVal = inImgDbl[x][y];
                resImg[x][y] = (currVal - minVal) / scaleFactor;
            }
        }

        return resImg;
    }

    public double getEntropy(double[][] cMatrix, int scalarRange) {
        double sum = 0.0;

        for(int x = 0; x < scalarRange; x++) {
            for(int y = 0; y < scalarRange; y++) {
                double p_ij = cMatrix[x][y];
                if(p_ij > 0.0) {
                    sum += p_ij * Math.log(p_ij);
                }
            }
        }

        return -sum;
    }

    public double getHomogenity(double[][] cMatrix, int scalarRange) {
        double sum = 0.0;

        for(int x = 0; x < scalarRange; x++) {
            for(int y = 0; y < scalarRange; y++) {
                double p_ij = cMatrix[x][y];

                sum += p_ij / (1 + Math.abs(x-y));
            }
        }

        return sum;
    }

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is TextureAnalysis\n");
    } //showAbout

} //class FilterTemplate_

