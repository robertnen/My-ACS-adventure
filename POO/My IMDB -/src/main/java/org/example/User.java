package org.example;

import java.io.File;
import java.io.FileNotFoundException;
import java.time.LocalDateTime;
import java.util.*;

public abstract class User<T> implements Observer {
    private Information information;
    private AccountType userType;
    private String username;
    private int level;
    private String experience;
    private ArrayList<String> notifications = new ArrayList<>();
    private ArrayList<String> favoriteProductions = new ArrayList<>(), productionsContribution = new ArrayList<>();
    private ArrayList<String> actorsContribution = new ArrayList<>(), favoriteActors = new ArrayList<>();
    private SortedSet<T> favorites = null;

    private LevelStrategy levelStrategy;

    public User() {

    }

    public User(ArrayList<String> notifications, ArrayList<String> actorsContribution,
                ArrayList<String> favoriteActors, ArrayList<String> favoriteProductions,
                ArrayList<String> productionsContribution, Information information,
                AccountType userType, String username, String experience) {

        this.notifications = notifications;
        this.actorsContribution = actorsContribution;
        this.favoriteActors = favoriteActors;
        this.favoriteProductions = favoriteProductions;
        this.productionsContribution = productionsContribution;
        this.information = information;
        this.userType = userType;
        this.username = username;
        this.experience = experience;

        updateFavorites();
    }

    public LevelStrategy getLevelStrategy() {
        return levelStrategy;
    }

    public void setLevelStrategy(LevelStrategy levelStrategy) {
        this.levelStrategy = levelStrategy;
    }

    public int useLevel(int experience) {
        return levelStrategy.calculateExperience() + experience;
    }

    @Override
    public void update(String notification) {
        notifications.add(notification);
    }

    public static class Information {
        private Credentials credentials;
        private String name, country, gender;
        private int age;
        private LocalDateTime birthDate;

        public Information(InformationBuilder builder) {
            this.credentials = builder.credentials;
            this.name = builder.name;
            this.country = builder.country;
            this.age = builder.age;
            this.gender = builder.gender;
            this.birthDate = builder.birthDate;
        }

        public Credentials getCredentials() {
            return credentials;
        }

        public String getName() {
            return name;
        }

        public String getCountry() {
            return country;
        }

        public int getAge() {
            return age;
        }

        public String getGender() {
            return gender;
        }

        public LocalDateTime getBirthDate() {
            return birthDate;
        }

        public static class InformationBuilder {
            private Credentials credentials;
            private String name, country, gender;
            private int age;
            private LocalDateTime birthDate;

            public InformationBuilder(String name, int age, LocalDateTime birthDate, Credentials credentials) {
                this.credentials = credentials;
                this.name = name;
                this.age = age;
                this.birthDate = birthDate;
            }

            public InformationBuilder gender(String gender) {
                this.gender = gender;
                return this;
            }

            public InformationBuilder country(String country) {
                this.country = country;
                return this;
            }

            public Information build() {
                return new Information(this);
            }
        }

        @Override
        public String toString() {
            return "    Information ["
                    + "     \nName = '" + getName() + "' "
                    + "     \nAge = '" + getAge() + "' "
                    + "     \nGender = '" + getGender() + "' "
                    + "     \nCountry = '" + getCountry() + "' "
                    + "     \nBirthdate = '" + getBirthDate() + "' "
                    + "     \nCredentials = '" + getCredentials()
                    + "'\n]";
        }
    }

    public void updateLevel() {
        this.level = Integer.parseInt(this.experience);
    }

    public void updateFavorites() {
        if(favorites == null) favorites = new TreeSet<>();

        for(String actor : favoriteActors)  favorites.add((T) actor);
        for(String production : favoriteProductions) favorites.add((T) production);
    }

    public int getLevel() {
        return level;
    }

    public void setLevel(int level) {
        this.level = level;
    }

    public String generateUniqueUsername(String name) {

        Random random = new Random();

        List<String> words = new ArrayList<>();

        try {
            Scanner sn = new Scanner(new File("src/main/java/org/example/animals.txt"));

            while(sn.hasNextLine()) {
                String word = sn.nextLine();
                words.add(word);
            }

            boolean isUnique = true;

            while(isUnique) {
                String username = name + "_" + words.get(random.nextInt(words.size())) + "_" + random.nextInt(10000);
                IMDB imdb = IMDB.getInstance();

                for(Object user : imdb.getUsers()) {
                    if(((User) user).getUsername().equals(username)) {
                        isUnique = false;
                        break;
                    }
                }

                if(isUnique) return username;
            }
            return "";

        } catch (FileNotFoundException e) {
            System.out.println("Couldn't generate unique username.");
            return null;
        }
    }

    public void logout() {
        System.out.println("You logged out. Have a wonderful day!");
    }

    public ArrayList<String> getNotifications() {
        return notifications;
    }

    public String getUsername() { return username; }

    public AccountType getUserType() {
        return userType;
    }

    public String getExperience() {
        return experience;
    }

    public SortedSet<T> getFavorites() {
        return favorites;
    }

    public ArrayList<String> getActorsContribution() {
        return actorsContribution;
    }

    public ArrayList<String> getFavoriteActors() {
        return favoriteActors;
    }

    public ArrayList<String> getFavoriteProductions() {
        return favoriteProductions;
    }

    public ArrayList<String> getProductionsContribution() {
        return productionsContribution;
    }

    public Information getInformation() {
        return information;
    }

    public void setNotifications(ArrayList<String> notifications) {
        this.notifications = notifications;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void setUserType(AccountType userType) {
        this.userType = userType;
    }

    public void setExperience(String experience) {
        this.experience = experience;
    }

    public void setInformation(Information information) {
        this.information = information;
    }

    public void setFavorites(SortedSet<T> favorites) {
        this.favorites = favorites;
    }

    public void setActorsContribution(ArrayList<String> actorsContribution) {
        this.actorsContribution = actorsContribution;
    }

    public void setFavoriteActors(ArrayList<String> favoriteActors) {
        this.favoriteActors = favoriteActors;
    }

    public void setFavoriteProductions(ArrayList<String> favoriteProductions) {
        this.favoriteProductions = favoriteProductions;
    }

    public void setProductionsContribution(ArrayList<String> productionsContribution) {
        this.productionsContribution = productionsContribution;
    }

    @Override
    public String toString() {
        return "User [ "
                + "Username = '" + getUsername() + "' "
                + "Usertype = '" + getUserType() + "' "
                + "Information = '" + getInformation() + "' "
                + "Experience = '" + getExperience() + "' "
                + "Notifications = '" + getNotifications() + "' "
                + "Favorite Actors = '" + getFavoriteActors() + "' "
                + "Favorite Productions = '" + getFavoriteProductions() + "' "
                + "Actors Contributions = '" + getActorsContribution() + "' "
                + "Productions Contributions = '" + getProductionsContribution() + "' "
                + "Favorites = '" + getFavorites()
                + "']";
    }
}

