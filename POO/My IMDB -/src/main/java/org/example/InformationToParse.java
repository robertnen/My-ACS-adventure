package org.example;

import java.time.LocalDateTime;

public class InformationToParse {
    private Credentials credentials;
    private String name, country;
    private int age;
    private String gender;
    private LocalDateTime birthDate;

    public InformationToParse(Credentials credentials, String name, String country, int age,
                              String gender, LocalDateTime birthDate) {
        this.credentials = credentials;
        this.name = name;
        this.country = country;
        this.age = age;
        this.gender = gender;
        this.birthDate = birthDate;
    }

    public String getName() {
        return name;
    }

    public String getGender() {
        return gender;
    }

    public int getAge() {
        return age;
    }

    public Credentials getCredentials() {
        return credentials;
    }

    public LocalDateTime getBirthDate() {
        return birthDate;
    }

    public String getCountry() {
        return country;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void setBirthDate(LocalDateTime birthDate) {
        this.birthDate = birthDate;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }

    public void setCredentials(Credentials credentials) {
        this.credentials = credentials;
    }

    @Override
    public String toString() {
        return "InformationToParse ["
                + "Name = '" + getName() + "' "
                + "Age = '" + getAge() + "' "
                + "Gender = '" + getGender() + "' "
                + "Country = '" + getCountry() + "' "
                + "Birthdate = '" + getBirthDate() + "' "
                + "Credentials = '" + getCredentials()
                + "']";
    }

}