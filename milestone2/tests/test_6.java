class  For{
    public static void main() {
       int a=0;
       {
        int v=0;
        {
            int c=0;
            {
                int d=0;
            }
        }
       }
       for(int i=0;i<a;i++){
        a=a-1;
        ;
       }
       for(int i=0;i<a;i++){
        a=a-1;
        ;
       }
       for(int i=0;i<a;i++){
            for(int j=0;j<a;j++){
                // a-=1;
                a=a-1;
                ;
            }
       }
       
    }
}
