public class Calculator {
    public int add(int x, int y) {
        return x + y;
    }
    
    public double add(double x, double y) {
        return x + y;
    }
    
    public int add(int x, int y, int z) {
        return x + y + z;
    }
    
    public static void main(String args[]) {
        Calculator calculator = new Calculator();
        int result1 = calculator.add(1, 2);
        double result2 = calculator.add(1.5, 2.5);
        int result3 = calculator.add(1, 2, 3);
        System.out.println("Result 1: " + result1);
        System.out.println("Result 2: " + result2);
        System.out.println("Result 3: " + result3);
    }
}
