package Observer;

import Subject.BaseSubject;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-29 10:19
 **/
public class ModObserver extends Observer{
	int mod;

	public ModObserver(int v, BaseSubject subject) {
		mod = v;
		setSubject(subject);
	}

	@Override
	public void update() {
		System.out.println(String.format("%d mod %d is %d.", subject.getValue(), mod, subject.getValue() % mod));
	}
}
