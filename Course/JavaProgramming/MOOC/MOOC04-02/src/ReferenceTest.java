
public class ReferenceTest {

	public static void main(String[] args) {
		
		int num1 = 5;
		int num2 = num1;
		System.out.println("num1: " + num1 + ", num2: " + num2);
		num2 = 10;
		System.out.println("num1: " + num1 + ", num2: " + num2);
		
		
		MyNumber obj1 = new MyNumber();
		MyNumber obj2 = new MyNumber();
		System.out.println(obj1.num);
		System.out.println(obj2.num);
		System.out.println("======接下来输出新值=====");
		
		obj2 = obj1;
		obj2.num = 10;
		
		System.out.println(obj1.num);
		System.out.println(obj2.num);

	}

}
