package GUI;

import org.example.*;

import java.util.List;

public class CustomFunctionGUI {
    public static User findUser(String email, String password) {
        IMDB imdb = IMDB.getInstance();

        for(Object u : imdb.getUsers()) {
            Credentials credential = ((User) u).getInformation().getCredentials();
            if(credential.getEmail().equals(email) && credential.getPassword().equals(password))
                return (User) u;
        }

        return null;
    }

    public static Production findProduction(String name) {
        for(Object p : IMDB.getInstance().getProductions())
            if(((Production) p).getTitle().equals(name)) return (Production) p;

        return null;
    }

    public static User findUser(String name) {
        IMDB imdb = IMDB.getInstance();

        for(Object u : imdb.getUsers())
            if(((User) u).getUsername().equals(name)) return (User) u;

        return null;
    }

    public static String displayContributions(User user) {
        if(user.getUserType() == AccountType.Regular) return "Regulars don't have a contribution list";
        String result = "";

        for(Object production : user.getProductionsContribution())
            result += production + " (Production)\n";

        for(Object actor : user.getActorsContribution())
            result += actor + " (Actor)\n";

        return result;
    }

    public static String displayRatings(Production production) {
        if(production == null) return "_";
        String result = production.getTitle() + ": ";
        List<Rating> ratings = ((Production) production).getRatings();

        for(Rating r : ratings)
            result += "\n     > From: " + r.getUsername() + "\n         > Comment: " + r.getComment()
                   + "\n         > Rating: " + r.getRating();

        return result;
    }

    public static String displayUser(User user) {
        return  "\n\n     Username = " + user.getUsername() +
                        "\n     Type = " + user.getUserType() +
                        "\n     Age = " + user.getInformation().getAge() +
                        "\n     Country = " + user.getInformation().getCountry() +
                        "\n     Gender = " + user.getInformation().getGender() +
                        "\n     BirthDate = " + user.getInformation().getBirthDate() +
                        "\n     Email = " + user.getInformation().getCredentials().getEmail();
    }

    public static String displayUserFull(User user) {
        String result =  "\n     Username = " + user.getUsername() +
                "\n     Type = " + user.getUserType() +
                "\n     Age = " + user.getInformation().getAge() +
                "\n     Country = " + user.getInformation().getCountry() +
                "\n     Gender = " + user.getInformation().getGender() +
                "\n     BirthDate = " + user.getInformation().getBirthDate() +
                "\n\n\n     Name = " + user.getInformation().getName() +
                "\n     Notifications:";

        for(Object notification : user.getNotifications()) result += "\n               " + notification;

        result += "\n     Favorites:";
        for(Object favorite : user.getFavorites()) result += "\n               " + favorite;

        result += "\n     Production contributions:";
        for(Object production : user.getProductionsContribution()) result += "\n               " + production;

        result += "\n     Actor contributions:";
        for(Object actor : user.getProductionsContribution()) result += "\n               " + actor;

        return result;
    }

    public static String displayRequest(Request r) {
        String result = "Type: " + r.getType() + "\nFrom: " + r.getUsername() + "\nType: " + r.getType();

        result += "\nDetails: " + r.getDescription() + "\nName: " +
                (r.getType() == RequestType.ACTOR_ISSUE ? r.getActorName() : r.getMovieTitle());
        result += "\nDate: " + r.getCreatedDate();
        return result;
    }

    public static String displayResults(String input) {
        IMDB imdb = IMDB.getInstance();
        String result = "";

        for(Object production : imdb.getProductions())
            if(((Production) production).getTitle().equals(input) || ((Production) production).getTitle().startsWith(input))
                result += "\n" + ((Production) production).getTitle() + " (" +
                        ((Production) production).getType() + ")" + " -> " +
                        ((Production) production).getAverageRating() + " / 10";

        for(Object actor : imdb.getActors())
            if(((Actor) actor).getName().equals(input) || ((Actor) actor).getName().startsWith(input))
                result += "\n" + ((Actor) actor).getName() + " (Actor)";

        return result;
    }

    public static String displayResultsByGender(String input) {
        String result = "";

        for(Object production : IMDB.getInstance().getProductions())
            if(containsGenre((Production) production, input))
                result += "\n" + ((Production) production).getTitle() + " (" +
                        ((Production) production).getType() + ")" + " -> " +
                        ((Production) production).getAverageRating() + " / 10";

        return result;
    }

    public static String displayResultsByActor(String input) {
        String result = "";

        for(Object actor : IMDB.getInstance().getActors())
            if(((Actor) actor).getName().equals(input) || ((Actor) actor).getName().startsWith(input))
                result += "\n" + ((Actor) actor).getName() + " (Actor)";

        return result;
    }

