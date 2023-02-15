import ij.*;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

import java.awt.*;
import java.util.Stack;
import java.util.Vector;

import ij.gui.GenericDialog;
import ij.gui.PointRoi;


public class RegionGrowing_ implements PlugInFilter {

    public static int BG_VAL = 0;  //background value ==> not the target objects
    public static int FG_VAL = 255; //segmented object
    public static int UNPROCESSED = -1; //not processed so far

    ImagePlus imPlus = null;
    int bgCount = 0;
    int fgCount = 0;

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about")) {
            showAbout();
            return DONE;
        }
        imPlus = imp;
        return DOES_8G + ROI_REQUIRED;
    } //setup

    public static Vector<Point> GetSeedPositions(ImagePlus ip) {
        Vector<Point> seedPositions = new Vector<Point>();
        PointRoi pr = (PointRoi) ip.getRoi();
        int[] xCoords = pr.getXCoordinates();
        int[] yCoords = pr.getYCoordinates();
        int numOfPoints = xCoords.length;
        Rectangle boundingBox = pr.getBounds();

        for (int i = 0; i < numOfPoints; i++) {
            seedPositions.add(new Point(xCoords[i] + boundingBox.x, yCoords[i] + boundingBox.y));
        }

        return seedPositions;
    }


    public int[][] segmentImage(int[][] inDataArrInt, int threshMax, int threshMin, int width, int height, String n) {
        int[][] segmentedImg = new int[width][height];
        bgCount = 0;
        fgCount = 0;

        //all pixels are unprocessed
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                segmentedImg[x][y] = UNPROCESSED;
            }
        }

        Stack<Point> procStack = new Stack<>();
        // let's check all the seeds
        for (Point currSeed : GetSeedPositions(this.imPlus)) {
            if (segmentedImg[currSeed.x][currSeed.y] == UNPROCESSED) { // still unprocessed
                int actVal = inDataArrInt[currSeed.x][currSeed.y];
                if (actVal >= threshMin && actVal <= threshMax) { //interval matching
                    segmentedImg[currSeed.x][currSeed.y] = FG_VAL;
                    fgCount++;
                    procStack.push(currSeed);
                } else {
                    segmentedImg[currSeed.x][currSeed.y] = BG_VAL;
                    bgCount++;
                }
            }
        }

        // let's use N8
        if (n == "N8") {
            while (!procStack.empty()) {
                Point actPos = procStack.pop();
                //let's check the neighbours
                for (int xOffset = -1; xOffset <= 1; xOffset++) {
                    for (int yOffset = -1; yOffset <= 1; yOffset++) {
                        int nbx = actPos.x + xOffset;
                        int nby = actPos.y + yOffset;

                        //check if insight the image
                        if (nbx >= 0 && nbx < width && nby >= 0 && nby < height) { //if still inside the image
                            if (segmentedImg[nbx][nby] == UNPROCESSED) { //if still unprocessed
                                int nbVal = inDataArrInt[nbx][nby];
                                if (nbVal >= threshMin && nbVal <= threshMax) { //is inside the interval
                                    segmentedImg[nbx][nby] = FG_VAL;
                                    fgCount++;
                                    procStack.push(new Point(nbx, nby));
                                } else {
                                    segmentedImg[nbx][nby] = BG_VAL;
                                    bgCount++;
                                }
                            }
                        }
                    }
                }
            }
        }

        if (n == "N4") {
            int[] xOffset = new int[]{-1, 0, 0, 1};
            int[] yOffset = new int[]{0, -1, 1, 0};

            while (!procStack.empty()) {
                Point actPos = procStack.pop();
                //let's check the neighbours
                for (int i = 0; i < xOffset.length; i++) {
                    int nbx = actPos.x + xOffset[i];
                    int nby = actPos.y + yOffset[i];

                    //check if insight the image
                    if (nbx >= 0 && nbx < width && nby >= 0 && nby < height) { //if still inside the image
                        if (segmentedImg[nbx][nby] == UNPROCESSED) { //if still unprocessed
                            int nbVal = inDataArrInt[nbx][nby];
                            if (nbVal >= threshMin && nbVal <= threshMax) { //is inside the interval
                                segmentedImg[nbx][nby] = FG_VAL;
                                fgCount++;
                                procStack.push(new Point(nbx, nby));
                            } else {
                                segmentedImg[nbx][nby] = BG_VAL;
                                bgCount++;
                            }
                        }
                    }
                }
            }
        }

        //clean-up. all UNPROCESSED
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                if (segmentedImg[x][y] == UNPROCESSED) {
                    segmentedImg[x][y] = BG_VAL;
                }
            }
        }
        System.out.println("size of stack = " + procStack.size());
        System.out.println("FG count = " + fgCount + " BG count = " + bgCount);
        return segmentedImg;

    }

    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[]) ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();

        int threshMin = 100;
        int threshMax = 200;


        //for interval thresh: request min and max thresh from user
        GenericDialog gd = new GenericDialog("interval threshold for RG");
        gd.addSlider("Tmin", 0, 255, threshMin);
        gd.addSlider("Tmax", 0, 255, threshMax);

        gd.showDialog();
        if (gd.wasCanceled()) {
            return;
        }

        threshMin = (int) (gd.getNextNumber() + 0.5);
        threshMax = (int) (gd.getNextNumber() + 0.5);


        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);


        int[][] segmentedImg4 = segmentImage(inDataArrInt, threshMax, threshMin, width, height, "N4");
        int[][] segmentedImg8 = segmentImage(inDataArrInt, threshMax, threshMin, width, height, "N8");

        ImageJUtility.showNewImage(segmentedImg4, width, height, "N4: tmin=" + threshMin + " tmax=" + threshMax + " FGcount=" + fgCount + " BGcount= " + bgCount);
        ImageJUtility.showNewImage(segmentedImg8, width, height, "N8: tmin=" + threshMin + " tmax=" + threshMax + " FGcount=" + fgCount + " BGcount= " + bgCount);

    } //run

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is Region Growing algorithm\n");
    } //showAbout

} //class RegionGrowing_



