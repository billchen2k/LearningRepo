
public class FloatDoubleMaxMinTest {

	public static void main(String[] args) {
		System.out.println(Float.MIN_VALUE);
		System.out.println(Float.MAX_VALUE);
		System.out.println(Double.MIN_VALUE);
		System.out.println(Double.MAX_VALUE);

		float f1 = Float.MIN_VALUE;
		float f2 = Float.MAX_VALUE;
		float f3 = -1 * Float.MIN_VALUE;
		float f4 = -1 * Float.MAX_VALUE;
		System.out.println(f1 + ", " + f2 + ", " + f3 + ", " + f4);

		double d1 = Double.MIN_VALUE;
		double d2 = Double.MAX_VALUE;
		double d3 = -1 * Double.MIN_VALUE;
		double d4 = -1 * Double.MAX_VALUE;
		System.out.println(d1 + ", " + d2 + ", " + d3 + ", " + d4);

	}

}
