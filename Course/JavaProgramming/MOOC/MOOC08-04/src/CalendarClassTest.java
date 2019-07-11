import java.util.Calendar;
import java.util.GregorianCalendar;

public class CalendarClassTest {

	public static void main(String[] args) {
		Calendar gc = Calendar.getInstance();
		System.out.println(gc.getClass().getName());
		//Calendar.getInstance();返回的是GregorianCalendar对象
		
		GregorianCalendar gc2 = new GregorianCalendar();
		System.out.println(gc2.getClass().getName());
	}

}
