package GUI;

import GUI.pages.*;
import GUI.Frames.RunFrame;
import org.example.AccountType;
import org.example.User;

import java.awt.*;

public class MainGUI {

    private final Audio player = new Audio();
    private final Color bgColor = new Color(100, 118, 135);
    private RunFrame frame = null;

    private User user = null;
    private User userBackup = null;
    private int order = 0;
    private int searchOption = -1;
    private boolean isView = false, isOthers = false;

    public void main() {
        if(frame != null && frame.isRunning()) {
            System.out.println("You are already having a window opened!");
            return;
        }

        frame = new RunFrame();

        // start my soundtrack
        String song = "src/main/java/Assets/song/My_Brick_Breaker_OST.wav";
        String production = "_";
        player.setFile(song);
        player.play(-5.f);

        Page page = new LogInForm(frame);
        while(frame.isRunning()) {
            switch(page.getOption()) {
                case -2 -> { // close the program
                    frame.setRunning(false);
                    user = null;
                    continue;
                }
                case 0 -> { // login form
                    frame.cleanFrame();
                    page = new LogInForm(frame);
                }
                case 1 -> {// home page
                    frame.cleanFrame();
                    page = new HomePage(frame);
                }
                case 3 -> { // settings page
                    frame.cleanFrame();
                    page = new SettingsPage(frame, userBackup);
                }
                case 4 -> { // my account page
                    frame.cleanFrame();
                    page = new AccountPage(frame, userBackup);
                }
                case 5 -> { // create request
                    frame.cleanFrame();
                    page = new CreateRequestPage(frame, userBackup);
                }
                case 6 -> { // view requests
                    if(userBackup.getUserType() == AccountType.Regular) {
                        page.setOption(1);
                        continue;
                    }
                    frame.cleanFrame();
                    page = new ViewRequestsPage(frame, userBackup, order);
                    isView = true;
                }
                case 7 -> { // search
                    frame.cleanFrame();
                    String input = page.getSearchText();
                    page = new SearchPage(frame, input, searchOption);
                    searchOption = 0;
                }
                case 8 -> { // add / remove production / actor
                    frame.cleanFrame();
                    page = new OthersPage(frame, userBackup, production);
                    isOthers = true;
                }
                default -> System.out.print("");
            }

            // wait for page to stop
            while(page.isRunning()) System.out.print("");

            this.user = page.getUser();
            if(user != null) userBackup = user;

            if(isOthers) {
                isOthers = false;
                production = ((OthersPage) page).getProduction();
            }

            if(isView) order = ((ViewRequestsPage) page).getOrder();

            if(searchOption != -1) searchOption = ((SearchPage) page).getChoice();
            if(page.getOption() != 7) searchOption = -1;

            if(order == -1) isView = false;
        }
    }
}
