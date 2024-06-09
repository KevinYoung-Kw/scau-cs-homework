package main.java;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class DiningTable {
    private final Philosopher[] philosophers;
    private final Chopstick[] chopsticks;
    private final ExecutorService executorService;


    public DiningTable(int strategy) {
        philosophers = new Philosopher[5];
        chopsticks = new Chopstick[5];
        executorService = Executors.newFixedThreadPool(5);

        for (int i = 0; i < chopsticks.length; i++) {
            chopsticks[i] = new Chopstick(i);
        }

        for (int i = 0; i < philosophers.length; i++) {
            Chopstick leftChopstick = chopsticks[i];
            Chopstick rightChopstick = chopsticks[(i + 1) % chopsticks.length];
            philosophers[i] = new Philosopher(i, leftChopstick, rightChopstick, strategy);
        }
    }

    public void startDining() {
        for (Philosopher philosopher : philosophers) {
            new Thread(philosopher).start();
        }
    }

    public void stopDining() throws InterruptedException {
        executorService.shutdownNow();
        if (!executorService.awaitTermination(60, TimeUnit.SECONDS)) {
            System.err.println("Pool did not terminate");
        }
    }

    public Philosopher[] getPhilosophers() {
        return philosophers;
    }

    public Chopstick[] getChopsticks() {
        return chopsticks;
    }

    public void restartDining() {
        // 先 stop 线程
        try {
            stopDining();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}