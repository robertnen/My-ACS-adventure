package org.example;

import java.text.SimpleDateFormat;

public class RequestToSave {

    private RequestType type;
    private String username, createdDate, description, actorName, movieTitle, to;

    public RequestToSave() {}
    public RequestToSave(Request request) {
        this.movieTitle = request.getMovieTitle();
        this.actorName = request.getActorName();
        this.description = request.getDescription();
        this.username = request.getUsername();
        this.to = request.getTo();

        this.createdDate = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss").format(request.getCreatedDate());
        this.type = request.getType();
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

    public String getCreatedDate() {
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

    public void setCreatedDate(String createdDate) {
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
