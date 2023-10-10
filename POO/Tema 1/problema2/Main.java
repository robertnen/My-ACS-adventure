package problema8;

import java.util.Arrays;

public class Main {
    public static void main(String args[]) {
        final int MAX_SIZE = 10;
        double[] arr = new double[MAX_SIZE];

        for(int i = 0; i < MAX_SIZE; i++)
            arr[i] = Math.random();

        Arrays.sort(arr);
        System.out.println(Arrays.binarySearch(arr, arr[4]));

        for(double num : arr)
            System.out.print("" + num + " ");
    }
}
