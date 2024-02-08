package org.example;

import java.util.ArrayList;

public class Regular<T> extends User<T> implements RequestsManager, LevelStrategy {

    public Regular() {super();}
    public Regular(ArrayList<String> notifications, ArrayList<String> actorsContribution,
                   ArrayList<String> favoriteActors, ArrayList<String> favoriteProductions,
                   ArrayList<String> productionsContribution, Information information,
                   AccountType userType, String username, String experience) {
        super(notifications, actorsContribution, favoriteActors, favoriteProductions, productionsContribution,
                information, userType, username, experience);
    }

    public boolean addRating(Production production, Rating rating) {
        if(!production.getRatings().contains(rating)) {
            this.setExperience(Integer.toString(Integer.parseInt(this.getExperience() + this.calculateExperience())));
            production.getRatings().add(rating);
            System.out.println("Rating added.");
            return true;
        }

        if(this.removeRating(production, rating)) {
            production.getRatings().add(rating);
            System.out.println("Rating updated.");
            return true;
        }

        System.out.println("Rating couldn't be added.");
        return false;
    }
    public boolean removeRating(Production production, Rating rating) {
        if(production.getRatings().contains(rating)) {
            production.getRatings().remove(rating);
            return true;
        }

        System.out.println("Rating couldn't be removed");
        return false;
    }

    @Override
    public int calculateExperience() {
        return 1;
    }

    @Override
    public void createRequest(Request r) {
        IMDB imdb = IMDB.getInstance();
        imdb.getRequests().add(r);
        String name;

        RequestsHolder requests = new RequestsHolder();

        switch(r.getType()) {
            case DELETE_ACCOUNT, OTHERS -> requests.getAdminRequests().add(r);
            case MOVIE_ISSUE -> {
                name = r.getMovieTitle();

                for(Object user : imdb.getUsers()) {
                    if(user instanceof Contributor)
                        if(((Contributor) user).getProductionsContribution().contains(name)) {
                            ((Contributor) user).getRequests().add(r);
                            break;
                        }

                    if(user instanceof Admin)
                        if(((Admin) user).getProductionsContribution().contains(name)) {
                            ((Admin) user).getRequests().add(r);
                            break;
                        }
                }
            }

            case ACTOR_ISSUE -> {
                name = r.getActorName();

                for(Object user : imdb.getUsers()) {
                    if(user instanceof Contributor)
                        if(((Contributor) user).getActorsContribution().contains(name)) {
                            ((Contributor) user).getRequests().add(r);
                            break;
                        }

                    if(user instanceof Admin)
                        if(((Admin) user).getActorsContribution().contains(name)) {
                            ((Admin) user).getRequests().add(r);
                            break;
                        }
                }
            }
        }
    }

    @Override
    public void removeRequest(Request r) {
        IMDB imdb = IMDB.getInstance();
        imdb.getRequests().remove(r);
        RequestsHolder requests = new RequestsHolder();

        if(r.getType() == RequestType.DELETE_ACCOUNT || r.getType() == RequestType.OTHERS) {
            requests.getAdminRequests().remove(r);
            return;
        }

        for(Object user : imdb.getUsers()) {
            if(user instanceof Contributor) ((Contributor) user).getRequests().remove(r);
            if(user instanceof Admin) ((Admin) user).getRequests().remove(r);
        }
    }

    @Override
    public void update(String notification) {
        this.getNotifications().add(notification);
    }

    @Override
    public String toString() {
        return "Regular ["
                + "\n   Username = '" + getUsername() + "' "
                + "\n   UserType = '" + getUserType() + "' "
                + "\n   Information = '" + getInformation() + "' "
                + "\n   Experience = '" + getExperience() + "' "
                + "\n   Notifications = '" + getNotifications() + "' "
                + "\n   Favorite Actors = '" +  getFavoriteActors() + "' "
                + "\n   Favorite Productions = '" + getFavoriteProductions() + "' "
                + "\n   Actors Contributions = '" + getActorsContribution() + "' "
                + "\n   Productions Contribution = '" + getProductionsContribution() + "' "
                + "']\n";
    }
}
