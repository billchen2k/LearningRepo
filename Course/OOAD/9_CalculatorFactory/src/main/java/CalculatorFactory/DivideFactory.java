package CalculatorFactory;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-15 11:53
 **/
public class DivideFactory implements CalculatorFactory{
	@Override
	public Operator createOperator() {
		return new Divide();
	}
}
