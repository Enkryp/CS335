class Whileandnested {
    public static void main() {
        int a=5;
        int b=0;
        while(a>b){
            b++;
        }
        while(a>b){
            b++;
        }
        while(a>b){
            b++;
        }
        while(a>b){
            b++;
        }
        while(a>b){
            b++;
        }
        while(a>b){
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
