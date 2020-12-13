package Discount;

/**
 * Discount certain amount of money for every N amount of money.
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-13 23:12
 **/
public class DiscountNEveryN implements DiscountStrategy{

	private double discountAmount;
	private double discountThreshold;

	public DiscountNEveryN(double discountAmount, double discountThreshold) {
		this.discountAmount = discountAmount;
		this.discountThreshold = discountThreshold;
		if(discountAmount > discountThreshold) {
			System.out.println("Discount amount larger than discount threshold. Unexpected low price may occur.");
		}
	}

	@Override
	public double performDiscount(double originalPrice) {
		return originalPrice - ((int) (originalPrice / discountThreshold)) * discountAmount;
	}

	@Override
	public int getPriority() {
		return 10;
	}


}
