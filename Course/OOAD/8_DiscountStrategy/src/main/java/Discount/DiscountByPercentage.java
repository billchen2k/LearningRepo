package Discount;

/**
 * Discount by percentage.
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-13 23:14
 **/
public class DiscountByPercentage implements DiscountStrategy{

	private double percentage;

	public DiscountByPercentage(double percentage) {
		this.percentage = percentage;
	}

	@Override
	public double performDiscount(double originalPrice) {
		return originalPrice * percentage;
	}

	@Override
	public int getPriority() {
		return 30;
	}
}
