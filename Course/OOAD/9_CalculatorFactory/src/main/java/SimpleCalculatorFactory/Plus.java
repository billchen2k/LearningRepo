package SimpleCalculatorFactory;

public class Plus implements Operator {
	@Override
	public double calc(double num1, double num2) {
		return num1 + num2;
	}
}
