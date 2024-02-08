package org.example;

import java.util.ArrayList;
import java.util.List;
import java.util.SortedSet;

public class Admin<T> extends Staff<T> implements StaffInterface {

    public Admin() {super();}

    public Admin(ArrayList<String> notifications, ArrayList<String> actorsContribution,
                 ArrayList<String> favoriteActors, ArrayList<String> favoriteProductions,
                 ArrayList<String> productionsContribution, Information information,
                 AccountType userType, String username, String experience,
                 SortedSet<T> contributions, List<Request> requests) {
        super(notifications, actorsContribution, favoriteActors, favoriteProductions, productionsContribution,
                information, userType, username, experience, contributions, requests);
    }

    public boolean addUser(User user) {

        IMDB imdb = IMDB.getInstance();

        if(imdb.getUsers().contains(user)) {
            System.out.println("User already exists");
            return true;
        }

        boolean usernameExists = false, emailExists = false;

        for(Object account : imdb.getUsers())
            if(((User) account).getUsername().equals(user.getUsername()) ||
                    ((User) account).getInformation().getCredentials().getEmail().equals(
                            user.getInformation().getCredentials().getEmail()))
                return false;

        imdb.getUsers().add(user);

        return true;
    }

    public boolean removeUser(User user) {

        IMDB imdb = IMDB.getInstance();

        if(!imdb.getUsers().contains(user)) {
            System.out.println("User doesn't exist");
            return false;
        }

        if (user instanceof Regular) {
            for(Object production : imdb.getProductions())
                for(Object rating : ((Production) production).getRatings())
                    if(((Rating) rating).getUsername().equals(((Regular) user).getUsername()))
                        ((Production) production).getRatings().remove(rating);
        }

        if (user instanceof Contributor) {
            for(Object request : imdb.getRequests())
                if(((Request) request).getUsername().equals(((Contributor) user).getUsername()))
                    imdb.getRequests().remove(request);

            for(Object production : ((Contributor) user).getProductionsContribution())
                imdb.getAdminContributions().add((String) production);

            for(Object actor : ((Contributor) user).getActorsContribution())
                imdb.getAdminContributions().add((String) actor);
        }


        imdb.getUsers().remove(user);
        return true;
    }

    @Override
    public void addProductionSystem(Production p) {
        IMDB imdb = IMDB.getInstance();

        if(imdb.getProductions().contains(p)) {
            System.out.println("Production is already in database");
            return;
        }

        if(this.getProductionsContribution().contains(p.getTitle())) {
            System.out.println("Production is already in your productions contribution list");
            return;
        }

        imdb.getProductions().add(p);
        imdb.getAdminContributions().add(p.getTitle());
    }

    @Override
    public void addActorSystem(Actor a) {
        IMDB imdb = IMDB.getInstance();

        if(imdb.getActors().contains(a)) {
            System.out.println("Actor is already in database");
            return;
        }

        if(this.getActorsContribution().contains(a.getName())) {
            System.out.println("Actor is already your contribution list");
            return;
        }

        imdb.getActors().add(a);
        imdb.getAdminContributions().add(a.getName());

    }

    @Override
    public void removeProductionSystem(Production p) {
        IMDB imdb = IMDB.getInstance();

        if(!this.getProductionsContribution().contains(p.getTitle())) {
            System.out.println("Production is not in your contribution list");
            return;
        }

        if(imdb.getProductions().contains(p)) {
            imdb.getProductions().remove(p);
            this.getProductionsContribution().remove(p.getTitle());
            return;
        }

        System.out.println("Production is not in the database");
    }

    @Override
    public void removeActorSystem(Actor a) {
        IMDB imdb = IMDB.getInstance();

        if(!this.getActorsContribution().contains(a.getName())) {
            System.out.println("Actor is not in your contribution list");
            return;
        }

        if(imdb.getActors().contains(a)) {
            imdb.getActors().remove(a);
            this.getActorsContribution().remove(a.getName());
            return;
        }

        System.out.println("Actor is not in the database");
    }

    @Override
    public void updateProduction(Production p) {
        IMDB imdb = IMDB.getInstance();

        if(this.getProductionsContribution().contains(p.getTitle())) {
            for(Object production : imdb.getProductions())
                if(((Production) production).getTitle().equals(p.getTitle())) {
                    imdb.getProductions().remove(production);
                    imdb.getProductions().add(p);
                    System.out.println("Production updated successfully.");
                    return;
                }
            System.out.println("Production cannot be updated because it does not exist in the database.");
        }
        System.out.println("Production cannot be updated because it not in your contribution list");
    }

    @Override
    public void updateActor(Actor a) {
        IMDB imdb = IMDB.getInstance();
        boolean isUpdated = false;

        if(this.getActorsContribution().contains(a.getName())) {
            for(Object actor : imdb.getActors())
                if(((Actor) actor).getName().equals(a.getName())) {
                    imdb.getActors().remove(actor);
                    imdb.getActors().add(a);
                    System.out.println("Actor updated successfully");
                    isUpdated = true;
                }
            System.out.println("Actor cannot be updated because it does not exist in the database.");
        }

        System.out.println("Actor cannot be updated because it not in your contribution list");
    }

    @Override
    public void update(String notification) {
        this.getNotifications().add(notification);
    }

    @Override
    public String toString() {
        return "Admin ["
                + "\n   Username = '" + getUsername() + "' "
                + "\n   UserType = '" + getUserType() + "' "
                + "\n   Information = '" + getInformation() + "' "
                + "\n   Experience = '" + getExperience() + "' "
                + "\n   Notifications = '" + getNotifications() + "' "
                + "\n   Favorite Actors = '" +  getFavoriteActors() + "' "
                + "\n   Favorite Productions = '" + getFavoriteProductions() + "' "
                + "\n   Actors Contributions = '" + getActorsContribution() + "' "
                + "\n   Productions Contribution = '" + getProductionsContribution() + "' "
                + "\n   Contributions = '" + getContributions() + "' "
                + "\n   Requests = '" + getRequests()
                + "'\n]";
    }
}
