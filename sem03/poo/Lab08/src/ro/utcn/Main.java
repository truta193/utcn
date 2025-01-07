package ro.utcn;

import java.util.ArrayList;
import java.util.List;
import ro.utcn.model.Person;
import ro.utcn.model.Student;
import ro.utcn.model.Teacher;
import ro.utcn.service.DbStorageService;
import ro.utcn.service.FileStorageService;
import ro.utcn.service.StorageService;
import ro.utcn.Comparable;

public class Main {

  public static void main(String[] args) {
    Student student = new Student(9.0);
    student.setName("Mary");
    Teacher teacher = new Teacher("Bob", 10);

    student.printDetails();
    teacher.printDetails();

    StorageService storageService = new DbStorageService();

    storageService.save(teacher);

    Person p = (Person) storageService.load(teacher.getUuid().toString());
    p.printDetails();


//    ObjectSorter objectSorter = new ObjectSorter();
//    Comparable[] myStudents = new Comparable[3];
//    myStudents[0] = new Student(7.0);
//    myStudents[1] = new Student(10.0);
//    myStudents[2] = new Student(4.5);
//    Comparable[] myTeachers = new Comparable[3];
//    myTeachers[0] = new Teacher("Bob", 10);
//    myTeachers[1] = new Teacher("Bobby", 10);
//    myTeachers[2] = new Teacher("John", 20);
//
//    Comparable[] sortedTeachers = objectSorter.sort(myTeachers, false);
//    for (Comparable comparable : sortedTeachers) {
//      System.out.println(((Teacher)comparable).getName());
//    }
//
//    Comparable[] sortedStudents = objectSorter.sort(myStudents, false);
//    for (Comparable comparable : sortedStudents) {
//      System.out.println(((Student)comparable).getGrade());
//    }

  }
}