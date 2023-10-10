import java.util.Random;
import java.util.Vector;

public class Main {
   public Main() {
   }

   private static int task1(Vector<Integer> var0, int var1) {
      int var2 = 0;

      while(var0.indexOf(var1) != -1) {
         var2++;
         var0.remove(var0.indexOf(var1));
      }

      return var2;
   }
   
   public static void task2(Vector<Integer> arr) {
        int maxVal = -1, minVal = 21, posMin = 0;
        float mean = 0;

        int pos = 0;
        for(int num : arr) {
            if(num > maxVal) maxVal = num;
            if(num < minVal) {
                minVal = num;
                posMin = pos;
            }
            mean += num;
            pos++;
        }

        mean /= 20;
        System.out.println("Max: " + maxVal);
        System.out.println("PosMin: " + posMin);
        System.out.println("Mean: " + mean);

   }

   public static void main(String[] var0) {
      Vector<Integer> var1 = new Vector<Integer>(20);
      Random var2 = new Random();

      int var3;
      for(var3 = 0; var3 < 20; ++var3) {
         var1.add(var3, var2.nextInt(10));
      }

      System.out.println("Arr = " + var1);
      var3 = var2.nextInt(10);
      System.out.println("\nx = " + var3);
      task2(var1);
      System.out.println(task1(var1, var3));
      System.out.println("Arr = " + var1);
   }
}
