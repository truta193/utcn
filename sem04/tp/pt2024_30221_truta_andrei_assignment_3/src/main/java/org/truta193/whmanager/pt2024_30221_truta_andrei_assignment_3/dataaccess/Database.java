package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

/**
 * Utility class for managing database connections, as a singleton
 */
public class Database {
    private static String url = null;

    private static Database instance = new Database();

    /**
     * Private constructor to prevent instantiation.
     */
    private Database() {
    }

    /**
     * Initializes the database with the given file name.
     *
     * @param fileName The file name or URL of the SQLite database.
     */
    public static void initDatabase(String fileName) {
        url = fileName;
        try {
            Class.forName("org.sqlite.JDBC");
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Initializes and retrieves a connection to the database.
     *
     * @return A Connection object representing the database connection.
     * @throws IllegalStateException if the database has not been initialized.
     */
    private Connection initConnection() {
        if (url == null) {
            throw new IllegalStateException("Database not initialized");
        }

        Connection connection = null;
        try {
            connection = DriverManager.getConnection(url);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return connection;
    }

    /**
     * Retrieves an instance of the database connection.
     *
     * @return A Connection object representing the database connection.
     */
    public static Connection getInstance() {
        return instance.initConnection();
    }
}
