package ue02.part2.test;

import ue02.part2.utility.FileUtility;

import java.io.File;

public class FileTest {
    public static void main(String[] args) {
        FileUtility.head("testfolder/test.txt",5);
        FileUtility.LOC("testfolder/test.txt");
        //FileUtility.treeSize("src");
    }
}
