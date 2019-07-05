
public class ArgumentPassing {
	public static void changeValue(int a)
	{
		a = 10;
	}
	public static void changeValue(String s1)
	{
		s1 = "def";
	}
	public static void changeValue(StringBuffer s1)
	{
		s1.append("def");
	}
	public static void main(String[] args) {
		int a = 5;        //基本类型
		String b = "abc"; //不可变对象
		StringBuffer c = new StringBuffer("abc"); //可变对象
		changeValue(a);
		changeValue(b);
		changeValue(c);
		System.out.println(a);
		System.out.println(b);
		System.out.println(c);
	}
}
