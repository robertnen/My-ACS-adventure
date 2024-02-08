package Exceptions;

public class InformationIncompleteException extends Exception {
    public InformationIncompleteException() {
        super("Information object can not be created without adding credentials");
    }
}
