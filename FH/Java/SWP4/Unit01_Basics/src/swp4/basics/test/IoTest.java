package swp4.basics.test;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;

public class IoTest {

    // Version 1: using FIleInputStream
    public static void readContentOfFile_v1(String filename)
    {
        FileInputStream fin = null;
        try{
            int i = 0;
            fin = new FileInputStream(filename);    // würde sonst exception werfen --> check-exception! pflicht.
            do {
                i = fin.read();
                if(i != -1) {
                    System.out.print((char)i);
                }
            } while(i != -1);
        } catch(IOException e)
        {
            System.err.println("Couldn't read from file: " + filename);
            e.printStackTrace();
        }
        finally {
            try{
                if(fin != null) {
                    fin.close();
                }
            } catch(IOException e) {
                e.printStackTrace();
            }
        }
    }

    // Version 2 using try-with-resource
    public static void readContentOfFile_v2(String filename)
    {
        try(FileInputStream fin = new FileInputStream(filename)) { // try-with-resource
            int i = 0;
            do {
                i = fin.read();
                if(i != -1) {
                    System.out.print((char)i);
                }
            } while(i != -1);
        } catch (IOException e) {
            System.err.println("Could not read from file: " + filename);
            e.printStackTrace();
        } // automatically calls fin.close()
    }

    // Version 3: using bufferedreader
    public static void readContentOfFile_v3(String filename) {
        try(BufferedReader bReader = new BufferedReader(new InputStreamReader(new FileInputStream(filename)))) {
            String s;
            while((s = bReader.readLine()) != null)
            {
                System.out.println(s);
            }
        } catch (IOException e)
        {
            System.err.println("Could not read from file: " + filename);
            e.printStackTrace();
        }
    }

    public static void readContentOfFile_v4(String filename){
        try(Scanner scanner = new Scanner(new File(filename))) {
            while(scanner.hasNext())
            {
                System.out.println(scanner.nextLine());
            }
        } catch(IOException e) {
            System.err.println("Could not read from file: " + filename);
            e.printStackTrace();
        }
    }

    // Version 5: Streaming API
    public static void readContentOfFile_v5(String filename)
    {
        try {
            Files.lines(Paths.get(filename)).forEach(System.out::println);
        } catch(IOException e)
        {
            System.err.println("Could not read from file: " + filename);
            e.printStackTrace();
        }
    }

    // Version 1: FileOutputStream
    public static void writeContentOfFile_v1(String filename) {
        try(FileOutputStream fout = new FileOutputStream(filename)) {
            String toWrite = "Hello from SWP4, using FileOutputStream";
            fout.write(toWrite.getBytes());
        } catch(IOException e) {
            System.out.println("Coult not write to file: " + filename);
            e.printStackTrace();
        }
    }

    // VErsion 2: FileWriter
    public static void writeContentOfFile_v2(String filename){
        try(FileWriter fout = new FileWriter(filename)) {
            fout.write("Seas oida wos geht");
        } catch(IOException e)
        {
            System.out.println("Coult not write to file: " + filename);
            e.printStackTrace();
        }
    }

    public static void main(String[] args){
        String filename="tmp/read.txt";
        System.out.println("Version 1: using FileInputStream (nested try-catch)");
        readContentOfFile_v1(filename);
        System.out.println();

        System.out.println("Version 2: using Fileinputstream (try-with-resource)");
        readContentOfFile_v2(filename);
        System.out.println();

        System.out.println("Version 3: using BufferedReader");
        readContentOfFile_v3(filename);
        System.out.println();

        System.out.println("Version 4: using Scanner");
        readContentOfFile_v4(filename);
        System.out.println();

        System.out.println("Version 5: using Streaming API");
        readContentOfFile_v5(filename);
        System.out.println();

        System.out.println("Version 1: write using FileOutputStream");
        writeContentOfFile_v1("tmp/write_v1.txt");
        System.out.println();

        System.out.println("Version 2: write using FileWriter");
        writeContentOfFile_v2("tmp/write_v2.txt");
        System.out.println();
    }
}
