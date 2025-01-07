package org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model;

public class Task {
    private final int id;
    private final int arrivalTime;
    private int serviceTime;

    static int idCounter = 0;

    public Task(int arrivalTime, int processingTime) {
        this.arrivalTime = arrivalTime;
        this.serviceTime = processingTime;
        this.id = idCounter++;
    }

    public int getId() {
        return id;
    }

    public int getArrivalTime() {
        return arrivalTime;
    }

    public int getServiceTime() {
        return serviceTime;
    }

    public void setServiceTime(int serviceTime) {
        this.serviceTime = serviceTime;
    }

    @Override
    public String toString() {
        return "(" + id + ", " + arrivalTime + ", " + serviceTime + ")";
    }
}
