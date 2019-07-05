
public class OOExample {
	private int a;
	public void setA(int a)
	{
		this.a = a;
	}
	public int add(int b)
	{
		return this.a + b;
	}
	public static void main(String[] a)
	{
		int b = 5;
		OOExample obj = new OOExample();
		obj.setA(10);
		System.out.println(obj.add(b));
		
	}
}
