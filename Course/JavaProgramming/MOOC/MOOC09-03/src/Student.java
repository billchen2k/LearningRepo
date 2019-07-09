
public class Student {
	
	public int divide(int x, int y) 
	{
		return x/y;
	}
	
	public static void main(String[] args) throws DivideByMinusException{
		Student newton = new Student();
		//newton.divide2(5, 0);
		newton.divide5(5, -2);
	}	
	
	public int divide2(int x, int y)
	{
		int result;
		try
		{
			result = x/y;
			System.out.println("result is " + result);
		}
		catch(ArithmeticException ex)
		{
			System.out.println(ex.getMessage());
			return 0;
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
			return 0;
		}
		return result;
	}
	
	//ArithmeticException is a unchecked exception,编译器可以不管
	public int divide3(int x, int y) throws ArithmeticException
	{		
		return x/y;
	}
	
	public int divide4(int x, int y) 
	{		
//		try
//		{
//			return divide3(x,y);
//		}
//		catch(ArithmeticException ex)
//		{
//			ex.printStackTrace();
//			return 0;
//		}
		return divide3(x,y);  //尽管divide3报告异常，divide4无需处理。因为这个异常是unchecked exception
		//如果调用divide5(x,y);  那么就需要做try。。。catch处理，因为它抛出checked exception
	}
	
	public int divide5(int x, int y) throws DivideByMinusException
	{		
		try
		{
			if(y<0)
			{
				throw new DivideByMinusException("The divisor is negative", y);
			}
			return divide3(x,y);
		}
		catch(ArithmeticException ex)
		{
			ex.printStackTrace();
			return 0;
		}
	}
}
