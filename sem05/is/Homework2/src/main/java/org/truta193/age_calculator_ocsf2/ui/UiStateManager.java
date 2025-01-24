package org.truta193.age_calculator_ocsf2.ui;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.atomic.AtomicBoolean;

public class UiStateManager {
    private final BlockingQueue<String> updateQueue = new LinkedBlockingQueue<>();
    private final AtomicBoolean running = new AtomicBoolean(false);
    private Thread updateThread;
    private UiUpdater uiUpdater;

    public interface UiUpdater {
        void update(String message);
    }

    public void setUiUpdater(UiUpdater updater) {
        this.uiUpdater = updater;
    }

    public void start() {
        if (running.compareAndSet(false, true)) {
            updateThread = new Thread(() -> {
                while (running.get()) {
                    try {
                        String update = updateQueue.poll(1, java.util.concurrent.TimeUnit.SECONDS);
                        if (update != null && uiUpdater != null) {
                            uiUpdater.update(update);
                        }
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                        break;
                    }
                }
            });
            updateThread.start();
        }
    }

    public void stop() {
        if (running.compareAndSet(true, false)) {
            if (updateThread != null) {
                updateThread.interrupt();
            }
        }
    }

    public void postUpdate(String message) {
        if (running.get()) {
            updateQueue.offer(message);
        }
    }
}
