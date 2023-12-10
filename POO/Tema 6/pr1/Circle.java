package pr1;

public class Circle extends Shape {
    double radius;

    Circle() {}

    Circle(double radius) {
        this.radius = radius;
    }

    Circle(double radius, String color, boolean filled) {
        super(color, filled);
        this.radius = radius;
    }

    public double getRadius() {return radius;}
    public void setRadius(double radius) {this.radius = radius;}

    @Override
    double getArea() {
        return Math.PI * radius * radius;
    }
    @Override
    double getPerimeter() {
        return 2 * Math.PI * radius;
    }

    @Override
    public String toString() {
        return "Color = " + color + "\nFilled = " + filled + "\nArea = " + getArea() + "\nPerimeter = " + getPerimeter();
    }
}
