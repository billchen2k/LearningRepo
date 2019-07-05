
public class Derived extends Base{
	private int num = 20;	
	
	public int getNum()	{
		return this.num;
	}	
	
	public static void main(String[] args) {
		Derived foo = new Derived();
		System.out.println(foo.getNum());
	}
}
