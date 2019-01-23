import java.util.Scanner;
public class Main{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int num = sc.nextInt();
        System.out.println(Fib(num));
        sc.close();
    }

    public static long Fib(int num) {
        if (num == 0)
            return 1;
        if (num == 1)
            return 1;
        if (num == 2)
            return 2;
        else {
            long temp1 = 1, temp2 = 2, temp3 = 3;
            for (int i = 0; i < num - 2; i++) {
                temp3 = temp1 + temp2;
                temp1 = temp2;
                temp2 = temp3;
            }
            return temp3;
        }
    }
}