import javax.swing.*;
import java.awt.*;
import java.util.Vector;

public class ScrollApp extends JFrame {

    public ScrollApp() {
        super("Book List");

        Vector<Book> books = new Vector<>();
        for(int i = 0; i < 50; i++)
            books.add(new Book("Book " + i, "Author " + i, "icon " + i));

        DefaultListModel<Book> listModel = new DefaultListModel<>();
        for(Book book : books) listModel.addElement(book);

        JList<Book> bookList = new JList<>(listModel);
        bookList.setCellRenderer(new BookListCellRenderer());
        JScrollPane scrollPane = new JScrollPane(bookList);

        getContentPane().add(scrollPane);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300, 400);
        setLocationRelativeTo(null);
        setVisible(true);

        repaint();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new ScrollApp());
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