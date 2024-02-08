package org.example;

import CLI.MainCLI;
import GUI.MainGUI;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import CLI.CustomFunctionsCLI;

import java.io.File;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;

public class IMDB {

    private static IMDB instance = null;

    private boolean isRunning = true;
    private List<Actor> actors = new ArrayList<>();
    private ArrayList<String> adminContributions = new ArrayList<>();
    private List<Production> productions = new ArrayList<>();
    private List<Request> requests = new ArrayList<>();
    private List<Object> users = new ArrayList<>();
    private final String accountsPath = "src/test/resources/testResources/accounts.json";
    private final String actorsPath = "src/test/resources/testResources/actors.json";
    private final String productionPath = "src/test/resources/testResources/production.json";
    private final String requestsPath = "src/test/resources/testResources/requests.json";
    private final String accountsPathCopy = "src/test/resources/testResources/accountsCopy.json";
    private final String actorsPathCopy = "src/test/resources/testResources/actorsCopy.json";
    private final String productionPathCopy = "src/test/resources/testResources/productionCopy.json";
    private final String requestsPathCopy = "src/test/resources/testResources/requestsCopy.json";

    private IMDB() {}
    private IMDB(List<Actor> actors, List<Production> productions, List<Request> requests, List<Object> users) {
        this.actors = actors;
        this.productions = productions;
        this.requests = requests;
        this.users = users;
    }

    public static IMDB getInstance() {
        if(instance == null) instance = new IMDB();
        return instance;
    }

