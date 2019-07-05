
public class Son extends Father
{
	public static void main(String[] a)
	{
	    Son s = new Son();
	    s.f1();  //Son没有定义f1,而是通过父类继承的
	}
}
