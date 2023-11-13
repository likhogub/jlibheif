package ru.likhogub;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Paths;

public class HelloJNI {

    static {
        System.load("/home/olikhogub/CLionProjects/jlibheif/build/libHelloJNI.so");
    }

    private native ByteBuffer sayHello(byte[] bytes);

    public static void main(String[] args) throws IOException {
        byte[] array = Files.readAllBytes(Paths.get("/home/olikhogub/Downloads/image1.heic"));
        ByteBuffer resultByteBuffer = new HelloJNI().sayHello(array);
        byte[] result = new byte[resultByteBuffer.remaining()];
        resultByteBuffer.get(result, 0, result.length);
        Files.write(Paths.get("/home/olikhogub/Downloads/sample1.png"), result);
    }
}
