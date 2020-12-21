package FactoryPattern;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-15 08:16
 *
 * Factory design pattern.
 **/

interface Operator {
	double calc(double num1, double num2);
}

class Plus implements Operator{
	@Override
	public double calc(double num1, double num2) {
		return num1 + num2;
	}
}

class Minus implements Operator {
	@Override
	public double calc(double num1, double num2) {
		return num1 - num2;
	}
}

class Times implements Operator {
	@Override
	public double calc(double num1, double num2) {
		return num1 * num2;
	}
}

class Divide implements Operator{
	@Override
	public double calc(double num1, double num2) {
		if (num2 == 0) {
			return 0;
		}
		return num1 / num2;
	}
}

class Pow implements Operator{
	@Override
	public double calc(double num1, double num2) {
		return Math.pow(num1, num2);
	}
}

class CalculatorFactory {
	public static final int OPERATOR_PLUS = 1;
	public static final int OPERATOR_MINUS = 2;
	public static final int OPERATOR_TIMES = 3;
	public static final int OPERATOR_DIVIDE = 4;
	public static final int OPERATOR_POW = 5;

	public static Operator createOperator(int o) {
		switch (o) {
			case OPERATOR_PLUS:
				return new Plus();
			case OPERATOR_MINUS:
				return new Minus();
			case OPERATOR_TIMES:
				return new Times();
			case OPERATOR_DIVIDE:
				return new Divide();
			case OPERATOR_POW:
				return new Pow();
		}
		return (Operator) (num1, num2) -> num1;
	}
}

public class Calculator {
	public static void main(String[] args) {
		Operator pluser = CalculatorFactory.createOperator(CalculatorFactory.OPERATOR_PLUS);
		System.out.println(pluser.calc(3, 4));
	}
}
