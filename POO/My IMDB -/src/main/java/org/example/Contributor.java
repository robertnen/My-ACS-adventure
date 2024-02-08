package org.example;

import java.util.ArrayList;
import java.util.List;
import java.util.SortedSet;

public class Contributor<T> extends Staff<T> implements RequestsManager, LevelStrategy {

    public Contributor() {super();}
    public Contributor(ArrayList<String> notifications, ArrayList<String> actorsContribution,
                       ArrayList<String> favoriteActors, ArrayList<String> favoriteProductions,
                       ArrayList<String> productionsContribution, Information information,
                       AccountType userType, String username, String experience,
                       SortedSet<T> contributions, List<Request> requests) {
        super(notifications, actorsContribution, favoriteActors, favoriteProductions, productionsContribution,
                information, userType, username, experience, contributions, requests);
    }

    @Override
    public int calculateExperience() {
        return 2;
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
                        if(((Contributor) user).getActorsContribution().contains(name) && !user.equals(this)) {
                            ((Contributor) user).getRequests().add(r);
                            break;
                        }

                    if(user instanceof Admin)
                        if(((Admin) user).getActorsContribution().contains(name) && !user.equals(this)) {
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
    public void addProductionSystem(Production p) {
        IMDB imdb = IMDB.getInstance();
        if(this.getProductionsContribution().contains(p.getTitle())) {
            System.out.println("Production is already in your contribution list");
            return;
        }

        if(imdb.getProductions().contains(p)) {
            System.out.println("Production is already in database");
            return;
        }

        imdb.getProductions().add(p);
        this.getProductionsContribution().add(p.getTitle());
    }

    @Override
    public void addActorSystem(Actor a) {
        IMDB imdb = IMDB.getInstance();

        if(this.getActorsContribution().contains(a.getName())) {
            System.out.println("Actor is already in your contribution list");
            return;
        }

        if(imdb.getActors().contains(a)) {
            System.out.println("Actor is already in database");
            return;
        }

        imdb.getActors().add(a);
        this.getActorsContribution().add(a.getName());
    }

    @Override
    public void removeProductionSystem(Production p) {
        IMDB imdb = IMDB.getInstance();

        if(!this.getProductionsContribution().contains(p.getTitle())) {
            System.out.println("Production is not in your contribution list");
            return;
        }

        if(!imdb.getProductions().contains(p)) {
            System.out.println("Production is not in the database");
            return;
        }

        imdb.getProductions().remove(p);
        this.getProductionsContribution().remove(p.getTitle());
    }

    @Override
    public void removeActorSystem(Actor a) {
        IMDB imdb = IMDB.getInstance();

        if(!this.getActorsContribution().contains(a.getName())) {
            System.out.println("Actor is not in your contribution list");
            return;
        }

        if(!imdb.getActors().contains(a)) {
            System.out.println("Actor is not in the database");
            return;
        }

        imdb.getActors().add(a);
        this.getActorsContribution().add(a.getName());
    }

    @Override
    public void updateProduction(Production p) {
        IMDB imdb = IMDB.getInstance();

        if(!this.getProductionsContribution().contains(p.getTitle())) {
            System.out.println("Production cannot be updated if it is not in your contribution list");
            return;
        }

        for(Object production : imdb.getProductions()) {
            if(((Production) production).getTitle().equals(p.getTitle())) {
                imdb.getProductions().remove(production);
                imdb.getProductions().add(p);
                System.out.println("Production updated successfully");
                return;
            }
        }

        System.out.println("Production cannot be updated because it is not in the database");
    }

    @Override
    public void updateActor(Actor a) {
        IMDB imdb = IMDB.getInstance();

        if(!this.getActorsContribution().contains(a.getName())) {
            System.out.println("Actor cannot be updated if it is not in your contribution list");
            return;
        }

        for(Object actor : imdb.getActors()) {
            if(((Actor) actor).getName().equals(a.getName())) {
                imdb.getActors().remove(actor);
                imdb.getActors().add(a);
                System.out.println("Actor updated successfully");
                return;
            }
        }

        System.out.println("Actor cannot be updated because it is not in the database");
    }

    @Override
    public void update(String notification) {
        this.getNotifications().add(notification);
    }

    @Override
    public String toString() {
        return "Contributor ["
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
