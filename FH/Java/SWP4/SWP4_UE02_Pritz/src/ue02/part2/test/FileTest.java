package ue02.part2.test;

import ue02.part2.utility.FileUtility;

import java.io.File;
import java.sql.SQLOutput;

public class FileTest {

    public static void nonexistant() {
        System.out.println("Testing nonexistant file (applies to all utilities):");
        FileUtility.head("Iwasneverhere.txt");
        System.out.println();
    }
    public static void head_test() {
        System.out.println("Test with 6 lines and head 5: ");
        FileUtility.head("testfolder/test.txt",5);
        System.out.println();

        System.out.println("Test with 6 lines and head 30: ");
        FileUtility.head("testfolder/test.txt",30);
        System.out.println();

        System.out.println("Test with 6 lines and head without parameter:");
        FileUtility.head("testfolder/test.txt");
        System.out.println();

        System.out.println("Test with empty file and head 5: ");
        FileUtility.head("testfolder/empty.txt",5);
        System.out.println();

        System.out.println("Test with head -1: ");
        FileUtility.head("testfolder/test.txt",-1);
        System.out.println();
    }
    public static void tail_test() {
        System.out.println("Test with 6 lines and tail 3:");
        FileUtility.tail("testfolder/test.txt",3);
        System.out.println();

        System.out.println("Test with 6 lines and tail 42:");
        FileUtility.tail("testfolder/test.txt",42);
        System.out.println();

        System.out.println("Test with 6 lines and tail -1:");
        FileUtility.tail("testfolder/test.txt",-1);
        System.out.println();

        System.out.println("Test with empty file and tail 3:");
        FileUtility.tail("testfolder/empty.txt",3);
        System.out.println();
    }
    public static void test_loc() {
        System.out.println("LOC for file with 6 lines, 9 words and 19 characters:");
        FileUtility.LOC("testfolder/test.txt");
        System.out.println();

        System.out.println("LOC for empty file:");
        FileUtility.LOC("testfolder/empty.txt");
        System.out.println();
    }
    public static void test_treeSize() {
        System.out.println("Test with file:");
        FileUtility.treeSize("testfolder/test.txt");
        System.out.println();

        System.out.println("Test with src/ue02/part2 directory:");
        FileUtility.treeSize("src\\ue02\\part2");
        System.out.println();

        System.out.println("Test with nonexistant directory:");
        FileUtility.treeSize("empty");
        System.out.println();
    }


    public static void main(String[] args) {
        //nonexistant();
        //head_test();
        //tail_test();
        //test_loc();
        test_treeSize();
    }
}
