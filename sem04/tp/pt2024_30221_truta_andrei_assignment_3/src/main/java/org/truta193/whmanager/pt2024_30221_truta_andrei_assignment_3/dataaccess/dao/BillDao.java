package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.dao;

import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.Database;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Bill;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Data Access Object (DAO) for handling CRUD operations related to Bill entities in the database.
 */
public class BillDao {

    /**
     * SQL string to create the 'logs' table if it does not exist.
     */
    private final String createTableString = "CREATE TABLE IF NOT EXISTS logs (id INTEGER PRIMARY KEY, order_id INTEGER)";

    /**
     * SQL string to insert a Bill entity into the 'logs' table.
     */
    private final String insertString = "INSERT INTO logs (order_id) VALUES (?)";

    /**
     * SQL string to select all Bill entities from the 'logs' table.
     */
    private final String selectAllString = "SELECT * FROM logs";

    /**
     * SQL string to select a Bill entity by ID from the 'logs' table.
     */
    private final String selectByIdString = "SELECT * FROM logs WHERE id = ?";

    /**
     * Constructs a BillDao object. Initializes the 'logs' table if it does not exist in the database.
     */
    public BillDao() {
        var database = Database.getInstance();
        try {
            DatabaseMetaData metaData = database.getMetaData();
            ResultSet resultSet = metaData.getTables(null, null, "logs", new String[]{"TABLE"});
            if (!resultSet.next()) {
                Statement statement = database.createStatement();
                statement.execute(createTableString);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                database.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * Inserts a Bill entity into the database.
     *
     * @param bill The Bill object to insert.
     */
    public Bill insertBill(Bill bill) {
        var database = Database.getInstance();
        try (var statement = database.prepareStatement(insertString)) {
            statement.setInt(1, bill.orderId());
            statement.executeUpdate();
            ResultSet resultSet = statement.getGeneratedKeys();
            if (resultSet.next()) {
                bill = new Bill(resultSet.getInt(1), bill.orderId());
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                database.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        try {
            database.close();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return bill;
    }

    /**
     * Retrieves a Bill entity from the database based on its ID.
     *
     * @param id The ID of the Bill entity to retrieve.
     * @return The Bill object with the specified ID, or null if not found.
     */
    public Bill getBillById(int id) {
        var database = Database.getInstance();
        try (var statement = database.prepareStatement(selectByIdString)) {
            statement.setInt(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                database.close();
                return new Bill(resultSet.getInt("id"), resultSet.getInt("order_id"));
            }
            return null;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        } finally {
            try {
                database.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * Retrieves all Bill entities from the database.
     *
     * @return A list of all Bill objects stored in the database.
     */
    public List<Bill> getAllBills() {
        var database = Database.getInstance();
        try (var statement = database.prepareStatement(selectAllString)) {
            ResultSet resultSet = statement.executeQuery();
            List<Bill> bills = new ArrayList<>();
            while (resultSet.next()) {
                bills.add(new Bill(resultSet.getInt("id"), resultSet.getInt("order_id")));
            }
            database.close();
            return bills;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        } finally {
            try {
                database.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

}
