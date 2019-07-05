
public class Main {
	final String TEXT = "HELLOWORLD";
	public static void main(String[] args) {
		syop syop = new syop();
		System.out.println(syop.toString());
		syop.setText("Tester!!");
		syop.ln();

		Boy boy = new Boy();
		Human boy1 = (Human) boy;
		HaveLunch(new Human(){
			@Override
			public void eat() {
				System.out.println("EAT ANNOYMOUSLY");
			}

			@Override
			public void walk() {
				System.out.println("WALK ANNOYMOUSLY");
			}
		});
	}

	public static void HaveLunch(Human a){
		/*

		 */

	}
}

