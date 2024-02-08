package GUI.pages;

import GUI.CustomFunctionGUI;
import GUI.upgradedJObjects.NavBar;
import GUI.upgradedJObjects.RoundedButton;
import GUI.Frames.RunFrame;
import org.example.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.util.Date;

public class CreateRequestPage extends Page {
    public CreateRequestPage(RunFrame frame, User user) {
        new NavBar(frame, this);

        // to field
        JTextField toField = new JTextField("   User to send...");
        toField.setBounds(560, 370, 470, 60);
        toField.setBackground(new Color(201, 198, 198));
        toField.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.BLACK));
        toField.setFont(new Font("sanserif", Font.PLAIN, 15));
        toField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                JTextField source = (JTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });

        frame.getBgPanel().add(toField);

        // name field
        JTextField nameField = new JTextField("   Name of production/actor...");
        nameField.setBounds(1160, 370, 250, 60);
        nameField.setBackground(new Color(201, 198, 198));
        nameField.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.BLACK));
        nameField.setFont(new Font("sanserif", Font.PLAIN, 15));
        nameField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                JTextField source = (JTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });

        frame.getBgPanel().add(nameField);

        // description field
        JTextField descriptionField = new JTextField("   Describe the request...");
        descriptionField.setBounds(560, 450, 470, 250);
        descriptionField.setBackground(new Color(201, 198, 198));
        descriptionField.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.BLACK));
        descriptionField.setFont(new Font("sanserif", Font.PLAIN, 15));
        descriptionField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                JTextField source = (JTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });

        frame.getBgPanel().add(descriptionField);

        // type of requests chooser
        JRadioButton[] radio = new JRadioButton[4];
        ButtonGroup radioGroup = new ButtonGroup();
        String[] options = {"Delete Account", "Actor Issue", "Movie Issue", "Others"};

        for(int i = 0; i < 4; i++) {
            radio[i] = new JRadioButton(options[i]);
            radio[i].setBounds(540 + i * 150, 300, 150, 50);
            radio[i].setBackground(frame.getBgColor());
            radioGroup.add(radio[i]);
            frame.getBgPanel().add(radio[i]);
        }

        // warning radio
        JLabel radioWarning = new JLabel("Please choose a type of request");
        radioWarning.setFont(f);
        radioWarning.setForeground(Color.RED);
        radioWarning.setBounds(590, 250, 500, 50);

        // user warning
        JLabel userWarning = new JLabel("User doesn't exist");
        userWarning.setFont(f);
        userWarning.setForeground(Color.RED);
        userWarning.setBounds(680, 790, 500, 50);

        // submit
        RoundedButton submitButton = new RoundedButton();
        submitButton.setText("Submit password");
        submitButton.addActionListener(e -> {
                    int choice = -1;

                    for(int i = 0; i < 4; i++)
                        if(radio[i].isSelected()) choice = i;

                    if(choice == -1) {
                        frame.getBgPanel().add(radioWarning);
                        frame.repaint();
                        return;
                    }

                    User u = CustomFunctionGUI.findUser(toField.getText());

                    if(u == null && (choice == 1 || choice == 2)) {
                        frame.getBgPanel().add(userWarning);
                        frame.repaint();
                        return;
                    }

                    Request request = new Request();
                    request.setDescription(descriptionField.getText());
                    request.setUsername(user.getUsername());
                    request.setTo(toField.getText());
                    request.setCreatedDate(new Date());

                    RequestType type;
                    switch(choice) {
                        case 1 -> type = RequestType.DELETE_ACCOUNT;
                        case 2 -> type = RequestType.ACTOR_ISSUE;
                        case 3 -> type = RequestType.MOVIE_ISSUE;
                        default -> type = RequestType.OTHERS;
                    }

                    request.setType(type);

                    // admin only
                    if(type == RequestType.DELETE_ACCOUNT || type == RequestType.OTHERS) {
                        request.setTo("Admin");
                        new RequestsHolder().getAdminRequests().add(request);
                        setOption(1);
                        stopRunning();
                        return;
                    }

                    if(type == RequestType.ACTOR_ISSUE) request.setActorName(nameField.getText());
                    else request.setMovieTitle(nameField.getText());

                    if(u.getUserType() == AccountType.Regular) ((Regular) u).createRequest(request);
                    else ((Contributor) u).createRequest(request);

                    setOption(1);
                    stopRunning();
                }
        );

        submitButton.setBackground(frame.getBgColor());
        submitButton.setBounds(690, 720, 220, 60);
        frame.getBgPanel().add(submitButton);

        frame.repaint();
    }
}
