import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ScrollApp2 extends JFrame implements ListSelectionListener, ActionListener {

    private JList<Book> listBook;
    private JTextField titleTextField;
    private JTextField authorTextField;

    public ScrollApp2() {
        super("Book List");

        DefaultListModel<Book> listModel = new DefaultListModel<>();
        for (int i = 0; i < 50; i++)
            listModel.addElement(new Book("Book " + i, "Author " + i, "icon " + i));

        listBook = new JList<>(listModel);
        listBook.setCellRenderer(new BookListCellRenderer());
        listBook.addListSelectionListener(this);

        JScrollPane scrollPane = new JScrollPane(listBook);

        JPanel detailsPanel = new JPanel(new GridLayout(2, 2));
        JLabel titleLabel = new JLabel("Title:");
        JLabel authorLabel = new JLabel("Author:");
        titleTextField = new JTextField();
        authorTextField = new JTextField();
        detailsPanel.add(titleLabel);
        detailsPanel.add(titleTextField);
        detailsPanel.add(authorLabel);
        detailsPanel.add(authorTextField);

        JPanel buttonPanel = new JPanel();
        JButton deleteButton = new JButton("Remove");
        deleteButton.addActionListener(this);
        buttonPanel.add(deleteButton);

        JPanel mainPanel = new JPanel(new BorderLayout());
        mainPanel.add(scrollPane, BorderLayout.CENTER);
        mainPanel.add(detailsPanel, BorderLayout.SOUTH);
        mainPanel.add(buttonPanel, BorderLayout.NORTH);

        getContentPane().add(mainPanel);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(800, 400);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new ScrollApp2());
    }

    @Override
    public void valueChanged(ListSelectionEvent e) {
        if (listBook.isSelectionEmpty())
            return;

        Book selectedBook = listBook.getSelectedValue();
        titleTextField.setText(selectedBook.getName());
        authorTextField.setText(selectedBook.getAuthor());
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getActionCommand().equals("Remove")) {
            int selectedIndex = listBook.getSelectedIndex();
            if (selectedIndex != -1) {
                DefaultListModel<Book> model = (DefaultListModel<Book>) listBook.getModel();
                model.remove(selectedIndex);
            }
        }
    }
}

class BookListCellRenderer extends JLabel implements ListCellRenderer<Book> {

    @Override
    public Component getListCellRendererComponent(JList<? extends Book> list, Book value, int index,
                                                  boolean isSelected, boolean cellHasFocus) {
        setText(value.getName() + " by " + value.getAuthor());
        setIcon(new ImageIcon(value.getIconName()));
        setOpaque(true);
        setBackground(isSelected ? list.getSelectionBackground() : list.getBackground());
        setForeground(isSelected ? list.getSelectionForeground() : list.getForeground());

        return this;
    }
}