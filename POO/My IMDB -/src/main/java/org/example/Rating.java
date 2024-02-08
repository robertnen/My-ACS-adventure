package org.example;

public class Rating {
    private String username, comment;

    private int rating;

    public Rating() {

    }

    public Rating(String username, String comment, int rating) {
        this.username = username;
        this.comment = comment;
        this.rating = rating;
    }

    public int getRating() {
        return rating;
    }

    public String getComment() {
        return comment;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void setComment(String comment) {
        this.comment = comment;
    }

    public void setRating(int rating) {
        this.rating = rating;
    }

    @Override
    public String toString() {
        return "Rating [" + " Username = '" + getUsername() + "', Rating = '" + getRating() + "', Comment = '" + getComment() + "]";
    }
}
