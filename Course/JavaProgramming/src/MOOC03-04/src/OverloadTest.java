
public class OverloadTest {

	public static void main(String[] args) {
		int a=1,b=2;
		System.out.println(add(1,2));
		System.out.println(add(1.5,2.5));
	}

	public static int add(int m, int n) 
	{
		return m + n;
	}
	public static double add(double m, double n) //和第9行行数重载overload
	{
		return m + n;
	}
	/*
	 * 以下函数非法，和第9行的函数名相同，形参相同
	public static double add(int m, int n) 
	{
		return (double) (m + n);
	}
	*/
}
