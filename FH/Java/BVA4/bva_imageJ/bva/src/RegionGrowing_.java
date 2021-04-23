import ij.IJ;
import ij.ImageJ;
import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.gui.PointRoi;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

import java.awt.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

/**
 * Applies a region growing onto a given image. This requires a ROI in form of points. (Lab 7)
 */
public class RegionGrowing_ implements PlugInFilter {

    public static final int FG_VAL = 255;
    public static final int BG_VAL = 0;
    public static final int UNPROCESSED_VAL = -1;

    private ImagePlus imp = null;

    public int setup(String arg, ImagePlus imp) {
        if (arg.equals("about")) {
            showAbout();
            return DONE;
        }

        this.imp = imp;

        // ROI = User has to set markers
        return DOES_8G + DOES_STACKS + SUPPORTS_MASKING + ROI_REQUIRED;
    } //setup

    private List<Point> getSeedPoints() {
        List<Point> seedPositions = new ArrayList<>();
        PointRoi pr = (PointRoi) imp.getRoi();
        int[] xPositions = pr.getXCoordinates();
        int[] yPositions = pr.getYCoordinates();
        Rectangle boundingBox = pr.getBounds();

        //finally fill
        for (int i = 0; i < xPositions.length; i++) {
            seedPositions.add(new Point(xPositions[i] + boundingBox.x, yPositions[i] + boundingBox.y));
        }

        return seedPositions;
    }

    public void run(ImageProcessor ip) {
        byte[] pixels = (byte[]) ip.getPixels();
        int width = ip.getWidth();
        int height = ip.getHeight();
        int[][] inDataArrInt = ImageJUtility.convertFrom1DByteArr(pixels, width, height);


        String type = "";
        GenericDialog initialgd = new GenericDialog("binary interval thresh");
        String[] items = {"Scalar based","Confidence based"};
        initialgd.addChoice("Neighbors",items,"N8");
        initialgd.showDialog();

        if(!initialgd.wasCanceled()){
            type = initialgd.getNextChoice();
        } else {
            return;
        }

        int lowerThresh = 100;
        int upperThresh = 200;
        String choice ="N8";
        double confidence = 0.1;

        GenericDialog gd = new GenericDialog("binary interval thresh");
        int[][] segmentedImage;
        if(type=="Scalar based") {
            gd.addSlider("Tlow=", 0, 255, lowerThresh);
            gd.addSlider("Tup=", 0, 255, upperThresh);
            String[] methods = {"N4", "N8"};

            gd.addChoice("Neighbors", methods, "N8");
            gd.showDialog();

            if (!gd.wasCanceled()) {
                lowerThresh = (int) gd.getNextNumber();
                upperThresh = (int) gd.getNextNumber();
                choice = gd.getNextChoice();
            }

            segmentedImage = performRegionGrowing(inDataArrInt, width, height, lowerThresh, upperThresh, choice, getSeedPoints());
            ImageJUtility.showNewImage(segmentedImage,width,height,"RG, lowerT="+lowerThresh+", upperT="+upperThresh+", neighbors="+choice);
        } else {
            gd.addNumericField("Confidence=",0);
            String[] methods = {"N4", "N8"};
            gd.addChoice("Neighbors", methods, "N8");

            gd.showDialog();
            if (!gd.wasCanceled()) {
                confidence = gd.getNextNumber();
                choice = gd.getNextChoice();
            }

            segmentedImage = performConfidenceRegionGrowing(inDataArrInt, width, height, confidence, choice, getSeedPoints());
            ImageJUtility.showNewImage(segmentedImage,width,height,"RG, confidence="+confidence+", neighbors="+choice);
        }





    } //run

