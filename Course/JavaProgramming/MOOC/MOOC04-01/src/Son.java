
public class Son extends Father {
	public void hi() {
		//子类可以扩展自己的成员方法
		System.out.println("hi~~~~~");
	}
	
	public static void main(String[] a)	{
	    Son s = new Son();
	    System.out.println(s.mobile); //Son没有定义mobile, 而是通过父类继承的
	    //System.out.println(s.money); //error 父类的money是私有的，子类无法直接访问
	    s.hello();  //Son没有定义f1, 而是通过父类继承的
	    s.hi();     //Son可以自定义自己的成员方法
	}
}
