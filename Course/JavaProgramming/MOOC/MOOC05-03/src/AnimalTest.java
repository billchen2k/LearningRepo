
public class AnimalTest {
	
	public static void haveLunch(Animal a)	{
		a.eat();
	}
	
	public static void main(String[] args) {
		Animal[] as = new Animal[4];
		as[0] = new Cat();
		as[1] = new Dog();
		as[2] = new Cat();
		as[3] = new Dog();
		
		for(int i=0;i<as.length;i++) {
			as[i].move();  //调用每个元素的自身的move方法
		}
		for(int i=0;i<as.length;i++) {
			haveLunch(as[i]);
		}
		
		haveLunch(new Cat());  //Animal  a = new Cat();  haveLunch(a);
		haveLunch(new Dog());
		haveLunch(
				new Animal()
				{
					public void eat() {
						System.out.println("I can eat from an anonymous class");						
					}
					public void move() {
						System.out.println("I can move from an anonymous class");
					}
					
				});
	}
}
