public class PrimeExample2{    
    static void checkPrime(int n){  
      int i,flag=0;      
            
      if(n==0||n==1){  
       System.out.println(0);      
      }else{  
       for(i=2;i*i<=n;i++){      
        if(n%i==0){      
         System.out.println(-1);      
         flag=1;      
         break;      
        }      
       }      
       if(flag==0)  { System.out.println(1); }  
      }//end of else  
    }  
     public static void main(String args[]){    
      checkPrime(1);  
      checkPrime(3);  
      checkPrime(17);  
      checkPrime(20);  
      checkPrime(1000000007);
    }    
    }   