package org.example;


public class Episode {
    private String episodeName, duration;

    public Episode() {

    }

    public Episode(String episodeName, String duration) {
        this.episodeName = episodeName;
        this.duration = duration;
    }

    public String getEpisodeName() {
        return episodeName;
    }

    public String getDuration() {
        return duration;
    }

    public void setEpisodeName(String episodeName) {
        this.episodeName = episodeName;
    }

    public void setDuration(String duration) {
        this.duration = duration;
    }

    @Override
    public String toString() {
        return "Episode ["
                + "Name = '" + getEpisodeName() + "', "
                + "Duration = '" + getDuration()
                + "']";
    }
}