package GUI.pages;

import GUI.CustomFunctionGUI;
import GUI.upgradedJObjects.NavBar;
import GUI.upgradedJObjects.RoundedButton;
import GUI.Frames.RunFrame;

import javax.swing.*;

public class SearchPage extends Page {
    private int choice = -1;
    public SearchPage(RunFrame frame, String input, int option) {

        new NavBar(frame, this);
        this.setSearchText(input);

        if(input.equals("")) {
            setOption(1);
            stopRunning();
            return;
        }

        choice = option;
        if(choice == -1) choice = 0; // default search

        String result;

        switch(choice) {
            case 0 -> result = CustomFunctionGUI.displayResults(input);
            case 1 -> result = CustomFunctionGUI.displayResultsByGender(input);
            case 2 -> result = CustomFunctionGUI.displayResultsByActor(input);
            case 3 -> result = CustomFunctionGUI.displayResultsBySeries(input);
            case 4 -> result = CustomFunctionGUI.displayResultsByMovie(input);
            case 5 -> result = CustomFunctionGUI.displayResultsByYear(input);
            case 6 -> result = CustomFunctionGUI.displayResultsByAverageRating(input);
            default -> result = CustomFunctionGUI.displayResultsByNumberOfRatings(input);
        }

        // result field
        JTextArea resultsField = new JTextArea(result);
        resultsField.setEditable(false);
        resultsField.setBackground(tintGrey);
        resultsField.setBounds(100, 170, 680, 660);

        frame.getBgPanel().add(resultsField);

        // genre button
        RoundedButton genreButton = new RoundedButton();
        genreButton.setText("By Genre");
        genreButton.addActionListener(e -> {
                    choice = 1;
                    setSearchText(input);
                    setOption(7);
                    stopRunning();
                }
        );
        genreButton.setBounds(870, 170, 290, 90);

        frame.getBgPanel().add(genreButton);

        // actor button
        RoundedButton actorButton = new RoundedButton();
        actorButton.setText("By Actor");
        actorButton.addActionListener(e -> {
                    choice = 2;
                    setSearchText(input);
                    setOption(7);
                    stopRunning();
                }
        );
        actorButton.setBounds(1240, 170, 290, 90);

        frame.getBgPanel().add(actorButton);

        // series button
        RoundedButton seriesButton = new RoundedButton();
        seriesButton.setText("By Series");
        seriesButton.addActionListener(e -> {
                    choice = 3;
                    setSearchText(input);
                    setOption(7);
                    stopRunning();
                }
        );
        seriesButton.setBounds(870, 330, 290, 90);

        frame.getBgPanel().add(seriesButton);

        // movie button
        RoundedButton movieButton = new RoundedButton();
        movieButton.setText("By Movie");
        movieButton.addActionListener(e -> {
                    choice = 4;
                    setSearchText(input);
                    setOption(7);
                    stopRunning();
                }
        );
        movieButton.setBounds(1240, 330, 290, 90);

        frame.getBgPanel().add(movieButton);

        // series button
        RoundedButton yearButton = new RoundedButton();
        yearButton.setText("By Year");
        yearButton.addActionListener(e -> {
                    choice = 5;
                    setSearchText(input);
                    setOption(7);
                    stopRunning();
                }
        );
        yearButton.setBounds(870, 490, 290, 90);

        frame.getBgPanel().add(yearButton);

        // average button
        RoundedButton averageButton = new RoundedButton();
        averageButton.setText("By Average Rating");
        averageButton.addActionListener(e -> {
                    choice = 6;
                    setSearchText(input);
                    setOption(7);
                    stopRunning();
                }
        );
        averageButton.setBounds(1240, 490, 290, 90);

        frame.getBgPanel().add(averageButton);

        // minimum button
        RoundedButton minimumButton = new RoundedButton();
        minimumButton.setText("By minimum number of Ratings");
        minimumButton.addActionListener(e -> {
                    choice = 7;
                    setSearchText(input);
                    setOption(7);
                    stopRunning();
                }
        );
        minimumButton.setBounds(1060, 660, 290, 90);

        frame.getBgPanel().add(minimumButton);

        frame.repaint();
    }

    public int getChoice() {
        return choice;
    }
}
