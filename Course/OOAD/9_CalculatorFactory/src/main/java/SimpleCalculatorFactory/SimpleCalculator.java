package SimpleCalculatorFactory;

public class SimpleCalculator {
	public static void main(String[] args) {
		Operator plus = SimpleCalculatorFactory.createOperator(SimpleCalculatorFactory.OPERATOR_PLUS);
		Operator minus = SimpleCalculatorFactory.createOperator(SimpleCalculatorFactory.OPERATOR_MINUS);
		System.out.println(plus.calc(3, 4));
		System.out.println(minus.calc(3, 4));
	}
}
