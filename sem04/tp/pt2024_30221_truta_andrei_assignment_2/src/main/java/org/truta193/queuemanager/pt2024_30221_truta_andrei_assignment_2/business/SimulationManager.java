package org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business;

import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model.ParamState;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model.Server;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.model.Task;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.controller.SimulationController;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.service.FileService;
import org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.service.StatisticsService;

import java.io.IOException;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class SimulationManager implements Runnable {
    private final ParamState paramState;
    public SelectionPolicy selectionPolicy = SelectionPolicy.SHORTEST_TIME;
    private final Scheduler scheduler;
    private int currentTime = 0;
    private boolean hasStarted = false;
    private final List<Task> generatedTasks;
    private final SimulationController simulationController;
    private final FileService fileService;
    private final StatisticsService statisticsService = new StatisticsService();

    public SimulationManager(
            ParamState paramState,
            SimulationController simulationController,
            FileService fileService
    ) {
        this.paramState = paramState;
        this.simulationController = simulationController;
        this.fileService = fileService;

        scheduler = new Scheduler(paramState.getNumberOfServers(), paramState.getNumberOfClients());
        scheduler.changeStrategy(selectionPolicy);
        generatedTasks = new ArrayList<>();
        generateNRandomTasks();
    }

    public void generateNRandomTasks() {
        for (int i = 0; i < paramState.getNumberOfClients(); i++) {
            int arrivalTime = (int) (Math.random() * (paramState.getMaxArrivalTime() - paramState.getMinArrivalTime()) + paramState.getMinArrivalTime());
            int processingTime = (int) (Math.random() * (paramState.getMaxProcessingTime() - paramState.getMinProcessingTime()) + paramState.getMinProcessingTime());
            Task t = new Task(arrivalTime, processingTime);
            generatedTasks.add(t);
        }
    }

    @Override
    public void run() {
        currentTime = 1;
        try {
            fileService.Save("queues.log", LocalDateTime.now().toString() + "\n");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        while (currentTime <= paramState.getTimeLimit()) {
            boolean hasRunningTasks = false;
            for (Server s : scheduler.getServers()) {
                if (s.getTasks().length > 0) {
                    hasRunningTasks = true;
                    break;
                }
            }
            if (!hasRunningTasks && hasStarted && generatedTasks.isEmpty()) {
                simulationController.refresh();
                currentTime++;
                try {
                    fileService.Save("queues.log", "Time: " + (currentTime - 1) + "\n");
                    fileService.Save("queues.log", scheduler.toString());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
                break;
            }


            Iterator<Task> iterator = generatedTasks.iterator();
            while (iterator.hasNext()) {
                Task t = iterator.next();
                if (t.getArrivalTime() == currentTime) {
                    scheduler.dispatchTask(t);
                    statisticsService.newTask(scheduler.getServers(), t);
                    iterator.remove();
                    hasStarted = true;
                }
            }
            statisticsService.newTimestamp(scheduler.getServers());

            simulationController.refresh();

            currentTime++;
            try {
                fileService.Save("queues.log", "Time: " + (currentTime - 1) + "\n");
                fileService.Save("queues.log", scheduler.toString());
            } catch (IOException e) {
                throw new RuntimeException(e);
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
        scheduler.stop();
        try {
            fileService.Save("queues.log", statisticsService.report());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public List<Task> getGeneratedTasks() {
        return generatedTasks;
    }

    public Scheduler getScheduler() {
        return scheduler;
    }

    public int getCurrentTime() {
        return this.currentTime;
    }
}
