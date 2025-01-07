package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.repository;

import javafx.beans.Observable;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.util.Callback;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.dao.ProductDao;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Product;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata.ProductEntry;

import java.util.List;

/**
 * Repository for handling CRUD operations related to Product entities in the database.
 */
public class ProductRepository {
    private final ProductDao productDao;

    /**
     * Observable list of product entries.
     */
    public final ObservableList<ProductEntry> productEntries;

    /**
     * Initializes a new instance of the ProductRepository class.
     */
    public ProductRepository() {
        this.productDao = new ProductDao();

        Callback<ProductEntry, Observable[]> extractor = c -> new Observable[]{
                c.idProperty(),
                c.nameProperty(),
                c.priceProperty(),
                c.quantityProperty()
        };
        productEntries = FXCollections.observableArrayList(extractor);

        List<Product> products = getAll();
        for (Product product : products) {
            productEntries.add(new ProductEntry(product));
        }
    }

    /**
     * Inserts a new product into the repository and returns the inserted product.
     *
     * @param product The product to insert.
     * @return The inserted product.
     */
    public Product insert(Product product) {
        Product p = productDao.insert(product);
        productEntries.add(new ProductEntry(p));
        return p;
    }

    /**
     * Updates an existing product in the repository and returns the updated product.
     *
     * @param id      The ID of the product to update.
     * @param product The product to update.
     * @return The updated product.
     */
    public Product update(int id, Product product) {
        return productDao.update(id, product);
    }

    /**
     * Deletes a product from the repository.
     *
     * @param id The ID of the product to delete.
     */
    public void delete(int id) {
        productDao.delete(new Product(id, "",0,0));
        productEntries.remove(productEntries.stream().filter(x -> x.getId() == id).findFirst().get());
    }

    /**
     * Retrieves a product entity from the database based on its ID.
     *
     * @param id The ID of the product to retrieve.
     * @return The product with the specified ID, or null if not found.
     */
    public Product getById(int id) {
        return productDao.getById(id);
    }

    /**
     * Retrieves all product entities from the database.
     *
     * @return A list of all products in the database.
     */
    public List<Product> getAll() {
        return productDao.getAll();
    }
}
