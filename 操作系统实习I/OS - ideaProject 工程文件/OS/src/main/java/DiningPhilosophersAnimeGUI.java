package main.java;

import javax.sound.sampled.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.URL;

public class DiningPhilosophersAnimeGUI extends JPanel {
    private final DiningTable diningTable;
    private final Image[] philosopherImages;
    private final Image chopstickImage;
    private final Image tableImage;

    private final JButton startButton;
    private final JButton stopButton;
    private final JButton musicButton;
    private final JTextField speedInput;
    private final JTextArea consoleOutput;
    private final JLabel speedLabel;

    private Clip clip;

    public DiningPhilosophersAnimeGUI(DiningTable diningTable) throws FileNotFoundException {
        this.diningTable = diningTable;
        this.philosopherImages = new Image[3];

        // Load images
        this.chopstickImage = loadImage("/chopstick.png");
        this.tableImage = loadImage("/table.png");
        this.philosopherImages[0] = loadImage("/thinking.png");
        this.philosopherImages[1] = loadImage("/eating.png");
        this.philosopherImages[2] = loadImage("/waiting.png");

        this.speedInput = new JTextField("1000", 6);
        this.speedInput.addActionListener(e -> updateSpeed());

        this.speedLabel = new JLabel();
        updateSpeedLabel(1000);

        this.startButton = createStyledButton("start", e -> diningTable.startDining());
        this.stopButton = createStyledButton("stop", e -> stopDining());
        this.musicButton = createStyledButton("music", e -> toggleMusic());

        this.clip = loadAudioClip("Sleep Walking Orchestra - BUMP OF C.wav");

        this.consoleOutput = new JTextArea(7, 30);
        this.consoleOutput.setEditable(false);
        this.consoleOutput.setFont(new Font("Monospaced", Font.PLAIN, 14));
        JScrollPane scrollPane = new JScrollPane(consoleOutput);

        JPanel consolePanel = new JPanel(new BorderLayout());
        consolePanel.setBorder(BorderFactory.createTitledBorder("Console Output"));
        consolePanel.add(scrollPane, BorderLayout.CENTER);

        this.setLayout(new BorderLayout());
        JPanel controlPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        controlPanel.setBorder(BorderFactory.createEmptyBorder(0, 10, 0, 10));
        controlPanel.add(startButton);
        controlPanel.add(stopButton);
        controlPanel.add(musicButton);
        controlPanel.add(new JLabel("Press Enter to change speed:"));
        controlPanel.add(speedInput);
        controlPanel.add(speedLabel);

        this.add(controlPanel, BorderLayout.NORTH);
        this.add(consolePanel, BorderLayout.SOUTH);

        System.setOut(new PrintStream(new TextAreaOutputStream(consoleOutput)));
        System.setErr(new PrintStream(new TextAreaOutputStream(consoleOutput)));
    }

    private JButton createStyledButton(String text, ActionListener actionListener) {
        JButton button = new JButton(text);
        button.addActionListener(actionListener);
        button.setFont(new Font("Arial", Font.BOLD, 14));
        button.setBackground(new Color(70, 130, 180));
        button.setForeground(Color.WHITE);
        button.setFocusPainted(false);
        button.setBorder(BorderFactory.createRaisedBevelBorder());
        return button;
    }

