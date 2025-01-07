package ro.utcn;

public class Main {
    public static void main(String[] args) {

        Inventory inventory = new Inventory();
        Product apple = new Product(Inventory.getNextId(), "Appe", "1 red apple", 2);
        Product grapes = new Product(Inventory.getNextId(), "Grapes", "3 grapes bundle", 10);
        apple.updateName("Apple");
        inventory.addProduct(grapes, 9);
        inventory.addProduct(apple, 5);
        inventory.removeProduct(apple, 1);
        inventory.getDetails();
        System.out.println();

        Customer customer1 = new Customer(Customer.getNextId(), "John Doe", "Bucharest", "jd@gmail.com", "0723456789");
        Customer customer2 = new Customer(Customer.getNextId(), "Jane Doe", "Braila", "jed@gmail.com", "0721156766");

        customer1.getDetails();
        System.out.println();

        Order order1 = new Order(Order.getNextId());
        order1.addProduct(grapes, 2);
        order1.getDetails();
        System.out.println();

        customer2.addOrder(order1);
        customer2.getDetails();
    }
}