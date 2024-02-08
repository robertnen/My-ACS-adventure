package Exceptions;

public class InvalidCommandException extends Exception {
    public InvalidCommandException() {
        super("Invalid command made by user");
    }
}
