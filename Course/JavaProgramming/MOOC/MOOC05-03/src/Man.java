public class Man extends Human {
	public void eat() {
		System.out.println("I can eat more");
	}
	
	public void plough() { }

	public static void main(String[] a)	{
		Man obj1 = new Man();
		obj1.eat();   // call Man.eat()
		Human obj2 =  (Human) obj1;
		obj2.eat();   // call Man.eat()
		Man obj3 = (Man) obj2;
		obj3.eat();	  // call Man.eat()
	}
}
