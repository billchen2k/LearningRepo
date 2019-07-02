
public class OperatorTest {
	public static void main(String[] args) {
		int a = 10;
		int b = 3;
		int c = a + b;  //13
		int d = a - b;  //7
		int e = a / b;  //3
		int f = a % b;  //1
		System.out.println(c + "," + d + "," + e + "," + f);

		System.out.println(a >> 1); //5�� ���� ����2
		System.out.println(a << 1); //20  ���� ����2

		System.out.println((5 > 2) && ((2 < 3) || (!false)));  //true
	}
}
