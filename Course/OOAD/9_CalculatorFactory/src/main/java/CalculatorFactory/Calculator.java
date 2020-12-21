package CalculatorFactory;

public class Calculator{
	public static void main(String[] args) {
		CalculatorFactory plusFactory = new PlusFactory();
		Operator plus = plusFactory.createOperator();
		CalculatorFactory minusFactory = new MinusFactory();
		Operator minus = minusFactory.createOperator();
		CalculatorFactory timesFactory = new TimesFactory();
		Operator times = timesFactory.createOperator();

		System.out.println(plus.calc(3, 4));
		System.out.println(minus.calc(3, 4));
		System.out.println(times.calc(3, 4));
	}
}
