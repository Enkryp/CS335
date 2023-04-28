//contains all the basic features contains a lot of print statement to verify the programm after running binary output is same as original java compiler
public class Car{
    static int car_number = 0;
    private int model=1;
    private int year;
    private int mileage;

    public Car(int Model, int Year, int Mileage) {
        car_number++;
        this.model = Model;
        this.year = Year;
        this.mileage = Mileage;
    }

    public  int getModel() {
        return model;
    }
    public int getYear() {
        return year;
    }

    public int getMileage() {
        return mileage;
    }
    public void setMileage(int Mileage) {
        this.mileage = Mileage;
    }
    public static int fn(int a){
        // System.out.println("Function called successfully");
        return a*2+5;
    }
    public static void pr(int a){
        System.out.println(a); 
    }
    public static int wert(int a){
        if(a==0)return 0;
        pr(a);
        return wert(a-1)+1;
    }
    public static void main(String args[]){
        //arithmetic operators
        int a=0;
        a=a+2;
        pr(a);
        int b=a-3;
        pr(b);
        int c=b*a; pr(c);
        c=a/2;
        a=a+100;
        int e=12;
        a=a/e; pr(a);
        a=-a;
        a=a+b*c/a+e-a; pr(a);
        //increments
        a++;pr(a);
        a--;pr(a);
        ++a;pr(a);
        --a;pr(a);
        // relational operators
        if(a==b) pr(1);
        else  pr(0);
        if(a!=b) pr(1);
        else pr(0);
        if(a>b) pr(1);
        else pr(0);
        if(a<b) pr(1);
        else pr(0);
        if(a>=b) pr(1);
        else pr(0);
        if(a<=b) pr(1);
        else pr(0);
        //Bitwise operator
        int bit=a&b;
        bit=a|b;
        bit=a^b;
        bit=~a;
        bit=(a<<2);
        bit =(a>>2);
        bit =(a>>>2);
        //Logical operator
        if(a==b&&b==c){pr(1);}
        else pr(0);
        if(a==b||b==c) pr(1);
        else pr(0);
        if(!(a==0))pr(1);
        else pr(0);
        //Assignment operators
        a=b;
        a+=b; pr(a);
        a-=b;a*=b;a/=b; pr(a);
        //ternary
        a=(a==b)?1:2;
        pr(a);
        //if else for and while
        for(int i=0;i<2;i++){
            if(a==b){
                int j=0;
                while(j<20){
                    a++;
                    j++;
                    pr(j);
                }
            }
            else {
                for(int l=0;l<23;l++){
                    a--;
                    pr(l);
                }
            }   
        }
        //function calling
        a=fn(a);
        pr(a);
        // recursion
        int y=wert(3);
        pr(y);
        //objects with static and private and public
        Car myCar = new Car(1001, 2015, 50000);
        pr(car_number);
        pr(myCar.getModel());
        pr(myCar.getYear());
        pr(myCar.getMileage());
        myCar.setMileage(55000);
        pr(myCar.getMileage());
        Car myCar2 = new Car(1002, 2020, 15000);
        pr(car_number);
        pr(myCar2.getModel());
        pr(myCar2.getYear());
        pr(myCar2.getMileage());
        myCar2.setMileage(20000);
        pr(myCar2.getMileage());
    }
}