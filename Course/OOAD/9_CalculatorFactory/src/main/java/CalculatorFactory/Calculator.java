package CalculatorFactory;

public class Calculator{
	public static void main(String[] args) {
		CalculatorFactory plusFactory = new PlusFactory();
		Operator plus = plusFactory.createOperator();
		System.out.println(plus.calc(3, 4));

		CalculatorFactory timesFactory = new TimesFactory();
		Operator times = plusFactory.createOperator();
		System.out.println(times.calc(3, 4));
	}
}
