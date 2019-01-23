import java.util.Arrays;
import java.util.Scanner;
public class Main{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int len = Integer.parseInt(sc.nextLine());
        String[] strArray = new String[len];
        for (int i = 0; i < len; i++) {
            strArray[i] = sc.nextLine();
        }
        Arrays.sort(strArray);
        for (int i = 0; i < len; i++) {
            System.out.println(strArray[i]);
        }

    }
}