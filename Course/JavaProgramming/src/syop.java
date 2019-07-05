class syop {

	protected String data = "Hello World!";

	void ln() {
		System.out.println(data);
	}

	void setText(String input) {
		this.data = input;
	}

}

class syop2 extends syop {

	void f() {
		System.out.print(data);
	}

	public static void main(String[] args) {
		syop P = new syop2();
		P.setText("HII!~!");
		P.ln();
		System.out.printf("Hi");
	}


}

class syop3 extends syop2 {
	void m() {

	}

}

