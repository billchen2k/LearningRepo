package Works;

public class CH3Q2 {
	public static void main(String[] args) {
		int line = 9;
		int spaceCount = line / 2;
		int starCount = 1;
		for(int i = 0; i < line; i+=2){
			for(int j = 0;j < spaceCount;j++)
				System.out.print(" ");
			for (int j = 0; j < starCount; j++)
				System.out.print("*");
			for (int j = 0; j < spaceCount; j++)
				System.out.print(" ");
			System.out.print("\n");
			spaceCount--;
			starCount+=2;
		}
		spaceCount+=2;
		starCount -= 4;
		for (int i = line; i > 0; i -= 2) {
			for (int j = 0; j < spaceCount; j++)
				System.out.print(" ");
			for (int j = 0; j < starCount; j++)
				System.out.print("*");
			for (int j = 0; j < spaceCount; j++)
				System.out.print(" ");
			System.out.print("\n");
			spaceCount++;
			starCount -= 2;
		}
	}
}
