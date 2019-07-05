class A
{
	private int id;

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}	
}

public class ObjectPassingTest {
	public static void main(String[] args) {
		A a = new A();
		a.setId(10);
		System.out.println(a.getId());
		changeValue(a);
		System.out.println(a.getId());
	}
	
	public static void changeValue(A b)	{
		b.setId(20);
		//b = new A();
	}
}
