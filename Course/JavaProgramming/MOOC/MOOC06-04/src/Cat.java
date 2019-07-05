
public class Cat implements SpecialAnimal {
	public void move() {
		System.out.println("I can move");
	}

	public static void main(String[] args) {
		Cat cat = new Cat();
		cat.color = "white";  //error, the variables in interface are constants.
	}
}
