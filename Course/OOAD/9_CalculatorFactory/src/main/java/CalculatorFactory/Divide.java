package CalculatorFactory;

public class Divide implements Operator {
	@Override
	public double calc(double num1, double num2) {
		if (num2 == 0) {
			return 0;
		}
		return num1 / num2;
	}
}
