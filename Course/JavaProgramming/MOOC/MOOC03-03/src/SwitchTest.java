public class SwitchTest {
	public static void main(String[] args) {
		int a1 = 1;
		int a2 = 2;
		switch (a1 + a2) {
			case 1:
				System.out.println("aaaaaaa");
				break;
			case 2:
				System.out.println("bbbbbbb");
				break;
			case 3:
				System.out.println("ccccccc");
				//break;
			default:
				System.out.println("ddddddd");
		}

		String b = "abc";
		switch (b) {
			case "abc":
				System.out.println("eeeeeee");
				break;
			case "def":
				System.out.println("fffffff");
				break;
			case "hgi":
				System.out.println("ggggggg");
				break;
			default:
				System.out.println("hhhhhhh");
		}

	}

}
