
public class IfElseTest {

	public static void main(String[] args) {
		int a = 5;
		if (a > 1) {
			System.out.println("aaaaaaa");
		}

		if (a > 10) {
			System.out.println("bbbbbbb");
		} else {
			System.out.println("ccccccc");
		}

		if (a > 10) {
			System.out.println("dddddd");
		} else if (a >= 5) {
			System.out.println("eeeeee");
		} else {
			System.out.println("ffffff");
		}
	}
}
