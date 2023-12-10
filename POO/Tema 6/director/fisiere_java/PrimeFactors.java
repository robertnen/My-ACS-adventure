/*
Java program that asks the user for an integer and then prints out all its prime factors.
 For example, when the user enters 150, the program should print: 2 3 5 5
*/

import java.util.Scanner;

public class PrimeFactors {

	public static boolean isPrime(int k) {
		if (k<2) {
			return false;		// 1 has only 1 unique divisor
		} // end if			// so it's not prime

		int sqrt = (int) Math.sqrt(k);	// calculate square root of k

		for (int j=2; j<=sqrt; j++) {	// iterate from 2 to root of k
			if (k%j==0) {		// if j is a divisor of k...
				return false;	// ...k is not prime
			} // end if
		} // end for

		return true;			// k is prime
	} // end isPrime

	public static String getFactors(int n) {
		String factors = "";
		int nCopy=n;
		int i=2;
		while (i<nCopy) {
			while (isPrime(i) && n%i == 0) {
				factors += i+" ";
				n /= i;
			} // while
			i++;
		} // while
		if (factors.equals("")) factors = "prime - no factors";
		return factors;
	} // getFactors

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		System.out.print("Enter an integer: ");
		int n = in.nextInt();
		System.out.println( getFactors( n));
	} // main()

} // class PrimeFactors