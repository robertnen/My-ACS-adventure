package GUI.upgradedJObjects;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.RoundRectangle2D;

public class RoundedPasswordField extends JPasswordField {
    private Shape shape;
    public RoundedPasswordField(int size) {
        super(size);
        setOpaque(false);
    }

    protected void paintComponent(Graphics g) {
        g.setColor(new Color(208, 213, 219));
        g.fillRoundRect(0, 0, getWidth()-1, getHeight()-1, 12, 12);
        super.paintComponent(g);
    }

    protected void paintBorder(Graphics g) {
        g.setColor(new Color(70, 82, 94));
        g.drawRoundRect(0, 0, getWidth()-1, getHeight()-1, 12, 12);
    }

    public boolean contains(int x, int y) {
        if (shape == null || !shape.getBounds().equals(getBounds())) {
            shape = new RoundRectangle2D.Float(0, 0, getWidth()-1, getHeight()-1, 12, 12);
        }
        return shape.contains(x, y);
    }
}
