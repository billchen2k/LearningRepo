
public class StringPassingTest {

	public static void main(String[] args) {
		String a = "abc";
		changeValue(a);
		System.out.println(a);
		
		a = "abc";
		String b = a;
		a = "def";
		System.out.println(b);
	}
	public static void changeValue(String b)
	{
		b = "def";
	}
}
