package org.example;

import org.jetbrains.annotations.NotNull;

import java.util.List;

public class Movie extends Production implements Comparable<Object> {

    private int releaseYear;
    private String duration;

    public Movie() {super();}
    public Movie(String title, String type, String plot, double averageRating,
                 List<String> actors, List<String> directors, List<Genre> genres, List<Rating> ratings,
                 int releaseYear, String duration) {

        super(title, type, plot, averageRating, actors, directors, genres, ratings);

        this.releaseYear = releaseYear;
        this.duration = duration;
    }

    public int getReleaseYear() {
        return releaseYear;
    }

    public String getDuration() {
        return duration;
    }

    public void setReleaseYear(int releaseYear) {
        this.releaseYear = releaseYear;
    }

    public void setDuration(String duration) {
        this.duration = duration;
    }

    @Override
    public void displayInfo() {
        System.out.println("\n===============Movie===============");
        System.out.println("Movie: " + getTitle() + "\nDuration: " + getDuration()
                                + "\nRelease year: " + getReleaseYear());

        System.out.println("Average rating: "  + getAverageRating());
        System.out.println("Plot: " + getPlot());
        System.out.println("Genres: " + getGenres());

        System.out.print("Actors:");
        for(String actor : getActors()) System.out.print(" " + actor);
        System.out.println();

        System.out.print("Directors:");
        for(String director : getDirectors()) System.out.print(" " + director);
        System.out.println();

        System.out.println("Ratings:");
        for(Rating rating : getRatings()) {
            System.out.println("    From " + rating.getUsername() + ": " + rating.getComment());
            System.out.println("    The user's rating: " + rating.getRating() + "\n");
        }
    }

    @Override
    public String toString() {
        return "Movie ["
                + "Name = " + getTitle() + "' "
                + "Release Year = '" + releaseYear + "' "
                + "Duration = '" + duration
                + "']";
    }

    @Override
    public int compareTo(@NotNull Object obj) {
        if (obj instanceof Movie movie)
            return this.getTitle().compareTo(movie.getTitle());

        return -1;
    }
}