    private void updateSpeed() {
        try {
            int speed = Integer.parseInt(speedInput.getText());
            Philosopher.setSleepTime(speed);
            updateSpeedLabel(speed);
            diningTable.restartDining();
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Please enter a valid number", "Invalid Input", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void updateSpeedLabel(int speed) {
        speedLabel.setText("Current Speed: " + speed + " ms");
        speedLabel.setFont(new Font("Arial", Font.PLAIN, 12));
    }

    private void stopDining() {
        Philosopher.isRunning = false;
        try {
            diningTable.stopDining();
        } catch (InterruptedException ex) {
            throw new RuntimeException(ex);
        }
    }

    private void toggleMusic() {
        if (clip != null) {
            if (clip.isRunning()) {
                clip.stop();
            } else {
                clip.setFramePosition(0);
                clip.start();
            }
        }
    }

    private Clip loadAudioClip(String path) {
        try {
            URL url = getClass().getClassLoader().getResource(path);
            if (url == null) {
                System.err.println("File not found: " + path);
                return null;
            }
            AudioInputStream audioIn = AudioSystem.getAudioInputStream(url);
            Clip clip = AudioSystem.getClip();
            clip.open(audioIn);
            return clip;
        } catch (UnsupportedAudioFileException | IOException | LineUnavailableException e) {
            e.printStackTrace();
            return null;
        }
    }

    private Image loadImage(String path) {
        URL url = getClass().getResource(path);
        if (url == null) {
            System.err.println("File not found: " + path);
            return null;
        }
        return new ImageIcon(url).getImage();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g.create();

        // 设计时的宽度和高度
        int originalWidth = 700;
        int originalHeight = 800;

        // 当前面板的宽度和高度
        int currentWidth = getWidth();
        int currentHeight = getHeight();

        // 计算宽度和高度的比例
        double widthRatio = (double) currentWidth / originalWidth;
        double heightRatio = (double) currentHeight / originalHeight;
        double scale = Math.min(widthRatio, heightRatio);

        int centerX = currentWidth / 2;
        int centerY = currentHeight / 2 - (int) (80 * scale);
        int radius = (int) (200 * scale);

        g2d.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 0.75f));
        g2d.drawImage(tableImage, centerX - (int) (90 * scale), centerY - (int) (60 * scale), (int) (220 * scale), (int) (170 * scale), this);
        g2d.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 1.0f));

        for (int i = 0; i < 5; i++) {
            double angle = 2 * Math.PI / 5 * i;
            int x = (int) (centerX + radius * Math.cos(angle));
            int y = (int) (centerY + radius * Math.sin(angle));

            Philosopher philosopher = diningTable.getPhilosophers()[i];
            String state = philosopher.getState();

            Image philosopherImage = philosopherImages[0];
            if ("Eating".equals(state)) {
                philosopherImage = philosopherImages[1];
            } else if ("Waiting".equals(state)) {
                philosopherImage = philosopherImages[2];
            }
            g2d.drawImage(philosopherImage, x - (int) (60 * scale), y - (int) (60 * scale), (int) (120 * scale), (int) (120 * scale), this);

            g2d.setColor(Color.BLACK);
            g2d.setFont(new Font("Arial", Font.BOLD, (int) (14 * scale)));
            g2d.drawString("PD " + philosopher.getID() + " " + state, x - (int) (60 * scale), y - (int) (70 * scale));

            int philosopherLeft = x - (int) (50 * scale);
            int philosopherRight = x + (int) (50 * scale);

            Chopstick chopstick = diningTable.getChopsticks()[i];
            int chopstickX = (int) (centerX + (radius - (120 * scale)) * Math.cos(angle));
            int chopstickY = (int) (centerY + (radius - (120 * scale)) * Math.sin(angle));

            if (chopstick.isUsed()) {
                g2d.setColor(Color.WHITE);
                if (philosopher.hasLeftChopstick() && philosopher.hasRightChopstick()) {
                    g2d.drawImage(chopstickImage, philosopherLeft + (int) (20 * scale), y + (int) (70 * scale), (int) (65 * scale), (int) (65 * scale), this);
                    g2d.drawImage(chopstickImage, philosopherRight - (int) (20 * scale), y + (int) (70 * scale), (int) (65 * scale), (int) (65 * scale), this);
                } else if (philosopher.hasLeftChopstick() && chopstick == philosopher.getLeftChopstick()) {
                    g2d.drawImage(chopstickImage, philosopherLeft - (int) (20 * scale), y + (int) (75 * scale), (int) (65 * scale), (int) (65 * scale), this);
                } else if (philosopher.hasRightChopstick() && chopstick == philosopher.getRightChopstick()) {
                    g2d.drawImage(chopstickImage, philosopherRight + (int) (20 * scale), y + (int) (75 * scale), (int) (65 * scale), (int) (65 * scale), this);
                }
            } else {
                g2d.setColor(Color.BLACK);
                g2d.drawImage(chopstickImage, chopstickX - (int) (30 * scale), chopstickY - (int) (30 * scale), (int) (40 * scale), (int) (40 * scale), this);
            }
        }
        g2d.dispose();
    }


    public void run() {
        // Main loop
        while (true) {
            updateGUI();
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }

    void updateGUI() {
        repaint();
    }

    public void stop() {
        if (clip != null) {
            clip.stop();
            clip.close();
        }
    }

    class TextAreaOutputStream extends OutputStream {
        private final JTextArea textArea;

        public TextAreaOutputStream(JTextArea textArea) {
            this.textArea = textArea;
        }

        @Override
        public void write(int b) {
            textArea.append(String.valueOf((char) b));
            textArea.setCaretPosition(textArea.getDocument().getLength());
        }
    }
}
