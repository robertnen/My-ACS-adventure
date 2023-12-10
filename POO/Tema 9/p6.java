import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class p6 {
    private JLabel label;
    private JTextField textField;
    private JButton button;
    private JScrollPane scrollPane;
    private JTextArea textArea;
    private JFrame frame;

    public p6() {
        frame = new JFrame("Problema 6");

        label = new JLabel("Path:");
        textField = new JTextField(20);
        button = new JButton("Content");
        scrollPane = new JScrollPane();
        textArea = new JTextArea();

        scrollPane.setViewportView(textArea);
        scrollPane.setVisible(false);

        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String path = textField.getText();
                File file = new File(path);

                if(file.exists() && !file.isDirectory()) {
                    try {
                        BufferedReader br = new BufferedReader(new FileReader(file));
                        String line;
                        StringBuilder content = new StringBuilder();
                        while ((line = br.readLine()) != null) {
                            content.append(line).append("\n");
                        }
                        br.close();
                        textArea.setText(content.toString());
                        System.out.println(content.toString());
                        scrollPane.setVisible(true);
                        frame.repaint();

                    } catch (IOException ex) {
                        ex.printStackTrace();
                    }
                } else {
                    textField.setText("");
                    scrollPane.setVisible(false);
                }
            }
        });

        GroupLayout layout = new GroupLayout(frame.getContentPane());
        frame.getContentPane().setLayout(layout);
        layout.setAutoCreateGaps(true);
        layout.setAutoCreateContainerGaps(true);

        layout.setHorizontalGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addComponent(label)
                        .addComponent(textField)
                        .addComponent(button)
                        .addComponent(scrollPane))
        );

        layout.setVerticalGroup(layout.createSequentialGroup()
                .addComponent(label)
                .addComponent(textField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addComponent(button)
                .addComponent(scrollPane)
        );

        frame.pack();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);
    }

    public JFrame getFrame() {
        return frame;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {new p6().getFrame().setVisible(true);}
        });
    }
}
