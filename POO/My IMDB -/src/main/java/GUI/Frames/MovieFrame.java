package GUI.Frames;

import GUI.upgradedJObjects.RoundedButton;
import GUI.upgradedJObjects.RoundedTextField;
import org.example.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.event.WindowEvent;
import java.util.ArrayList;

public class MovieFrame extends JFrame {
    protected final String title = "My IMDB - Movie";
    protected final ImageIcon icon = new ImageIcon("src/main/java/Assets/images/My_IMDB_icon.png");

    protected final Color bgColor = new Color(100, 118, 135);
    protected JPanel bgPanel = new JPanel();
    protected Font f2 = new Font("sanserif", Font.PLAIN, 15);
    protected int width = 720;
    protected int height = 1080;
    public MovieFrame(User user) {
        if(user.getUserType() == AccountType.Regular) return;
        setIconImage(icon.getImage());
        setTitle(this.title);
        setSize(this.width, this.height);
        setResizable(false);

        setLocationRelativeTo(null);

        bgPanel.setBackground(bgColor);
        add(bgPanel, BorderLayout.CENTER);

        bgPanel.setLayout(null);

        // production title
        RoundedTextField productionTitleField = new RoundedTextField(5);
        productionTitleField.setText("Production title");
        productionTitleField.setFont(f2);
        productionTitleField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                RoundedTextField source = (RoundedTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });
        productionTitleField.setBounds(140, 220, 440, 120);
        bgPanel.add(productionTitleField);

        // release year
        RoundedTextField releaseYearField = new RoundedTextField(5);
        releaseYearField.setText("Release year");
        releaseYearField.setFont(f2);
        releaseYearField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                RoundedTextField source = (RoundedTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });
        releaseYearField.setBounds(140, 400, 440, 120);
        bgPanel.add(releaseYearField);

        // duration
        RoundedTextField durationField = new RoundedTextField(5);
        durationField.setText("Duration");
        durationField.setFont(f2);
        durationField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                RoundedTextField source = (RoundedTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });
        durationField.setBounds(140, 580, 440, 120);
        bgPanel.add(durationField);

        // submit button
        RoundedButton submit = new RoundedButton();
        submit.setText("Submit");
        submit.setFont(f2);
        submit.addActionListener(e -> {
            String movieTitle = productionTitleField.getText(), releaseYear = releaseYearField.getText(), duration = durationField.getText();
            Production p = new Movie();
            p.setTitle(movieTitle);

            try {
                ((Movie) p).setReleaseYear(Integer.parseInt(releaseYear));
            } catch (NumberFormatException ee) {
                ((Movie) p).setReleaseYear(1900);
            }

            ((Movie) p).setDuration(duration);

            user.getProductionsContribution().add(p.getTitle());
            IMDB.getInstance().getProductions().add(p);
            dispatchEvent(new WindowEvent(this, WindowEvent.WINDOW_CLOSING));
        });
        submit.setBounds(250, 750, 200, 90);
        bgPanel.add(submit);

        setVisible(true);
        repaint();
    }
}
