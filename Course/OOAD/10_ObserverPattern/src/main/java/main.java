import Observer.DivObserver;
import Observer.ModObserver;
import Subject.Subject;

/**
 * Main Class
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-29 09:34
 **/
public class main {

	public static void main(String[] args) {
		Subject subject = new Subject();
		DivObserver divObserver = new DivObserver(4, subject);
		ModObserver modObserver = new ModObserver(3, subject);
		subject.registerObserver(divObserver);
		subject.registerObserver(modObserver);
		subject.setValue(14);
		System.out.println("Observer.DivObserver removed.");
		subject.removeObserver(divObserver);
		subject.setValue(18);
	}
}
