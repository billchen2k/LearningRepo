package Observer;

import Subject.BaseSubject;
import lombok.Setter;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-29 09:46
 **/
public abstract class Observer {
	@Setter
	protected BaseSubject subject;

	abstract public void update();

}