    private void readAccounts() {
        try {
            ObjectMapper objectMapper = new ObjectMapper();
            List<Map<String, Object>> accounts = objectMapper.readValue(new File(accountsPath), List.class);

            for (Map<String, Object> account : accounts) {

                // get user type
                String type = (String) account.get("userType");
                AccountType userType;

                switch(type) {
                    case "Admin" -> userType = AccountType.Admin;
                    case "Contributor" -> userType = AccountType.Contributor;
                    case "Regular" -> userType = AccountType.Regular;
                    default -> {
                        System.out.println("Wrong user type. Something went wrong.");
                        continue;
                    }
                }

                // get credentials
                Map<String, String> credentials = (Map<String, String>) ((Map<String, Object>) account.get("information")).get("credentials");
                Credentials credential = new Credentials(credentials.get("email"), credentials.get("password"));

                Map<String, Object> information = (Map<String, Object>) account.get("information");
                String date = (String) information.get("birthDate");
                LocalDateTime birthDate = LocalDate.parse(date).atStartOfDay();

                // get information and make a parser for it
                InformationToParse info = new InformationToParse(credential,
                                            (String) information.get("name"), (String) information.get("country"),
                                            (int) information.get("age"), (String) information.get("gender"),
                                            birthDate);


                // get notifications
                ArrayList<String> notifications = (ArrayList<String>) account.get("notifications");
                ArrayList<String> actorsContribution = (ArrayList<String>) account.get("actorsContribution");
                ArrayList<String> favoriteActors = (ArrayList<String>) account.get("favoriteActors");
                ArrayList<String> favoriteProductions = (ArrayList<String>) account.get("favoriteProductions");
                ArrayList<String> productionsContribution = (ArrayList<String>) account.get("productionsContribution");

                // make a parser for user and add it after
                UserToParse user = new UserToParse(notifications, actorsContribution, favoriteActors,
                                        favoriteProductions, productionsContribution, info, userType,
                                        (String) account.get("username"), (String) account.get("experience"));

                this.users.add(new UserFactory().makeUser(user, userType));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void readActors() {
        try {
            ObjectMapper objectMapper = new ObjectMapper();
            List<Map<String, Object>> actors = objectMapper.readValue(new File(actorsPath), List.class);

            ArrayList<Performances> actorPerformances = new ArrayList<>();

            for (Map<String, Object> actor : actors) {
                Actor a = new Actor();

                a.setName((String) actor.get("name"));
                a.setBiography((String) actor.get("biography"));

                List<Map<String, String>> performances = (List<Map<String, String>>) actor.get("performances");
                for (Map<String, String> performance : performances)
                    actorPerformances.add(new Performances(performance.get("title"), performance.get("type")));

                a.setPerformances(actorPerformances);
                this.actors.add(a);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void readProductions() {
        try {
            ObjectMapper objectMapper = new ObjectMapper();
            List<Map<String, Object>> productions = objectMapper.readValue(new File(productionPath), List.class);

            for (Map<String, Object> production : productions) {
                Production p;

                // it has to be dynamic casting
                if("Movie".equals(production.get("type"))) {
                    p = new Movie();
                    p.setType("Movie");
                    ((Movie) p).setDuration((String) production.get("duration"));

                    // how can a movie not have a release year????
                    if(production.get("releaseYear") != null) ((Movie) p).setReleaseYear((int) production.get("releaseYear"));
                } else {
                    p = new Series();
                    p.setType("Series");
                    ((Series) p).setReleaseYear((int) production.get("releaseYear"));
                }

                // the parts that can be set easy
                p.setTitle((String) production.get("title"));
                p.setDirectors((List<String>) production.get("directors"));
                p.setActors((List<String>) production.get("actors"));
                p.setPlot((String) production.get("plot"));
                p.setAverageRating((double) production.get("averageRating"));

                List<String> genres = (List<String>) production.get("genres");
                List<Genre> gGenres = new ArrayList<>();

                for(String genre : genres) {
                    CustomFunctionsCLI.updateGenres(genre, gGenres);
                }

                p.setGenres(gGenres);

                // adding the ratings
                List<Map<String, Object>> ratingInfo = (List<Map<String, Object>>) production.get("ratings");

                if(ratingInfo != null && !ratingInfo.isEmpty()) {
                    for(Map<String, Object> rating : ratingInfo) {
                        Rating r = new Rating((String) rating.get("username"), (String) rating.get("comment"),
                                                (int) rating.get("rating"));

                        p.getRatings().add(r);
                    }
                }

                // add seasons if it is a series
                if ("Series".equals(production.get("type"))) {
                    ((Series) p).setNumSeasons((int) production.get("numSeasons"));

                    Map<String, List<Map<String, Object>>> seasons = (Map<String, List<Map<String, Object>>>) production.get("seasons");

                    for (Map.Entry<String, List<Map<String, Object>>> seasonEntry : seasons.entrySet()) {
                        List<Episode> episodes = new ArrayList<>();

                        for (Map<String, Object> e : seasonEntry.getValue()) {
                            Episode episode = new Episode((String) e.get("episodeName"), (String) e.get("duration"));

                            episodes.add(episode);
                        }

                        ((Series) p).getSeasons().put(seasonEntry.getKey(), episodes);
                    }
                }
                this.getProductions().add(p);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void readRequests() {
        try {
            ObjectMapper objectMapper = new ObjectMapper();
            List<Map<String, Object>> requests = objectMapper.readValue(new File(requestsPath), List.class);

            for (Map<String, Object> request : requests) {

                Request r = new Request();

                if(request.get("movieTitle") != null) r.setMovieTitle((String) request.get("movieTitle"));
                if(request.get("actorName") != null) r.setActorName((String) request.get("actorName"));

                switch((String) request.get("type")) {
                    case "DELETE_ACCOUNT" -> r.setType(RequestType.DELETE_ACCOUNT);
                    case "ACTOR_ISSUE" -> r.setType(RequestType.ACTOR_ISSUE);
                    case "MOVIE_ISSUE" -> r.setType(RequestType.MOVIE_ISSUE);
                    case "OTHERS" -> r.setType(RequestType.OTHERS);
                    default -> {System.out.println("There is a wrong request type."); r.setType(null);}
                }

                Date date;

                try {
                    date = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss").parse((String) request.get("createdDate"));
                } catch (ParseException e) {
                    e.printStackTrace();
                    continue;
                }

                r.setCreatedDate(date);
                r.setUsername((String) request.get("username"));
                r.setTo((String) request.get("to"));
                r.setDescription((String) request.get("description"));

                this.requests.add(r);

                for(Request req : this.requests) {
                    if(req.getType() == RequestType.OTHERS || req.getType() ==  RequestType.DELETE_ACCOUNT)
                        new RequestsHolder().getAdminRequests().add(req);
                    else {
                        String username = req.getTo();

                        for(Object user : this.users) {
                            if(((User) user).getUsername().equals(username)) {
                                (((User) user).getUserType() == AccountType.Admin ? (Admin) user : (Contributor) user).setRequests(new ArrayList<>());
                                (((User) user).getUserType() == AccountType.Admin ? (Admin) user : (Contributor) user).getRequests().add(req);
                                ((User) user).getNotifications().add("You got a new request from " + ((User) user).getUsername() + ".");
                            }
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void run() {
        this.actors = new ArrayList<>();
        this.users = new ArrayList<>();
        this.productions = new ArrayList<>();
        this.requests = new ArrayList<>();

        // read the files
        readActors();
        readAccounts();
        readProductions();
        readRequests();
    }

    public void saveData() {
        saveActors();
        saveAccounts();
        saveProductions();
        saveRequests();
    }

    public void saveActors() {
        try {
            ObjectMapper objectMapper = new ObjectMapper();

            objectMapper.configure(SerializationFeature.ORDER_MAP_ENTRIES_BY_KEYS, true);
            objectMapper.configure(SerializationFeature.INDENT_OUTPUT, true);

            objectMapper.writeValue(new File(actorsPathCopy), this.getActors());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void saveAccounts() {
        try {
            ObjectMapper objectMapper = new ObjectMapper();

            objectMapper.configure(SerializationFeature.ORDER_MAP_ENTRIES_BY_KEYS, true);
            objectMapper.configure(SerializationFeature.INDENT_OUTPUT, true);

            List<UserToSave> output = new ArrayList<>();

            for(Object u : this.users) {
                User uu = ((User) u);

                User.Information inf = uu.getInformation();
                InformationToSave information = new InformationToSave(inf.getCredentials(), inf.getName(), inf.getCountry(),
                                                                    inf.getAge(), inf.getGender(),inf.getBirthDate());

                output.add(new UserToSave(uu.getNotifications(), uu.getActorsContribution(),
                                uu.getFavoriteActors(), uu.getFavoriteProductions(), uu.getProductionsContribution(),
                                information, uu.getUserType(), uu.getUsername(), uu.getExperience()));
            }

            objectMapper.writeValue(new File(accountsPathCopy), output);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void saveProductions() {
        try {
            ObjectMapper objectMapper = new ObjectMapper();

            objectMapper.configure(SerializationFeature.ORDER_MAP_ENTRIES_BY_KEYS, true);
            objectMapper.configure(SerializationFeature.INDENT_OUTPUT, true);

            objectMapper.writeValue(new File(productionPathCopy), this.getProductions());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void saveRequests() {
        try {
            ObjectMapper objectMapper = new ObjectMapper();

            objectMapper.configure(SerializationFeature.ORDER_MAP_ENTRIES_BY_KEYS, true);
            objectMapper.configure(SerializationFeature.INDENT_OUTPUT, true);

            List<RequestToSave> requestToSavesList = new ArrayList<>();

            for(Object request : this.getRequests()) requestToSavesList.add(new RequestToSave((Request) request));

            objectMapper.writeValue(new File(requestsPathCopy), requestToSavesList);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        instance = getInstance();
        instance.run();

        CustomFunctionsCLI cf = new CustomFunctionsCLI();
        cf.cleanTerminal();

        MainGUI menuGUI = new MainGUI();

        while(instance.isRunning) {
            int choice = cf.getChoice("Welcome to my IMDB! Please choose how do you wish to continue:",
                    "1. Using the terminal\n2. Using the GUI\n3. Exit","Please type 1, 2 or 3",
                    "Please write a valid number", 1, 3);

            if(choice == 1) new MainCLI().main();
            else if(choice == 2) menuGUI.main();
                 else instance.closeIMDB();
        }

        instance.saveData(); // make a copy of the database and save it
        System.out.println("IMDB was closed. Come back later!");
    }

    public List<Request> getRequests() {
        return requests;
    }

    public List<Production> getProductions() {
        return productions;
    }

    public List<Object> getUsers() {
        return users;
    }

    public List<Actor> getActors() {
        return actors;
    }

    public ArrayList<String> getAdminContributions() {
        return adminContributions;
    }

    public void setRequests(List<Request> requests) {
        this.requests = requests;
    }

    public void setActors(List<Actor> actors) {
        this.actors = actors;
    }

    public void setUsers(List<Object> users) {
        this.users = users;
    }

    public void setProductions(List<Production> productions) {
        this.productions = productions;
    }

    public void setAdminContributions(ArrayList<String> adminContributions) {
        this.adminContributions = adminContributions;
    }

    public void closeIMDB() {this.isRunning = false;}
}
