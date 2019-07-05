
public class BoxClassTest {
	public static void main(String[] args)
	{
		int i1 = 10;
		Integer i2 = 10;                // 自动装箱
		System.out.println(i1 == i2);   //true
		// 自动拆箱  基本类型和包装类进行比较，包装类自动拆箱
		
		Integer i3 = new Integer(10);
		System.out.println(i1 == i3);  //true
		// 自动拆箱  基本类型和包装类进行比较，包装类自动拆箱
		
		System.out.println(i2 == i3); //false
		// 两个对象比较，比较其地址。 
		// i2是常量，放在栈内存常量池中，i3是new出对象，放在堆内存中
		
		Integer i4 = new Integer(5);
		Integer i5 = new Integer(5);
		System.out.println(i1 == (i4+i5));   //true
		System.out.println(i2 == (i4+i5));   //true
		System.out.println(i3 == (i4+i5));   //true
		// i4+i5 操作将会使得i4,i5自动拆箱为基本类型并运算得到10. 
		// 基础类型10和对象比较, 将会使对象自动拆箱，做基本类型比较
		
		Integer i6 = i4 + i5;  // +操作使得i4,i5自动拆箱，得到10，因此i6 == i2.
		System.out.println(i1 == i6);  //true
		System.out.println(i2 == i6);  //true
		System.out.println(i3 == i6);  //false
	}	
}
