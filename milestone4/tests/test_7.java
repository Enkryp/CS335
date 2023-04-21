public class BinarySearchExample{  
    public static void binarySearch(int arr[], int first, int last, int key){  
      int mid = (first + last)/2;  
      while( first <= last ){  
         if ( arr[mid] < key ){  
           first = mid + 1;     
         }else if ( arr[mid] == key ){  
           System.out.println(mid);  
           break;  
         }else{  
            last = mid - 1;  
         }  
         mid = (first + last)/2;  
      }  
      if ( first > last ){  
         System.out.println(-1);  
      }  
    }  
    public static void main(String args[]){  
           int arr[] = new int [10];
           for (int i = 0; i < 10; i++) {
               arr[i] = 10*i;
           }
           int key = 30;  
           int last=10-1;  
           binarySearch(arr,0,last,key);   
           
           binarySearch(arr,0,last,50);   
           
           binarySearch(arr,0,last,100);     
    }  
   }  