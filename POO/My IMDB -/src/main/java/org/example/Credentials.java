package org.example;

public class Credentials {
    private String email, password;

    public Credentials() {

    }

    public Credentials(String email, String password) {
        this.email = email;
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setEmail(String username) {
        this.email = username;
    }

    @Override
    public String toString() {
        return "Credentials ["
                + "Email = '" + getEmail() + "' "
                + "Password = '" + getPassword()
                + "']";
    }
}
