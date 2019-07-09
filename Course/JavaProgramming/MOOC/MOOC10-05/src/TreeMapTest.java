import java.util.TreeMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;

public class TreeMapTest {

	public static void main(String[] args) {
		TreeMap<Integer,String> hm =new  TreeMap<Integer,String>();
		hm.put(1, null); 
		//hm.put(null, "abc");  编译没错，运行报空指针异常  
		hm.put(1000, "aaa");
		hm.put(2, "bbb");
		hm.put(30000, "ccc");
		System.out.println(hm.containsValue("aaa"));
		System.out.println(hm.containsKey(30000));
		System.out.println(hm.get(30000));
		
		hm.put(30000, "ddd");  //更新覆盖ccc
		System.out.println(hm.get(30000));
		
		//hm.remove(2);
		System.out.println("size: " + hm.size());
		
		//hm.clear();
		//System.out.println("size: " + hm.size());
		
		System.out.println("遍历开始==================");
		
		Integer key;
		String value;
		Iterator<Entry<Integer, String>> iter = hm.entrySet().iterator();
		while(iter.hasNext()) {
		    Map.Entry<Integer, String> entry = iter.next();
		    // 获取key
		    key = entry.getKey();
		    // 获取value
		    value = entry.getValue();
		    System.out.println("Key:" + key + ", Value:" + value);
		}
		System.out.println("遍历结束==================");
		
		TreeMap<Integer,String> hm2 =new  TreeMap<Integer,String>();
		for(int i=0;i<100000;i++)
		{
			hm2.put(i, "aaa");
		}
		traverseByEntry(hm2);
		traverseByKeySet(hm2);		
	}
	
	public static void traverseByEntry(TreeMap<Integer,String> ht)
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
	
	
	public static void traverseByKeySet(TreeMap<Integer,String> ht)
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
