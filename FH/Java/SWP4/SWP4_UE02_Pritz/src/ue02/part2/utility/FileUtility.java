package ue02.part2.utility;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Locale;
import java.util.Scanner;

public class FileUtility {

    private static ArrayList<TreeInfo> treeInfoList = new ArrayList<>();

    public static void head(String path, int count) {
        try(Scanner scanner = new Scanner(new File(path))) {
            if(count > 0) {
                while (scanner.hasNext() && count > 0) {
                    System.out.println(scanner.nextLine());
                    count--;
                }
            }
        } catch(IOException e) {
            System.err.println("Could not read from file: " + path);
            e.printStackTrace();
        }
    }

    public static void tail(String path, int count) {
        try {
            if(count > 0) {
                Object[] lines = Files.lines(Paths.get(path)).toArray();

                int position = lines.length < count ? 0 : lines.length-count;

                while (position<lines.length) {
                    System.out.println(lines[position]);
                    position++;
                }
            }
        } catch(IOException e) {
            System.err.println("Could not read from file: " + path);
            e.printStackTrace();
        }
    }

    public static void LOC(String path) {
        try(Scanner scanner = new Scanner(new File(path))) {
            int linecount = 0;
            int wordcount = 0;
            int charcount = 0;

            String line;
            while (scanner.hasNext()) {
                line = scanner.nextLine();
                linecount++;

                boolean word = false;
                for(char c:line.toCharArray()) {
                    if(!Character.isSpaceChar(c)) {
                        charcount++;
                        if(!word) {
                            wordcount++;
                            word = true;
                        }
                    } else {
                        word = false;
                    }
                }
            }

            System.out.println("Printing statistics for file: "+path);
            System.out.println("Lines: "+linecount);
            System.out.println("Words: "+wordcount);
            System.out.println("Chars: "+charcount);

        } catch(IOException e) {
            System.err.println("Could not read from file: " + path);
            e.printStackTrace();
        }
    }

    public static void treeSize(String path) {
        long totalSize = treeSizeWorker(path,0);
        if(treeInfoList.size()==1) {
            System.out.println("File "+path+": "+totalSize+" bytes");
        } else if (treeInfoList.size()>1) {
            System.out.println("Directory " + path + ": " + totalSize+" bytes");
            printTree();
        }
        treeInfoList.clear();
    }
    private static long treeSizeWorker(String path, int depth) {
        File root = new File(path);

        if(root.isDirectory()) {
            File[] files = root.listFiles();
            int bytes = 0;
            for(File f : files) {
                TreeInfo treeInfo = new TreeInfo(f.getName(), depth);
                treeInfoList.add(treeInfo);
                int index = treeInfoList.size()-1;
                long elementSize = treeSizeWorker(f.getPath(), depth+1);
                treeInfoList.get(index).setSize(elementSize);
                bytes += elementSize;
            }
            return bytes;
        } else {
            return root.length();
        }
    }
    private static void printTree() {
        for(TreeInfo ti : treeInfoList) {
            String line = "";
            for(int i=0; i<ti.getDepth(); i++) {
                line += "\t";
            }
            line += ti.getName() + " - " + String.format(Locale.GERMAN,"%,d",ti.getSize());
            System.out.println(line);
        }
    }

    private static class TreeInfo {
        private String name;
        private long size;
        private int depth;

        public TreeInfo(String name, int depth) {
            this.name = name;
            this.depth = depth;
        }

        public void setSize(long size) {
            this.size = size;
        }

        public String getName() {
            return this.name;
        }

        public long getSize() {
            return this.size;
        }

        public int getDepth() {
            return this.depth;
        }
    }

}
