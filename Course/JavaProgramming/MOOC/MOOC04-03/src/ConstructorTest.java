class MyPairNumber0
{
	public int m;
	public int n;
	public MyPairNumber0()
	{
		m = 0;
		n = 0;
	}
	public MyPairNumber0(int a)
	{
		m = a;
		n = 0;
	}
	public MyPairNumber0(int a, int b)
	{
		m = a;
		n = b;
	}	
}
public class ConstructorTest {

	public static void main(String[] args) {
		MyPairNumber0 obj1 = new MyPairNumber0();
		MyPairNumber0 obj2 = new MyPairNumber0(5);
		MyPairNumber0 obj3 = new MyPairNumber0(10,20);
		System.out.println("obj1 has " + obj1.m + "," + obj1.n);
		System.out.println("obj2 has " + obj2.m + "," + obj2.n);
		System.out.println("obj3 has " + obj3.m + "," + obj3.n);

		// A a = new A();  //error, A类中没有无参数的构造函数
	}
}