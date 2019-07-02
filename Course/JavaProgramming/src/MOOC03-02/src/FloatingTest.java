public class FloatingTest {
	public static void main(String[] args) {
		float f1 = 1.23f;
		// float f2 = 1.23;  error, float��ֵ�����f
		double d1 = 4.56d;
		double d2 = 4.56;  //double ����ʡ��ĩβd

		System.out.println(f1); //1.23
		System.out.println((double) f1); //ת����double, ���1.2300000190734863
		System.out.println(d1); //4.56
		System.out.println((float) d2); //4.56

		System.out.println(f1 == 1.229999999f); //true
		System.out.println(f1 - 1.229999999f); //0.0
		System.out.println(d2 == 4.559999999999999999d); //true
		System.out.println(d2 - 4.559999999999999999d); //0.0
	}
}
