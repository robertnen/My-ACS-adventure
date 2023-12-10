import javax.swing.*;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreePath;

import java.awt.event.ActionListener;
import java.io.File;
import java.text.SimpleDateFormat;
import java.util.Date;

public class TreeFile extends JFrame implements ActionListener {

    private JTree fTree;
    private JTable fTable;

    public TreeFile() {
        super("File tree");

        DefaultMutableTreeNode root = new DefaultMutableTreeNode(new File(System.getProperty("user.dir")));
        buildTree(root);

        fTree = new JTree(root);

        fTree.addTreeSelectionListener(new TreeSelectionListener() {
            @Override
            public void valueChanged(TreeSelectionEvent e) {
                new LoadFileInfoTask().execute();
            }
        });

        DefaultTableModel tableModel = new DefaultTableModel(
                new Object[]{"Name", "Size", "Last Modified", "Type"}, 0);
        fTable = new JTable(tableModel);

        JScrollPane treeScrollPane = new JScrollPane(fTree);
        JScrollPane tableScrollPane = new JScrollPane(fTable);

        JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, treeScrollPane, tableScrollPane);
        splitPane.setResizeWeight(0.5);

        getContentPane().add(splitPane);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1000, 800);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    private void buildTree(DefaultMutableTreeNode root) {
        File[] files = ((File) root.getUserObject()).listFiles();
        if(files != null) {
            for(File file : files) {
                DefaultMutableTreeNode node = new DefaultMutableTreeNode(file);
                root.add(node);
                if(file.isDirectory()) buildTree(node);
            }
        }
    }

    private class LoadFileInfoTask extends SwingWorker<Void, Object[]> {
        @Override
        protected Void doInBackground() throws Exception {
            DefaultTableModel tableModel = (DefaultTableModel) fTable.getModel();
            tableModel.setRowCount(0);

            TreePath selectionPath = fTree.getSelectionPath();
            if(selectionPath != null) {
                DefaultMutableTreeNode selectedNode = (DefaultMutableTreeNode) selectionPath.getLastPathComponent();
                File selectedFile = (File) selectedNode.getUserObject();
                if(selectedFile.isDirectory()) {
                    File[] files = selectedFile.listFiles();
                    if(files != null) {
                        for(File file : files) {
                            Object[] rowData = {
                                    file.getName(),
                                    file.length(),
                                    new SimpleDateFormat("MM/dd/yyyy HH:mm:ss").format(new Date(file.lastModified())),
                                    file.isDirectory() ? "Directory" : "File"
                            };
                            publish(rowData);
                        }
                    }
                }
            }
            return null;
        }

        @Override
        protected void process(java.util.List<Object[]> chunks) {
            DefaultTableModel tableModel = (DefaultTableModel) fTable.getModel();
            for(Object[] rowData : chunks) tableModel.addRow(rowData);

        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new TreeFile());
    }
}
