package org.example;

import java.util.ArrayList;
import java.util.List;
import java.util.SortedSet;
import java.util.TreeSet;

public abstract class Staff<T> extends User<T> implements StaffInterface {
    private List<Request> requests = new ArrayList<>();
    private SortedSet<T> contributions = new TreeSet<>();

    public Staff() { super();}

    public Staff(ArrayList<String> notifications, ArrayList<String> actorsContribution,
                 ArrayList<String> favoriteActors, ArrayList<String> favoriteProductions,
                 ArrayList<String> productionsContribution, Information information,
                 AccountType userType, String username, String experience,
                 SortedSet<T> contributions, List<Request> requests) {
            super(notifications, actorsContribution, favoriteActors, favoriteProductions, productionsContribution,
                    information, userType, username, experience);

            this.requests = requests;
            this.contributions = contributions;
    }

    public List<Request> getRequests() {
        return requests;
    }

    public SortedSet<T> getContributions() {
        return contributions;
    }

    public void setRequests(List<Request> requests) {
        this.requests = requests;
    }

    public void setContributions(SortedSet<T> contributions) {
        this.contributions = contributions;
    }
}
