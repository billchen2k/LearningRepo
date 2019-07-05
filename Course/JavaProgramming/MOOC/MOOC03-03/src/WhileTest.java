
public class WhileTest {

	public static void main(String[] args) {

		System.out.println("=============While Test==========");
		int x = 10;
		while (x < 20) {
			System.out.print("value of x : " + x);
			x++;
			System.out.print("\n");
		}

		System.out.println("=============Do  While Test==========");
		x = 10;
		do {
			x++;
			if (x % 2 == 0) {
				continue;
			}
			System.out.println("value of x : " + x);
		} while (x < 20);
	}

}
