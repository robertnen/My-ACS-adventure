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

public class ActorFrame extends JFrame {
    protected final String title = "My IMDB - Actor";
    protected final ImageIcon icon = new ImageIcon("src/main/java/Assets/images/My_IMDB_icon.png");
    protected final Color bgColor = new Color(100, 118, 135);
    protected JPanel bgPanel = new JPanel();
    protected int width = 720;
    protected int height = 1080;
    protected Font f2 = new Font("sanserif", Font.PLAIN, 15);

    public ActorFrame(User user) {
        if(user.getUserType() == AccountType.Regular) return;
        setIconImage(icon.getImage());
        setTitle(this.title);
        setSize(this.width, this.height);
        setResizable(false);

        setLocationRelativeTo(null);

        bgPanel.setBackground(bgColor);
        add(bgPanel, BorderLayout.CENTER);

        bgPanel.setLayout(null);

        // actor name
        RoundedTextField actorNameField = new RoundedTextField(5);
        actorNameField.setText("Actor name");
        actorNameField.setFont(f2);
        actorNameField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                RoundedTextField source = (RoundedTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });
        actorNameField.setBounds(140, 220, 440, 120);
        bgPanel.add(actorNameField);

        // biography
        RoundedTextField biographyField = new RoundedTextField(5);
        biographyField.setText("Actor biography");
        biographyField.setFont(f2);
        biographyField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                RoundedTextField source = (RoundedTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });
        biographyField.setBounds(140, 400, 440, 120);
        bgPanel.add(biographyField);

        // production title
        RoundedTextField productionTitleField = new RoundedTextField(5);
        productionTitleField.setText("Production");
        productionTitleField.setFont(f2);
        productionTitleField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                RoundedTextField source = (RoundedTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });
        productionTitleField.setBounds(140, 580, 440, 120);
        bgPanel.add(productionTitleField);

        // submit button
        RoundedButton submit = new RoundedButton();
        submit.setText("Submit");
        submit.setFont(f2);
        submit.addActionListener(e -> {
            String name = actorNameField.getText(), biography = biographyField.getText(), title = productionTitleField.getText();
            Performances p = new Performances(title, "Movie");
            Actor a = new Actor(name, biography, new ArrayList<>());
            a.getPerformances().add(p);

            user.getActorsContribution().add(a.getName());
            IMDB.getInstance().getActors().add(a);
            dispatchEvent(new WindowEvent(this, WindowEvent.WINDOW_CLOSING));
        });
        submit.setBounds(250, 750, 200, 90);
        bgPanel.add(submit);

        setVisible(true);
        repaint();
    }
}
