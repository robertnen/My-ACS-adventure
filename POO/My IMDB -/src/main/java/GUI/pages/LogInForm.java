package GUI.pages;

import GUI.CustomFunctionGUI;
import GUI.upgradedJObjects.RoundedButton;
import GUI.upgradedJObjects.RoundedPasswordField;
import GUI.upgradedJObjects.RoundedTextField;
import GUI.Frames.RunFrame;
import org.example.IMDB;
import org.example.User;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.regex.Pattern;

public class LogInForm extends Page {

    private final Color tintGrey = new Color(177, 186, 195);
    private boolean isEmailWarn = false;
    private boolean isUserWarn = false;
    private User user = null;

    public LogInForm(RunFrame frame) {

        // at the logo banner
        ImageIcon logo1 = new ImageIcon("src/main/java/Assets/images/My_IMDB.png");
        JLabel logo = new JLabel(logo1);

        logo.setBounds(500, 50, 600, 240);
        frame.getBgPanel().add(logo);

        // center panel for login
        JPanel form = new JPanel();
        form.setBounds(550, 360, 500, 400);
        form.setBackground(tintGrey);
        frame.getBgPanel().add(form);

        // email label
        JLabel emailLabel = new JLabel("Email");
        emailLabel.setFont(f);
        emailLabel.setBounds(208, 40, 80, 40);
        form.add(emailLabel);

        // rounded email field
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
        emailField.setBounds(50, 100, 400, 50);
        form.add(emailField);

        // password label
        JLabel passwordLabel = new JLabel("Password");
        passwordLabel.setFont(f);
        passwordLabel.setBounds(182, 195, 160, 40);
        form.add(passwordLabel);

        // rounded password field
        RoundedPasswordField passwordField = new RoundedPasswordField(32);
        passwordField.setText("a simple password example");
        passwordField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                JPasswordField source = (JPasswordField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });
        passwordField.setBounds(50, 255, 400, 50);
        form.add(passwordField);

        // invalid email warning
        JLabel emailWarning = new JLabel("Invalid Email");
        emailWarning.setFont(f);
        emailWarning.setForeground(Color.red);
        emailWarning.setBounds(163, 156, 250, 40);

        // invalid user warning
        JLabel userWarning = new JLabel("User doesn't exist");
        userWarning.setFont(f);
        userWarning.setForeground(Color.red);
        userWarning.setBounds(129, 156, 250, 40);

        // log in button
        RoundedButton submit = new RoundedButton();
        submit.setText("Log in");
        submit.setBackground(tintGrey);
        submit.setBounds(120, 336, 100, 40);
        submit.addActionListener(e -> {
            String email = emailField.getText(), password = passwordField.getText();
            if(!Pattern.compile("^(.+)@(\\S+)$").matcher(email).matches()) {
                if(isUserWarn) {
                    form.remove(userWarning);
                    isUserWarn = false;
                }

                form.add(emailWarning);
                form.repaint();
                isEmailWarn = true;
                return;
            }

            user = CustomFunctionGUI.findUser(email, password);

            if(user == null) {
                if(isEmailWarn) {
                    form.remove(emailWarning);
                    isEmailWarn = false;
                }

                form.add(userWarning);
                form.repaint();
                isUserWarn = true;
                return;
            }

            setUser(user);
            setOption(1);   // home page
            stopRunning();
        });

        form.add(submit);

        // exit button
        RoundedButton exit = new RoundedButton();
        exit.setText("Exit from GUI");
        exit.setBackground(tintGrey);
        exit.setBounds(250, 336, 150, 40);
        exit.addActionListener(e -> {
            IMDB imdb = IMDB.getInstance();
            imdb.saveData();
            System.out.println("Database copy made.");
            frame.dispatchEvent(new WindowEvent(frame, WindowEvent.WINDOW_CLOSING));
        });

        form.add(exit);

        // refresh everything
        frame.repaint();
    }
}
