package CLI;

import org.example.*;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Pattern;

public class MainCLI {

    private IMDB imdb = IMDB.getInstance();
    private CustomFunctionsCLI cf = new CustomFunctionsCLI();
    private User user = null;

    private boolean isLoggedIn = true;
    public void main() {
        login();

        while(isLoggedIn) {
            String intro =  "IMDB main menu. Please choose what action you want to do:";

            String choiceList = "1. View production details"
                    + "\n2. View actor details"
                    + "\n3. View notifications"
                    + "\n4. Search for actor/movie/series"
                    + "\n5. Add/Delete actor/movie/series to/from favorites"
                    + "\n6. Add/Delete user"
                    + "\n7. Add/Delete actor/movie/series from system"
                    + "\n8. Add/Delete rating to/from a production"
                    + "\n9. Update production details"
                    + "\n10. Update actor details"
                    + "\n11. Solve a request"
                    + "\n12. Log out";

            String warning = "Please choose a valid number between 1 and 12";

            int choice = cf.getChoice(intro, choiceList, warning, "That is not a number between 1 and 12", 1, 12);
            cf.cleanTerminal();

            switch(choice) {
                case 1 -> viewProduction();         // done
                case 2 -> viewActor();              // done
                case 3 -> viewNotifications();      // done
                case 4 -> searchContent();          // done
                case 5 -> modifyFavorites();        // done
                case 6 -> modifyUsers();            // done
                case 7 -> modifyContent();          // done
                case 8 -> modifyRating();           // done
                case 9 -> updateProduction();       // done
                case 10 -> updateActor();           // done
                case 11 -> solveRequest();          // done
                case 12 -> {                        // done
                    user.logout();
                    user = null;
                    isLoggedIn = false;
                }
            }
        }
    }

    public void viewProduction() {
        System.out.println("===============View production===============");
        String intro = "Please choose from the list how do you wish to continue:";
        String choiceList = "1. Search normally"
                        + "\n2. Filter by genres"
                        + "\n3. Filter by number of ratings"
                        + "\n4. Go back to menu";

        String warning = "Please choose a valid number between 1 and 4";
        int choice = cf.getChoice(intro, choiceList, warning, "That is not a number between 1 and 4", 1, 4);
        cf.addSpaceTerminal();

        Scanner sn = new Scanner(System.in);
        String input;

        List<Genre> genres = new ArrayList<>();
        Production p = null;
        boolean productionExists = false;

        switch(choice) {
            case 1 -> { // search for anything
                System.out.print("Type the production name: ");

                input = sn.nextLine();

                for(Object production : imdb.getProductions()) {
                    if(((Production) production).getTitle().equals(input)) {
                        productionExists = true;
                        p = ((Production) production);
                        break;
                    }
                }

                if(productionExists) p.displayInfo();
                else {
                    System.out.println("There is no production having this name");
                    cf.addSpaceTerminal();
                }
            }
            case 2 -> { // search for specific genres
                int size = cf.getChoice("How many genres?", "(Maximum 3)", "Please between 1 and 3",
                                        "That is not a number between 1 and 3.",1, 3);

                while(size-- != 0) {
                    System.out.print("Genre: ");

                    input = sn.nextLine();

                    switch(input) {
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
                        default -> {
                            System.out.println("Genre " + input + " does not exist in the database. Write another.\n");
                            size++;
                        }
                    }
                }

                for(Object production : imdb.getProductions()) {
                    boolean hasEverything = true;

                    for(Genre genre : genres)
                        if(!((Production) production).getGenres().contains(genre)) {
                            hasEverything = false;
                            break;
                        }

                    if(hasEverything) { // found production
                        ((Production) production).displayInfo();
                        productionExists = true;
                    }
                }

                if(!productionExists) {
                    System.out.println("There is no production having these genres");
                    cf.addSpaceTerminal();
                }
            }
            case 3 -> { // search by minimum number of ratings
                int size = cf.getChoice("How many reviews minimum?", "(Maximum 10), ", "Please between 1 and 10",
                        "That is not a number between 1 and 10.",1, 10);

                for(Object production : imdb.getProductions()) {
                    if(((Production) production).getRatings().size() >= size) {
                        productionExists = true;
                        ((Production) production).displayInfo();
                    }
                }

                if(!productionExists) {
                    System.out.println("There is no production having at least " + size + " reviews");
                    cf.addSpaceTerminal();
                }
            }
            case 4 -> cf.addSpaceTerminal();
        }

        if(choice != 4) {
            System.out.print("Press Enter twice to continue...");
            sn.nextLine();
        }
    }
    public void viewActor() {
        System.out.println("===============View actor===============");
        String intro = "Please choose from the list how do you wish to continue:";
        String choiceList = "1. Search normally"
                + "\n2. Search after title"
                + "\n3. Go back to menu";

        String warning = "Please choose a valid number between 1 and 3";
        int choice = cf.getChoice(intro, choiceList, warning, "That is not a number between 1 and 3", 1, 3);
        cf.addSpaceTerminal();

        Scanner sn = new Scanner(System.in);
        String input;

        Actor a = null;
        boolean actorExists = false;

        switch(choice) {
            case 1 -> { // search normally
                System.out.print("Name of the actor: ");
                input = sn.nextLine();

                for(Object actor : imdb.getActors()) {
                    if(((Actor) actor).getName().equals(input)) {
                        actorExists = true;
                        ((Actor) actor).displayInfo();
                        break;
                    }
                }

                if(!actorExists) {
                    System.out.println("Actor doesn't exist in the database");
                    cf.addSpaceTerminal();
                }
            }
            case 2 -> { // search by title
                System.out.print("Name of the production: ");
                input = sn.nextLine();

                for(Object production : imdb.getProductions()) {
                    if(((Production) production).getTitle().equals(input)) {
                        for(String name : ((Production) production).getActors())
                            for(Object actor : imdb.getActors())
                                if(((Actor) actor).getName().equals(name))
                                    ((Actor) actor).displayInfo();

                        actorExists = true;
                        break;
                    }
                }

                if(!actorExists) {
                    System.out.println("Production doesn't exist in the database");
                    cf.addSpaceTerminal();
                }
            }
            case 3 -> cf.addSpaceTerminal();
        }

        if(choice != 3) {
            System.out.print("Press Enter twice to continue...");
            sn.nextLine();
        }
    }

