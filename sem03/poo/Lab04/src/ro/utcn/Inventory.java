package ro.utcn;

import java.util.ArrayList;
import java.util.List;

public class Inventory {
    private List<Product> productList = new ArrayList<Product>();
    private List<Integer> productQuantity = new ArrayList<Integer>();
    static Integer lastId = -1;

    static Integer getNextId() {
        lastId++;
        return lastId;
    }

    void addProduct(Product product, Integer quantity) {
        if (quantity < 0) {
            System.out.println("Quantity must be positive");
            return;
        }

        if (!productList.contains(product)) {
            productList.add(product);
            productQuantity.add(quantity);
        } else {
            productQuantity.set(productList.indexOf(product), productQuantity.get(productList.indexOf(product)) + quantity);
        }
    }

    void removeProduct(Product product, Integer quantity) {
        if (quantity < 0) {
            System.out.println("Quantity must be positive");
            return;
        }

        if (!productList.contains(product)) {
            System.out.println("Product not found");
        } else {
            if (productQuantity.get(productList.indexOf(product)) < quantity) {
                System.out.println("Not enough products");
            } else {
                productQuantity.set(productList.indexOf(product), productQuantity.get(productList.indexOf(product)) - quantity);
            }
        }
    }

    void getDetails() {
        System.out.println("Products: ");
        for (int i = 0; i < productList.size(); i++) {
            System.out.println("\t" + productQuantity.get(i) + " " + productList.get(i).getName() + " : " + productList.get(i).getDescription());
        }
    }


}
