import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;

public class p4 extends JFrame {
    private JSlider redSlider, greenSlider, blueSlider;
    private JTextField colorTextField;

    public p4() {
        super("Problema 4");
        this.setSize(800, 400);

        redSlider = createSlider("Red", 0, 255, 0);
        greenSlider = createSlider("Green", 0, 255, 0);
        blueSlider = createSlider("Blue", 0, 255, 0);

        colorTextField = new JTextField();
        colorTextField.setEditable(false);

        redSlider.addChangeListener(new SliderChangeListener());
        greenSlider.addChangeListener(new SliderChangeListener());
        blueSlider.addChangeListener(new SliderChangeListener());

        setLayout(new GridLayout(4, 1));

        add(redSlider);
        add(greenSlider);
        add(blueSlider);
        add(colorTextField);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    private JSlider createSlider(String label, int min, int max, int initialValue) {
        JSlider slider = new JSlider(JSlider.HORIZONTAL, min, max, initialValue);
        slider.setMajorTickSpacing(50);
        slider.setPaintTicks(true);
        slider.setPaintLabels(true);
        slider.setBorder(BorderFactory.createTitledBorder(label));
        return slider;
    }

    private class SliderChangeListener implements ChangeListener {
        @Override
        public void stateChanged(ChangeEvent e) {
            int redValue = redSlider.getValue();
            int greenValue = greenSlider.getValue();
            int blueValue = blueSlider.getValue();

            Color color = new Color(redValue, greenValue, blueValue);
            colorTextField.setBackground(color);
            colorTextField.setText("RGB: (" + redValue + ", " + greenValue + ", " + blueValue + ")");
            colorTextField.setAlignmentX(400);;
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(p4::new);
    }
}
