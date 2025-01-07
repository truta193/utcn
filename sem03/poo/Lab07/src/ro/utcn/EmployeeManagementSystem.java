package ro.utcn;

import java.util.ArrayList;
import java.util.List;

public class EmployeeManagementSystem {
    private ArrayList<Employee> employees = new ArrayList<Employee>();
    private ArrayList<Project> projects = new ArrayList<Project>();

    private static Integer employeeId = -1;
    private static Integer projectId = -1;

    public EmployeeManagementSystem() {
    }

    private Integer getNextEmployeeId() {
        return ++employeeId;
    }

    private Integer getNextProjectId() {
        return ++projectId;
    }

    private Project getProjectById(Integer projectId) {
        for (Project project : projects) {
            if (project.getId().equals(projectId)) {
                return project;
            }
        }
        return null;
    }

    private Employee getEmployeeById(Integer employeeId) {
        for (Employee employee : employees) {
            if (employee.getId().equals(employeeId)) {
                return employee;
            }
        }
        return null;
    }

    public Employee hirePerson(String name, String position) {
        Employee employee = new Employee(getNextEmployeeId(), name, position);
        employees.add(employee);
        return employee;
    }

    public Project createProject(String name, String[] requiredPositions) {
        Project project = new Project(getNextProjectId(), name, requiredPositions);
        projects.add(project);
        return project;
    }


    public boolean assignToProject(Integer projectId, Integer employeeId) {
        Project project = getProjectById(projectId);
        Employee employee = getEmployeeById(employeeId);
        if (project == null) {
            System.out.println("[WARN] Project with id " + projectId + " does not exist");
            return false;
        }
        if (employee == null) {
            System.out.println("[WARN] Employee with id " + employeeId + " does not exist");
            return false;
        }

        return project.addTeamMember(employee);
    }

    public boolean deassignFromProject(Integer projectId, Integer employeeId) {
        Project project = getProjectById(projectId);
        Employee employee = getEmployeeById(employeeId);
        if (project == null) {
            System.out.println("[WARN] Project with id " + projectId + " does not exist");
            return false;
        }
        if (employee == null) {
            System.out.println("[WARN] Employee with id " + employeeId + " does not exist");
            return false;
        }

        return project.removeTeamMember(employee);
    }

    public List<Employee> searchEmployee(String name, boolean exactMatch) {
        List<Employee> result = new ArrayList<Employee>();
        if (exactMatch) {
            for (Employee employee : employees) {
                if (employee.getName().equals(name)) {
                    result.add(employee);
                }
            }
        } else {
            for (Employee employee : employees) {
                if (employee.getName().toLowerCase().contains(name.toLowerCase())) {
                    result.add(employee);
                }
            }
        }
        return result;
    }

    public void displayAllProjects() {
        for (Project project : projects) {
            project.displayInfo(0);
        }
        System.out.println();

    }

    public void displayAllEmployees() {
        for (Employee employee : employees) {
            employee.displayInfo(0);
        }
        System.out.println();

    }


}
