package org.example;

import java.util.ArrayList;
import java.util.SortedSet;
import java.util.TreeSet;

public class UserFactory {
    public Object makeUser(UserToParse user, AccountType type) {

        // I don't want to initialize later if lists are empty
        ArrayList<String> notifications, actorsContrib, prodContrib, favActors, favProductions;

        notifications = (user.getNotifications() == null ? new ArrayList<>() : user.getNotifications());
        actorsContrib = (user.getActorsContribution() == null ? new ArrayList<>() : user.getActorsContribution());
        prodContrib = (user.getProductionsContribution() == null ? new ArrayList<>() : user.getProductionsContribution());
        favActors = (user.getFavoriteActors() == null ? new ArrayList<>() : user.getFavoriteActors());
        favProductions = (user.getFavoriteProductions() == null ? new ArrayList<>() : user.getFavoriteProductions());

        User.Information info = new User.Information.InformationBuilder(user.getInformation().getName(),
                                                                        user.getInformation().getAge(),
                                                                        user.getInformation().getBirthDate(),
                                                                        user.getInformation().getCredentials())
                                                                        .country(user.getInformation().getCountry())
                                                                        .gender(user.getInformation().getGender())
                                                                        .build();

        SortedSet<Object> favorites = new TreeSet<>(), contributions = new TreeSet<>();

        // populate the lists
        for (String actor : favActors) favorites.add(actor);
        for (String production : favProductions) favorites.add(production);

        for (String actorContrib : actorsContrib) contributions.add(actorContrib);
        for (String proContrib : prodContrib) contributions.add(proContrib);

        switch (type) {
            case Admin -> {
                Admin<Object> admin = new Admin<>(notifications, actorsContrib, favActors, favProductions,
                        prodContrib, info, AccountType.Admin, user.getUsername(), user.getExperience(),
                        contributions, null);

                admin.setFavorites(favorites);
                return admin;
            }

            case Contributor -> {
                Contributor<Object> contributor = new Contributor<>(notifications, actorsContrib,
                        favActors, favProductions, prodContrib, info, AccountType.Contributor,
                        user.getUsername(), user.getExperience(), contributions, null);

                contributor.setFavorites(favorites);
                return contributor;
            }

            case Regular -> {
                return new Regular<>(notifications, actorsContrib,
                        favActors, favProductions, prodContrib, info, AccountType.Regular,
                        user.getUsername(), user.getExperience());
            }

            default -> {
                System.out.println("Something went wrong in UserFactory");
                return null;
            }
        }
    }
}
