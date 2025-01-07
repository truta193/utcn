package ro.utcn;

public class Employee {
    private final Integer id;
    private String name;
    private String position;

    public Employee(Integer id, String name, String position) {
        this.id = id;
        this.name = name;
        this.position = position;
    }

    void displayInfo() {
        System.out.println(id + ". " + name + " is a " + position);
    }

    void displayInfo(int indentCount) {
        for (int i = 0; i < indentCount; i++) System.out.print("\t");
        System.out.println(id + ". " + name + " is a " + position);
    }

    public String getPosition() {
        return position;
    }

    public Integer getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setPosition(String position) {
        this.position = position;
    }
}
