package Discount;

/**
 * The interface for discount strategy
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-13 22:58
 **/
public interface DiscountStrategy {
	public abstract double performDiscount(double originalPrice);
	public abstract int getPriority();
}
