package ro.utcn;

import java.util.Arrays;
import java.util.List;

public class Main {
    final int CONSTANT = 5;

    public static void main(String[] args) {
        System.out.println("Hello, world!");
        List<String> stringList = Arrays.asList(args);
        sortStrings(stringList);
        printStrings(stringList);
    }

    public static void printStrings(List<String> stringList) {
        for (String s : stringList) {
            System.out.println(s);
        }
    }

    public static void sortStrings(List<String> stringList) {
        stringList.sort(String::compareTo);
    }
}