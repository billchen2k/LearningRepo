
public class Initialization {
	
	boolean v1;
	byte v2;
	char v3;
	double v4;
	float v5;
	int  v6;
	long v7;
	short v8; 
	
	
	public static void main(String[] args) {
		Initialization obj = new Initialization();
		System.out.println("The initial value of boolean variable is " + obj.v1);
		System.out.println("The initial value of byte variable is " + obj.v2);
		System.out.println("The initial value of char variable is " + obj.v3);  //\u0000 space
		System.out.println("The initial value of double variable is " + obj.v4);
		System.out.println("The initial value of float variable is " + obj.v5);
		System.out.println("The initial value of int variable is " + obj.v6);
		System.out.println("The initial value of long variable is " + obj.v7);
		System.out.println("The initial value of short variable is " + obj.v8);
		
		int a = 3;
		System.out.println(a);  //error, a 没有初始化

	}

}
