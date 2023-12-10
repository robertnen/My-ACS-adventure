// /*
//  * Programare orientata pe obiecte
//  * Seria CC
//  * Laboratorul 6
//  * 
//  */

// import java.lang.reflect.Constructor;
// import java.lang.reflect.Modifier;

// /**
//  *
//  * @author Nan Mihai
//  */
// public class Test01 {
//     public static void main(String args[]) {
//         boolean ok = true;
//         //Verificarea relatiilor de mostenire
//         Shape obj1;
//         obj1 = new Square();
//         obj1 = new Rectangle();
//         obj1 = new Circle();
//         Rectangle obj3 = new Square();
//         //Verificarea constructorilor
//         Constructor[] allConstructors = Square.class.getDeclaredConstructors();
//         if(allConstructors.length != 3) {
//             System.out.println("Clasa Square NU are definiti toti constructorii!");
//             ok = false;
//         }
//         Circle circle = new Circle(2.0, "green", true);
//         Square square = new Square(5.0, "black", true);
//         if(!Modifier.isAbstract(Shape.class.getModifiers())) {
//             System.out.println("Clasa Shape NU este abstracta!");
//             ok = false;
//         }
//         if(!Shape.class.isAssignableFrom(Square.class) && !Rectangle.class.isAssignableFrom(Square.class)) {
//             System.out.println("Clasele NU respecta relatia de mostenire descrisa!");
//             ok = false;
//         }
//         if(!circle.isFilled() || !circle.getColor().equals("green")) {
//             System.out.println("Constructorul din clasa Circle NU este definit conform specificatiilor!");
//             ok = false;
//         } else if(!square.isFilled() || !square.getColor().equals("black") || square.getWidth() != square.getLength()) {
//             System.out.println("Constructorul din clasa Square NU este definit conform specificatiilor!");
//             ok = false;
//         } else if(ok){
//             System.out.println("Au trecut toate testele!");
//         }
//     }
// }