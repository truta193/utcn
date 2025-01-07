package ro.utcn.model;

import ro.utcn.Comparable;
import java.util.UUID;
import java.io.Serializable;

public abstract class Person implements Comparable, Serializable {

    private final UUID uuid = UUID.randomUUID();
    private String name;

    public Person() {
        this.name = "person";
    }

    public Person(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public UUID getUuid() {
        return uuid;
    }

    public void printDetails() {
        System.out.println("Name: " + getName());
        System.out.println("Role: " + getRole());
    }

    public abstract String getRole();

}
