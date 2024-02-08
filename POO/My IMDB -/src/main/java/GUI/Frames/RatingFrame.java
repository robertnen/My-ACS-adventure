package GUI.Frames;

import GUI.CustomFunctionGUI;
import GUI.upgradedJObjects.RoundedButton;
import GUI.upgradedJObjects.RoundedTextField;
import org.example.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.event.WindowEvent;

public class RatingFrame extends JFrame {
    protected final String title = "My IMDB - Rating";
    protected final ImageIcon icon = new ImageIcon("src/main/java/Assets/images/My_IMDB_icon.png");

    protected final Color bgColor = new Color(100, 118, 135);
    protected JPanel bgPanel = new JPanel();
    protected Font f2 = new Font("sanserif", Font.PLAIN, 15);
    protected int width = 720;
    protected int height = 1080;
    public RatingFrame(User user) {
        if(user.getUserType() != AccountType.Regular) return;
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
        productionTitleField.setText(user.getUsername());
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

        // comment
        RoundedTextField commentField = new RoundedTextField(5);
        commentField.setText("Comment");
        commentField.setFont(f2);
        commentField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                RoundedTextField source = (RoundedTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });
        commentField.setBounds(140, 400, 440, 120);
        bgPanel.add(commentField);

        // rating
        RoundedTextField ratingField = new RoundedTextField(5);
        ratingField.setText("Rating");
        ratingField.setFont(f2);
        ratingField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                RoundedTextField source = (RoundedTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });
        ratingField.setBounds(140, 580, 440, 120);
        bgPanel.add(ratingField);

        // submit button
        RoundedButton submit = new RoundedButton();
        submit.setText("Submit");
        submit.setFont(f2);
        submit.addActionListener(e -> {
            String title = productionTitleField.getText(), comment = commentField.getText(), rating = ratingField.getText();
            Production p = CustomFunctionGUI.findProduction(title);
            if(p == null) return;

            int rat = 5;

            try {
                rat = Integer.parseInt(rating);
                if(rat < 0) rat = 0;
                if(rat > 10) rat = 10;
            } catch (NumberFormatException ignored) {}

            Rating r = new Rating(user.getUsername(), comment, rat);

            p.getRatings().add(r);
            dispatchEvent(new WindowEvent(this, WindowEvent.WINDOW_CLOSING));

        });
        submit.setBounds(250, 750, 200, 90);
        bgPanel.add(submit);

        setVisible(true);
        repaint();
    }
}
