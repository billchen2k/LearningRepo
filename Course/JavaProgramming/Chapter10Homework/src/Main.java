import java.util.*;
import java.util.spi.CurrencyNameProvider;

class Currency {
	private String name;        //货币名称
	private int originalValue;  //原始值
	private int value;          //转换为人民币后的值

	public static String[] CURRENCY_NAME = {"CNY", "HKD", "USD", "EUR"};
	public static int[] CURRENCY_RATIO = {100, 118, 15, 13};
	public static HashMap<String, Integer> CURRENCY_RATIO_MAP = new HashMap<String, Integer>();

	static {
		for (int i = 0; i < 4; i++) {
			CURRENCY_RATIO_MAP.put(CURRENCY_NAME[i], CURRENCY_RATIO[i]);
		}
	}

	public String getName() {

		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getOriginalValue() {
		return originalValue;
	}

	public void setOriginalValue(int originalValue) {
		this.originalValue = originalValue;
	}

	public int getValue() {
		return value;
	}

	public void setValue(int value) {
		this.value = value;
	}

	public Currency(String name, int originalValue, int value) {
		this.name = name;
		this.originalValue = originalValue;
		this.value = value;
	}
}

class HKD extends Currency implements Comparable {

	public HKD(int value) {
		super("HKD", value, value / CURRENCY_RATIO_MAP.get("HKD") * 100);
	}

	@Override
	public int compareTo(Object o) {
		Currency oc = (Currency) o;
		return oc.getValue() <= this.getValue() ? 1 : -1;
	}
}

class USD extends Currency implements Comparable {
	public USD(int value) {
		super("USD", value, value / CURRENCY_RATIO_MAP.get("USD") * 100);
	}

	@Override
	public int compareTo(Object o) {
		Currency oc = (Currency) o;
		return oc.getValue() <= this.getValue() ? 1 : -1;
	}
}

class EUR extends Currency implements Comparable {
	public EUR(int value) {
		super("EUR", value, value / CURRENCY_RATIO_MAP.get("EUR") * 100);
	}

	@Override
	public int compareTo(Object o) {
		Currency oc = (Currency) o;
		return oc.getValue() <= this.getValue() ? 1 : -1;
	}
}

public class Main {
	public static void main(String[] args) {
		Currency[] cs = new Currency[3];
		//初始化
		Scanner sc = new Scanner(System.in);
		//利用hasNextXXX()判断是否还有下一输入项
		int a = 0;
		int b = 0;
		int c = 0;
		if (sc.hasNext()) {
			a = sc.nextInt();
			cs[0] = new HKD(a);
		}

		if (sc.hasNext()) {
			b = sc.nextInt();
			cs[1] = new USD(b);
		}

		if (sc.hasNext()) {
			c = sc.nextInt();
			cs[2] = new EUR(c);
		}
		Arrays.sort(cs);
		for (int i = 0; i < 3; i++) {
			System.out.println(cs[i].getName() + cs[i].getOriginalValue());
		}
	}
}