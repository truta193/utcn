package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.repository;

import javafx.beans.Observable;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.util.Callback;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.dao.BillDao;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.dao.ClientDao;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.dao.OrderDao;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.dao.ProductDao;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Bill;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Client;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Order;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Product;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata.OrderEntry;

import java.util.List;

/**
 * Repository for handling CRUD operations related to Order entities in the database.
 */
public class OrderRepository {
    private final OrderDao orderDao;
    private final ClientDao clientDao;
    private final ProductDao productDao;
    private final BillRepository billRepository;

    /**
     * Observable list of order entries.
     */
    public final ObservableList<OrderEntry> orderEntries;

    /**
     * Initializes a new instance of the OrderRepository class.
     */
    public OrderRepository(BillRepository billRepository) {
        this.orderDao = new OrderDao();
        this.clientDao = new ClientDao();
        this.productDao = new ProductDao();
        this.billRepository = billRepository;

        Callback<OrderEntry, Observable[]> extractor = c -> new Observable[]{
                c.idProperty(),
                c.clientIdProperty(),
                c.productIdProperty(),
                c.quantityProperty(),
                c.priceProperty()
        };
        orderEntries = FXCollections.observableArrayList(extractor);

        List<Order> orders = getAll();
        for (Order order : orders) {
            orderEntries.add(new OrderEntry(order));
        }
    }

    /**
     * Inserts a new order into the repository and returns the inserted order.
     * Decreases the quantity of the product by the quantity of the order.
     *
     * @param order The order to insert.
     * @return The inserted order.
     */
    public Order insert(Order order) {
        Client client = clientDao.getById(order.getClientId());
        Product product = productDao.getById(order.getProductId());

        if (client == null || product == null) return null;
        if (product.getQuantity() < order.getQuantity()) return null;

        product.setQuantity(product.getQuantity() - order.getQuantity());
        productDao.update(product.getId(), product);
        Order ret = orderDao.insert(order);
        orderEntries.add(new OrderEntry(ret));

        Bill bill = new Bill(order.getId());
        billRepository.insert(bill);
        return ret;
    }

    /**
     * Retrieves an order entity from the database based on its ID.
     *
     * @param id
     */
    public void delete(int id) {
        orderDao.delete(new Order(id, 0, 0, 0.0));
        orderEntries.remove(orderEntries.stream().filter(x -> x.getId() == id).findFirst().get());
    }

    /**
     * Retrieves an order entity from the database based on its ID.
     *
     * @param id The ID of the order entity to retrieve.
     * @return The Order object with the specified ID, or null if not found.
     */
    public Order getById(int id) {
        return orderDao.getById(id);
    }

    /**
     * Retrieves all order entities from the database.
     *
     * @return A list of all order entities.
     */
    public List<Order> getAll() {
        return orderDao.getAll();
    }
}
