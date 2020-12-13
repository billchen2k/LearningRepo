package Discount;

/**
 * No any discount
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-13 23:08
 **/
public class NoDiscount implements DiscountStrategy{

	@Override
	public double performDiscount(double originalPrice) {
		return originalPrice;
	}

	@Override
	public int getPriority() {
		return 100;
	}
}