    public static int[][] performRegionGrowing(int[][] inImg, int width, int height, int lowerThresh, int upperThresh, String method, List<Point> seeds) {
        int[][] returnImg = new int[width][height];
        // init with -1
        for(int x=0; x < width; x++) {
            for(int y=0; y < height; y++) {
                returnImg[x][y] = UNPROCESSED_VAL;
            }
        }

        //entrekursivieren!
        // check all seed points
        Stack<Point> processingStack = new Stack<>();
        for(Point p : seeds) {
            if(returnImg[p.x][p.y]== UNPROCESSED_VAL) {
                int actVal = inImg[p.x][p.y];

                if(actVal >= lowerThresh && actVal <= upperThresh) {
                    returnImg[p.x][p.y] = FG_VAL;
                    processingStack.push(p);
                } else {
                    returnImg[p.x][p.y] = BG_VAL;
                }
            }
        }

        // now grow the regions
        while(!processingStack.empty()) {
            Point actPos = processingStack.pop();

            // check all neighbours in N4 or N8
            for(int xOffset=-1; xOffset <= 1; xOffset++) {
                for(int yOffset=-1; yOffset <= 1; yOffset++) {
                    if(method == "N8" || xOffset==0 || yOffset==0) {
                        int nbX = actPos.x + xOffset;
                        int nbY = actPos.y + yOffset;
                        if (nbX >= 0 && nbX < width && nbY >= 0 && nbX < height && returnImg[nbX][nbY] == UNPROCESSED_VAL) {
                            int actVal = inImg[nbX][nbY];

                            if (actVal >= lowerThresh && actVal <= upperThresh) {
                                returnImg[nbX][nbY] = FG_VAL;
                                processingStack.push(new Point(nbX, nbY));
                            } else {
                                returnImg[nbX][nbY] = BG_VAL;
                            }
                        }
                    } // if
                }
            }
        }

        for(int x=0; x < width; x++) {
            for(int y=0; y < height; y++) {
                if(returnImg[x][y] == UNPROCESSED_VAL) {
                    returnImg[x][y] = BG_VAL;
                }
            }
        }

        return returnImg;
    }

    public static int[][] performConfidenceRegionGrowing(int[][] inImg, int width, int height, double confidence, String method, List<Point> seeds) {
        int[][] returnImg = new int[width][height];
        // init with -1
        for(int x=0; x < width; x++) {
            for(int y=0; y < height; y++) {
                returnImg[x][y] = UNPROCESSED_VAL;
            }
        }

        //entrekursivieren!
        // check all seed points
        Stack<Point> processingStack = new Stack<>();
        Stack<int[]> confidenceStack = new Stack<>();
        for(Point p : seeds) {
            if(returnImg[p.x][p.y]== UNPROCESSED_VAL) {
                int actVal = inImg[p.x][p.y];
                int lower = actVal - (int)(255*confidence);
                int upper = actVal + (int)(255*confidence);
                int[] tmp = {lower,upper};

                returnImg[p.x][p.y] = FG_VAL;
                processingStack.push(p);

                confidenceStack.push(tmp);
            }
        }

        // now grow the regions
        while(!processingStack.empty()) {
            Point actPos = processingStack.pop();
            int[] thresholds = confidenceStack.pop();

            // check all neighbours in N4 or N8
            for(int xOffset=-1; xOffset <= 1; xOffset++) {
                for(int yOffset=-1; yOffset <= 1; yOffset++) {
                    if(method == "N8" || xOffset==0 || yOffset==0) {
                        int nbX = actPos.x + xOffset;
                        int nbY = actPos.y + yOffset;
                        if (nbX >= 0 && nbX < width && nbY >= 0 && nbX < height && returnImg[nbX][nbY] == UNPROCESSED_VAL) {
                            int actVal = inImg[nbX][nbY];

                            if (actVal >= thresholds[0] && actVal <= thresholds[1]) {
                                returnImg[nbX][nbY] = FG_VAL;
                                processingStack.push(new Point(nbX, nbY));
                                confidenceStack.push(thresholds);
                            } else {
                                returnImg[nbX][nbY] = BG_VAL;
                            }
                        }
                    } // if
                }
            }
        }

        for(int x=0; x < width; x++) {
            for(int y=0; y < height; y++) {
                if(returnImg[x][y] == UNPROCESSED_VAL) {
                    returnImg[x][y] = BG_VAL;
                }
            }
        }

        return returnImg;
    }

    void showAbout() {
        IJ.showMessage("About Template_...",
                "this is a PluginFilter template\n");
    } //showAbout

} //class RegionGrow_