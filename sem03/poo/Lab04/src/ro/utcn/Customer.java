package ro.utcn;

import java.util.ArrayList;
import java.util.List;

public class Customer {
    private Integer id;
    private String name;
    private String address;
    private String email;
    private String phone;
    private List<Order> placedOrders = new ArrayList<Order>();

    static Integer lastId = -1;

    static Integer getNextId() {
        lastId++;
        return lastId;
    }

    public Customer(Integer id, String name, String address, String email, String phone) {
        this.id = id;
        this.name = name;
        this.address = address;
        this.email = email;
        this.phone = phone;
    }

    public void getDetails() {
        System.out.println("Customer: ");
        System.out.println("\tName: " + name);
        System.out.println("\tAddress: " + address);
        System.out.println("\tEmail: " + email);
        System.out.println("\tPhone: " + phone);
        System.out.println("\tId: " + id);
        System.out.println("\tOrders: ");
        for (int i = 0; i < placedOrders.size(); i++) {
            //TODO: Needs \t\t for each order so do this manually instead of calling method
            placedOrders.get(i).getDetails();
            System.out.println();

        }
    }

    public void updateName(String newName) {
        name = newName;
    }
    public void updateAddress(String newAddress) {
        address = newAddress;
    }
    public void updateEmail(String newEmail) {
        email = newEmail;
    }
    public void updatePhone(String newPhone) {
        phone = newPhone;
    }
    public void addOrder(Order newOrder) {
        newOrder.setClientId(this.id);
        placedOrders.add(newOrder);
    }

    public Integer getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getAddress() {
        return address;
    }

    public String getEmail() {
        return email;
    }

    public String getPhone() {
        return phone;
    }

    public List<Order> getPlacedOrders() {
        return placedOrders;
    }


}
