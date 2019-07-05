
public class LifeCycleTest {

	public static void main(String[] args) {
		int a=0;  // a 在main函数中都是active
		
		//i只能活在for循环中
		for(int i=0; i<5; i++) {
			int k = 0;
			k++;
		}
		
		if(a>0) {
			Object obj1 = new Object();  //obj1 只能在if分支中
			System.out.println("a is positive");
		} else {
			Object obj2 = new Object();  //obj2只能在else分支中
			System.out.println("a is non-positive");
		}
	}
}
