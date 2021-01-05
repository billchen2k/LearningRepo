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
		value = 0;
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
