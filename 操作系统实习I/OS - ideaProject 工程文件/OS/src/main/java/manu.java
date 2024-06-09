package main.java;

import javax.swing.*;
import java.awt.*;
import java.io.FileNotFoundException;
import java.net.URL;

public class manu {
    private JFrame frame;
    private DiningPhilosophersAnimeGUI gui;
    private DiningTable currentDiningTable;
    private JMenu menu;
    private JPanel introPanel;

    public manu() {
        frame = new JFrame("哲学家进餐问题 - 介绍界面");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(700, 850);
        frame.setLocationRelativeTo(null);

        URL iconUrl = getClass().getResource("/icon.png");
        ImageIcon icon = new ImageIcon(iconUrl);// 创建一个ImageIcon，替换为你的图标文件的路径

        frame.setIconImage(icon.getImage()); // 将ImageIcon设置为JFrame的图标

        JPanel introPanel = new JPanel();
        introPanel.setLayout(new BoxLayout(introPanel, BoxLayout.Y_AXIS));
        introPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20)); // 设置边距

        URL menuUrl = getClass().getResource("/menu.png");
        ImageIcon imageIcon = new ImageIcon(menuUrl);
        // 设置图片大小
        imageIcon.setImage(imageIcon.getImage().getScaledInstance(300, 300, Image.SCALE_DEFAULT));

        JLabel imageLabel = new JLabel(imageIcon);
        imageLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        introPanel.add(imageLabel);

        JLabel introLabel = new JLabel(
                "<html><body style='font-size:13px; font-family:Microsoft YaHei; color: #333333;'>" +
                        "<div style='text-align: left;'>" +
                        "欢迎使用哲学家就餐模拟程序<br>" +
                        "功能：实现了延迟设置，多种策略的哲学家就餐问题模拟<br><br><br>" +
                        "版本：1.2<br>" +
                        "开发次数：2次<br>" +
                        "开发者：葬送的芙莉莲<br><br>" +
                        "[ README ]<br>" +
                        "所有功能均已通过多轮测试<br>" +
                        "选中策略后，即可开始进行模拟<br>" +
                        "在切换策略时，请确保已经按下了停止按钮<br>" +
                        "将鼠标悬停在一些功能上会有提示<br>" +
                        "叉子变大表示被选中，叉子变小表示未被选中<br>" +
                        "sleepTime决定了线程的读写持续时间范围 [0, sleepTime]<br><br>" +
                        "感觉Swing库比Fx库要难多了......" +
                        "</div></body></html>");
        introLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        introPanel.add(Box.createVerticalStrut(20)); // 增加空白
        introPanel.add(introLabel);

        frame.add(introPanel, BorderLayout.CENTER); // 更改为居中显示
        frame.setVisible(true);


        JMenuBar menuBar = new JMenuBar();
        menu = new JMenu("选择策略[鼠标悬停时有解释]");
        menuBar.add(menu);

        JMenuItem exitMenuItem = new JMenuItem("结束程序");
        exitMenuItem.addActionListener(e -> System.exit(0)); // 当菜单项被点击时，结束程序

        // 将菜单项添加到菜单栏
        menuBar.add(exitMenuItem);

        frame.setJMenuBar(menuBar);
        frame.setVisible(true);

        final boolean[] isFirstTime = {true};

        for (Strategy strategy : Strategy.values()) {
            JMenuItem menuItem = new JMenuItem(strategy.getName());
            menuItem.setToolTipText(strategy.getDescription());
            menuItem.addActionListener(e -> {
                try {
                    if (isFirstTime[0]) {
                        frame.remove(introPanel);
                        isFirstTime[0] = false;
                    }
                    initializeGUI(strategy.getId());
                    frame.setTitle("哲学家进餐问题 - " + strategy.getName());
                    frame.revalidate();
                    frame.repaint();
                } catch (FileNotFoundException ex) {
                    ex.printStackTrace();
                    JOptionPane.showMessageDialog(frame, "Error initializing GUI: " + ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
                } catch (InterruptedException ex) {
                    throw new RuntimeException(ex);
                }
            });
            menu.add(menuItem);
        }

        frame.setJMenuBar(menuBar);
        frame.setVisible(true);
    }

    public void initializeGUI(int strategy) throws FileNotFoundException, InterruptedException {
        if (gui != null) {
            gui.stop();
            frame.remove(gui);
        }

        if (currentDiningTable != null) {
            currentDiningTable.stopDining();
        }

        currentDiningTable = new DiningTable(strategy);
        gui = new DiningPhilosophersAnimeGUI(currentDiningTable);
        frame.add(gui);

        logger.logMessage("Initializing GUI with strategy: " + strategy);
        System.out.println("Initializing GUI with strategy: " + strategy);

        new Thread(() -> {
            gui.run();
        }).start();
    }


    public static void main(String[] args) {
        logger.setupLogger();
        SwingUtilities.invokeLater(manu::new);
    }
}

enum Strategy {
    STRATEGY_1(1, "不做任何处理", "<html>策略1：<br>这是最基本的策略，哲学家首先随机获取左侧或右侧的筷子。<br>如果两个筷子都获取成功，哲学家就开始吃饭。</html>"),
    STRATEGY_2(2, "最多4人持筷子", "<html>策略2：<br>这个策略在策略1的基础上添加了一个条件，只有当筷子的使用者少于四个时，哲学家才尝试获取筷子。<br>这是为了避免死锁，因为如果五个哲学家都持有一个筷子，那么他们都无法开始吃饭。</html>"),
    STRATEGY_3(3, "按号奇偶持筷", "<html>策略3：<br>这个策略根据哲学家的ID来决定获取筷子的顺序。<br>如果哲学家的ID是奇数，那么他首先获取左边的筷子，然后获取右边的筷子。<br>如果哲学家的ID是偶数，那么他首先获取右边的筷子，然后获取左边的筷子。<br>这是为了避免死锁，因为至少有一个哲学家能够获取到两个筷子。</html>"),
    STRATEGY_4(4, "同时拿两支筷子", "<html>策略4：<br>这个策略是在策略1的基础上，将获取筷子的操作放在一个同步块中。<br>这样可以保证哲学家在获取筷子时不会被其他哲学家打断。<br>这是为了避免死锁，因为哲学家在获取筷子时不会被其他哲学家打断，所以他总是能够获取到两个筷子。</html>");

    private final int id;
    private final String name;
    private final String description;

    Strategy(int id, String name, String description) {
        this.id = id;
        this.name = name;
        this.description = description;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }
}
