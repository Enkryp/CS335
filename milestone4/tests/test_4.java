public class BubbleSort {

    public static void main(String args[]) {
        int n = 100;
        int array[] = new int[n];
        for(int i=0;i<n;i++)
        array[i] = n-i;
        for(int i=0; i<n-1; i++) {
            for(int j=0; j<n-i-1; j++) {
                if(array[j] > array[j+1]) {
                    int temp = array[j];
                    array[j] = array[j+1];
                    array[j+1] = temp;
                }
            }
        }
        for(int i=0; i<n; i++) {
            System.out.println(array[i]);
        }
    }
}
