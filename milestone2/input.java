class FibonacciExample1 {
    
    public static void main(String args[]) {
        int n1 = 0, n2 = 1, n3, i, count = 10;
        System.out.print(n1 + " " + n2);// printing 0 and 1
        for (i = 2; i < count; ++i)// loop starts from 2 because 0 and 1 are already printed
        {
            n3 = n1 + n2;
            System.out.println(" " + n3);
            n1 = n2;
            n2 = n3;
        }
        System.out.println(function1(n1, n2));
        System.out.println(function3(n1, n2));
    }
    {}

    public static long function1(int a, int b) {
        return function2(a, b);
    }

    public static int function2(int a, int b) {
        return a + b;

    }

    public static float function3(int a, int b) {
        return a + b;
    }
    public int function(int a){
        System.out.println(c);
        return a;
    }
    int c=0;

}