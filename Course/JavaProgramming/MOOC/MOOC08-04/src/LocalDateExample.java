import java.time.LocalDate;
import java.time.Month;
import java.time.ZoneId;

public class LocalDateExample {

    public static void main(String[] args) {
 
        //当前时间
        LocalDate today = LocalDate.now();
        System.out.println("Current Date="+today);
 
        //根据指定时间创建LocalDate
        LocalDate firstDay_2014 = LocalDate.of(2014, Month.JANUARY, 1);
        System.out.println("Specific Date="+firstDay_2014);
 
        //给定错误时间参数，将报异常java.time.DateTimeException
        //LocalDate feb29_2014 = LocalDate.of(2014, Month.FEBRUARY, 29);
 
        //可以更改时区
        LocalDate todayBeijing = LocalDate.now(ZoneId.of("Asia/Shanghai"));
        System.out.println("Current Date in Shanghai="+todayBeijing);
 
        //从纪元日01/01/1970开始365天 
        LocalDate dateFromBase = LocalDate.ofEpochDay(365);
        System.out.println("365th day from base date= "+dateFromBase);
 
        //2014年的第100天 
        LocalDate hundredDay2014 = LocalDate.ofYearDay(2014, 100);
        System.out.println("100th day of 2014="+hundredDay2014);
    }
 
}