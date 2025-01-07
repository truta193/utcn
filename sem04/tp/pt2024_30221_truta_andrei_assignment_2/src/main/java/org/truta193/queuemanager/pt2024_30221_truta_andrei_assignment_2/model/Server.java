package org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.atomic.AtomicInteger;

public class Server implements Runnable {
    private final int id;
    private final BlockingQueue<Task> tasks;
    private final AtomicInteger waitingPeriod;

    public AtomicInteger getWaitingPeriod() {
        return waitingPeriod;
    }

    static int idCounter = 0;

    public Server() {
        this.id = ++idCounter;
        tasks = new LinkedBlockingQueue<>();
        waitingPeriod = new AtomicInteger(0);
    }

    public void addTask(Task newTask) {
        tasks.add(newTask);
        waitingPeriod.addAndGet(newTask.getServiceTime());
    }

    public int getId() {
        return id;
    }

    public void run() {
        while (!Thread.currentThread().isInterrupted()) {
            Task nextTask = tasks.peek();

            if (nextTask != null) {
                if (nextTask.getServiceTime() > 1) {
                    nextTask.setServiceTime(nextTask.getServiceTime() - 1);
                } else {
                    tasks.poll();
                }
            }

            long sleepStartTime = System.currentTimeMillis();
            while (System.currentTimeMillis() < sleepStartTime + 1000) {
                try {
                    Thread.sleep(1000 - (System.currentTimeMillis() - sleepStartTime));
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }
    }

    public Task[] getTasks() {
        return tasks.toArray(new Task[0]);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (Task t : tasks) {
            sb.append(t).append("; ");
        }

        return sb.toString();
    }
}
