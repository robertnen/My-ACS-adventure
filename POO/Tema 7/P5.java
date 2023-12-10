import java.io.File;
import java.util.Map;
import java.util.TreeMap;
import java.util.HashMap;

public class P5 {

    public static double getSizeKB(File f) {
        return (double) f.length() / 1024;
    }

    public static void main(String[] args) {
        File dir = new File(".");

        Map<String, Double> fileHMap = new HashMap<>();
        addFiles(fileHMap, dir);

        display(fileHMap);

        Map<String, Double> fileTMap = new TreeMap<>(fileHMap);

        display(fileTMap);
    }

    private static void addFiles(Map<String, Double> fileMap, File dir) {
        File[] fileList = dir.listFiles();

        if(fileList == null) return;

        for(File file : fileList)
            if(file.isFile()) fileMap.put(file.getName(), getSizeKB(file));
    }

    private static void display(Map<String, Double> fileMap) {
        for (Map.Entry<String, Double> entry : fileMap.entrySet()) {
            System.out.println(entry.getKey() + " -> " + entry.getValue() + " KB");
        }
    }
}