    public void viewNotifications() {
        System.out.println("===============Notifications===============");
        System.out.println("You have " + user.getNotifications().size() + " notifications:");
        for(Object notification : user.getNotifications()) {
            System.out.println(notification);
        }

        cf.addSpaceTerminal();
        System.out.println("Press Enter twice to continue...");

        Scanner sn = new Scanner(System.in);
        sn.nextLine();
    }
    public void searchContent() {
        Scanner sn = new Scanner(System.in);
        String input, firstLetter;
        System.out.println("===============Search production / actor===============");
        System.out.print("Type what are you looking for: ");

        input = sn.nextLine();

        firstLetter = input.substring(0, 1).toUpperCase();
        input = input.substring(1);

        input = firstLetter + input;

        for(Object production : imdb.getProductions())
            if(((Production) production).getTitle().startsWith(input))
                System.out.println(((Production) production).getTitle() + " (" + ((Production) production).getType() + ")");

        for(Object actor : imdb.getActors())
            if(((Actor) actor).getName().startsWith(input)) System.out.println(((Actor) actor).getName() + " (Actor)");

        System.out.print("Press Enter twice to continue...");
        sn.nextLine();
    }

    public void modifyFavorites() {
        System.out.println("===============Add/Remove to/from favorites===============");
        String intro = "Please choose from the list how do you wish to continue:";
        String choiceList = "1. Add a production to favorites"
                        + "\n2. Remove a production from favorites"
                        + "\n3. Add an actor to favorites"
                        + "\n4. Remove an actor from favorites"
                        + "\n5. Go back to menu";

        String warning = "Please choose a valid number between 1 and 5";
        int choice = cf.getChoice(intro, choiceList, warning, "That is not a number between 1 and 5", 1, 5);
        cf.cleanTerminal();

        String input;
        Scanner sn = new Scanner(System.in);

        Production p = null;
        Actor a = null;

        boolean flag = false;

        switch(choice) {
            case 1 -> { // add production to favorites
                System.out.println("===============Add production to favorites===============");
                System.out.print("      Name of the production: ");

                input = sn.nextLine();

                for(Object production : imdb.getProductions())
                    if(((Production) production).getTitle().equals(input)) {
                        flag = true;
                        p = ((Production) production).getType().equals("Movie") ? (Movie) production : (Series) production;
                        break;
                    }

                if(!flag) {
                    System.out.println("Production doesn't exist in the database.");
                    cf.addSpaceTerminal();
                } else {
                    if(user.getFavorites().contains(p.getTitle())) {
                        System.out.println("Production is already in the favorites list.");
                    } else {
                        user.getFavorites().add(p.getTitle());
                        System.out.println("Production added in the favorites list.");
                    }
                }
            }
            case 2 -> { // remove production from favorites
                System.out.println("===============Remove production from favorites===============");
                System.out.print("      Name of the production: ");

                input = sn.nextLine();

                for(Object production : imdb.getProductions())
                    if(((Production) production).getTitle().equals(input)) {
                        flag = true;
                        p = ((Production) production).getType().equals("Movie") ? (Movie) production : (Series) production;
                        break;
                    }

                if(!flag) {
                    System.out.println("Production doesn't exist in the database.");
                    cf.addSpaceTerminal();
                } else {
                    if(!user.getFavorites().contains(p.getTitle())) {
                        System.out.println("Production is not in the favorites list.");
                    } else {
                        user.getFavorites().remove(p.getTitle());
                        System.out.println("Production removed from the favorite list.");
                    }
                }
            }
            case 3 -> { // add actor to favorites
                System.out.println("===============Add actor to favorites===============");
                System.out.print("      Name of the actor: ");

                input = sn.nextLine();

                for(Object actor : imdb.getActors())
                    if(((Actor) actor).getName().equals(input)) {
                        flag = true;
                        a = (Actor) actor;
                        break;
                    }

                if(!flag) {
                    System.out.println("Actor doesn't exist in the database.");
                    cf.addSpaceTerminal();
                } else {
                    if(user.getFavorites().contains(a.getName())) {
                        System.out.println("Actor is already in the favorites list.");
                    } else {
                        user.getFavorites().add(a.getName());
                        System.out.println("Actor added in the favorites list.");
                    }
                }
            }
            case 4 -> { // remove actor from favorites
                System.out.println("===============Remove actor from favorites===============");
                System.out.print("      Name of the actor: ");

                input = sn.nextLine();

                for(Object actor : imdb.getActors())
                    if(((Actor) actor).getName().equals(input)) {
                        flag = true;
                        a = (Actor) actor;
                        break;
                    }

                if(!flag) {
                    System.out.println("Actor doesn't exist in the database.");
                    cf.addSpaceTerminal();
                } else {
                    if(!user.getFavorites().contains(a.getName())) {
                        System.out.println("Actor is not in the favorites list.");
                    } else {
                        user.getFavorites().remove(a.getName());
                        System.out.println("Actor removed from the favorites list.");
                    }
                }
            }
            case 5 -> cf.addSpaceTerminal();
        }

        if(choice != 5) {
            System.out.print("Press Enter twice to continue...");
            sn.nextLine();
        }
    }
    public void modifyUsers() {
        System.out.println("===============Add/Remove user===============");
        if(this.user.getUserType() != AccountType.Admin) {
            System.out.println("Only admins can use this option. Press Enter twice to continue...");
            cf.addSpaceTerminal();
            new Scanner(System.in).nextLine();
            return;
        }

        String intro = "Please choose from the list how do you wish to continue:";
        String choiceList = "1. Add a user"
                        + "\n2. Remove a user"
                        + "\n3. Go back to menu";

        String warning = "Please choose a valid number between 1 and 3";
        int choice = cf.getChoice(intro, choiceList, warning, "That is not a number between 1 and 3", 1, 3);
        cf.addSpaceTerminal();

        String input;
        boolean userExist = false;
        Scanner sn = new Scanner(System.in);

        switch(choice) {
            case 1 -> { // add user
                User user = null;
                String name, country, gender;
                LocalDateTime birthDate = null;
                Credentials credentials = new Credentials();
                int age = 0;

                // name, country, gender, credentials  and age
                System.out.print("      Name of the user: ");
                name = sn.nextLine();

                for(Object u : imdb.getUsers()) {
                    if(((User) u).getUsername().equals(name)) {
                        System.out.println("User already exists in the database.");
                        System.out.print("Press Enter twice to continue...");
                        sn.nextLine();
                        return;
                    }
                }

                System.out.print("      Country of the user: ");
                country = sn.nextLine();

                System.out.print("      Gender of the user: ");
                gender = sn.nextLine();

                boolean isEmail = false;

                while(!isEmail) {
                    System.out.print("      Email of the user: ");
                    input = sn.nextLine();
                    credentials.setEmail(input);
                    isEmail = true;

                    if(!Pattern.compile("^(.+)@(\\S+)$").matcher(input).matches()) {
                        System.out.println("Invalid email. Please try again.");
                        cf.addSpaceTerminal();
                        isEmail = false;
                    }
                }

                System.out.print("Password of the user: ");
                credentials.setPassword(sn.nextLine());

                age = cf.getChoice("Age of the user", "(Between 13 and 100)",
                                "The age needs to be between 13 and 100",
                                "That is not a number between 13 and 100", 13, 100);


                // username and userType
                String username = this.user.generateUniqueUsername(name);

                List<String> userTypes = new ArrayList<>();

                userTypes.add("Admin");
                userTypes.add("Contributor");
                userTypes.add("Regular");

                input = "";
                while(!userTypes.contains(input)) {
                    System.out.print("      User type: ");
                    input = sn.nextLine();

                    if(!userTypes.contains(input))
                        System.out.println("Write 'Admin', 'Contributor' or 'Regular'.\n");
                }

                switch(input) {
                    case "Admin" -> {user = new Admin(); user.setUserType(AccountType.Admin);}
                    case "Contributor" -> {user = new Contributor(); user.setUserType(AccountType.Contributor);}
                    case "Regular" -> {user = new Regular(); user.setUserType(AccountType.Regular);}
                }

                // birthDate
                boolean isValid = false;

                while(!isValid) {
                    System.out.print("      Enter a date in the format yyyy-MM-dd: ");
                    input = sn.nextLine();

                    input += " 00:00:00";

                    try {
                        birthDate = LocalDateTime.parse(input, DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
                        isValid = true;
                    } catch (Exception e) {
                        System.out.println("Invalid date format. Please enter a date in the format yyyy-MM-dd.");
                        cf.addSpaceTerminal();
                    }
                }

                User.Information.InformationBuilder infoB =
                        new User.Information.InformationBuilder(name, age, birthDate, credentials)
                                                .country(country).gender(gender);

                user.setUsername(username);
                user.setInformation(infoB.build());
                user.setExperience("1");
                user.setNotifications(new ArrayList<>());
                user.setFavoriteProductions(new ArrayList<>());
                user.setFavoriteActors(new ArrayList<>());
                user.setProductionsContribution(new ArrayList<>());
                user.setActorsContribution(new ArrayList<>());

                imdb.getUsers().add(user);
            }
            case 2 -> { // remove user
                System.out.print("Name of the user: ");
                input = sn.nextLine();

                for(Object user : imdb.getUsers()) {
                    if(((User) user).getUsername().equals(input)) {
                        userExist = true;
                        if(((Admin) this.user).removeUser((User) user)) System.out.println("User was removed.");
                        else System.out.println("User couldn't be removed.");
                        break;
                    }
                }

                if(!userExist) {
                    System.out.println("User doesn't exist in the database.");
                    cf.addSpaceTerminal();
                }
            }
            case 3 -> cf.addSpaceTerminal();
        }

        if(choice != 3) {
            System.out.print("Press Enter twice to continue...");
            sn.nextLine();
        }
    }

    public void modifyContent() {
        System.out.println("===============Add/Remove actor/production===============");
        if(this.user.getUserType() == AccountType.Regular) {
            System.out.println("Option is unavailable for regular users. Press Enter twice to continue...");
            cf.addSpaceTerminal();
            new Scanner(System.in).nextLine();
            return;
        }

        String intro = "Please choose from the list how do you wish to continue:";
        String choiceList = "1. Add a production"
                        + "\n2. Remove a production"
                        + "\n3. Add an actor"
                        + "\n4. Remove an actor"
                        + "\n5. Go back to menu";

        String warning = "Please choose a valid number between 1 and 5";
        int choice = cf.getChoice(intro, choiceList, warning, "That is not a number between 1 and 5", 1, 5);

        String input;
        Scanner sn = new Scanner(System.in);

        switch(choice) {
            case 1 -> { // add a production
                Production production = null;

                boolean isOk = false;

                while(!isOk) {
                    System.out.print("      Production type: ");
                    input = sn.nextLine();
                    isOk = true;

                    // get production type
                    switch(input) {
                        case "Movie" -> {production = new Movie(); production.setType("Movie");}
                        case "Series" -> {production = new Series(); production.setType("Series");}
                        default -> {
                            System.out.println("Please choose between Movie or Series.");
                            isOk = false;
                            continue;
                        }
                    }

                    System.out.print("      Title: ");
                    input = sn.nextLine();

                    for(Object p : imdb.getProductions()) {
                        if(((Production) p).getTitle().equals(input)) {
                            System.out.println("Production is already in the database.");
                            System.out.print("Press Enter twice to continue...");
                            sn.nextLine();
                            return;
                        }
                    }

                    production.setTitle(input);

                    System.out.print("      Plot: ");
                    production.setPlot(sn.nextLine());

                    production.setAverageRating(0);

                    int size = cf.getChoice("How many actors?", "(Maximum 30)",
                                        "Please type a number between 1 and 30",
                                        "That is not a number between 1 and 30", 1, 30);

                    List<String> actors = new ArrayList<>();

                    for(int i = 0; i < size; i++) {
                        System.out.print("      Actor " + (i + 1) + ": ");
                        actors.add(sn.nextLine());
                    }

                    size = cf.getChoice("How many directors?", "(Maximum 5)",
                            "Please type a number between 1 and 5",
                            "That is not a number between 1 and 5", 1, 5);

                    List<String> directors = new ArrayList<>();

                    for(int i = 0; i < size; i++) {
                        System.out.print("      Director " + (i + 1) + ": ");
                        directors.add(sn.nextLine());
                    }

                    size = cf.getChoice("How many genres?", "(Maximum 8)",
                            "Please type a number between 1 and 8",
                            "That is not a number between 1 and 8", 1, 8);

                    List<Genre> genres = new ArrayList<>();

                    for(int i = 0; i < size; i++) {
                        System.out.print("      Genre " + (i + 1) + ": ");
                        input = sn.nextLine();

                        cf.updateGenres(input, genres);
                    }

                    production.setActors(actors);
                    production.setDirectors(directors);
                    production.setGenres(genres);

                    if(production.getType().equals("Movie")) {
                        System.out.print("      Duration: ");
                        ((Movie) production).setDuration(sn.nextLine());

                        int year = cf.getChoice("      When was it released?",
                                "      (Maximum 2024)", "Please type a number between 1900 and 2024",
                                "That is not a number between 1 and 30", 1900, 2024);

                        ((Movie) production).setReleaseYear(year);
                    } else {
                        int year = cf.getChoice("      When was it released?",
                                "      (Maximum 2024)", "Please type a number between 1900 and 2024",
                                "That is not a number between 1 and 30", 1900, 2024);

                        ((Series) production).setReleaseYear(year);

                        int num = cf.getChoice("      How many seasons?",
                                    "      (Maximum 30)", "Please type a number between 1 and 30",
                                    "That is not a number between 1 and 30", 1, 30);

                        ((Series) production).setNumSeasons(num);

                        for(int i = 1; i <= num; i++) {
                            int numEp = cf.getChoice("      How many epsisods in season " + i + "?",
                                    "      (Maximum 30)", "Please type a number between 1 and 30",
                                    "That is not a number between 1 and 30", 1, 30);

                            System.out.println("      Season " + i + ":");
                            List<Episode> episodes = new ArrayList<>();
                            for(int j = 1; j <= num; j++) {
                                Episode episode = new Episode();

                                System.out.println("            Episode " + j + ":");

                                System.out.print("                  Name: ");
                                episode.setEpisodeName(sn.nextLine());

                                System.out.print("                  Duration: ");
                                episode.setDuration(sn.nextLine());

                                episodes.add(episode);
                            }

                            ((Series) production).getSeasons().put("Season " + i, episodes);
                        }
                    }

                    imdb.getProductions().add(production);
                    this.user.getProductionsContribution().add(production.getTitle());
                }

            }
            case 2 -> { // remove a production
                System.out.print("Production you want to remove: ");
                input = sn.nextLine();

                if(!this.user.getProductionsContribution().contains(input)) {
                    System.out.println("You can't remove something you didn't added.");
                    cf.addSpaceTerminal();
                    System.out.print("Press Enter twice to continue...");
                    sn.nextLine();
                    return;
                }

                for(Object p : imdb.getProductions()) {
                    if(((Production) p).getTitle().equals(input)) {
                        imdb.getProductions().remove(p);
                        this.user.getProductionsContribution().remove(input);
                        System.out.println("Production was removed from database");
                        return;
                    }
                }

                System.out.println("Production doesn't exist in the database.");
            }
            case 3 -> { // add an actor
                Actor actor = new Actor();

                System.out.print("      Name for the actor: ");
                input = sn.nextLine();

                if(this.user.getActorsContribution().contains(input)) {
                    System.out.println("Actor is already in your contribution list.");
                    System.out.print("Press Enter twice to continue...");
                    sn.nextLine();
                    return;
                }

                for(Object a : imdb.getActors()) {
                    if(((Actor) a).getName().equals(input)) {
                        System.out.println("Actor is already in database.");
                        System.out.print("Press Enter twice to continue...");
                        sn.nextLine();
                        return;
                    }
                }

                actor.setName(input);

                System.out.print("        Biography: ");
                actor.setBiography(sn.nextLine());

                ArrayList<Performances> performances = new ArrayList<>();

                int size = cf.getChoice("In how many performances was the actor?",
                                        "(Maximum 30)", "Please type a number between 1 and 30",
                                        "That is not a number between 1 and 30", 1, 30);

                for(int i = 1; i <= size; i++) {
                    Performances performance = new Performances();

                    System.out.print("      Title of production " + i + ": ");
                    performance.setTitle(sn.nextLine());

                    System.out.print("      Type of production " + i + ": ");
                    performance.setType(sn.nextLine());

                    performances.add(performance);
                }

                actor.setPerformances(performances);

                imdb.getActors().add(actor);
                this.user.getActorsContribution().add(actor.getName());
            }
            case 4 -> { // remove an actor
                System.out.print("Name of the actor: ");
                input = sn.nextLine();

                if(!this.user.getActorsContribution().contains(input)) {
                    System.out.println("Actor can not be removed if it isn't in your contribution list.");
                    System.out.print("Press Enter twice to continue...");
                    sn.nextLine();
                    return;
                }

                for(Object a : imdb.getActors()) {
                    if(((Actor) a).getName().equals(input)) {
                        imdb.getActors().remove(a);
                        System.out.println("Actor was removed from the database");
                        break;
                    }
                }
                System.out.println("Actor is not in the database");
            }
            case 5 -> cf.addSpaceTerminal();
        }

        if(choice != 5) {
            System.out.print("Press Enter twice to continue...");
            sn.nextLine();
        }
    }

    private void modifyRating() {
        System.out.println("===============Add/Remove rating to/from a production===============");
        if(this.user.getUserType() != AccountType.Regular) {
            System.out.println("Option is available only for regular users. Press Enter twice to continue...");
            cf.addSpaceTerminal();
            new Scanner(System.in).nextLine();
            return;
        }

        String intro = "Please choose from the list how do you wish to continue:";
        String choiceList = "1. Add a rating"
                        + "\n2. Remove a rating"
                        + "\n3. Go back to menu";

        String warning = "Please choose a valid number between 1 and 3";
        int choice = cf.getChoice(intro, choiceList, warning, "That is not a number between 1 and 3", 1, 3);

        String input;
        Scanner sn = new Scanner(System.in);

        switch(choice) {
            case 1 -> { // add a rating
                System.out.print("      Production you want to add a rating: ");
                input = sn.nextLine();

                Production production = null;
                boolean productionExists = false;

                for(Object p : imdb.getProductions()) {
                    if(((Production) p).getTitle().equals(input)) {
                        production = (Production) p;
                        productionExists = true;
                        break;
                    }
                }

                if(!productionExists) {
                    System.out.println("Production doesn't exist in the database.");
                    break;
                }

                Rating rating = new Rating();
                rating.setUsername(this.user.getUsername());

                System.out.print("      Type your review: ");
                rating.setComment(sn.nextLine());

                int grade = cf.getChoice("      What rating are you giving?",
                                        "(You can choose from 1 to 10)",
                                        "Please type a number between 1 and 10.",
                                        "That is not a number between 1 and 10", 1, 10);

                rating.setRating(grade);

                ((Regular) this.user).addRating(production, rating);
            }
            case 2 -> { // remove a rating
                System.out.print("      Production you want to remove a rating: ");
                input = sn.nextLine();

                Production production = null;
                boolean productionExists = false;

                for(Object p : imdb.getProductions()) {
                    if(((Production) p).getTitle().equals(input)) {
                        production = (Production) p;
                        productionExists = true;
                        break;
                    }
                }

                if(!productionExists) {
                    System.out.println("Production doesn't exist in the database.");
                    break;
                }

                for(Rating r : production.getRatings())
                    if(r.getUsername().equals(this.user.getUsername()))
                        ((Regular) this.user).removeRating(production, r);
            }
            case 3 -> cf.addSpaceTerminal();
        }

        if(choice != 3) {
            System.out.print("Press Enter twice to continue...");
            sn.nextLine();
        }
    }

    public void updateProduction() {
        if(this.user.getUserType() == AccountType.Regular) {
            System.out.println("Only admins and contributors can use this option. Press Enter twice to continue...");
            cf.addSpaceTerminal();
            new Scanner(System.in).nextLine();
            return;
        }

        System.out.println("===============Update production===============");
        String intro = "Please choose from the list how do you wish to continue:";
        String choiceList = "1. Change title"
                + "\n2. Add actor to production"
                + "\n3. Add season (if Series)"
                + "\n4. Add episodes to last season (if Series)"
                + "\n5. Go back to menu";

        String warning = "Please choose a valid number between 1 and 5";
        int choice = cf.getChoice(intro, choiceList, warning, "That is not a number between 1 and 5", 1, 5);
        cf.cleanTerminal();

        Scanner sn = new Scanner(System.in);
        String input;

        System.out.println("Productions you can update: ");
        for(Object production : this.user.getProductionsContribution())
            System.out.println("        " + production);

        System.out.print("Title of the production you want to update: ");
        input = sn.nextLine();

        if(!this.user.getProductionsContribution().contains(input)) {
            System.out.println("Production can not be updated if it isn't in your contribution list. Press Enter twice to continue...");
            cf.addSpaceTerminal();
            return;
        }

        Production production = null;
        boolean productionExists = false;

        for(Object p : imdb.getProductions()) {
            if(((Production) p).getTitle().contains(input)) {
                production = (Production) p;
                productionExists = true;
                break;
            }
        }

        if(!productionExists) {
            System.out.println("Production doesn't exist in the database. Press Enter twice to continue...");
            sn.nextLine();
            return;
        }

        switch(choice) {
            case 1 -> { // change title
                System.out.print("      New title: ");
                production.setTitle(sn.nextLine());
                System.out.println("Production's title updated.");
                 }
            case 2 -> { // add actor to production
                System.out.print("        Name of the actor: ");
                production.getActors().add(sn.nextLine());
                System.out.println("Production's actors list updated.");
            }
            case 3 -> { // add season if Series
                if(!production.getType().equals("Series")) {
                    System.out.println("A movie can not have seasons.");
                    break;
                }

                int size = cf.getChoice("      Number of episodes: ",
                        "(Maximum 32)", "Please type a number between 1 and 32",
                        "That is not a number between 1 and 32", 1, 32);

                List<Episode> episodes = new ArrayList<>();

                for(int i = 1; i <= size; i++) {
                    Episode episode = new Episode();

                    System.out.print("        Episode " + i + " name: ");
                    episode.setEpisodeName(sn.nextLine());

                    System.out.print("        Episode " + i + " duration: ");
                    episode.setDuration(sn.nextLine());

                    System.out.println("=================================================");
                    episodes.add(episode);
                }

                ((Series) production).getSeasons().put("Season " + ((Series) production).getNumSeasons(), episodes);
                System.out.println("Production's new season added.");
            }
            case 4 -> { // add episodes to last season if Series
                int size = cf.getChoice("      Number of episodes: ",
                        "(Maximum 16)", "Please type a number between 1 and 16",
                        "That is not a number between 1 and 16", 1, 16);

                Series s = ((Series) production);

                int lastEp = s.getSeasons().get("Season " + s.getNumSeasons()).size();

                for(int i = lastEp + 1; i < lastEp + size; i++) {
                    Episode episode = new Episode();

                    System.out.print("        Episode " + i + " name: ");
                    episode.setEpisodeName(sn.nextLine());

                    System.out.print("        Episode " + i + " duration: ");
                    episode.setDuration(sn.nextLine());

                    System.out.println("=================================================");
                    s.getSeasons().get("Season " + s.getNumSeasons()).add(episode);
                }
                System.out.println("Production's new episodes added.");
            }
            case 5 -> cf.addSpaceTerminal();
        }

        if(choice != 5) {
            System.out.print("Press Enter twice to continue...");
            sn.nextLine();
        }
    }

    public void updateActor() {
        if(this.user.getUserType() == AccountType.Regular) {
            System.out.println("Only admins and contributors can use this option. Press Enter twice to continue...");
            cf.addSpaceTerminal();
            new Scanner(System.in).nextLine();
            return;
        }

        System.out.println("===============Update Actor===============");
        String intro = "Please choose from the list how do you wish to continue:";
        String choiceList = "1. Change actor name"
                + "\n2. Change actor biography"
                + "\n3. Add performances"
                + "\n4. Go back to menu";

        String warning = "Please choose a valid number between 1 and 4";
        int choice = cf.getChoice(intro, choiceList, warning, "That is not a number between 1 and 4", 1, 4);
        cf.cleanTerminal();

        System.out.println("Actors you can update: ");
        for(Object actor : this.user.getActorsContribution())
            System.out.println("        " + actor);

        Scanner sn = new Scanner(System.in);
        String input;

        System.out.print("Name of the actor you want to update: ");
        input = sn.nextLine();

        if(!this.user.getProductionsContribution().contains(input)) {
            System.out.println("Actor can not be updated if it isn't in your contribution list. Press Enter twice to continue...");
            cf.addSpaceTerminal();
            return;
        }

        Actor actor = null;
        boolean actorExists = false;

        for(Object a : imdb.getProductions()) {
            if(((Actor) a).getName().contains(input)) {
                actor = (Actor) a;
                actorExists = true;
                break;
            }
        }

        if(!actorExists) {
            System.out.println("Actor doesn't exist in the database. Press Enter twice to continue...");
            sn.nextLine();
            return;
        }

        switch(choice) {
            case 1 -> { // change actor name
                System.out.print("      New actor name: ");
                actor.setName(sn.nextLine());
                System.out.println("Actor's name updated.");
            }
            case 2 -> { // change actor biography
                System.out.print("        New actor biography");
                actor.setBiography(sn.nextLine());
                System.out.println("Actor's biography updated");
            }
            case 3 -> { // add performances
                int size = cf.getChoice("       How many performances?", "(Maximum 5)",
                        "Please type a number between 1 and 5.",
                        "That is not a number between 1 and 5", 1, 5);

                for(int i = 1; i <= size; i++) {
                    Performances performance = new Performances();

                    System.out.print("        Production type: ");
                    performance.setType(sn.nextLine());

                    System.out.print("        Production title: ");
                    performance.setTitle(sn.nextLine());

                    actor.getPerformances().add(performance);
                }
                System.out.println("Actor's performances updated.");
            }
            case 4 -> cf.addSpaceTerminal();
        }

        if(choice != 4) {
            System.out.print("Press Enter twice to continue...");
            sn.nextLine();
        }
    }

    public void solveRequest() {
        if(this.user.getUserType() == AccountType.Regular) {
            System.out.println("Only admins and contributors can use this option. Press Enter twice to continue...");
            cf.addSpaceTerminal();
            new Scanner(System.in).nextLine();
            return;
        }

        System.out.println("===============Solve a request===============");
        String intro = "Please choose from the list how do you wish to continue:";
        String choiceList = "1. View all of your requests."
                + "\n2. View details of specific request"
                + "\n3. Mark as done a specific request"
                + "\n4. Go back to menu";

        String warning = "Please choose a valid number between 1 and 4";
        int choice = cf.getChoice(intro, choiceList, warning, "That is not a number between 1 and 4", 1, 4);
        cf.cleanTerminal();

        Scanner sn = new Scanner(System.in);
        String input;

        switch(choice) {
            case 1 -> { // view requests
                System.out.println("===============Your requests===============");

                if(this.user.getUserType() == AccountType.Admin) {
                    System.out.println("===============Admin requests===============");
                    for(Request r : new RequestsHolder().getAdminRequests()) r.displayInfo();
                }

                boolean isAdmin = this.user.getUserType() == AccountType.Admin;
                User user = isAdmin ? new Admin() : new Contributor();

                System.out.println("===============Movie/Actor requests===============");
                for(Object request : (isAdmin ? (Admin) user : (Contributor) user).getRequests())
                    ((Request) request).displayInfo();

            }
            case 2 -> { // view specific requests
                System.out.println("===============View specific requests===============");

                System.out.print("      Find request after username: ");
                input = sn.nextLine();

                if(this.user.getUserType() == AccountType.Admin) {
                    System.out.println("===============Admin requests===============");
                    for(Request r : new RequestsHolder().getAdminRequests())
                        if(r.getUsername().equals(input)) r.displayInfo();
                }

                boolean isAdmin = this.user.getUserType() == AccountType.Admin;
                User user = isAdmin ? new Admin() : new Contributor();

                System.out.println("===============Movie/Actor requests===============");
                for(Object request : (isAdmin ? (Admin) user : (Contributor) user).getRequests())
                    if(((Request) request).getUsername().equals(input)) ((Request) request).displayInfo();
            }
            case 3 -> { // mark request as done
                System.out.println("===============Mark as done specific request===============");

                System.out.print("      Find request after username: ");
                input = sn.nextLine();

                if(this.user.getUserType() == AccountType.Admin) {
                    for(Request r : new RequestsHolder().getAdminRequests())
                        if(r.getUsername().equals(input)) {
                            new RequestsHolder().removeRequest((Request) r);

                            for(Object user : imdb.getUsers()) {
                                if(((User) user).getUsername().equals(input))
                                    ((User) user).getNotifications().add("A request was marked as done by an admin.");
                            }
                        }
                }

                boolean isAdmin = this.user.getUserType() == AccountType.Admin;
                User user = isAdmin ? new Admin() : new Contributor();

                for(Object request : (isAdmin ? (Admin) user : (Contributor) user).getRequests())
                    if(((Request) request).getUsername().equals(input)) {
                        (isAdmin ? (Admin) user : (Contributor) user).getRequests().remove(request);
                        for(Object u : imdb.getUsers()) {
                            if(((User) u).getUsername().equals(input))
                                ((User) u).getNotifications().add("A request was marked as done by "
                                        + user.getUsername() + ".");
                        }
                    }
            }
            case 4 -> cf.addSpaceTerminal();
        }

        if(choice != 4) {
            System.out.print("Press Enter twice to continue...");
            sn.nextLine();
        }
    }

    public void login() {
        boolean isLoggedIn = false;

        while(!isLoggedIn) {
            System.out.println("\n===============Log in===============");
            System.out.println("Please enter your email and password");
            System.out.print("      Email: ");

            Scanner sn = new Scanner(System.in);

            if(!sn.hasNextLine()) {
                System.out.println("        Please enter the email");
                cf.addSpaceTerminal();
                continue;
            }

            String email = sn.nextLine();

            if(!Pattern.compile("^(.+)@(\\S+)$").matcher(email).matches()) {
                System.out.println("        Invalid email");
                cf.addSpaceTerminal();
                continue;
            }

            System.out.print("      Password: ");

            if(!sn.hasNextLine()) {
                System.out.println("        Please enter the password");
                cf.addSpaceTerminal();
                continue;
            }

            String password = sn.nextLine();

            boolean userExists = false;

            for(Object user : imdb.getUsers()) {
                Credentials credential = ((User) user).getInformation().getCredentials();

                if(credential.getEmail().equals(email) && credential.getPassword().equals(password)) {
                    this.user = ((User) user);
                    userExists = true;
                    break;
                }
            }

            if(userExists) {
                cf.cleanTerminal();
                System.out.println("Welcome back, " + this.user.getUsername() + "!");
                isLoggedIn = true;
                continue;
            }

            cf.addSpaceTerminal();
            System.out.println("Email or password not found or incorrect. Please try again!\n");
        }
    }
}
