import Discount.DiscountByPercentage;
import Discount.DiscountByPercentageAboveN;
import Discount.DiscountBySubstraction;
import Discount.DiscountNEveryN;
import Product.Product;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * Main Class
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-13 21:58
 **/
public class Main {

	public static void main(String[] args) {

		System.out.println("---------- Four strategies for four products: ----------");
		Product p1 = new Product(688, "Product 1", new DiscountBySubstraction(100));								// 直降 100
		Product p2 = new Product(688, "Product 2", new DiscountNEveryN(30, 200));			// 每 200 减 30
		Product p3 = new Product(688, "Product 3", new DiscountByPercentage(0.85));										// 85 折
		Product p4 = new Product(688, "Product 4", new DiscountByPercentageAboveN(0.7, 300));	// 300 元以上 7 折

		ArrayList<Product> products = new ArrayList<Product>(Arrays.asList(p1, p2, p3, p4));

		products.forEach(oneProduct -> {
			System.out.printf("The discount price for <%s> is: ￥%.2f\n", oneProduct.getProductName(), oneProduct.getDiscountPrice());
		});

		System.out.println("---------- Change p1's discount strategy: ----------");
		p1.clearDiscountStrategy();
		p1.addDiscountStrategy(new DiscountNEveryN(20, 300)); // 给 p1 增加一个每 300 减 20 的优惠
		System.out.printf("The discount price for <%s> is: ￥%.2f\n", p1.getProductName(), p1.getDiscountPrice());

		System.out.println("---------- A product with four strategies: ----------");
		Product p5 = new Product(688, "Product 5");
		p5.addDiscountStrategy(new DiscountBySubstraction(10));
		p5.addDiscountStrategy(new DiscountNEveryN(20, 200));
		p5.addDiscountStrategy(new DiscountByPercentageAboveN(0.8, 200));
		p5.addDiscountStrategy(new DiscountByPercentage(0.98));
		System.out.printf("The discount price for <%s> is: ￥%.2f\n", p5.getProductName(), p5.getDiscountPrice());

	}
}
