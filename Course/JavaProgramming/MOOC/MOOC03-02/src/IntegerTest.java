public class IntegerTest {
	public static void main(String[] args) {
		short a1 = 32767;
		System.out.println(a1);
		//short a2 = 32768;  error Խ��		

		int b1 = 2147483647;
		System.out.println(b1);
		//int b2 = 2147483648; error Խ��		

		long c1 = 1000000000000L;
		System.out.println(c1);

		long c2 = 2147483647;  //��ʽ���˴�int���long�Ĳ���
		System.out.println(c2);

		long c3 = 2147483648L; //ȥ��L������
		System.out.println(c3);
	}
}
