import java.text.DecimalFormat;

public class DecimalFormaterRuleTest {
	public static void main(String[]args){
        
        DecimalFormat df1,df2;
         
        System.out.println("整数部分为0的情况，0/#的区别");
        // 整数部分为0 ， #认为整数不存在，可不写； 0认为没有，但至少写一位，写0
        df1 = new DecimalFormat("#.00");
        df2 = new DecimalFormat("0.00");
         
        System.out.println(df1.format(0.1)); // .10  
        System.out.println(df2.format(0.1)); // 0.10  
         
        System.out.println("小数部分0/#的区别");
        //#代表最多有几位，0代表必须有且只能有几位
        df1 = new DecimalFormat("0.00");
        df2 = new DecimalFormat("0.##");
         
        System.out.println(df1.format(0.1)); // 0.10
        System.out.println(df2.format(0.1)); // 0.1
         
        System.out.println(df1.format(0.006)); // 0.01
        System.out.println(df2.format(0.006)); // 0.01
         
        System.out.println("整数部分有多位");
        //0和#对整数部分多位时的处理是一致的 就是有几位写多少位
        df1 = new DecimalFormat("0.00");
        df2 = new DecimalFormat("#.00");
         
        System.out.println(df1.format(2)); // 2.00
        System.out.println(df2.format(2)); // 2.00
         
        System.out.println(df1.format(20)); // 20.00
        System.out.println(df2.format(20)); // 20.00
         
        System.out.println(df1.format(200)); // 200.00
        System.out.println(df2.format(200)); // 200.00
         
         
    }
}
