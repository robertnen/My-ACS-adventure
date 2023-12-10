import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Table {
    private List<List<Object>> data;

    public Table(Object[][] rows) {
        this.data = new ArrayList<>();
        for (Object[] row: rows) this.data.add(Arrays.asList(row));
    }

    public void print(Printer printer) {printer.printTable(this.data);}

    public interface Printer {
        void printTable(List<List<Object>> data);
    }

    public class AsciiPrinter implements Printer {
        private int[] columnWidths;

        public AsciiPrinter(int[] columnWidths) {this.columnWidths = columnWidths;}

        @Override
        public void printTable(List<List<Object>> data) {
            printHorizontalLine();
            for(int i = 0; i < data.size(); i++) {
                List<Object> row = data.get(i);
                System.out.print("| ");
                for(int j = 0; j < row.size(); j++) {
                    Object cell = row.get(j);
                    System.out.format("%-" + columnWidths[j] + "s | ", cell.toString());
                }
                System.out.println();
                if(i == 0) printHorizontalLine();
            }
            printHorizontalLine();
        }

        private void printHorizontalLine() {
            for(int width: columnWidths) System.out.print("+" + "-".repeat(width + 2));
            System.out.println("+");
        }
    }

    public class CsvPrinter implements Printer {
        private String delimiter;

        public CsvPrinter() {this.delimiter = ",";}

        @Override
        public void printTable(List<List<Object>> data) {
            for(List<Object> row: data) {
                for(int i = 0; i < row.size(); i++) {
                    Object cell = row.get(i);
                    System.out.print(cell.toString());
                    if(i < row.size() - 1) System.out.print(delimiter);
                }
                System.out.println();
            }
        }
    }
}