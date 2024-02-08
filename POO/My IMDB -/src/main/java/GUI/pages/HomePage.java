package GUI.pages;

import GUI.upgradedJObjects.NavBar;
import GUI.Frames.RunFrame;

import javax.swing.*;
import java.awt.*;

public class HomePage extends Page{

    public HomePage(RunFrame frame) {
        new NavBar(frame, this);

        JPanel yearPanel = new JPanel(), scrollPanel = new JPanel(), favoritesPanel = new JPanel();

        // film of the year
        yearPanel.setBounds(80, 150, 890, 380);
        yearPanel.setBackground(new Color(218, 232, 252));
        yearPanel.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.BLACK));

        ImageIcon yearGIF = new ImageIcon("src/main/java/Assets/gifs/bahoi.gif");
        JLabel yearLabel = new JLabel(yearGIF);
        yearLabel.setBounds(10, 10, 540, 360);
        yearPanel.add(yearLabel);

        JLabel yearTitle = new JLabel("Best movie of 2023");
        yearTitle.setFont(f);
        yearTitle.setBounds(590, 25, 320, 40);
        yearPanel.add(yearTitle);

        JTextArea yearField = new JTextArea("     'Bahoi sare de pe pod', is one\n of the best " +
                                            "movies of all time. The\n plot is simple: a normal " +
                                            "romanian in\n a hot summer day jumping from a \nbridge. " +
                                            "Starting with his quote \n'Mama, dar vreau sa sar si eu " +
                                            "bre \noleaca ca sa filmez si eu, te rog eu!'\n it leads " +
                                            "to a fascinating ending:\n Bahoi jumps from the bridge. \n \t- added by Robert");
        yearField.setFont(new Font("sanserif", Font.PLAIN, 20));
        yearField.setEditable(false);
        yearField.setBackground(new Color(195, 207, 226));
        yearField.setBounds(560, 85, 320, 280);
        yearPanel.add(yearField);

        frame.getBgPanel().add(yearPanel);


        // recommendations
        scrollPanel.setBounds(80, 560, 890, 280);
        scrollPanel.setBackground(new Color(179, 179, 179));
        scrollPanel.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.BLACK));

        scrollPanel.setLayout(new FlowLayout());

        String[] imgPaths = {"src/main/java/Assets/images/bahoi_sare.png",
                            "src/main/java/Assets/images/telecomanda.png",
                            "src/main/java/Assets/images/olarit_all_around.png",
                             "src/main/java/Assets/images/orez_cu_lapte.png"};

        Dimension imgD = new Dimension(160, 200);
        final int imagesNum = 4;

        JLabel[] pics = new JLabel[imagesNum];

        for(int i = 0; i < imagesNum; i++) {
            ImageIcon meme = new ImageIcon(imgPaths[i]);
            Image newMeme = meme.getImage();
            newMeme = newMeme.getScaledInstance(160, 200, Image.SCALE_SMOOTH);
            pics[i] = new JLabel(new ImageIcon(newMeme));
            pics[i].setPreferredSize(imgD);
            pics[i].setBounds(70 + 200 * i, 60, 160, 200);
            scrollPanel.add(pics[i]);
        }

        for(JLabel pic : pics) scrollPanel.add(pic);

        JLabel recommendations = new JLabel("Your recommendations");
        recommendations.setFont(f);
        recommendations.setBounds(300, 10, 400, 40);
        scrollPanel.add(recommendations);

        frame.getBgPanel().add(scrollPanel);

        // favorites
        favoritesPanel.setBounds(1030, 150, 480, 690);
        favoritesPanel.setBackground(new Color(186, 200, 211));
        favoritesPanel.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.BLACK));

        JLabel newsTitle = new JLabel("My IMDB news:");
        newsTitle.setFont(f);
        newsTitle.setBounds(150, 20, 300, 40);

        favoritesPanel.add(newsTitle);

        imgPaths = new String[]{"src/main/java/Assets/images/becali.png",
                                "src/main/java/Assets/images/wtf_romania.png",
                                "src/main/java/Assets/images/vadim.png",
                                "src/main/java/Assets/images/woman.jpg"};

        Dimension newsD = new Dimension(100, 100);

        JLabel[] picsN = new JLabel[imagesNum];

        for(int i = 0; i < imagesNum; i++) {
            ImageIcon meme = new ImageIcon(imgPaths[i]);
            Image newMeme = meme.getImage();
            newMeme = newMeme.getScaledInstance(100, 100, Image.SCALE_SMOOTH);
            picsN[i] = new JLabel(new ImageIcon(newMeme));
            picsN[i].setPreferredSize(newsD);
            picsN[i].setBounds(30, 100 + 150 * i, 100, 100);
            favoritesPanel.add(picsN[i]);
        }

        for(JLabel pic : picsN) favoritesPanel.add(pic);

        String becali = "     'Hazard s-a hazardat!' Noul film \n" +
                        "din 2024 ce il are in rol principal pe \n" +
                        "Gigi Becali in drumul sau spre finala \n" +
                        "UEL in sezonul 2012-2013.";

        String romania = "     Serialul '3 cars of police in front \n" +
                         "of my house' urmeaza sa aiba un \n" +
                         "nou sezon dupa ce a avut un rating \n" +
                         "incredibil de 8.5 / 10 pe My IMDB.";

        String vadim = "     5 studenti de la ACS au reusit sa \n" +
                       "faca un AI de il imita pe Vadim si au \n" +
                       "lansat deja un serial cu acesta. Din \n" +
                       "cauza ca injura mult, acesta este 18+.";

        String woman = "    Gest incredibil facut de o romanca! \n" +
                       "  Ea s-a despartit de un actor foarte \n" +
                       "  cunoscut dupa ce firma sa a dat \n" +
                       "  faliment. Vezi de ce a facut asta.";

        String[] newsArea = {becali, romania, vadim, woman};

        JTextArea becaliArea = new JTextArea(becali);
        becaliArea.setFont(new Font("sanserif", Font.PLAIN, 18));
        becaliArea.setEditable(false);
        becaliArea.setBackground(new Color(195, 207, 226));
        becaliArea.setBounds(150, 100, 300, 100);
        favoritesPanel.add(becaliArea);

        for(int i = 0; i < imagesNum; i++) {
            JTextArea newArea = new JTextArea(newsArea[i]);
            newArea.setFont(new Font("sanserif", Font.PLAIN, 18));
            newArea.setEditable(false);
            newArea.setBackground(new Color(195, 207, 226));
            newArea.setBounds(150, 100 + 150 * i, 300, 100);
            favoritesPanel.add(newArea);
        }

        frame.getBgPanel().add(favoritesPanel);

        frame.repaint();
    }
}
