package Product;

import Discount.DiscountStrategy;
import Discount.NoDiscount;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-13 22:53
 **/
public class Product {

	private double originalPrice;
	private String productName;

	private ArrayList<DiscountStrategy> discountStrategies;

	public Product(double price, String name, ArrayList<DiscountStrategy> strategies) {
		originalPrice = price;
		productName = name;
		discountStrategies = strategies;
	}

	public Product(double price, String name, DiscountStrategy strategy) {
		originalPrice = price;
		productName = name;
		discountStrategies = new ArrayList<>() {{
				add(strategy);
			}};
	}

	public Product(double price, String name) {
		this(price, name, new ArrayList<>());
	}

	public Product() {
		this(0, "Unknown Product", new ArrayList<DiscountStrategy>(Arrays.asList(new NoDiscount())) );
	}

	public double getOriginalPrice() {
		return originalPrice;
	}

	public double getDiscountPrice() {
		if (discountStrategies == null) {
			return originalPrice;
		}
		 discountStrategies.sort(new Comparator<DiscountStrategy>() {
			@Override
			public int compare(DiscountStrategy o1, DiscountStrategy o2) {
				return o1.getPriority() - o2.getPriority();
			}
		});
		double discountPrice = originalPrice;
		for (DiscountStrategy strategy : discountStrategies) {
			discountPrice = strategy.performDiscount(discountPrice);
		}
		return discountPrice;
	}

	public void setDiscountStrategies(ArrayList<DiscountStrategy> discountStrategies) {
		this.discountStrategies = discountStrategies;
	}

	public void addDiscountStrategy(DiscountStrategy strategy) {
		this.discountStrategies.add(strategy);
	}

	public void clearDiscountStrategy() {
		this.discountStrategies.clear();
		this.discountStrategies.add(new NoDiscount());
	}

	public ArrayList<DiscountStrategy> getDiscountStrategies() {
		return discountStrategies;
	}

	public String getProductName() {
		return productName;
	}

	public void setProductName(String productName) {
		this.productName = productName;
	}
}
