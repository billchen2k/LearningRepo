
public class IntegerTest {

	public static void main(String[] args) {
		Integer n1 = 127;
		Integer n2 = 127;
		System.out.println(n1==n2); 
		//对象双等号是比较指针是否指向同一个东西
		
		Integer n3 = 128;
		Integer n4 = 128;
		System.out.println(n3==n4);
		
		Integer n5 = new Integer(127);
		System.out.println(n1==n5);
	}

}
