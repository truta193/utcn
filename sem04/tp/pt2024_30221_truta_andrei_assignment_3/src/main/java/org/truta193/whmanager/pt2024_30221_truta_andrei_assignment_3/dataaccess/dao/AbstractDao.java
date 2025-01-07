package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.dao;

import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.Database;

import java.beans.IntrospectionException;
import java.lang.reflect.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.beans.PropertyDescriptor;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 * Abstract DAO (Data Access Object) class for database operations on a specific entity type.
 *
 * @param <T> The type of entity this DAO operates on.
 */
public class AbstractDao<T> {
    private final Class<T> type;

    /**
     * Constructs a new AbstractDao instance.
     */
    @SuppressWarnings("unchecked")
    public AbstractDao() {
        this.type = (Class<T>) ((ParameterizedType) getClass().getGenericSuperclass()).getActualTypeArguments()[0];
        createTable();
    }

    /**
     * Generates the SQL CREATE TABLE query based on the fields of the entity class.
     *
     * @return The SQL CREATE TABLE query string.
     */
    private String createTableQuery() {
        StringBuilder sb = new StringBuilder();
        sb.append("CREATE TABLE IF NOT EXISTS ");
        sb.append(type.getSimpleName());
        sb.append("s ");
        sb.append("(");
        for (Field field : type.getDeclaredFields()) {
            String fieldName = field.getName();
            String fieldType = field.getType().getSimpleName();
            if (fieldName.equals("id")) {
                sb.append(fieldName);
                sb.append(" ");
                sb.append("INTEGER PRIMARY KEY");
            } else {
                sb.append(fieldName);
                sb.append(" ");
                sb.append(fieldType);
            }
            sb.append(",");
        }
        sb.deleteCharAt(sb.length() - 1);
        sb.append(")");
        return sb.toString();
    }

