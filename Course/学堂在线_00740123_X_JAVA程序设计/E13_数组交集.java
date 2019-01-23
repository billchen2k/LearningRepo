import java.util.Scanner;
import java.util.Arrays;
public class Main{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int len1=0, len2=0;
        len1 = sc.nextInt();
        int[] array1 = new int[len1];
        for(int i =0;i<len1;i++) array1[i]=sc.nextInt();
        len2 = sc.nextInt();
        int[] array2 = new int[len2];
        for (int i = 0;i<len2;i++) array2[i]=sc.nextInt();
        Arrays.sort(array1);
        Arrays.sort(array2);
        int count1=0, count2=0;
        for (int i = 0; i < len1; i++) {
            for (int j = 0; j < len2; j++) {
                if (array1[i] == array2[j]) {
                    count1++;
                    break;
                }
            }
        }
        for (int i = 0; i < len2; i++) {
            for (int j = 0; j < len1; j++) {
                if (array2[i] == array1[j]) {
                    count2++;
                    break;
                }
            }
        }
        if (count1 == 0 && count2 == 0)
            System.out.println("None");
        else {
            System.out.println(count1>=count2?count1:count2);
        }
       
    }
}