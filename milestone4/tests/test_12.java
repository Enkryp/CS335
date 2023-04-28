// 4D array declaration and array passing in functions.
public class  MultiArrayAccess{
    public static void printarray(int a[],int n){
        for(int i=0;i<n;i++){
            System.out.println(a[i]);
        }
    }
    public static void main(String args[]) {
        int a [][][][]= new int [10][100][20][4];
        int b = a[0][0][0][0];
        a[4][5][2][0] = 20;

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 100; j++) {
                for(int k=0;k<20;k++){
                    for(int l=0;l<4;l++){
                        a[i][j][k][l] = i + j*k+l;
                        
                    }
                }
            }
        }
        System.out.println(a[4][5][2][1]);
        int c[]=new int [7];
        for(int i=0;i<7;i++){
            c[i]=a[i][i][2][3]*2;
        }
        printarray(c,7);
    }
}