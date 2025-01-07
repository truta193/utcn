package org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.strategy;

import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model.Server;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model.Task;

import java.util.List;

public interface IStrategy {
    void addTask(List<Server> servers, Task t);
}