    /**
     * Creates the database table if it does not exist based on the entity class structure.
     */
    private void createTable() {
        Connection connection = null;
        PreparedStatement statement = null;
        String query = createTableQuery();
        try {
            connection = Database.getInstance();
            statement = connection.prepareStatement(query);
            statement.execute();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                statement.close();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
            try {
                connection.close();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
    }

    /**
     * Creates a list of objects of type T from the ResultSet using reflection.
     *
     * @param resultSet The ResultSet containing query results.
     * @return A list of objects of type T.
     */
    private List<T> createObjects(ResultSet resultSet) {
        List<T> list = new ArrayList<T>();
        Constructor[] ctors = type.getDeclaredConstructors();
        Constructor ctor = null;
        for (Constructor constructor : ctors) {
            ctor = constructor;
            if (ctor.getGenericParameterTypes().length == 0)
                break;
        }
        try {
            while (resultSet.next()) {
                assert ctor != null;
                ctor.setAccessible(true);
                T instance = (T) ctor.newInstance();
                for (Field field : type.getDeclaredFields()) {
                    String fieldName = field.getName();
                    Object value = resultSet.getObject(fieldName);
                    PropertyDescriptor propertyDescriptor = new PropertyDescriptor(fieldName, type);
                    Method method = propertyDescriptor.getWriteMethod();
                    method.invoke(instance, value);
                }
                list.add(instance);
            }
        } catch (InstantiationException | IntrospectionException | IllegalAccessException | SecurityException |
                 IllegalArgumentException | InvocationTargetException | SQLException e) {
            e.printStackTrace();
        }

        return list;
    }

    /**
     * Utility method to close database resources (connection, statement, resultset).
     *
     * @param connection The database connection to close.
     * @param statement  The prepared statement to close.
     * @param resultSet  The result set to close.
     */
    private void close(Connection connection, PreparedStatement statement, ResultSet resultSet) {
        try {
            if (resultSet != null) {
                resultSet.close();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        try {
            if (statement != null) {
                statement.close();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        try {
            if (connection != null) {
                connection.close();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    /**
     * Sets the ID field of an entity object using reflection.
     *
     * @param t  The entity object.
     * @param id The ID value to set.
     */
    private void setId(T t, int id) {
        Field[] fields = type.getDeclaredFields();
        for (Field field : fields) {
            field.setAccessible(true);
            if (field.getName().equals("id")) {
                try {
                    field.set(t, id);
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    /**
     * Creates the SQL query string to retrieve an entity object by a specific field value.
     *
     * @param field The name of the field to use in the WHERE clause.
     * @return The SQL query string.
     */
    private String createGetByIdQuery(String field) {
        StringBuilder sb = new StringBuilder();
        sb.append("SELECT ");
        sb.append(" * ");
        sb.append(" FROM ");
        sb.append(type.getSimpleName());
        sb.append("s");
        sb.append(" WHERE ");
        sb.append(field);
        sb.append(" = ? ");
        return sb.toString();
    }

    /**
     * Retrieves an entity object by its ID from the database.
     *
     * @param id The ID of the entity to retrieve.
     * @return The entity object if found, or null if not found.
     */
    public T getById(int id) {
        Connection connection = null;
        PreparedStatement statement = null;
        ResultSet resultSet = null;
        String query = createGetByIdQuery("id");
        try {
            connection = Database.getInstance();
            statement = connection.prepareStatement(query);
            statement.setInt(1, id);
            resultSet = statement.executeQuery();

            return createObjects(resultSet).get(0);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } finally {
            close(connection, statement, resultSet);
        }
    }

    /**
     * Creates the SQL query string to retrieve all entity objects from the database.
     *
     * @return The SQL query string.
     */
    private String createGetAllQuery() {
        StringBuilder sb = new StringBuilder();
        sb.append("SELECT ");
        sb.append(" * ");
        sb.append(" FROM ");
        sb.append(type.getSimpleName());
        sb.append("s");
        return sb.toString();
    }

    /**
     * Retrieves a list of all entity objects from the database.
     *
     * @return A list containing all entity objects.
     */
    public List<T> getAll() {
        Connection connection = null;
        PreparedStatement statement = null;
        ResultSet resultSet = null;
        String query = createGetAllQuery();

        try {
            connection = Database.getInstance();
            statement = connection.prepareStatement(query);
            resultSet = statement.executeQuery();
            return createObjects(resultSet);
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            close(connection, statement, resultSet);
        }

        return null;
    }

    /**
     * Creates the SQL INSERT query string for inserting a new entity object into the database.
     *
     * @param fields The array of fields representing the columns to insert.
     * @param values The array of values representing the corresponding values to insert.
     * @return The SQL INSERT query string.
     */
    private String createInsertQuery(Field[] fields, Object[] values) {
        StringBuilder sb = new StringBuilder();
        sb.append("INSERT ");
        sb.append("INTO ");
        sb.append(type.getSimpleName());
        sb.append("s ");
        sb.append("(");
        for (int i = 0; i < fields.length; i++) {
            if (fields[i].getName().equals("id")) {
                continue;
            }
            String separator = i == fields.length - 1 ? "" : ",";
            sb.append(fields[i].getName());
            sb.append(separator);
        }
        sb.append(") ");
        sb.append(" VALUES (");
        for (int i = 0; i < fields.length; i++) {
            if (fields[i].getName().equals("id")) {
                continue;
            }

            String separator = i == fields.length - 1 ? "" : ",";
            if (values[i] instanceof String) {
                sb.append("'" + values[i].toString() + "'");
            } else {
                sb.append(values[i].toString());
            }
            sb.append(separator);
        }
        sb.append(")");
        return sb.toString();
    }

    /**
     * Inserts a new entity object into the database.
     *
     * @param t The entity object to insert.
     * @return The inserted entity object.
     */
    public T insert(T t) {
        Connection connection = null;
        PreparedStatement statement = null;
        Field[] fields = type.getDeclaredFields();
        Object[] values = new Object[fields.length];
        for (int i = 0; i < fields.length; i++) {
            try {
                fields[i].setAccessible(true);
                values[i] = fields[i].get(t);
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        }
        String query = createInsertQuery(fields, values);

        connection = Database.getInstance();
        ResultSet resultIds = null;
        int id = -1;
        try {
            statement = connection.prepareStatement(query);
            statement.execute();
            resultIds = statement.getGeneratedKeys();
            if (resultIds.next()) {
                id = resultIds.getInt(1);
                setId(t, id);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            close(connection, statement, resultIds);
        }
        return t;
    }

    /**
     * Creates the SQL UPDATE query string for updating an existing entity object in the database.
     *
     * @param fields The array of fields representing the columns to update.
     * @param values The array of values representing the corresponding new values.
     * @param field  The field name representing the WHERE clause condition (typically "id").
     * @param id     The value of the WHERE clause condition.
     * @return The SQL UPDATE query string.
     */
    private String createUpdateQuery(Field[] fields, Object[] values, String field, int id) {
        StringBuilder sb = new StringBuilder();
        sb.append("UPDATE ");
        sb.append(type.getSimpleName());
        sb.append("s ");
        sb.append("SET ");
        for (int i = 0; i < fields.length; i++) {
            if (fields[i].getName().equals("id")) {
                continue;
            }
            String separator = i == fields.length - 1 ? "" : ",";
            sb.append(fields[i].getName());
            sb.append(" = ");
            if (values[i] instanceof String) {
                sb.append("'" + values[i].toString() + "'");
            } else {
                sb.append(values[i].toString());
            }
            sb.append(separator);
        }
        sb.append(" WHERE ").append(field).append(" = ").append(id);
        return sb.toString();
    }

    /**
     * Updates an existing entity object in the database.
     *
     * @param id The ID of the entity to update.
     * @param t  The updated entity object.
     * @return The updated entity object.
     */
    public T update(int id, T t) {
        Connection connection = null;
        PreparedStatement statement = null;
        Field[] fields = type.getDeclaredFields();
        Object[] values = new Object[fields.length];
        for (int i = 0; i < fields.length; i++) {
            try {
                fields[i].setAccessible(true);
                values[i] = fields[i].get(t);
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        }
        String query = createUpdateQuery(fields, values, "id", id);

        connection = Database.getInstance();
        try {
            statement = connection.prepareStatement(query);
            statement.execute();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            close(connection, statement, null);
        }
        return t;
    }

    /**
     * Creates the SQL DELETE query string for deleting an entity object from the database.
     *
     * @param field The field name representing the WHERE clause condition (typically "id").
     * @param id    The value of the WHERE clause condition.
     * @return The SQL DELETE query string.
     */
    private String createDeleteQuery(String field, int id) {
        StringBuilder sb = new StringBuilder();
        sb.append("DELETE ");
        sb.append("FROM ");
        sb.append(type.getSimpleName());
        sb.append("s ");
        sb.append("WHERE ").append(field).append(" = ").append(id);
        return sb.toString();
    }

    /**
     * Deletes an entity object from the database.
     *
     * @param t The entity object to delete.
     */
    public void delete(T t) {
        Connection connection = null;
        PreparedStatement statement = null;

        int id = -1;
        for (Field field : type.getDeclaredFields()) {
            field.setAccessible(true);
            if (field.getName().equals("id")) {
                try {
                    id = Integer.parseInt(field.get(t).toString());
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                }
            }
        }
        if (id == -1) {
            throw new RuntimeException("No id found");
        }

        String query = createDeleteQuery("id", id);

        connection = Database.getInstance();
        try {
            statement = connection.prepareStatement(query);
            statement.execute();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            close(connection, statement, null);
        }
    }
}
