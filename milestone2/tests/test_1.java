public class Fibonacci {
  public static void main(String args[]) {
      int n = 10;
      int fib[] = new int[11];

      fib[0] = 0;
      fib[1] = 1;

      for (int i = 2; i <= n; i++) {
          fib[i] = fib[i-1] + fib[i-2];
      }

      for (int i = 0; i <= n; i++) {
        System.out.println(fib);
        //TODO handle this
      }
  }
}