package main.java;

public class Philosopher implements Runnable {
    private final int id;
    private final Chopstick leftChopstick;
    private final Chopstick rightChopstick;
    private String state;
    private final int strategy;
    private boolean hasLeftChopstick = false;
    private boolean hasRightChopstick = false;
    public static int sleepTime = 1000;
    public static boolean isRunning = true;

    public Philosopher(int id, Chopstick leftChopstick, Chopstick rightChopstick, int strategy) {
        this.id = id;
        this.leftChopstick = leftChopstick;
        this.rightChopstick = rightChopstick;
        this.state = "Thinking";
        this.strategy = strategy;
    }

    public static void setSleepTime(int speed) {
        sleepTime = speed;
    }


    @Override
    public void run() {
        try {
            isRunning = true;
            while (!Thread.currentThread().isInterrupted() && isRunning) { // Check isRunning
                think();
                switch (strategy) {
                    case 1:
                        strategy1();
                        break;
                    case 2:
                        strategy2();
                        break;
                    case 3:
                        strategy3();
                        break;
                    case 4:
                        strategy4();
                        break;
                }
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void think() throws InterruptedException {
        state = "Thinking";
        System.out.println("Philosopher " + id + " is " + state);
        logger.logMessage("Philosopher " + id + " is " + state);

        Thread.sleep((long) (Math.random() * sleepTime));
    }

    private void eat() throws InterruptedException {
        if (hasLeftChopstick && hasRightChopstick) {
            state = "Eating";
            System.out.println("Philosopher " + id + " is " + state);
            logger.logMessage("Philosopher " + id + " is " + state);

            Thread.sleep((long) (Math.random() * sleepTime));
        }
    }

    private void pickUpLeftChopstick() throws InterruptedException {
        state = "Waiting";
        System.out.println("Philosopher " + id + " is " + state + " for picking up left chopstick with id " + leftChopstick.getId());
        logger.logMessage("Philosopher " + id + " is " + state + " for picking up left chopstick with id " + leftChopstick.getId());

        if (leftChopstick.pickUp()) {
            hasLeftChopstick = true;
            state = "Waiting";
        }
    }

    private void pickUpRightChopstick() throws InterruptedException {
        state = "Waiting";
        System.out.println("Philosopher " + id + " is " + state + " for picking up right chopstick with id " + rightChopstick.getId());
        logger.logMessage("Philosopher " + id + " is " + state + " for picking up right chopstick with id " + rightChopstick.getId());

        if (rightChopstick.pickUp()) {
            hasRightChopstick = true;
            state = "Waiting";
        }
    }

    private void putDownRightChopstick() throws InterruptedException {
        rightChopstick.putDown();
        hasRightChopstick = false;
        state = "Waiting";
        System.out.println("Philosopher " + id + " is " + state + " for putting down right chopstick with id " + rightChopstick.getId());
        logger.logMessage("Philosopher " + id + " is " + state + " for putting down right chopstick with id " + rightChopstick.getId());
    }

    private void putDownLeftChopstick() throws InterruptedException {
        leftChopstick.putDown();
        hasLeftChopstick = false;
        state = "Waiting";
        System.out.println("Philosopher " + id + " is " + state + " for putting down left chopstick with id " + leftChopstick.getId());
        logger.logMessage("Philosopher " + id + " is " + state + " for putting down left chopstick with id " + leftChopstick.getId());
    }


    private void strategy1() throws InterruptedException {
        if (Math.random() < 0.5) {
            synchronized (leftChopstick) {
                pickUpLeftChopstick();
                synchronized (rightChopstick) {
                    pickUpRightChopstick();
                    eat();
                    putDownRightChopstick();
                }
                putDownLeftChopstick();
            }
        } else {
            synchronized (rightChopstick) {
                pickUpRightChopstick();
                synchronized (leftChopstick) {
                    pickUpLeftChopstick();
                    eat();
                    putDownLeftChopstick();
                }
                putDownRightChopstick();
            }
        }
    }

    private void strategy2() throws InterruptedException {
        synchronized (rightChopstick) {
            if (Chopstick.isUsedByLessThanFourPhilosophers()) {
                pickUpRightChopstick();
                synchronized (leftChopstick) {
                    pickUpLeftChopstick();
                    eat();
                    putDownLeftChopstick();
                }
                putDownRightChopstick();
            }
        }
    }

    private void strategy3() throws InterruptedException {
        if (id % 2 == 1) {
            synchronized (leftChopstick) {
                pickUpLeftChopstick();
                synchronized (rightChopstick) {
                    pickUpRightChopstick();
                    eat();
                    putDownRightChopstick();
                }
                putDownLeftChopstick();
            }
        } else {
            synchronized (rightChopstick) {
                pickUpRightChopstick();
                synchronized (leftChopstick) {
                    pickUpLeftChopstick();
                    eat();
                    putDownLeftChopstick();
                }
                putDownRightChopstick();
            }
        }
    }

    private void strategy4() throws InterruptedException {
        synchronized (leftChopstick) {
            synchronized (rightChopstick) {
                pickUpLeftChopstick();
                pickUpRightChopstick();
                eat();
                putDownRightChopstick();
                putDownLeftChopstick();
            }
        }
    }

    public void interrupt() throws InterruptedException {
        if (hasLeftChopstick) {
            putDownLeftChopstick();
        }
        if (hasRightChopstick) {
            putDownRightChopstick();
        }
        state = "Thinking";
        Thread.currentThread().interrupt();
    }

    public String getState() {
        return state;
    }

    public boolean hasRightChopstick() {
        return hasRightChopstick;
    }

    public boolean hasLeftChopstick() {
        return hasLeftChopstick;
    }

    public Chopstick getLeftChopstick() {
        return leftChopstick;
    }

    public Chopstick getRightChopstick() {
        return rightChopstick;
    }

    public String getID() {
        return String.valueOf(id);
    }

    public void restart() {
        hasLeftChopstick = false;
        hasRightChopstick = false;
        state = "Thinking";
    }
}
