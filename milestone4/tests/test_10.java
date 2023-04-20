class EuclidsAlgorithm {
    int a1 = 100;
    int b1 = 134;
	public int f1(int a, int b) {
        return a+b;
    }

}

public class E2 {

    int aa=0;
    static int bb=10;

    public static void main(String args[]) {
    E2 e2 = new E2();
    EuclidsAlgorithm euclidsAlgorithm = new EuclidsAlgorithm();

    e2.aa= euclidsAlgorithm.f1(euclidsAlgorithm.a1, euclidsAlgorithm.b1);

    System.out.println(bb+e2.aa);
    
    
    }

}