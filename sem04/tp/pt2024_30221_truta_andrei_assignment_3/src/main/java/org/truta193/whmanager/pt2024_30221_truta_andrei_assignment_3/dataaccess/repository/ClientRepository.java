package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.repository;

import javafx.beans.Observable;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.util.Callback;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.dataaccess.dao.ClientDao;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Client;
import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata.ClientEntry;

import java.util.List;

/**
 * Repository for handling CRUD operations related to Client entities in the database.
 */
public class ClientRepository {
    private final ClientDao clientDao;

    /**
     * Observable list of client entries.
     */
    public final ObservableList<ClientEntry> clientEntries;

    /**
     * Initializes a new instance of the ClientRepository class.
     */
    public ClientRepository() {
        this.clientDao = new ClientDao();

        Callback<ClientEntry, Observable[]> extractor = c -> {
            Observable[] res = new Observable[]{
                    c.idProperty(),
                    c.nameProperty(),
                    c.emailProperty(),
                    c.passwordProperty(),
                    c.addressProperty()
            };
            return res;
        };
        clientEntries = FXCollections.observableArrayList(extractor);

        List<Client> clients = getAll();
        for (Client client : clients) {
            clientEntries.add(new ClientEntry(client));
        }
    }

    /**
     * Inserts a new client into the repository and returns the inserted client.
     *
     * @param client The client to insert.
     * @return The inserted client.
     */
    public Client insert(Client client) {
        Client c = clientDao.insert(client);
        clientEntries.add(new ClientEntry(c));
        return c;
    }

    /**
     * Updates an existing client in the repository and returns the updated client.
     *
     * @param id     The ID of the client to update.
     * @param client The updated client object.
     * @return The updated client.
     */
    public Client update(int id, Client client) {
        return clientDao.update(id, client);
    }

    /**
     * Deletes a client from the repository by ID and removes it from the observable list.
     *
     * @param id The ID of the client to delete.
     */
    public void delete(int id) {
        clientDao.delete(new Client(id, "", "", "", ""));
        clientEntries.remove(clientEntries.stream().filter(x -> x.getId() == id).findFirst().get());
    }

    /**
     * Retrieves a client from the repository by ID.
     *
     * @param id The ID of the client to retrieve.
     * @return The retrieved client, or null if not found.
     */
    public Client getById(int id) {
        return clientDao.getById(id);
    }

    /**
     * Retrieves all clients from the repository.
     *
     * @return A list of all clients.
     */
    public List<Client> getAll() {
        return clientDao.getAll();
    }
}
