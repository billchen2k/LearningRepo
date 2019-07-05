
public class B {
	public Integer num = 100;
	public Integer num2 = 128;
	public Character c = 100;
	
	public static void main(String[] args) {
		A a = new A();
		B b = new B();
		//Integer -128~127有常量池  true
		System.out.println(a.num == b.num);
		//Integer 128不在常量池          false
		System.out.println(a.num2 == b.num2);
		//Character 0-127在常量池    true
		System.out.println(a.c == b.c);
	}

}
