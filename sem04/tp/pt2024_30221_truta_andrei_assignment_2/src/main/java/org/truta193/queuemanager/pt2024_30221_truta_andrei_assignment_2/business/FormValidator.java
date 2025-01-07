package org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business;

public class FormValidator {
    public boolean validateForm(
            String numberOfServers,
            String numberOfClients,
            String timeLimit,
            String maxProcessingTime,
            String minProcessingTime,
            String maxArrivalTime,
            String minArrivalTime,
            SelectionPolicy selectionPolicy) {
        return numberOfServers.trim().matches("[0-9]+") &&
                numberOfClients.trim().matches("[0-9]+") &&
                timeLimit.trim().matches("[0-9]+") &&
                maxProcessingTime.trim().matches("[0-9]+") &&
                minProcessingTime.trim().matches("[0-9]+") &&
                maxArrivalTime.trim().matches("[0-9]+") &&
                minArrivalTime.trim().matches("[0-9]+") &&
                Integer.parseInt(maxProcessingTime) >= Integer.parseInt(minProcessingTime) &&
                Integer.parseInt(maxArrivalTime) >= Integer.parseInt(minArrivalTime) &&
                selectionPolicy != null && (selectionPolicy.equals(SelectionPolicy.SHORTEST_QUEUE) || selectionPolicy.equals(SelectionPolicy.SHORTEST_TIME));
    }
}
