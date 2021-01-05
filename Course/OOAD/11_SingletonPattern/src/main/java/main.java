/**
 * @author billchen
 * @version 1.0
 * @create 2021-01-05 09:18
 **/
public class main {

	private static GlobalClass globalInstance = null;

	private static void foo() {
		if (globalInstance != null) {
			globalInstance.setValue(1);
			System.out.println("Global value is set to 1.");
		}
	}

	private static void bar() {
		if (globalInstance != null) {
			globalInstance.setValue(2);
			System.out.println("Global value is set to 2.");
		}
	}

	public static void main(String[] args) {
		globalInstance = GlobalClass.getInstance();
		foo();
		bar();
	}
}
