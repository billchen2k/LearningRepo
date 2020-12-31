package Subject;

import Observer.Observer;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-29 10:12
 **/
public class Subject extends BaseSubject{

	int value;

	@Override
	public void setValue(int v) {
		value = v;
		System.out.println("Value updated. Now notifying observers...");
		notifyObservers();
	}

	@Override
	public int getValue() {
		return value;
	}

	@Override
	public void notifyObservers() {
		for(Observer observer: observers) {
			observer.update();
		}
	}

	@Override
	public void registerObserver(Observer o) {
		observers.add(o);
	}

	@Override
	public void removeObserver(Observer o) {
		observers.remove(o);
	}
}
