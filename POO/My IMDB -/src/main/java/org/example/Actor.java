package org.example;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.List;

public class Actor implements Comparable<Object> {
    private String name;
    private ArrayList<Performances> performances;

    private String biography;

    public Actor() {

    }

    public Actor(String name, String biography, ArrayList<Performances> performances) {
        this.name = name;
        this.biography = biography;
        this.performances = performances;
    }

    public void displayInfo() {
        System.out.println("\n===============Actor===============");
        System.out.println("Name: " + getName() + "\nNumber of performances: " + getPerformances().size());
        System.out.println("Biography: " + getBiography());

        System.out.println("Performances: ");
        for(Performances performance : performances)
            System.out.println("      " + performance.getType() + ": " + performance.getTitle());
    }

    public String getName() {
        return name;
    }

    public String getBiography() {
        return biography;
    }

    public List<Performances> getPerformances() {
        return performances;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setPerformances(ArrayList<Performances> performances) {
        this.performances = performances;
    }

    public void setBiography(String biography) {
        this.biography = biography;
    }

    @Override
    public String toString() {
        return "Actor ["
                + "Name = '" + getName() + "' "
                + "Performances = '" + getPerformances() + "' "
                + "Biography = '" + getBiography()
                + "']";
    }

    @Override
    public int compareTo(@NotNull Object obj) {
        if(obj instanceof Actor actor) {
            return this.getName().compareTo(actor.getName());
        }

        return -1;
    }
}
