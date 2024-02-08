package org.example;

import java.util.ArrayList;
import java.util.List;

public abstract class Production implements Comparable<Object> {

    private String title, type, plot;
    private double averageRating;
    private List<String> actors = new ArrayList<>(), directors = new ArrayList<>();
    private List<Genre> genres = new ArrayList<>();
    private List<Rating> ratings = new ArrayList<>();

    public abstract void displayInfo();

    public Production() {

    }

    public Production(String title, String type, String plot, double averageRating,
                      List<String> actors, List<String> directors, List<Genre> genres, List<Rating> ratings) {
        this.title = title;
        this.type = type;
        this.plot = plot;
        this.averageRating = averageRating;
        this.actors = actors;
        this.directors = directors;
        this.genres = genres;
        this.ratings = ratings;
    }

    public String getTitle() {
        return title;
    }

    public String getType() {
        return type;
    }

    public String getPlot() {
        return plot;
    }

    public double getAverageRating() {
        return averageRating;
    }

    public List<String> getDirectors() {
        return directors;
    }

    public List<String> getActors() {
        return actors;
    }

    public List<Rating> getRatings() {
        return ratings;
    }

    public List<Genre> getGenres() {
        return genres;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setPlot(String plot) {
        this.plot = plot;
    }

    public void setAverageRating(double averageRating) {
        this.averageRating = averageRating;
    }

    public void setActors(List<String> actors) {
        this.actors = actors;
    }

    public void setDirectors(List<String> directors) {
        this.directors = directors;
    }

    public void setRatings(List<Rating> ratings) {
        this.ratings = ratings;
    }

    public void setGenres(List<Genre> genres) {
        this.genres = genres;
    }
}
