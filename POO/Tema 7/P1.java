// import java.io.File;
// import java.io.FileNotFoundException;
// import java.util.Comparator;
// import java.util.Scanner;
// import java.util.TreeSet;

// public class P1 {

//     static TreeSet<String> tree = new TreeSet<String>();

//     public static void main(String[] args) throws FileNotFoundException {
//         printWordsComparator(printWords("./test01.txt"));
//     }

//     public static TreeSet<String> printWords(String filePath) throws FileNotFoundException {
//         File f = new File(filePath);

//         Scanner scan = new Scanner(f);

//         while(scan.hasNext()) {
//             tree.add(scan.next());
//         }

//         scan.close();
//         System.out.println("Tree in ordine cresc: " + tree);
//         return tree;
//     }

//     public static TreeSet<String> printWordsComparator(TreeSet<String> tree) {

//         TreeSet<String> revTree = new TreeSet<String>(new Comparator<String>() {
//                                                         @Override
//                                                         public int compare(String s1, String s2) {
//                                                                 return -s1.compareTo(s2);
//                                                         }
//                                                     });

//         revTree.addAll(tree);

//         System.out.println("Tree in ordine descresc: " + revTree);

//         return revTree;
//     }

// }
