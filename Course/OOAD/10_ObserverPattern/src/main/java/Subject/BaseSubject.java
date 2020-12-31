package Subject;

import java.util.ArrayList;
import Observer.Observer;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-29 09:47
 **/
public abstract class BaseSubject {

	ArrayList<Observer> observers = new ArrayList<>();
	abstract public void setValue(int v);
	abstract public int getValue();
	abstract public void notifyObservers();
	abstract public void registerObserver(Observer o);
	abstract public void removeObserver(Observer o);
}
