
public class ImmutableObjectTest {
	public static void main(String[] args) {
		String a = new String("abc");
		String b = a;
		System.out.println(b);
		a = "def";
		System.out.println(b);
		
		a=new String("abc");
		change(a);
		System.out.println(a);
	}
	public static void change(String b)
	{
		b = "def";
	}
}
