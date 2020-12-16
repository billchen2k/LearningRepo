package SimpleCalculatorFactory;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-15 11:43
 **/
public class SimpleCalculatorFactory {
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
