package ro.utcn.service;

import ro.utcn.model.Student;
import ro.utcn.model.Teacher;
import java.util.UUID;
import java.sql.*;

//TODO: Currently limited to teacher/student classes; could make this general (store serialized object for example)
public class DbStorageService implements StorageService {

    private final String url = "jdbc:sqlite:/home/andrei/Documents/2023-2024/POO/Lab08/storage.db";

    //AUTO_INCREMENT not needed - integer primary key is an alias for rowid
    private final String sqlInit1 = "CREATE TABLE IF NOT EXISTS teachers (\n"
            + "	id integer PRIMARY KEY,\n"
            + "	uuid text NOT NULL,\n"
            + "	name text NOT NULL,\n"
            + "	numberOfStudents integer NOT NULL\n"
            + ");\n";
    private final String sqlInit2 = "CREATE TABLE IF NOT EXISTS students (\n"
            + "	id integer PRIMARY KEY ,\n"
            + "	uuid text NOT NULL,\n"
            + "	name text NOT NULL,\n"
            + "	grade real NOT NULL\n"
            + ");";


    Connection connection = null;

    private boolean lazyLoad() {
        if (connection == null) {
            try {
                connection = DriverManager.getConnection(url);
                if (connection == null) {
                    System.out.println("No connection to database.");
                    return false;
                }
                Statement statement = connection.createStatement();
                statement.execute(sqlInit1);
                statement.execute(sqlInit2);

            } catch (SQLException e) {
                System.out.println(e.getMessage());
                return false;
            }
        }
        return true;
    }

    @Override
    public void save(Object object) {
        if (!lazyLoad()) return;

        if (object instanceof Teacher) {
            Teacher teacher = (Teacher) object;
            String sql = "INSERT INTO teachers(uuid,name,numberOfStudents) VALUES(?,?,?)";
            try {
                PreparedStatement preparedStatement = connection.prepareStatement(sql);
                preparedStatement.setString(1, teacher.getUuid().toString());
                preparedStatement.setString(2, teacher.getName());
                preparedStatement.setInt(3, teacher.getNumberOfStudents());
                preparedStatement.executeUpdate();
            } catch (SQLException e) {
                System.out.println(e.getMessage());
                return;
            }
        } else {
            Student student = (Student) object;
            System.out.println(student.getName() + " " + student.getGrade());
            String sql = "INSERT INTO students(uuid,name,grade) VALUES(?,?,?)";
            try {
                PreparedStatement preparedStatement = connection.prepareStatement(sql);
                preparedStatement.setString(1, student.getUuid().toString());
                preparedStatement.setString(2, student.getName());
                preparedStatement.setDouble(3, student.getGrade());
                preparedStatement.executeUpdate();
            } catch (SQLException e) {
                System.out.println(e.getMessage());
                return;
            }
        }
    }


    @Override
    public Object load(String uuid) {
        if (!lazyLoad()) return null;

        String sql1 = "SELECT * FROM teachers WHERE uuid = ?";
        String sql2 = "SELECT * FROM students WHERE uuid = ?";
        try {
            PreparedStatement preparedStatement = connection.prepareStatement(sql1);
            preparedStatement.setString(1, uuid);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                Teacher teacher = new Teacher(resultSet.getString("name"), resultSet.getInt("numberOfStudents"));
                return teacher;
            }
            preparedStatement = connection.prepareStatement(sql2);
            preparedStatement.setString(1, uuid);
            resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                Student student = new Student(resultSet.getDouble("grade"));
                student.setName(resultSet.getString("name"));
                return student;
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }


        return null;
    }
}
