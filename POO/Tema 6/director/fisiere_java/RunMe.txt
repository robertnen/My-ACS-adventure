/*
 Java program with the name RunMe that will take input from the keyboard and will count the number
 of elements that are numbers(int) and the number of elements that are not numbers. The count will stop
 when we give as an input zero 0. Then the programm will display the results and will terminate.
 We also have to develop a class named Counter. We also have to use the class named Scanner. 
*/

import java.util.Scanner;

public class RunMe {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		Counter counter = new Counter();
		String strInput;
		int n;
		do {
			System.out.print("Enter element (numeric/non-numeric) (zero to quit): ");
			strInput = in.nextLine();
			try {
				n = Integer.parseInt(strInput);
				if (n==0) break;
				counter.incrementNums();
			} catch (NumberFormatException x) {
				counter.incrementNonNums();
			}
		} while (true);
		System.out.println("Number of numeric elements = "+counter.getNums());
		System.out.println("Number of non-numeric elements = "+counter.getNonNums());
	} // main()

} // class RunMe

class Counter {

	private int numCount;
	private int nonNumCount;

	public Counter() {
		numCount = 0;
		nonNumCount = 0;
	}

	public void incrementNums() {
		numCount++;
	}

	public void incrementNonNums() {
		nonNumCount++;
	}

	public int getNums() {
		return numCount;
	}

	public int getNonNums() {
		return nonNumCount;
	}
} // class Counter