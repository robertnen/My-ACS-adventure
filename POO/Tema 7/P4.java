// import java.io.BufferedReader;
// import java.io.FileReader;
// import java.io.IOException;
// import java.util.LinkedList;
// import java.util.Map;
// import java.util.TreeMap;

// public class P4 {
//     public static void main(String[] args) {
//         TreeMap<String, LinkedList<Integer>> wordMap = new TreeMap<String, LinkedList<Integer>>();
//         try {
//             BufferedReader reader = new BufferedReader(new FileReader("./test01.txt"));
//             String line;
//             int lineNumber = 1;

//             while((line = reader.readLine()) != null) {
//                 String[] words = line.split("\\s+");

//                 for (String word : words) {
//                     word = word.replaceAll("[^a-zA-Z]", "").toLowerCase();

//                     if (!word.isEmpty()) {
//                         if (!wordMap.containsKey(word)) {
//                             wordMap.put(word, new LinkedList<Integer>());
//                         }
//                         wordMap.get(word).add(lineNumber);
//                     }
//                 }
//                 lineNumber++;
//             }

//             reader.close();
//         } catch (IOException e) {
//             e.printStackTrace();
//         }

//         for(Map.Entry<String, LinkedList<Integer>> entry : wordMap.entrySet()) {
//             if(entry.getValue().size() != 1) continue;
//             System.out.println(entry.getKey() + " -> " + entry.getValue());
//         }
//     }
// }