
public class PrimeDetector {
    public static void main(String args[]) {
        int n = 99567;

        // int isPrime = 1;
        
        
        
        //     for (int i = 2; i*i <= n; i++) {
        //         if (n % i == 0) {
        //             isPrime = 0;
        //             break;
        //         }
        //     }
        

        if (n < 2) {
            int isPrime = 0;
            
        }else if(n==3){
            int isprime = 5;
        }
        else{
            int isprime = 10;
        } 

        System.out.println(isPrime);

    }
}