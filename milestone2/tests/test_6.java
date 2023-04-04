public class  MultiArrayAccess{
    public static void main(String args[]) {

        int a [][]= new int [10][100];
        int b = a[0][0];
        a[4][5] = b;

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 100; j++) {
                a[i][j] = i + j;
            }
        }


    }

}