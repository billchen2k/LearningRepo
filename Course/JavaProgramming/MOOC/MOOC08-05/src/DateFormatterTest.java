import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class DateFormatterTest {

	public static void main(String[] args) {
		//将字符串转化为时间
		String dateStr= "2016年10月25日";
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy年MM月dd日");
        LocalDate date= LocalDate.parse(dateStr, formatter);
        System.out.println(date.getYear() + "-" + date.getMonthValue() + "-" + date.getDayOfMonth());
        
        System.out.println("==========================");
        
        //将日期转换为字符串输出
        LocalDateTime now = LocalDateTime.now();
        DateTimeFormatter format = DateTimeFormatter.ofPattern("yyyy年MM月dd日 hh:mm:ss");
        String nowStr = now.format(format);
        System.out.println(nowStr);


	}

}
