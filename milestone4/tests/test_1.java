// Demonstrates printing, common operators like +, *, % use of break.

public class PrimeDetector {
    public static void main(String args[]) {
        int n = 99567;

        int isPrime = 1;
        
        
        
            for (int i = 2; i*i <= n; i++) {
                if (n % i == 0) {
                    isPrime = 0;
                    break;
                }
            }
        

        if (n < 2) {
            isPrime = 0;
            
        } 

        System.out.println(isPrime);

    }
}