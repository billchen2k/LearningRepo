import java.util.HashSet;


public class HashSetJudgeRuleTest {

	public static void main(String[] args) {
		HashSet<Cat> hs = new HashSet<Cat>();
		hs.add(new Cat(1));
		hs.add(new Cat(2));
		hs.add(new Cat(3));
		hs.add(new Cat(3));
		System.out.println(hs.size()); //4
	}
}
