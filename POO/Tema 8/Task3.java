// import java.util.Iterator;

// public class Task3 {

//     public static void main(String[] args) {
//         LinkedList<Integer> list = new LinkedList<>();
//         list.add(10);
//         list.add(20);
//         list.addFirst(5);
//         list.add(22);
//         list.add(25);
//         list.add(30);

//         int last = 0;
//         System.out.println("Afisare 1");
//         for (Integer i : list) {
//             System.out.print(i + ", ");
//             if (i < last) {
//                 System.err.println("LinkedList a fost implementata gresit.");
//             }
//             last = i;
//         }
//         System.out.println();

//         System.out.println("Afisare 2");
//         Iterator<Integer> itr = list.iterator();
//         while (itr.hasNext()) {
//             System.out.print(itr.next() + ", ");
//         }
//         System.out.println();
//     }
// }