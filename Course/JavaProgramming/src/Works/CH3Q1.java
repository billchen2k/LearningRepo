package Works;

public class CH3Q1 {
	public static void main(String[] args) {
		int count = 1;
		for (int i = 0; i < args[0].charAt(0) - '0'; i++) {
			for (int j = 0; j < (int) args[0].charAt(0) - '0'; j++) {
				System.out.print(count + " ");
				count++;
			}
			System.out.print("\n");
		}
	}

	int a = 0;
}
