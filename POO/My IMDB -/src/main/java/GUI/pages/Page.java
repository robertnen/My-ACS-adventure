package GUI.pages;

import org.example.User;

import java.awt.*;

public abstract class Page {
    private int option = -1;
    protected Font f = new Font("sanserif", Font.PLAIN, 30);
    protected Font f2 = new Font("sanserif", Font.PLAIN, 15);
    protected Font f3 = new Font("sanserif", Font.PLAIN, 24);
    protected final Color tintGrey = new Color(177, 186, 195);
    private boolean isRunning = true;
    private String searchText = "";
    private User user = null;

    public int getOption() {
        return option;
    }

    public void setOption(int option) {
        this.option = option;
    }

    public boolean isRunning() {
        return isRunning;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public User getUser() {
        return user;
    }

    public void stopRunning() {isRunning = false;}

    public String getSearchText() {
        return searchText;
    }

    public void setSearchText(String searchText) {
        this.searchText = searchText;
    }
}
