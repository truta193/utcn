package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.repository;

import javafx.beans.Observable;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.util.Callback;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.dao.BillDao;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Bill;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Client;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata.BillEntry;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata.ClientEntry;

import java.util.List;

/**
 * Repository for handling CRUD operations related to Bill entities in the database.
 */
public class BillRepository {
    private final BillDao billDao;

    public final ObservableList<BillEntry> billEntries;

    public BillRepository() {
        this.billDao = new BillDao();

        Callback<BillEntry, Observable[]> extractor = c -> {
            Observable[] res = new Observable[]{
                    c.idProperty(),
                    c.orderIdProperty()
            };
            return res;
        };
        billEntries = FXCollections.observableArrayList(extractor);

        List<Bill> bills = getAll();
        for (Bill bill : bills) {
            billEntries.add(new BillEntry(bill));
        }
    }

    /**
     * Gets all bills from the repository.
     *
     * @return A list of all bills.
     */
    public List<Bill> getAll() {
        return billDao.getAllBills();
    }

    /**
     * Inserts a new bill into the repository and returns the inserted bill.
     *
     * @param bill The bill to insert.
     * @return The inserted bill.
     */
    public Bill insert(Bill bill) {
        Bill b = billDao.insertBill(bill);
        billEntries.add(new BillEntry(b));
        return b;
    }
}
