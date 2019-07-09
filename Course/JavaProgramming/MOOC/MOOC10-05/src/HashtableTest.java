import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;

public class HashtableTest {

	public static void main(String[] args) {
		Hashtable<Integer,String> ht =new  Hashtable<Integer,String>();
		//ht.put(1, null); 编译不报错  运行报错
		//ht.put(null,1);  编译报错
		ht.put(1000, "aaa");
		ht.put(2, "bbb");
		ht.put(30000, "ccc");
		System.out.println(ht.contains("aaa"));
		System.out.println(ht.containsValue("aaa"));
		System.out.println(ht.containsKey(30000));
		System.out.println(ht.get(30000));
		
		ht.put(30000, "ddd");  //更新覆盖ccc
		System.out.println(ht.get(30000));
		
		ht.remove(2);
		System.out.println("size: " + ht.size());
		
		ht.clear();
		System.out.println("size: " + ht.size());
		
		
		Hashtable<Integer,String> ht2 =new  Hashtable<Integer,String>();
		for(int i=0;i<100000;i++)
		{
			ht2.put(i, "aaa");
		}
		traverseByEntry(ht2);
		traverseByKeySet(ht2);
		traverseByKeyEnumeration(ht2);		
	}
	
	public static void traverseByEntry(Hashtable<Integer,String> ht)
	{
		long startTime = System.nanoTime();
		System.out.println("============Entry迭代器遍历==============");
		Integer key;
		String value;
		Iterator<Entry<Integer, String>> iter = ht.entrySet().iterator();
		while(iter.hasNext()) {
		    Map.Entry<Integer, String> entry = iter.next();
		    // 获取key
		    key = entry.getKey();
		    // 获取value
		    value = entry.getValue();
		    //System.out.println("Key:" + key + ", Value:" + value);
		}
		long endTime = System.nanoTime();
	    long duration = endTime - startTime;
	    System.out.println(duration + "纳秒");
	}
	
	
	public static void traverseByKeySet(Hashtable<Integer,String> ht)
	{
		long startTime = System.nanoTime();
		System.out.println("============KeySet迭代器遍历=============="); 
		Integer key;
		String value;
		Iterator<Integer> iter = ht.keySet().iterator();
		while(iter.hasNext()) {
		    key = iter.next();		    
		    // 获取value
		    value = ht.get(key);
		    //System.out.println("Key:" + key + ", Value:" + value);
		}
		long endTime = System.nanoTime();
	    long duration = endTime - startTime;
	    System.out.println(duration + "纳秒");
	}
	
	
	public static void traverseByKeyEnumeration(Hashtable<Integer,String> ht)
	{
		long startTime = System.nanoTime();
		System.out.println("============KeyEnumeration迭代器遍历=============="); 
		Integer key;
		String value;
		Enumeration<Integer> keys = ht.keys();
		while(keys.hasMoreElements()) {
		    key = keys.nextElement();   
		    // 获取value
		    value = ht.get(key);
		    //System.out.println("Key:" + key + ", Value:" + value);
		}
		long endTime = System.nanoTime();
	    long duration = endTime - startTime;
	    System.out.println(duration + "纳秒");
	}
}
