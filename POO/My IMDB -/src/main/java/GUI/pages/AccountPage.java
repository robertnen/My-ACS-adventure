package GUI.pages;

import GUI.CustomFunctionGUI;
import GUI.upgradedJObjects.NavBar;
import GUI.Frames.RunFrame;
import org.example.User;

import javax.swing.*;
import java.awt.*;

public class AccountPage extends Page {
    public AccountPage(RunFrame frame, User user) {
        new NavBar(frame, this);

        // user avatar
        ImageIcon userImage = new ImageIcon("src/main/java/Assets/images/user.jpeg");
        JLabel userAvatar = new JLabel(userImage);
        userAvatar.setBounds(155, 200, 200, 200);
        userAvatar.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.BLACK));

        frame.getBgPanel().add(userAvatar);

        // user description
        JTextArea userDescription = new JTextArea(CustomFunctionGUI.displayUserFull(user));
        userDescription.setBounds(470, 200, 1000, 550);
        userDescription.setBackground(new Color(201, 198, 198));
        userDescription.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.BLACK));
        userDescription.setEditable(false);
        userDescription.setFont(new Font("sanserif", Font.PLAIN, 12));

        frame.getBgPanel().add(userDescription);
        frame.repaint();
    }
}
