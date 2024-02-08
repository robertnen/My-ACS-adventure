package GUI.pages;

import GUI.CustomFunctionGUI;
import GUI.Frames.ActorFrame;
import GUI.Frames.MovieFrame;
import GUI.Frames.RatingFrame;
import GUI.upgradedJObjects.NavBar;
import GUI.upgradedJObjects.RoundedButton;
import GUI.upgradedJObjects.RoundedTextField;
import GUI.Frames.RunFrame;
import org.example.AccountType;
import org.example.Production;
import org.example.Rating;
import org.example.User;

import javax.swing.*;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.util.List;

public class OthersPage extends Page {
    private String production = "_";

    public OthersPage(RunFrame frame, User user, String production) {
        new NavBar(frame, this);

        // contribution field
        RoundedTextField contributionField = new RoundedTextField(15);
        contributionField.setText("Name/Title");
        contributionField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                JTextField source = (JTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
            }
        });
        contributionField.setBounds(80, 140, 210, 90);
        contributionField.setFont(f);

        frame.getBgPanel().add(contributionField);

        // delete field
        RoundedButton deleteField = new RoundedButton();
        deleteField.setText("Delete");
        deleteField.setFont(f);
        deleteField.addActionListener(e -> {
            if(user.getUserType() == AccountType.Regular) return;

            if(user.getProductionsContribution().remove(contributionField.getText()) || user.getActorsContribution().remove(contributionField.getText())) {
                setOption(8);
                stopRunning();
            }
        });
        deleteField.setBounds(370, 140, 210, 90);

        frame.getBgPanel().add(deleteField);

        // contribution area
        JTextArea contributionArea = new JTextArea(CustomFunctionGUI.displayContributions(user));
        contributionArea.setFont(f2);
        contributionArea.setEditable(false);
        contributionArea.setBounds(80, 290, 500, 540);

        frame.getBgPanel().add(contributionArea);

        // rating field
        RoundedTextField ratingField = new RoundedTextField(15);
        ratingField.setText("Production name");
        this.production = production;
        if(!production.equals("_")) ratingField.setText(this.production);
        else ratingField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                JTextField source = (JTextField) e.getComponent();
                source.setText("");
                source.removeFocusListener(this);
                }
            });
        ratingField.setBounds(640, 340, 290, 90);
        ratingField.setFont(f);

        frame.getBgPanel().add(ratingField);

        // add rating field
        RoundedButton addField = new RoundedButton();
        addField.setText("Add rating");
        addField.setFont(f3);
        addField.addActionListener(e -> new RatingFrame(user));
        addField.setBounds(960, 340, 210, 90);

        frame.getBgPanel().add(addField);

        // rating area
        JTextArea ratingArea = new JTextArea(CustomFunctionGUI.displayRatings(CustomFunctionGUI.findProduction(this.production)));
        ratingArea.setFont(f2);
        ratingArea.setEditable(false);
        ratingArea.setBounds(640, 480, 940, 350);

        frame.getBgPanel().add(ratingArea);

        // remove rating field
        RoundedButton removeField = new RoundedButton();
        removeField.setText("Remove rating");
        removeField.setFont(f3);
        removeField.addActionListener(e -> {
            this.production = ratingField.getText();
            setOption(8);
            stopRunning();

            if(user.getUserType() != AccountType.Regular) return;
            Production p = CustomFunctionGUI.findProduction(this.production);
            if(p == null) return;

            List<Rating> ratings = p.getRatings();
            for(Rating r : ratings)
                if(r.getUsername().equals(user.getUsername()))
                    ratings.remove(r);
        });
        removeField.setBounds(1200, 340, 210, 90);

        frame.getBgPanel().add(removeField);

        // view ratings field
        RoundedButton viewField = new RoundedButton();
        viewField.setText("View ratings");
        viewField.setFont(f2);
        viewField.addActionListener(e -> {
            this.production = ratingField.getText();
            setOption(8);
            stopRunning();

            Production p = CustomFunctionGUI.findProduction(this.production);
            if(p == null) return;
            ratingField.setText(CustomFunctionGUI.displayRatings(p));
        });
        viewField.setBounds(1440, 340, 140, 90);

        frame.getBgPanel().add(viewField);

        // add actor
        RoundedButton actorField = new RoundedButton();
        actorField.setText("Actor");
        actorField.setFont(f3);
        actorField.addActionListener(e -> new ActorFrame(user));
        actorField.setBounds(950, 140, 215, 90);

        frame.getBgPanel().add(actorField);

        // add production
        RoundedButton movieField = new RoundedButton();
        movieField.setText("Production");
        movieField.setFont(f3);
        movieField.addActionListener(e -> new MovieFrame(user));
        movieField.setBounds(1210, 140, 215, 90);

        frame.getBgPanel().add(movieField);

        frame.repaint();
    }

    public String getProduction() {
        return production;
    }

    public void setProduction(String production) {
        this.production = production;
    }
}
