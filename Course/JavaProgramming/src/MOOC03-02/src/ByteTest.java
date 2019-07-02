
public class ByteTest {
	public static void main(String[] args) {
		byte a = (byte) -128;
		System.out.println(a);  //-128
		byte b = (byte) 127;
		System.out.println(b);  //127
		byte c = (byte) -129;
		System.out.println(c);  //127
		byte d = (byte) 128;
		System.out.println(d);  //-128
	}
}
