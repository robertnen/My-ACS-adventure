package CLI;

import org.example.Genre;

import java.util.List;
import java.util.Scanner;

public class CustomFunctionsCLI {

    private final int newLineNum = 15;
    private final int newLineSpace = 2;
    public CustomFunctionsCLI() {}

    public static void updateGenres(String genre, List<Genre> genres) {
        switch(genre) {
            case "Action" -> genres.add(Genre.ACTION);
            case "Adventure" -> genres.add(Genre.ADVENTURE);
            case "Animation" -> genres.add(Genre.ANIMATION);
            case "Biography" -> genres.add(Genre.BIOGRAPHICAL);
            case "Comedy" -> genres.add(Genre.COMEDY);
            case "Cooking" -> genres.add(Genre.COOKING);
            case "Crime" -> genres.add(Genre.CRIME);
            case "Disaster" -> genres.add(Genre.DISASTER);
            case "Documentary" -> genres.add(Genre.DOCUMENTARY);
            case "Drama" -> genres.add(Genre.DRAMA);
            case "Experimental" -> genres.add(Genre.EXPERIMENTAL);
            case "Family" -> genres.add(Genre.FAMILY);
            case "Fantasy" -> genres.add(Genre.FANTASY);
            case "Historical" -> genres.add(Genre.HISTORICAL);
            case "History" -> genres.add(Genre.HISTORY);
            case "Horror" -> genres.add(Genre.HORROR);
            case "Martial arts" -> genres.add(Genre.MARTIAL_ARTS);
            case "Music" -> genres.add(Genre.MUSIC);
            case "Musical" -> genres.add(Genre.MUSICAL);
            case "Mystery" -> genres.add(Genre.MYSTERY);
            case "Noir" -> genres.add(Genre.NOIR);
            case "Political" -> genres.add(Genre.POLITICAL);
            case "Romance" -> genres.add(Genre.ROMANCE);
            case "SF" -> genres.add(Genre.SCIENCE_FICTION);
            case "Silent" -> genres.add(Genre.SILENT);
            case "Social" -> genres.add(Genre.SOCIAL);
            case "Sport" -> genres.add(Genre.SPORT);
            case "Spy" -> genres.add(Genre.SPY);
            case "Supernatural" -> genres.add(Genre.SUPERNATURAL);
            case "Thriller" -> genres.add(Genre.THRILLER);
            case "War" -> genres.add(Genre.WAR);
            case "Western" -> genres.add(Genre.WESTERN);
            default -> System.out.println("Genre " + genre + " <--------------- does not exist.");
        }
    }

    public void cleanTerminal() {
        for(int i = 0; i < newLineNum; i++) System.out.println();
    }

    public void addSpaceTerminal() {
        for(int i = 0; i < newLineSpace; i++) System.out.println();
    }

    public int getChoice(String intro, String choiceList, String warning, String error, int lower, int upper) {
        int choice = 0;
        boolean isOk = false;

        while(!isOk) {
            System.out.flush();
            System.out.println(intro);
            System.out.print(choiceList);
            System.out.print("\nYour choice: ");
            Scanner sn = new Scanner(System.in);

            if(!sn.hasNext()) continue;
            String input = sn.nextLine();

            try {
                choice = Integer.parseInt(input);

                if(choice < lower || choice > upper) {
                    System.out.println("\n" + warning + "\n");
                    continue;
                }

                isOk = true;

            } catch (NumberFormatException ignored) {
                System.out.println("\n" + error + "\n");
            }
        }

        return choice;
    }
}
