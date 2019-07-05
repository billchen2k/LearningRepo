public class MyPairNumber {
	private int m;
	private int n;

	public int getM() {
		return m;
	}

	public void setM(int m) {
		this.m = m;
	}

	public int getN() {
		return n;
	}

	public void setN(int n) {
		this.n = n;
	}

	public MyPairNumber() {
		this(0, 0);
	}

	public MyPairNumber(int m) {
		this(m, 0);
	}

	public MyPairNumber(int m, int n) {
		this.m = m;
		this.n = n;
	}

	public int sum() {
		return this.add(m, n);  //return add(m,n);  also ok
	}

	public int add(int a, int b) {
		return a + b;
	}
}
