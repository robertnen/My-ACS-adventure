package GUI.Frames;

import javax.swing.*;
import java.awt.*;

public class RunFrame extends JFrame {

    private boolean isRunning = true;
    private final int width = 1600;
    private final int height = 900;
    private JPanel bgPanel = new JPanel();
    private final String title = "My IMDB";
    private final ImageIcon icon = new ImageIcon("src/main/java/Assets/images/My_IMDB_icon.png");

    private final Color bgColor = new Color(100, 118, 135);

    public RunFrame() {
        setIconImage(icon.getImage());
        setTitle(this.title);
        setSize(this.width, this.height);
        setResizable(false);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        bgPanel.setBackground(bgColor);
        add(bgPanel, BorderLayout.CENTER);

        bgPanel.setLayout(new GridBagLayout());

        // for when the frame is closed
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent e) {isRunning = false;}
        });

        setLocationRelativeTo(null);
        setVisible(true);
    }

    public boolean isRunning() {
        return isRunning;
    }

    public void setRunning(boolean running) {
        isRunning = running;
    }

    public Color getBgColor() {
        return bgColor;
    }

    public JPanel getBgPanel() {
        return bgPanel;
    }

    public void cleanFrame() {
        getContentPane().removeAll();
        bgPanel.removeAll();

        bgPanel.setBackground(bgColor);
        add(bgPanel, BorderLayout.CENTER);

        bgPanel.setLayout(new GridBagLayout());
        repaint();
    }
}
