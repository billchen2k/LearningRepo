package CalculatorFactory;

public class Pow implements Operator {
	@Override
	public double calc(double num1, double num2) {
		return Math.pow(num1, num2);
	}
}
