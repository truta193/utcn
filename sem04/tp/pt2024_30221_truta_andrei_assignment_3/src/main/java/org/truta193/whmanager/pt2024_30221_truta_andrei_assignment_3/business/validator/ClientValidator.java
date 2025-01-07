package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.business.validator;

import org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.Client;

/**
 * Validator class for validating client creation.
 */
public class ClientValidator {
    /**
     * Validates the client creation.
     *
     * @param client the client to validate
     * @return true if the client is valid, false otherwise
     */
    public boolean validateClient(Client client) {
        return client != null &&
                !client.getName().isEmpty() &&
                !client.getEmail().isEmpty() &&
                !client.getPassword().isEmpty() &&
                !client.getAddress().isEmpty();
    }
}
