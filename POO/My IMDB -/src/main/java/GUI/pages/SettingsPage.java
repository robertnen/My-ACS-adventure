package GUI.pages;

import GUI.CustomFunctionGUI;
import GUI.Frames.RunFrame;
import GUI.upgradedJObjects.*;
import org.example.User;
import org.jetbrains.annotations.NotNull;

import javax.swing.*;
import java.awt.*;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.util.regex.Pattern;

public class SettingsPage extends Page {
    public SettingsPage(RunFrame frame, @NotNull User user) {

        new NavBar(frame, this);

        // user avatar
        ImageIcon userImage = new ImageIcon("src/main/java/Assets/images/user.jpeg");
        JLabel userAvatar = new JLabel(userImage);
        userAvatar.setBounds(155, 235, 200, 200);
        userAvatar.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.BLACK));

        frame.getBgPanel().add(userAvatar);

        // user description
        JTextArea userDescription = new JTextArea(CustomFunctionGUI.displayUser(user));
        userDescription.setBounds(130, 600, 450, 215);
        userDescription.setBackground(new Color(201, 198, 198));
        userDescription.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.BLACK));
        userDescription.setEditable(false);
        userDescription.setFont(new Font("sanserif", Font.PLAIN, 15));

        frame.getBgPanel().add(userDescription);

        // email field
        RoundedTextField emailField = new RoundedTextField(32);
        emailField.setText("email_example_A_domain.com...");
        emailField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                JTextField source = (JTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });
        emailField.setBounds(960, 200, 400, 50);
        frame.getBgPanel().add(emailField);

        // name field
        RoundedTextField nameField = new RoundedTextField(32);
        nameField.setText("new name example");
        nameField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                JTextField source = (JTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });
        nameField.setBounds(960, 450, 400, 50);
        frame.getBgPanel().add(nameField);

        // password field
        RoundedPasswordField passwordField = new RoundedPasswordField(32);
        passwordField.setText("new password example");
        passwordField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                JTextField source = (JTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });
        passwordField.setBounds(960, 320, 400, 50);
        frame.getBgPanel().add(passwordField);

        // email warning
        JLabel emailWarning = new JLabel("Invalid email");
        emailWarning.setFont(f);
        emailWarning.setForeground(Color.RED);
        emailWarning.setBounds(1400, 195, 300, 50);

        // email button
        RoundedButton emailButton = new RoundedButton();
        emailButton.setText("Submit email");
        emailButton.addActionListener(e -> {
            if(!Pattern.compile("^(.+)@(\\S+)$").matcher(emailField.getText()).matches()) {
                frame.getBgPanel().add(emailWarning);
                frame.repaint();
                return;
            }

            user.getInformation().getCredentials().setEmail(emailField.getText());
        });
        emailButton.setBounds(530, 200, 330, 50);
        frame.getBgPanel().add(emailButton);

        // password button
        RoundedButton passwordButton = new RoundedButton();
        passwordButton.setText("Submit password");
        passwordButton.addActionListener(e ->
            user.getInformation().getCredentials().setPassword(passwordField.getText())
        );
        passwordButton.setBounds(530, 320, 330, 50);
        frame.getBgPanel().add(passwordButton);

        // name button
        RoundedButton nameButton = new RoundedButton();
        nameButton.setText("Submit name");
        nameButton.addActionListener(e -> {
            user.setUsername(user.generateUniqueUsername(nameField.getText()));
            frame.getBgPanel().remove(userDescription);
            userDescription.setText(CustomFunctionGUI.displayUser(user));
            frame.getBgPanel().add(userDescription);
            System.out.println(user.getUsername());
        });
        nameButton.setBounds(530, 450, 330, 50);
        frame.getBgPanel().add(nameButton);

        frame.repaint();
    }
}
