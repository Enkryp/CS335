// Demonstrates construcotrs, static and non-static field variables, use of this keyword 

public class Car {
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

    public private int getModel() {
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

    public static void main(String args[]) {
        Car myCar = new Car(1001, 2015, 50000);
        System.out.println(car_number);
        System.out.println(myCar.getModel());
        System.out.println(myCar.getYear());
        System.out.println(myCar.getMileage());

        myCar.setMileage(55000);
        System.out.println(myCar.getMileage());
        // System.out.println();
        Car myCar2 = new Car(1002, 2020, 15000);
        System.out.println(car_number);
        System.out.println(myCar2.getModel());
        System.out.println(myCar2.getYear());
        System.out.println(myCar2.getMileage());

        myCar2.setMileage(20000);
        System.out.println(myCar2.getMileage());
    }
}

