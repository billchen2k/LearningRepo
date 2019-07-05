
public class StringNewTest {
	public static void main(String[] args) {
		String s0 = "abcdef";
		String s1 = "abc";
		String s2 = "abc";
		String s3 = new String("abc");
		String s4 = new String("abc");
		System.out.println(s1 == s2); //true 常量池
		System.out.println(s1 == s3); //false 一个栈内存，一个堆内存
		System.out.println(s3 == s4); //false 两个都是堆内存
		System.out.println("=========================");
		
		String s5 = s1 + "def";    //涉及到变量，故编译器不优化
		String s6 = "abc" + "def"; //都是常量 编译器会自动优化成abcdef
		String s7 = "abc" + new String ("def");//涉及到new对象，编译器不优化
		System.out.println(s5 == s6); //false
		System.out.println(s5 == s7); //false
		System.out.println(s6 == s7); //false
		System.out.println(s0 == s6); //true 
		System.out.println("=========================");
		
		String s8 = s3 + "def";//涉及到new对象，编译器不优化
		String s9 = s4 + "def";//涉及到new对象，编译器不优化
		String s10 = s3 + new String("def");//涉及到new对象，编译器不优化
		System.out.println(s8 == s9); //false
		System.out.println(s8 == s10); //false
		System.out.println(s9 == s10); //false
	}
}
