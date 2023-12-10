import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Find4 {
    private static File findFile(File dir, String name) {
        File result = null;
        File[] dirlist  = dir.listFiles();

        for(int i = 0; i < dirlist.length; i++) {
            if(dirlist[i].isDirectory()) {
                result = findFile(dirlist[i], name);
                if(result != null) break;
            } else if(dirlist[i].getName().matches(name)) {
                return dirlist[i];
            }
        }
        return result;
    }

    public static void main(String args[]) throws FileNotFoundException {
        File start = new File("./director");
        File ext = new File("./extension.in");
        File words = new File("./words.in");

        Scanner inw = new Scanner(words);

        while(inw.hasNextLine()) {
            String line = inw.nextLine(), aux;
            Scanner ine = new Scanner(ext);
            while(ine.hasNextLine()) {
                aux = line;
                String extLine = ine.nextLine();

                aux += extLine;
                if(findFile(start, aux) != null) System.out.println(aux + " found!");
            }
            ine.close();
        }
        inw.close();
    }
}
