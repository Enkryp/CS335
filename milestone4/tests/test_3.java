// Demonstartes inter class interaction between two classes

class Rectangle {
    int length;
    int width;

 
    public int getLength() {
        return length;
    }

    public int getWidth() {
        return width;
    }

    public int getArea() {
        return length * width;
    }
}

 public class Main{
    public static void main(String args[]) {
        int length = 10;

        int width = 20;

        Rectangle rectangle1 = new Rectangle();
        rectangle1.length = length;
        rectangle1.width = width;

        int area = rectangle1.getArea();

        System.out.println(area);
    }
}