    public static String displayResultsBySeries(String input) {
        String result = "";

        for(Object production : IMDB.getInstance().getProductions())
            if( ((Production) production).getType().equals("Series") &&
                    (((Production) production).getTitle().equals(input)
                            || ((Production) production).getTitle().startsWith(input)))

                result += "\n" + ((Production) production).getTitle() + " (" +
                        ((Production) production).getType() + ")" + " -> " +
                        ((Production) production).getAverageRating() + " / 10";

        return result;
    }

    public static String displayResultsByMovie(String input) {
        String result = "";

        for(Object production : IMDB.getInstance().getProductions())
            if( ((Production) production).getType().equals("Movie") &&
                    (((Production) production).getTitle().equals(input)
                            || ((Production) production).getTitle().startsWith(input)))

                result += "\n" + ((Production) production).getTitle() + " (" +
                        ((Production) production).getType() + ")" + " -> " +
                        ((Production) production).getAverageRating() + " / 10";

        return result;
    }

    public static String displayResultsByYear(String input) {
        String result = "";

        int year;

        try {
            year = Integer.parseInt(input);
        } catch (NumberFormatException e) {
            return "";
        }

        for(Object production : IMDB.getInstance().getProductions()) {
            if(((Production) production).getType().equals("Movie") && ((Movie) production).getReleaseYear() == year)
                result += "\n" + ((Production) production).getTitle() + " (" +
                        ((Production) production).getType() + ")" + " -> " +
                        ((Production) production).getAverageRating() + " / 10";

            if(((Production) production).getType().equals("Series") && ((Series) production).getReleaseYear() == year)
                result += "\n" + ((Production) production).getTitle() + " (" +
                        ((Production) production).getType() + ")" + " -> " +
                        ((Production) production).getAverageRating() + " / 10";
        }

        return result;
    }

    public static String displayResultsByAverageRating(String input) {
        String result = "";

        double average;

        try {
            average = Double.parseDouble(input);
        } catch (NumberFormatException e) {
            return "";
        }

        for(Object production : IMDB.getInstance().getProductions()) {
            if(((Production) production).getAverageRating() >= average)
                result += "\n" + ((Production) production).getTitle() + " (" +
                        ((Production) production).getType() + ")" + " -> " +
                        ((Production) production).getAverageRating() + " / 10";
        }

        return result;
    }

    public static String displayResultsByNumberOfRatings(String input) {
        String result = "";

        int num;

        try {
            num = Integer.parseInt(input);
        } catch (NumberFormatException e) {
            return "";
        }

        for(Object production : IMDB.getInstance().getProductions()) {
            if(((Production) production).getRatings().size() >= num)
                result += "\n" + ((Production) production).getTitle() + " (" +
                        ((Production) production).getType() + ")" + " -> " +
                        ((Production) production).getAverageRating() + " / 10";
        }

        return result;
    }

    public static boolean containsGenre(Production p, String genre) {
        Genre g;

        switch(genre) {
            case "Action" -> g = Genre.ACTION;
            case "Adventure" -> g = Genre.ADVENTURE;
            case "Animation" -> g = Genre.ANIMATION;
            case "Biography" -> g = Genre.BIOGRAPHICAL;
            case "Comedy" -> g = Genre.COMEDY;
            case "Cooking" -> g = Genre.COOKING;
            case "Crime" -> g = Genre.CRIME;
            case "Disaster" -> g = Genre.DISASTER;
            case "Documentary" -> g = Genre.DOCUMENTARY;
            case "Drama" -> g = Genre.DRAMA;
            case "Experimental" -> g = Genre.EXPERIMENTAL;
            case "Family" -> g = Genre.FAMILY;
            case "Fantasy" -> g = Genre.FANTASY;
            case "Historical" -> g = Genre.HISTORICAL;
            case "History" -> g = Genre.HISTORY;
            case "Horror" -> g = Genre.HORROR;
            case "Martial arts" -> g = Genre.MARTIAL_ARTS;
            case "Music" -> g = Genre.MUSIC;
            case "Musical" -> g = Genre.MUSICAL;
            case "Mystery" -> g = Genre.MYSTERY;
            case "Noir" -> g = Genre.NOIR;
            case "Political" -> g = Genre.POLITICAL;
            case "Romance" -> g = Genre.ROMANCE;
            case "SF" -> g = Genre.SCIENCE_FICTION;
            case "Silent" -> g = Genre.SILENT;
            case "Social" -> g = Genre.SOCIAL;
            case "Sport" -> g = Genre.SPORT;
            case "Spy" -> g = Genre.SPY;
            case "Supernatural" -> g = Genre.SUPERNATURAL;
            case "Thriller" -> g = Genre.THRILLER;
            case "War" -> g = Genre.WAR;
            case "Western" -> g = Genre.WESTERN;
            default -> g = Genre.COOKING;
        }
        return p.getGenres().contains(g);
    }
}
