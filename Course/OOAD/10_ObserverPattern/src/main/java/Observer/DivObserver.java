package Observer;

import Subject.BaseSubject;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-29 10:09
 **/
public class DivObserver extends Observer{

	int div;

	public DivObserver(int v, BaseSubject subject) {
		div = v;
		setSubject(subject);
	}

	@Override
	public void update() {
		System.out.println(String.format("%d div %d is %d.", subject.getValue(), div, subject.getValue() / div));
	}
}
