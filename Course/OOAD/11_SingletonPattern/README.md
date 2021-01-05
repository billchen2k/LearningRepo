# Singleton Pattern

> 10185101210 陈俊潼

运行截图如下：

![2021-01-05-CWLpfr](https://billc.oss-cn-shanghai.aliyuncs.com/img/2021-01-05-CWLpfr.png)

主要代码：

main.java:

```java
/**
 * @author billchen
 * @version 1.0
 * @create 2021-01-05 09:18
 **/
public class main {

	private static GlobalClass globalInstance = null;

	private static void foo() {
		if (globalInstance != null) {
			globalInstance.setValue(1);
			System.out.println("Global value is set to 1.");
		}
	}

	private static void bar() {
		if (globalInstance != null) {
			globalInstance.setValue(2);
			System.out.println("Global value is set to 2.");
		}
	}

	public static void main(String[] args) {
		globalInstance = GlobalClass.getInstance();
		foo();
		bar();
	}
}
```

GlobalClass.java:
```java
/**
 * A singleton class
 *
 * @author billchen
 * @version 1.0
 * @create 2021-01-05 09:19
 **/
public class GlobalClass {
	private static GlobalClass instance = null;
	private int value;

	private GlobalClass() {
		value= 0;
	}

	public static GlobalClass getInstance() {
		if (instance == null) {
			instance = new GlobalClass();
		}
		return instance;
	}

	public void setValue(int new_value){
		this.value = new_value;
	}

	public int getValue() {
		return value;
	}

}
```