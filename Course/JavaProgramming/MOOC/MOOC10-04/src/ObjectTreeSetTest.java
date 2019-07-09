import java.util.TreeSet;


public class ObjectTreeSetTest {

	public static void main(String[] args) {
		/*
		System.out.println("==========Cat TreeSet ==============");
		TreeSet<Cat> ts = new TreeSet<Cat>();  
		ts.add(new Cat(2));  
		ts.add(new Cat(1));  
		ts.add(new Cat(3));  
		ts.add(new Cat(5));  
		ts.add(new Cat(4)); 
		ts.add(new Cat(4)); 
		System.out.println(ts.size());  //5		
		
		System.out.println("==========Dog TreeSet ==============");
		
		
		TreeSet<Dog> ts2 = new TreeSet<Dog>();  
		ts2.add(new Dog(2));  
		ts2.add(new Dog(1));  
		ts2.add(new Dog(3));  
		ts2.add(new Dog(5));  
		ts2.add(new Dog(4)); 
		ts2.add(new Dog(4)); 
		System.out.println(ts2.size());  //5
		*/
		
		//添加到TreeSet的，需要实现Comparable接口，即实现compareTo方法

		System.out.println("==========Tiger TreeSet ==============");
		
		
		TreeSet<Tiger> ts3 = new TreeSet<Tiger>();  
		ts3.add(new Tiger(2));  
		ts3.add(new Tiger(1));  
		ts3.add(new Tiger(3));  
		ts3.add(new Tiger(5));  
		ts3.add(new Tiger(4)); 
		ts3.add(new Tiger(4)); 
		System.out.println(ts3.size());  //5
	}

}
