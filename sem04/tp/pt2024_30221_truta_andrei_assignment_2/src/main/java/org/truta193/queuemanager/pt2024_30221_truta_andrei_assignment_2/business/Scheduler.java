package org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business;

import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model.Server;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model.Task;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.strategy.ConcreteStrategyQueue;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.strategy.ConcreteStrategyTime;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.strategy.IStrategy;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Scheduler {
    private final List<Server> servers;
    private int maxNoServers;
    private int maxTasksPerServer;
    private IStrategy strategy;

    private final ExecutorService executor;

    public Scheduler(int maxNoServers, int maxTasksPerServer) {
        servers = new ArrayList<>();
        this.maxNoServers = maxNoServers;
        this.maxTasksPerServer = maxTasksPerServer;
        for (int i = 0; i < maxNoServers; i++) {
            servers.add(new Server());
        }
        strategy = new ConcreteStrategyQueue();

        executor = Executors.newFixedThreadPool(maxNoServers);
        for (Server server : servers) {
            executor.execute(server);
        }
    }

    public void changeStrategy(SelectionPolicy policy) {
        if (policy == SelectionPolicy.SHORTEST_QUEUE) {
            strategy = new ConcreteStrategyQueue();
        } else {
            strategy = new ConcreteStrategyTime();
        }
    }

    public void dispatchTask(Task t) {
        strategy.addTask(servers, t);
    }

    public List<Server> getServers() {
        return servers;
    }

    public void stop() {
        executor.shutdownNow();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        int i = 1;
        for (Server s : servers) {
            sb.append("Queue ").append(i++).append(": ");
            sb.append(s.toString()).append("\n");
        }
        return sb.toString();
    }
}
