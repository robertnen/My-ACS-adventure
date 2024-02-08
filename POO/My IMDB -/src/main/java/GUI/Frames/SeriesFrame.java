package GUI.Frames;

import javax.swing.*;
import java.awt.*;

public class SeriesFrame extends JFrame {
    protected final String title = "My IMDB - Series";
    protected final ImageIcon icon = new ImageIcon("src/main/java/Assets/images/My_IMDB_icon.png");

    protected final Color bgColor = new Color(100, 118, 135);
    protected JPanel bgPanel = new JPanel();
    protected int width = 720;
    protected int height = 1080;
    public SeriesFrame() {
        setIconImage(icon.getImage());
        setTitle(this.title);
        setSize(this.width, this.height);
        setResizable(false);

        bgPanel.setBackground(bgColor);
        add(bgPanel, BorderLayout.CENTER);

        bgPanel.setLayout(new GridBagLayout());
    }
}
