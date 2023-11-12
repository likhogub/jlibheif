package ru.likhogub;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;

public class HelloJNI {

    static {
        System.load("/home/olikhogub/CLionProjects/jlibheif/build/libHelloJNI.so");
    }

    private native byte[] sayHello(byte[] bytes);

    public static void main(String[] args) throws IOException {
        byte[] array = Files.readAllBytes(Paths.get("/home/olikhogub/Downloads/sample1.heic"));
        byte[] result = new HelloJNI().sayHello(array);
        Files.write(Paths.get("/home/olikhogub/Downloads/sample1.png"), result);
    }
}
