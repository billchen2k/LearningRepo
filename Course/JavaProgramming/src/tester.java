class tester {

	public void oneMethod() throws NullPointerException{
		;
	}

	public void test() {
		try {
			oneMethod();
			System.out.print("condition 1");
		} catch (Exception e) {
			System.out.print("condition 3");
		} finally {
			System.out.println("condition 4");
		}
	}
}