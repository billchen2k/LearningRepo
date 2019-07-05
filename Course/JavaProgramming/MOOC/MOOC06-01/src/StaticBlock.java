
class StaticBlock
{
	//staticl block > anonymous block > constructor function	
	static
	{
		System.out.println("22222222222222222222");
	}
	{
		System.out.println("11111111111111111111");
	}
	public StaticBlock()
	{
		System.out.println("33333333333333333333");
	}
	{
		System.out.println("44444444444444444444");
	}
}