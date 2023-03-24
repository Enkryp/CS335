class ifelse {
    public static void main(String args[]) {
        // create graph
        int a=0;
        int b=1;
        int c=a;
        int d=c;
        if(a<d){
            a++;
        }
        else if(b<d) {
            a--;
        }
        else if(c<d){
            a--;
        }
        else {;
            a=a-2;
        }

    }
}
