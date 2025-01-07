package org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.service;

import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model.Server;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model.Task;

import java.util.List;

public class StatisticsService {
    private double averageWaitingTime = 0;
    private double averageServiceTime = 0;
    private int peakHour = 0;
    private int peakHourTaskCount = 0;
    private int normalizerCoefficient = 0;

    private int timeStamp = 0;
    public void newTask(List<Server> servers, Task task) {
        averageServiceTime += task.getServiceTime();
        normalizerCoefficient++;
        for (Server server: servers) {
            for (Task t: server.getTasks()) {
                if (t.getArrivalTime() < task.getArrivalTime()) {
                    averageWaitingTime += task.getArrivalTime() - t.getArrivalTime();
                }
            }
        }
    }

    public void newTimestamp(List<Server> servers) {
        timeStamp++;
        int currentTaskCount = 0;
        for (Server server : servers) {
            currentTaskCount += server.getTasks().length;
        }
        if (currentTaskCount > peakHourTaskCount) {
            peakHourTaskCount = currentTaskCount;
            peakHour = timeStamp;
        }
    }

    public String report() {
        return "Average waiting time: " + String.format("%.2f", averageWaitingTime / normalizerCoefficient) + "\n" +
                "Average service time: " + String.format("%.2f", averageServiceTime / normalizerCoefficient) + "\n" +
                "Peak hour: " + peakHour + "\n";
    }
}
