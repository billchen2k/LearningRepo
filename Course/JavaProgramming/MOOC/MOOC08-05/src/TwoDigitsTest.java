

import java.math.BigDecimal;
import java.text.DecimalFormat;
import java.text.NumberFormat;
public class TwoDigitsTest {

	public static void main(String[] args) {
		double   f   =   111231.5585;  
		BigDecimal   b   =   new   BigDecimal(f);  
		double   f1   =   b.setScale(2,BigDecimal.ROUND_HALF_UP).doubleValue();  
		System.out.println(f1); //111231.56
		
		DecimalFormat   df   =new DecimalFormat("#.00");  
		String f2 = df.format(f);
		System.out.println(f2); //111231.56
		 
		String f3 = String.format("%.2f",f);
		System.out.println(f3); //111231.56
		
		NumberFormat ddf1=NumberFormat.getInstance() ;
		System.out.println(ddf1.getClass().getName());
		ddf1.setMaximumFractionDigits(2); 
		String f4= ddf1.format(f) ; 
		System.out.println(f4);  //111,231.56		
	}
}
