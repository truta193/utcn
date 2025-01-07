package ro.utcn;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Project {
    private final Integer id;
    private final String name;
    private final List<String> requiredPositions = new ArrayList<String>();
    private final ArrayList<Employee> employees = new ArrayList<Employee>();

    public Project(Integer id, String name, String[] requiredPositions) {
        this.id = id;
        this.name = name;
        this.requiredPositions.addAll(Arrays.asList(requiredPositions));

    }

    public boolean addTeamMember(Employee employee) {
        if (requiredPositions.contains(employee.getPosition())) {
            employees.add(employee);
            requiredPositions.remove(employee.getPosition());
            return true;
        }
        System.out.println("[WARN] Employee " + employee.getName() + " is not needed");
        return false;
    }

    public boolean removeTeamMember(Employee employee) {
        if (employees.contains(employee)) {
            employees.remove(employee);
            requiredPositions.add(employee.getPosition());
            return true;
        }
        System.out.println("[WARN] Employee " + employee.getName() + " is was not found in the project");

        return false;
    }

    public void displayInfo() {
        if (requiredPositions.isEmpty())
            System.out.println(id + ". " + name);
        else
            System.out.println(id + ". " + name + " still requires positions " + requiredPositions);
        if (!employees.isEmpty()) {
            System.out.println("Team members: ");
            for (Employee employee : employees) {
                employee.displayInfo();
            }
        }
    }

    public void displayInfo(int indentCount) {
        System.out.print("\t".repeat(indentCount));
        if (requiredPositions.isEmpty())
            System.out.println(id + ". " + name);
        else
            System.out.println(id + ". " + name + " still requires positions " + requiredPositions);
        if (!employees.isEmpty()) {
            System.out.print("\t".repeat(indentCount + 1));
            System.out.println("Team members: ");
            for (Employee employee : employees) {
                employee.displayInfo(indentCount + 1);
            }
        }
    }

    public Integer getId() {
        return id;
    }


}
