    class If_else_for
    {  
        public static int function1(){
            int j=0;
            int k=j;
            return k+j;
        }
        public static void main()   
        {  
            int a=0;
            int n=a+5;
            for(int i=0;i<n;i++){
                int j=i;
                if(i<j)break;
                else j++;
                if(i<a){
                    break;
                }
                else {
                    a++;
                }
            }
            function1();
        }  
    }  