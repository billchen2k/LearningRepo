
public class CharTest {
	public static void main(String[] args) {
		char a = 'a';
		char b = 97;  //根据ascii码转化为a
		char c = '我';
		char d = '\u4e00'; //“一”字  \u4e00--\u9fa5  两万多汉字
		System.out.println(a);
		System.out.println(b);
		System.out.println(c);
		System.out.println(d);
	}
}
