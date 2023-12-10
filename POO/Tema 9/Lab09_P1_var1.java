import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class Problema1V1 extends JFrame implements ActionListener {
    JTextField t1, t2, t3;
    JTextField rezultat;
    JButton button;
    
    public Problema1V1(String name) {
        super(name);
        
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300, 300);
        setMinimumSize(new Dimension(300, 300));
        JPanel p=new JPanel();
        p.setLayout(new GridLayout(1,3));
        t1 = new JTextField(10);
        t2 = new JTextField(10);
        t3 = new JTextField(15);
        p.add(t1);
        p.add(t2);
        p.add(t3);
        
        button = new JButton("OK");
        JPanel p1=new JPanel();
        p1.add(button);
        
        rezultat = new JTextField(20);
        JPanel p2=new JPanel();
        p2.add(rezultat);
        
        //rezultat.setVisible(false);
        
        add(p, BorderLayout.NORTH);
        add(p1, BorderLayout.SOUTH);
        add(p2, BorderLayout.CENTER);
        
        t1.addActionListener(this);
        t2.addActionListener(this);
        t3.addActionListener(this);
        
        pack();
        setVisible(true);
    }
    
    @Override
    public void actionPerformed(ActionEvent e) {
        //rezultat.setVisible(true);
        rezultat.setText(t1.getText() + "\\" + t2.getText() + "\\" + t3.getText());
    }
    
        public static void main(String args[]) {
        Problema1V1 obj = new Problema1V1("Problema 1");
    }
}
