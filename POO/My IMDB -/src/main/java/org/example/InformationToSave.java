package org.example;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class InformationToSave {
    private Credentials credentials;
    private String name;
    private String country;
    private int age;
    private String gender;
    private String birthDate;

    public InformationToSave(Credentials credentials, String name, String country, int age,
                             String gender, LocalDateTime birthDate) {
        this.credentials = credentials;
        this.name = name;
        this.country = country;
        this.age = age;
        this.gender = gender;

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        this.birthDate = birthDate.format(formatter);
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

    public String getBirthDate() {
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

    public void setBirthDate(String birthDate) {
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