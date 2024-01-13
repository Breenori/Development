package swp4.basics.test;

import java.io.File;
import java.sql.SQLOutput;

public class FileTest {
    public static void main(String[] args) {
        File root = new File("/");
        if(root.isDirectory()) {
            File[] files = root.listFiles();
            for(File f : files) {
                System.out.println(f.getName() + ", size: " + f.length());
            }
        }
    }
}
