// Demonstrates support for recursion

public class EuclidsAlgorithm {

	public static int findGCD(int a, int b) {
        if (b == 0) {
            return a;
        } 
        
        if(b!=0) {
            return findGCD(b, a % b);
        }
        return 0;
    }
    public static void main(String args[]) {
        int num1 = 100;

        int num2 = 134;

        int gcd = findGCD(num1, num2);

        System.out.println(gcd);
    }

    // Euclid's division algorithm for finding the GCD of two numbers
    
}
