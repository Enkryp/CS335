// Define a base class Animal with some properties and methods
class Animal {
    String name;
    int age;
    
    // Constructor for creating a new Animal instance
    public Animal(String name, int age) {
        this.name = name;
        this.age = age;
    }
    
    // Method for making the Animal speak
    public void speak() {
        System.out.println("Animal " + name + " speaks!");
    }
}

// Define a subclass Cat that extends the Animal class
class Cat extends Animal {
    // Constructor for creating a new Cat instance
    public Cat(String name, int age) {
        super(name, age);
    }
    
    // Override the speak method to make the Cat meow
    @Override
    public void speak() {
        System.out.println("Cat " + name + " meows!");
    }
    
    // Method for making the Cat scratch
    public void scratch() {
        System.out.println("Cat " + name + " scratches!");
    }
}

// Define a subclass Dog that extends the Animal class
class Dog extends Animal {
    // Constructor for creating a new Dog instance
    public Dog(String name, int age) {
        super(name, age);
    }
    
    // Override the speak method to make the Dog bark
    @Override
    public void speak() {
        System.out.println("Dog " + name + " barks!");
    }
    
    // Method for making the Dog fetch
    public void fetch() {
        System.out.println("Dog " + name + " fetches!");
    }
}

// Main class to test the Animal, Cat, and Dog classes
public class AnimalInheritance {
    public static void main(String args[]) {
        // Create a new Animal instance and make it speak
        Animal animal = new Animal("Generic Animal", 5);
        System.out.println("\n");
        System.out.println("Creating an Animal instance:");
        animal.speak();
        System.out.println("\n");
        
        // Create a new Cat instance and make it speak and scratch
        Cat cat = new Cat("Kitty", 3);
        System.out.println("Creating a Cat instance:");
        cat.speak();
        cat.scratch();
        System.out.println("\n");
        
        // Create a new Dog instance and make it speak and fetch
        Dog dog = new Dog("Buddy", 2);
        System.out.println("Creating a Dog instance:");
        dog.speak();
        dog.fetch();
        System.out.println("\n");
    }
}
