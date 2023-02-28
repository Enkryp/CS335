public class CopyArray {    
    public static void main(String args[]) {        
                
        int  arr1[]= new int [] {1, 2, 3, 4, 5};     
            
        int arr2[] = new int[arr1.length];    
        
        for (int i = 0; ;) {     
            arr2[i] = arr1[i];     
        }      
            
        System.out.println("Elements of original array: ");    
        for (int i = 0;;) {     
            System.out.print(arr1[i] + " ");    
        }     
            
        System.out.println();    
            
        
        System.out.println("Elements of new array: ");    
        for (int i = 0; i < arr2.length(); i++) {     
            System.out.print(arr2[i] + " ");    
        }     
    }    
}    