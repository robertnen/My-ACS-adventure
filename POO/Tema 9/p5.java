import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class p5 extends JFrame {
    private JButton colorButton;
    private Color[] colors = {Color.RED, Color.BLUE, Color.GREEN, Color.YELLOW};
    private int currentColorIndex = 0;

    public p5() {
        super("Problema 5");
        setSize(100, 100);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new FlowLayout());

        colorButton = new JButton("Colors");
        colorButton.setMnemonic(KeyEvent.VK_C);

        colorButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                changeColor();
            }
        });

        addKeyListener(new KeyListener() {
            @Override
            public void keyTyped(KeyEvent e) {}

            @Override
            public void keyPressed(KeyEvent e) {
                if(e.getKeyCode() == KeyEvent.VK_ALT && e.getKeyChar() == 'C')
                    changeColor();
            }

            @Override
            public void keyReleased(KeyEvent e) {
            }
        });

        add(colorButton);
        setVisible(true);
        setFocusable(true);
    }

    private void changeColor() {
        currentColorIndex = (currentColorIndex + 1) % colors.length;
        Color selectedColor = colors[currentColorIndex];

        colorButton.setForeground(selectedColor);
        colorButton.setBackground(selectedColor);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {new p5();}
        });
    }
}
