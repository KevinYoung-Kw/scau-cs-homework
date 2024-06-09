package main.java;

import java.io.IOException;
import java.util.logging.*;

public class logger {
    private static final Logger logger = Logger.getLogger(logger.class.getName());

    public static void setupLogger() {
        FileHandler fileHandler;
        try {
            String timestamp = String.valueOf(System.currentTimeMillis());
            fileHandler = new FileHandler(timestamp + ".txt");

            SimpleFormatter formatter = new SimpleFormatter();
            fileHandler.setFormatter(formatter);

            logger.addHandler(fileHandler);

            logger.setLevel(Level.OFF);
        } catch (IOException e) {
            logger.log(Level.SEVERE, "Error setting up logger", e);
        }
    }

    public static void logMessage(String message) {
        logger.info(message);
    }
}