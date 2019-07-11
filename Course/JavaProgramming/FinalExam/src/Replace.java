public class Replace {
	public static void main(String[] args) {
		String a = "HelloWorld, World!";
		String b = "World";
		String c = "Replacer";
		int pos = 0;
		int tmp = 0;
		a.replace(b, c);
		System.out.println(a);
	}
}
