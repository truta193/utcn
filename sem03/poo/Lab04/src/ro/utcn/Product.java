package ro.utcn;

public class Product {
    private Integer id;
    private String name;
    private String description;
    private double price;

    public Product(Integer id, String name, String description, double price) {
        this.id = id;
        this.name = name;
        this.description = description;
        this.price = price;
    }

    void getDetails() {
        System.out.println("Product: " + name);
        System.out.println("Description: " + description);
        System.out.println("Price: " + price);
        System.out.println("Id: " + id);
    }

    void updatePrice(double newPrice) {
        price = newPrice;
    }
    void updateDescription(String newDescription) {
        description = newDescription;
    }
    void updateName(String newName) {
        name = newName;
    }

    Integer getId() {
        return id;
    }

    double getPrice() {
        return price;
    }

    String getName() {
        return name;
    }

    String getDescription() {
        return description;
    }

}
