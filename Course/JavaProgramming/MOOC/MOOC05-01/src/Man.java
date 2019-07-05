public class Man extends Human
{
	//overwrite重写父类方法
	public void eat(){
		System.out.println("I can eat more");
	}
	//扩展，比父类拥有更多的方法
	public void plough(){
		System.out.println("I can plough");
	} //耕田

	public static void main(String[] a)	{
		Man obj1 = new Man();
		obj1.eat();
	}
}
