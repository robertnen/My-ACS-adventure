// import java.util.Comparator;

// public class Task2 {

//     public static void main(String args[]) {
//         Catalog catalog = new Catalog();
//         catalog.addStudent("Alexandru", 7, 324);
//         catalog.addStudent("Ioana", 5, 321);
//         catalog.addStudent("Maria", 10, 322);
//         catalog.addStudent("Ionut", 6.2, 323);
//         catalog.addStudent("Diana", 7, 322);

//         Catalog catalog2 = new Catalog(new Comparator<Catalog.Student>() {
//             @Override
//             public int compare(Catalog.Student o1, Catalog.Student o2) {
//                 return o1.compareTo(o2);
//             }
//         });
//         catalog2.addAll(catalog);

//         System.out.println("Verificam...");
//         System.out.println("Continutul colectiei: " + catalog);
//         System.out.println("Continutul colectiei: " + catalog2);

//         Catalog.Student last = null;
//         for (Object o : catalog) {
//             if (last == null) {
//                 last = (Catalog.Student) o;
//                 continue;
//             }
//             int r = last.media != ((Catalog.Student) o).media ? new Double(last.media).compareTo(((Catalog.Student) o).media) : last.name.compareTo(((Catalog.Student) o).name);
//             if (r != last.compareTo(((Catalog.Student) o))) {
//                 System.err.println("Catalog.Student.compareTo a fost implementata gresit.");
//             }
//         }

//         if (catalog.size() != 5) {
//             System.err.println("Catalog.size() a fost implementata gresit.");
//         }

//         catalog.removeStudent("Ionut");
//         if (catalog.size() != 4) {
//             System.err.println("Catalog.remove() a fost implementata gresit.");
//         }
//         catalog.removeStudent("");
//         if (catalog.size() != 4) {
//             System.err.println("Catalog.remove() a fost implementata gresit.");
//         }

//         if (catalog.byClass(322).size() != 2) {
//             System.err.println("Catalog.byClass() a fost implementata gresit.");
//         }

//         catalog.removeStudent("Maria");
//         if (catalog.byClass(322).size() != 1) {
//             System.err.println("Catalog.remove() a fost implementata gresit.");
//         }

//         if (catalog.getStudent("Maria") != null) {
//             System.err.println("Catalog.getStudent() a fost implementata gresit.");
//         }

//         if ((catalog.getStudent("Alexandru") == null) || (catalog.getStudent("Alexandru").media != 7)) {
//             System.err.println("Catalog.getStudent() a fost implementata gresit.");
//         }
//     }

// }
