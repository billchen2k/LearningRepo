
public class StringConstantTest {
	public static void main(String[] args) {
		String s1 = "abc";
		String s2 = "abc";
		String s3 = "ab" + "c"; //都是常量，编译器将优化，下同
		String s4 = "a" + "b" + "c";
		System.out.println(s1 == s2); //true
		System.out.println(s1 == s3); //true
		System.out.println(s1 == s4); //true
	}
}
