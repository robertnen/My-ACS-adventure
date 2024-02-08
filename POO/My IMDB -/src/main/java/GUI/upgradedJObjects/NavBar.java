package GUI.upgradedJObjects;

import GUI.Frames.RunFrame;
import GUI.pages.Page;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class NavBar {
    public NavBar(RunFrame frame, Page page) {

        Color navBarColor = new Color(245, 245,245);

        // navbar
        JPanel form = new JPanel();
        form.setBounds(0, 0, 1600, 90);
        form.setBackground(navBarColor);
        form.setBorder(BorderFactory.createMatteBorder(0, 0, 2, 0, Color.BLACK));
        frame.getBgPanel().add(form);

        BufferedImage homeImage = null;
        try {
            homeImage = ImageIO.read(new File("src/main/java/Assets/images/My_IMDB_icon.png"));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        JButton homeButton = new JButton(new ImageIcon(homeImage));
        homeButton.setBounds(0, 0, 80, 90);
        homeButton.setBorder(BorderFactory.createEmptyBorder());
        homeButton.setContentAreaFilled(false);

        // go back to homepage
        homeButton.addActionListener(e -> {page.setOption(1); page.stopRunning();});

        form.add(homeButton);

        Font f = new Font("sanserif", Font.PLAIN, 18);

        // top-right buttons

        // log out
        JButton logOutButton = new JButton("Log out");
        logOutButton.setBounds(1600 - 120, 0, 120, 88);
        logOutButton.setBackground(navBarColor);
        logOutButton.setBorder(BorderFactory.createEmptyBorder());
        logOutButton.setFont(f);

        // go to log in
        logOutButton.addActionListener(e -> {page.setOption(0); page.stopRunning();});

        form.add(logOutButton);

        // account
        JButton accountButton = new JButton("My account");
        accountButton.setBounds(1600 - 240, 0, 120, 88);
        accountButton.setBackground(navBarColor);
        accountButton.setBorder(BorderFactory.createEmptyBorder());
        accountButton.setFont(f);

        // go to account
        accountButton.addActionListener(e -> {page.setOption(4); page.stopRunning();});

        form.add(accountButton);

        // settings
        JButton settingsButton = new JButton("Settings");
        settingsButton.setBounds(1600 - 360, 0, 120, 88);
        settingsButton.setBackground(navBarColor);
        settingsButton.setBorder(BorderFactory.createEmptyBorder());
        settingsButton.setFont(f);

        // go to settings
        settingsButton.addActionListener(e -> {page.setOption(3); page.stopRunning();});

        form.add(settingsButton);

        // create request
        JButton addReqButton = new JButton("Create request");
        addReqButton.setBounds(1600 - 480, 0, 120, 88);
        addReqButton.setBackground(navBarColor);
        addReqButton.setBorder(BorderFactory.createEmptyBorder());
        addReqButton.setFont(f);

        // go to create request
        addReqButton.addActionListener(e -> {page.setOption(5); page.stopRunning();});

        form.add(addReqButton);

        // view requests
        JButton remReqButton = new JButton("View requests");
        remReqButton.setBounds(1600 - 620, 0, 140, 88);
        remReqButton.setBackground(navBarColor);
        remReqButton.setBorder(BorderFactory.createEmptyBorder());
        remReqButton.setFont(f);

        // go to view requests
        remReqButton.addActionListener(e -> {page.setOption(6); page.stopRunning();});

        form.add(remReqButton);

        // add / modify
        JButton addButton = new JButton("+");
        addButton.setBounds(90, 0, 80, 88);
        addButton.setBackground(navBarColor);
        addButton.setBorder(BorderFactory.createEmptyBorder());
        addButton.setFont(f);

        addButton.addActionListener(e -> {page.setOption(8); page.stopRunning();});

        form.add(addButton);

        // go to view requests
        remReqButton.addActionListener(e -> {page.setOption(6); page.stopRunning();});

        form.add(remReqButton);

        // search bar
        RoundedTextField searchField = new RoundedTextField(32);
        searchField.setText("         Search recommendation: Trailer Dacia Berlina 'Husa volan imitatie de piele ce imita lemnul'");
        searchField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                JTextField source = (JTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });
        searchField.setBounds(180, 23, 570, 42);
        form.add(searchField);

        // search bar button
        JButton searchButton = new JButton("Search");
        searchButton.setBounds(780, 23, 140, 42);
        searchButton.setBackground(navBarColor);
        searchButton.setFont(f);

        // go to search page
        searchButton.addActionListener(e -> {
            page.setOption(7);
            page.stopRunning();

            page.setSearchText(searchField.getText());
        });

        form.add(searchButton);

        form.repaint();
    }
}
