package ro.utcn;

import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        EmployeeManagementSystem ems = new EmployeeManagementSystem();
        Project p1 = ems.createProject(
                "Airport Security Systems",
                new String[]{"Developer", "Developer", "Developer", "Project Manager", "Project Manager"}
        );
        Project p2 = ems.createProject(
                "Airport Ticketing System",
                new String[]{"Developer", "Developer", "Project Manager"}
        );
        Project p3 = ems.createProject(
                "Video Surveillance Systems",
                new String[]{"Developer", "Developer", "Developer", "Developer", "Project Manager"}
        );

        Employee e1 = ems.hirePerson("Mihai Man", "Developer");
        Employee e2 = ems.hirePerson("Mihai Pop", "Developer");
        ems.hirePerson("Mihai Popescu", "Developer");
        ems.hirePerson("Beniamin Popa", "Developer");
        ems.hirePerson("John Doe", "Project Manager");
        ems.hirePerson("David Giosan", "Developer");
        ems.hirePerson("Alex Muntean", "Developer");
        ems.hirePerson("Mitrut Marc", "Project Manager");
        ems.hirePerson("Ioana Pop", "Developer");
        ems.hirePerson("Claudia Vanator", "Developer");
        ems.hirePerson("Alexia Pop", "Project Manager");
        ems.hirePerson("Corb Denis", "Developer");
        ems.hirePerson("Viorel Haiduc", "Developer");
        ems.hirePerson("Florentina Alexandrescu", "Project Manager");
        ems.hirePerson("Tudor Man", "Developer");
        ems.hirePerson("Zamfir Gavris", "Developer");
        ems.hirePerson("Crina Jolt", "Project Manager");
        ems.hirePerson("Matei Cotfas", "Developer");
        ems.hirePerson("Monica Moldovan", "Developer");
        ems.hirePerson("Monica Finica", "Developer");

        System.out.println("All employees: ");
        ems.displayAllEmployees();

        System.out.println("\n" + "All projects: ");
        ems.displayAllProjects();

        ems.assignToProject(p1.getId(), e1.getId());
        ems.assignToProject(0, 2);
        ems.assignToProject(0, 3);
        ems.assignToProject(0, 4);
        ems.assignToProject(0, 5);
        ems.assignToProject(1, 6);
        ems.assignToProject(1, 7);
        ems.assignToProject(1, 8);
        ems.assignToProject(2, 0);
        ems.assignToProject(2, 9);
        ems.assignToProject(2, 15);
        ems.assignToProject(3, 17);

        System.out.println("\n" + "All projects: ");
        ems.displayAllProjects();

        System.out.println("Employees with name containing 'mih':");
        List<Employee> l = ems.searchEmployee("mih", false);
        for (Employee e : l) {
            e.displayInfo();
        }
        System.out.println("\n" + "Employees with name containing 'MIH':");
        List<Employee> l2 = ems.searchEmployee("MIH", false);
        for (Employee e : l2) {
            e.displayInfo();
        }

    }
}