public class ArgumentPassingTest {

	public static void main(String[] args) {
		int a = 1, b = 2;
		swap(a,b);
		System.out.println("a is " + a + ", b is " + b);  //a=1, b=2
		
		MyNumber obj1 = new MyNumber();
		MyNumber obj2 = new MyNumber();
		obj2.num = 10;
		swap(obj1, obj2);
		System.out.println("obj1 is " + obj1.num + ", obj2 is " + obj2.num);  //  obj1  10,   obj2  5

	}
	public static void swap(int m, int n)
	{
		int s = m;
		m = n;
		n = s;
	}
	public static void swap(MyNumber obj3, MyNumber obj4)
	{
		int s = obj3.num;
		obj3.num = obj4.num;
		obj4.num = s;
	}

}
