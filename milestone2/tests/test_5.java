class Whileandnested {
    public static void main() {
        int a=5;
        int b=0;

        while(a>b){
            b++;
        }

        while(a>2*b){
            b=b+3;
        }

        
        while(a>4*b){
            int c=0;
            while(b>c){
                int d=0;
                while(d>b){
                    b++;
                }
                d++;
            }
            c++;
        }
    }
}
