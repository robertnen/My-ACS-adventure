import java.awt.*;
import java.awt.event.*;
import java.io.*;

import javax.swing.*;

class Problema2 extends JFrame implements ActionListener, ItemListener {
    JTextField quiz;
    JCheckBox r1, r2, r3, r4;
    ButtonGroup group;
    JButton button;
    
    public Problema2(String fis) {
        super("Problema 2");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        quiz = new JTextField(150);
        quiz.setEditable(false);
        
        r1 = new JCheckBox();
        r2 = new JCheckBox();
        r3 = new JCheckBox();
        r4 = new JCheckBox();
        // group = new ButtonGroup();
        // group.add(r1);
        // group.add(r2);
        // group.add(r3);
        // group.add(r4);
        JPanel rb=new JPanel();
        rb.setLayout(new GridLayout(4,1));
        rb.add(r1);
        rb.add(r2);
        rb.add(r3);
        rb.add(r4);
        
        button = new JButton("Raspunde");
        button.setEnabled(false);
        button.addActionListener(this);
        
        add(quiz, BorderLayout.NORTH);
        add(rb, BorderLayout.CENTER);
        add(button,BorderLayout.SOUTH);
        
        r1.addActionListener(this);
        r2.addActionListener(this);
        r3.addActionListener(this);
        r4.addActionListener(this);
        
        pack();
        setVisible(true);
        try {
            RandomAccessFile br = new RandomAccessFile(fis,"r");
                quiz.setText(br.readLine());
                r1.setText(br.readLine());
                r2.setText(br.readLine());
                r3.setText(br.readLine());
                r4.setText(br.readLine());
                
        } catch (IOException ex) {
            System.err.println("Exceptie");
        }
    }
    
    

    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource() instanceof JCheckBox) {
            button.setEnabled(true);
        } else if(e.getSource() instanceof JButton) {
            if(r1.isSelected() && r3.isSelected()) {
                r1.setForeground(Color.green);
                r3.setForeground(Color.green);
            } else if(r1.isSelected()) {
                r1.setForeground(Color.green);
                r3.setForeground(Color.red);
            } else if(r3.isSelected()) {
                r1.setForeground(Color.red);
                r3.setForeground(Color.green);
            } else {
                r1.setForeground(Color.red);
                r3.setForeground(Color.red);
            }
            button.setEnabled(false);
        }
    }

   public static void main(String args[]) {
        Problema2 pb2 = new Problema2("intrebare.txt");
        
    }

    @Override
    public void itemStateChanged(ItemEvent e) {
            
    }
}