package GUI.pages;

import GUI.CustomFunctionGUI;
import GUI.upgradedJObjects.NavBar;
import GUI.upgradedJObjects.RoundedButton;
import GUI.Frames.RunFrame;
import org.example.*;

import javax.swing.*;
import java.util.List;

public class ViewRequestsPage extends Page {

    private int i = 0;
    private List<Request> requests = null;
    public ViewRequestsPage(RunFrame frame, User user, int order) {


        if(user.getUserType() == AccountType.Contributor) requests = ((Contributor) user).getRequests();
        else requests = new RequestsHolder().getAdminRequests();

        if(requests == null || requests.isEmpty() || order >= requests.size() || requests.size() == 1) {
            i = -1;
            setOption(1);
            stopRunning();
            return;
        }

        i = order;

        new NavBar(frame, this);

        // show request
        JTextArea requestShow = new JTextArea(CustomFunctionGUI.displayRequest(requests.get(i)));
        requestShow.setBounds(580, 380, 470, 200);
        requestShow.setBackground(tintGrey);
        requestShow.setEditable(false);
        requestShow.setFont(f2);

        frame.getBgPanel().add(requestShow);

        // show total
        JTextField totalField = new JTextField("Number of requests: " + requests.size());
        totalField.setBounds(340, 440, 200, 50);
        totalField.setBackground(tintGrey);
        totalField.setEditable(false);
        totalField.setFont(f2);

        frame.getBgPanel().add(totalField);

        // prev
        RoundedButton prevButton = new RoundedButton();
        prevButton.setText("Previous");
        prevButton.addActionListener(e -> {
                    if(i <= 0) return;
                    i--;
                    setOption(6);
                    stopRunning();
                }
        );

        prevButton.setBackground(frame.getBgColor());
        prevButton.setBounds(610, 310, 150, 50);
        frame.getBgPanel().add(prevButton);

        // next
        RoundedButton nextButton = new RoundedButton();
        nextButton.setText("Next");
        nextButton.addActionListener(e -> {
                    if(i >= requests.size() - 1) return;
                    i++;
                    setOption(6);
                    stopRunning();
                }
        );

        nextButton.setBackground(frame.getBgColor());
        nextButton.setBounds(860, 310, 150, 50);
        frame.getBgPanel().add(nextButton);

        // mark as done
        RoundedButton markButton = new RoundedButton();
        markButton.setText("Close request");
        markButton.addActionListener(e -> {
                    if(user.getUserType() == AccountType.Admin) new RequestsHolder().getAdminRequests().remove(requests.get(i));
                    else ((Contributor) user).getRequests().remove(requests.get(i));

                    for(Object req : IMDB.getInstance().getRequests())
                        if(((Request) req).getUsername().equals(user.getUsername())) IMDB.getInstance().getRequests().remove(req);

                    requests.remove(i);
                    if(i > 0) i--;

                    if(!requests.isEmpty()) {
                        setOption(6);
                        stopRunning();
                        return;
                    }

                    i = -1;
                    setOption(1);
                    stopRunning();
                }
        );

        markButton.setBackground(frame.getBgColor());
        markButton.setBounds(680, 625, 270, 50);
        frame.getBgPanel().add(markButton);

        frame.repaint();
    }

    public int getOrder() {
        return i;
    }
}
