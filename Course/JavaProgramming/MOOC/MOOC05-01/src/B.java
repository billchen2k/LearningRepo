
public class B extends A{
	public B()
	{
		//super(); 编译器自动增加super()
		System.out.println("333333");
	}
	public B(int a)
	{
		super(a);  //编译器不会自动增加super();
		System.out.println("444444");
	}
	public static void main(String[] a)
	{
		B obj1 = new B();
		System.out.println("==============");
		B obj2 = new B(10);		
	}

}
