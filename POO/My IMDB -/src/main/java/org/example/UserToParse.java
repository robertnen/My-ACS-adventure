package org.example;

import java.util.ArrayList;

public class UserToParse {

    private InformationToParse information;
    private AccountType userType;
    private String username;
    private String experience;
    private ArrayList<String> notifications;
    private ArrayList<String> favoriteProductions, productionsContribution;
    private ArrayList<String> actorsContribution, favoriteActors;

    public UserToParse() {

    }

    public UserToParse(ArrayList<String> notifications, ArrayList<String> actorsContribution,
                       ArrayList<String> favoriteActors, ArrayList<String> favoriteProductions,
                       ArrayList<String> productionsContribution, InformationToParse information,
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

    public InformationToParse getInformation() {
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

    public void setInformation(InformationToParse information) {
        this.information = information;
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
        return "UserToParse [ "
                + "Username = '" + getUsername() + "' "
                + "Usertype = '" + getUserType() + "' "
                + "Information = '" + getInformation() + "' "
                + "Experience = '" + getExperience() + "' "
                + "Notifications = '" + getNotifications() + "' "
                + "Favorite Actors = '" + getFavoriteActors() + "' "
                + "Favorite Productions = '" + getFavoriteProductions() + "' "
                + "Actors Contributions = '" + getActorsContribution() + "' "
                + "Productions Contributions = '" + getProductionsContribution()
                + "']";
    }
}
