package org.example;

import java.util.Date;

public class Request {

    private RequestType type;
    private String username, description, actorName, movieTitle, to;
    private Date createdDate;

    public Request() {}
    public Request(String movieTitle, String actorName, String description, String username, String to,
                   Date createdDate, RequestType type) {
        this.movieTitle = movieTitle;
        this.actorName = actorName;
        this.description = description;
        this.username = username;
        this.to = to;
        this.createdDate = createdDate;
        this.type = type;
    }

    public void displayInfo() {
        System.out.println("\n===============Request===============");
        System.out.println("        Type: " + getType());
        System.out.println("        Created Date: " + getCreatedDate());
        System.out.println("        Username: " + getUsername());
        System.out.println("        Admin: " + getTo());
        System.out.println("        Description: " + getDescription());
    }

    public String getMovieTitle() {
        return movieTitle;
    }

    public String getActorName() {
        return actorName;
    }

    public String getDescription() {
        return description;
    }

    public String getUsername() {
        return username;
    }

    public String getTo() {
        return to;
    }

    public Date getCreatedDate() {
        return createdDate;
    }

    public RequestType getType() {
        return type;
    }

    public void setMovieTitle(String movieTitle) {
        this.movieTitle = movieTitle;
    }

    public void setActorName(String actorName) {
        this.actorName = actorName;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void setTo(String to) {
        this.to = to;
    }

    public void setCreatedDate(Date createdDate) {
        this.createdDate = createdDate;
    }

    public void setType(RequestType type) {
        this.type = type;
    }

    @Override
    public String toString() {
        return "Request ["
                + "\n   Username = '" + getUsername() + "' "
                + "\n   Date created = '" + getCreatedDate() + "' "
                + "\n   Movie = '" + getMovieTitle() + "' "
                + "\n   Actor = '" + getActorName() + "' "
                + "\n   Description = '" + getDescription() + "' "
                + "\n   Type = '" + getType()
                + "'\n]";
    }
}
