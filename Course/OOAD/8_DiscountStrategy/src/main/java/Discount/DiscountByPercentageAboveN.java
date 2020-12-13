package Discount;

/**
 * Discount the amount that is over N by a certain percentage.
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-13 23:15
 **/
public class DiscountByPercentageAboveN implements DiscountStrategy{

	private double percentage;
	private double discountThreshold;

	public DiscountByPercentageAboveN(double percentage, double discountThreshold) {
		this.percentage = percentage;
		this.discountThreshold = discountThreshold;
	}

	@Override
	public double performDiscount(double originalPrice) {
		return originalPrice <= discountThreshold ?
				originalPrice :
				discountThreshold + percentage * (originalPrice - discountThreshold);
	}

	@Override
	public int getPriority() {
		return 35;
	}
}
