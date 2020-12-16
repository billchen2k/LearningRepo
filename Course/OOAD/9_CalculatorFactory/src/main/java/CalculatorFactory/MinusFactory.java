package CalculatorFactory;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-15 11:52
 **/
public class MinusFactory implements CalculatorFactory{
	@Override
	public Operator createOperator() {
		return new Minus();
	}
}
