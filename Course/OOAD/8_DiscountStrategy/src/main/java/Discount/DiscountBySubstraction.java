package Discount;

/**
 * Directly substract certain amount for the original product.
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-13 23:09
 **/
public class DiscountBySubstraction implements DiscountStrategy{

	private double substractionAmount;

	public DiscountBySubstraction(double amount) {
		substractionAmount = amount;
	}

	@Override
	public double performDiscount(double originalPrice) {
		return Math.max(0, originalPrice - substractionAmount);
	}

	@Override
	public int getPriority() {
		return 80;
	}

}
