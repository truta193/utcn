package ro.utcn.model;

import java.io.Serializable;

public class Teacher extends Person implements Serializable {

    private int numberOfStudents;

    public Teacher(String name) {
        super(name);
    }

    public Teacher(String name, int numberOfStudents) {
        super(name);
        this.numberOfStudents = numberOfStudents;
    }

    @Override
    public String getRole() {
        return "teacher";
    }

    @Override
    public int compareTo(Object object) {
        if (this.numberOfStudents < ((Teacher) object).numberOfStudents) return -1;
        if (this.numberOfStudents > ((Teacher) object).numberOfStudents) return 1;
        return this.getName().compareTo(((Teacher) object).getName());
    }

    public int getNumberOfStudents() {
        return numberOfStudents;
    }

    public void setNumberOfStudents(int numberOfStudents) {
        this.numberOfStudents = numberOfStudents;
    }
}
