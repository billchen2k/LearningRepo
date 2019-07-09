import java.util.HashMap;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;

public class MapCompareTest {

	public static void main(String[] args) {
		int n = 1000000;
		System.out.println("============HashMap=============");
		HashMap<Integer,String> hm =new  HashMap<Integer,String>();
		for(int i=0;i<n;i++) {
			hm.put(i, "aaa");
		}
		traverseByEntry(hm);
		traverseByKeySet(hm);
		
		System.out.println("============Hashtable=============");
		Hashtable<Integer,String> ht2 =new  Hashtable<Integer,String>();
		for(int i=0;i<n;i++) {
			ht2.put(i, "aaa");
		}
		traverseByEntry(ht2);
		traverseByKeySet(ht2);
	}
	
	public static void traverseByEntry(Map<Integer,String> ht)
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
	
	
	public static void traverseByKeySet(Map<Integer,String> ht)
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
}
