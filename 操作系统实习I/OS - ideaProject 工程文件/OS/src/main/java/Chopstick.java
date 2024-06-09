package main.java;

public class Chopstick {
    private final int id;
    private boolean isUsed;
    private static int totalUsed = 0; // 全局计数器

    public Chopstick(int id) {
        this.id = id;
        this.isUsed = false;
    }

    public synchronized boolean pickUp() {
        while (isUsed) {
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        isUsed = true;
        totalUsed++;
        return true;
    }

    public synchronized void putDown() {
        isUsed = false;
        totalUsed--;
        notifyAll();
    }

    public int getId() {
        return id;
    }

    public boolean isUsed() {
        return isUsed;
    }

    public static synchronized boolean isUsedByLessThanFourPhilosophers() {
        return totalUsed < 4;
    }
}
