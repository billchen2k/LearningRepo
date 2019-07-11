
import java.time.Duration;
import java.time.Instant;
import java.util.Date;
 
public class InstantExample {
 
    public static void main(String[] args) {
        //当前时间戳
        Instant timestamp = Instant.now();
        System.out.println("Current Timestamp = "+timestamp);
 
        //从毫秒数来创建时间戳
        Instant specificTime = Instant.ofEpochMilli(timestamp.toEpochMilli());
        System.out.println("Specific Time = "+specificTime);
 
        Date date = Date.from(timestamp); 
        System.out.println("current date = " + date);
    }
 
}