// Demonstrates 3-dimensional array creation and access, nested for-loops

public class  MultiArrayAccess{
    public static void main(String args[]) {

        int a [][][]= new int [10][100][20];
        int b = a[0][0][0];
        a[4][5][2] = 20;

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 100; j++) {
                for(int k=0;k<20;k++)
                a[i][j][k] = i + j*k;
            }
        }
        System.out.println(a[4][5][2]);

    }

}