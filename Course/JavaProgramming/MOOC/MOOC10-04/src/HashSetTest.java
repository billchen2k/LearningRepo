import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;

public class HashSetTest {
	public static void main(String[] args) {
		HashSet<Integer> hs = new HashSet<Integer>();
		hs.add(null);
		hs.add(1000);
		hs.add(20);
		hs.add(3);
		hs.add(40000);
		hs.add(5000000);
		hs.add(3);                      //3 重复
		hs.add(null);                   //null重复
		System.out.println(hs.size());  //6
		if(!hs.contains(6))
		{
			hs.add(6);
		}
		System.out.println(hs.size());  //7
		hs.remove(4);
		System.out.println(hs.size());  //6
		//hs.clear();
		//System.out.println(hs.size());  //0
		
		System.out.println("============for循环遍历=============="); 
	    for(Integer item : hs)
	    {
	    	System.out.println(item);
	    }
	    
	    System.out.println("============测试集合交集==============");
	    
	    HashSet<String> set1 = new HashSet<String>();
	    HashSet<String> set2 = new HashSet<String>();

        set1.add("a");
        set1.add("b");
        set1.add("c");

        set2.add("c");
        set2.add("d");
        set2.add("e");

        //交集
        set1.retainAll(set2);
        System.out.println("交集是 "+set1);
        
        System.out.println("============测试多种遍历方法速度==============");
		
		HashSet<Integer> hs2 = new HashSet<Integer>();
		for(int i=0;i<100000;i++)	{
			hs2.add(i);
		}
		traverseByIterator(hs2);
		traverseByFor(hs2);		
	}
	
	public static void traverseByIterator(HashSet<Integer> hs)
	{
		long startTime = System.nanoTime();
		System.out.println("============迭代器遍历=============="); 
	    Iterator<Integer> iter1 = hs.iterator();  
	    while(iter1.hasNext()){  
	        iter1.next();  
	    }
		long endTime = System.nanoTime();
	    long duration = endTime - startTime;
	    System.out.println(duration + "纳秒");
	}
	public static void traverseByFor(HashSet<Integer> hs)
	{
		long startTime = System.nanoTime();
		System.out.println("============for循环遍历=============="); 
	    for(Integer item : hs)
	    {
	    	;
	    }
		long endTime = System.nanoTime();
	    long duration = endTime - startTime;
	    System.out.println(duration + "纳秒");
	}
}
