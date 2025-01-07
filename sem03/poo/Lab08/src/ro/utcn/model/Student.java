package ro.utcn.model;

import ro.utcn.AddressAware;
import ro.utcn.Comparable;
import ro.utcn.Identifiable;

import java.io.Serializable;

public class Student extends Person implements Identifiable, AddressAware, Comparable, Serializable {

    private Double grade;

    public Student(String name) {
        super(name);
    }

    public Student(Double grade) {
        super("student");
        this.grade = grade;
    }

    @Override
    public String getId() {
        return null;
    }

    @Override
    public void setId(String id) {

    }

    @Override
    public String getAddress() {
        return null;
    }

    @Override
    public void setAddress(String address) {

    }

    @Override
    public String getRole() {
        return "student";
    }


    public Double getGrade() {
        return grade;
    }

    @Override
    public int compareTo(Object object) {
        if (this.grade < ((Student) object).grade) return -1;
        if (this.grade > ((Student) object).grade) return 1;
        return this.getName().compareTo(((Student) object).getName());
    }
}
