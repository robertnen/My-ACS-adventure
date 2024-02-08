package org.example;

public class Performances {
    private String title, type;

    public Performances() {

    }

    public Performances(String name, String type) {
        this.title = name;
        this.type = type;
    }

    public String getTitle() {
        return title;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    @Override
    public String toString() {
        return "Pair ["
                + "Title = '" + getTitle() + "' "
                + "Type  = '" + getType()
                + "']";
    }
}
