package org.example;

import org.jetbrains.annotations.NotNull;

import java.util.*;


public class Series extends Production {

    private int releaseYear, numSeasons;
    private Map<String, List<Episode>> seasons = new TreeMap<>(Comparator.naturalOrder());

    public Series() {

    }

    public Series(String title, String type, String plot, double averageRating,
                  List<String> actors, List<String> directors, List<Genre> genres, List<Rating> ratings,
                  int releaseYear, int numSeasons, Map<String, List<Episode>> seasons) {

        super(title, type, plot, averageRating, actors, directors, genres, ratings);

        this.releaseYear = releaseYear;
        this.numSeasons = numSeasons;
        this.seasons = seasons;
    }

    public int getReleaseYear() {
        return releaseYear;
    }

    public int getNumSeasons() {
        return numSeasons;
    }

    public Map<String, List<Episode>> getSeasons() {
        return seasons;
    }

    public void setReleaseYear(int releaseYear) {
        this.releaseYear = releaseYear;
    }

    public void setNumSeasons(int numSeasons) {
        this.numSeasons = numSeasons;
    }

    public void setSeasons(Map<String, List<Episode>> seasons) {
        this.seasons = seasons;
    }

    @Override
    public void displayInfo() {
        System.out.println("\n===============Series===============");
        System.out.println("Series: " + getTitle() + "\nNumber of seasons: " + getNumSeasons()
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

        System.out.println("Seasons:");
        for(Map.Entry<String, List<Episode>> season : getSeasons().entrySet()) {
            System.out.println("    " + season.getKey() + ":");
            int episodeNum = 1;
            for(Episode episode : season.getValue()) {
                System.out.println("        Episode " + episodeNum + ": "  + episode.getEpisodeName());
                System.out.println("        Duration: " + episode.getDuration());
                System.out.println("        ------------------------");
                episodeNum++;
            }
        }

        System.out.println("Ratings:");
        for(Rating rating : getRatings()) {
            System.out.println("    From " + rating.getUsername() + ": " + rating.getComment());
            System.out.println("    The user's rating: " + rating.getRating() + "\n");
        }
    }

    @Override
    public String toString() {
        return "Series: ["
                    + "\nTitle = '" + this.getTitle() + "' "
                    + "\nType = '" + this.getType() + "' "
                    + "\nPlot = '" + this.getPlot() + "' "
                    + "\nAverage Rating = '" + this.getAverageRating() + "' "
                    + "\nActors = '" + this.getActors() + "' "
                    + "\nDirectors = '" + this.getDirectors() + "' "
                    + "\nGenres = '" + this.getGenres() + "' "
                    + "\nRatings = '" + this.getRatings() + "' "
                    + "\nRelease Year = '" + this.getReleaseYear() + "' "
                    + "\nNumber of Seasons = '" + this.getNumSeasons() + "' "
                    + "\nSeasons = '" + this.getSeasons() + "]";
    }

    @Override
    public int compareTo(@NotNull Object obj) {
        if (obj instanceof Series series)
            return this.getTitle().compareTo(series.getTitle());

        return -1;
    }
}
