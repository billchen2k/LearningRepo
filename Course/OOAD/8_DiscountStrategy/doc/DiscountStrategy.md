## OOAD Assignment 8

> 10185101210 陈俊潼

### 策略模式设计方案

商场打折的策略模式设计方案类图如下：

![Model!Main_0](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-12-13-Uskr96.png)

这里给出了 4 种折扣方案：

- `DiscountBySubstraction`：直接在价格上减去若干元
- `DiscountNEveryN`：每满若干元减去若干元
- `DiscountByPercentage`：在价格上打若干折
- `DiscountByPercentageAboveN`：超过若干元的部分打若干折

以及一个 `NoDiscount` 策略用于表示没有任何折扣。

例如，针对 4 个价格均为 688 元的商品，采用了 4 种折扣策略，运行结果如下图所示：

![image-20201213233601100](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-12-13-v4zsEN.png)

源代码见另一个压缩包内。

### 其他问题

1. 折扣方式改掉怎么办?

使用 `Product` 的 `setDiscountStrategy()` 方法即可。如：

```java
p1.setDiscountStrategies(new ArrayList<>(Arrays.asList(new DiscountNEveryN(20, 300))));
```

![image-20201213233744032](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-12-13-QoaHCE.png)

2. 多种折扣方式同时使用怎么办?

首先将 `Product` 类中的 `discountStrategy` 从一个对象属性变成一个列表封装的属性，同时将属性名从 `discountStrategy` 改为 `discountStrategies`，如下图所示：

![ClassDiagram2Fixed](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-12-13-IhPMWG.png)



然后在各个折扣策略中指定优先级，数字小优先级越高。如果在 `Product` 的折扣策略列表中有多个折扣策略，则最后的价格会按照各个策略的优先级从低至高进行计算。例如，指定一个同时具有多个策略的产品，反复使用 `addDiscountStrategy` 来添加折扣策略，计算结果如下图所示：

![image-20201213234523760](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-12-13-VcC11t.png)

---

### 完整代码

Main.java

```java
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
```

Product.java

```java
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
```

DiscountStrategy.java

```java
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

```

NoDiscount.java

```
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
```

DiscountByPercentage.java

```java
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

```

DiscountByPercentageAboveN.java

```java
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
```

DiscountBySubtraction.java

```java
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
```

DiscountNEveryN.java

```java
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
```

