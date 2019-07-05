package Homework;

public class CH3Q1 {
	public static void main(String[] args) {
		int count = 1;
		for (int i = 0; i < args[0].charAt(0) - '0'; i++) {
			for (int j = 0; j < Integer.parseInt(args[0]); j++) {
				System.out.printf("%-2d ", count);
				count++;
			}
			System.out.print("\n");
		}
	}
}
