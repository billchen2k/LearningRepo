import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.TreeSet;


public class ObjectHashSetTest {

	public static void main(String[] args) {
		System.out.println("==========Cat HashSet ==============");
		HashSet<Cat> hs = new HashSet<Cat>();  
		hs.add(new Cat(2));  
		hs.add(new Cat(1));  
		hs.add(new Cat(3));  
		hs.add(new Cat(5));  
		hs.add(new Cat(4)); 
		hs.add(new Cat(4)); 
		System.out.println(hs.size());  //6
		
		System.out.println("========================");
		LinkedHashSet<Cat> lhs= new LinkedHashSet<Cat>();  
		lhs.add(new Cat(2));  
		lhs.add(new Cat(1));  
		lhs.add(new Cat(3));  
		lhs.add(new Cat(5));  
		lhs.add(new Cat(4));  
		lhs.add(new Cat(4));		
		System.out.println(lhs.size());  //6
		
		
		
		System.out.println("==========Dog HashSet ==============");
		HashSet<Dog> hs2 = new HashSet<Dog>();  
		hs2.add(new Dog(2));  
		hs2.add(new Dog(1));  
		hs2.add(new Dog(3));  
		hs2.add(new Dog(5));  
		hs2.add(new Dog(4)); 
		hs2.add(new Dog(4)); 
		System.out.println(hs2.size());  //5
		
		System.out.println("========================");
		LinkedHashSet<Dog> lhs2= new LinkedHashSet<Dog>();  
		lhs2.add(new Dog(2));  
		lhs2.add(new Dog(1));  
		lhs2.add(new Dog(3));  
		lhs2.add(new Dog(5));  
		lhs2.add(new Dog(4));  
		lhs2.add(new Dog(4)); 		
		System.out.println(lhs2.size());  //5
		

		System.out.println("==========Tiger HashSet ==============");		
		HashSet<Tiger> hs3 = new HashSet<Tiger>();  
		hs3.add(new Tiger(2));  
		hs3.add(new Tiger(1));  
		hs3.add(new Tiger(3));  
		hs3.add(new Tiger(5));  
		hs3.add(new Tiger(4)); 
		hs3.add(new Tiger(4)); 
		System.out.println(hs3.size());  //6
		
		System.out.println("========================");
		LinkedHashSet<Tiger> lhs3= new LinkedHashSet<Tiger>();  
		lhs3.add(new Tiger(2));  
		lhs3.add(new Tiger(1));  
		lhs3.add(new Tiger(3));  
		lhs3.add(new Tiger(5));  
		lhs3.add(new Tiger(4));  
		lhs3.add(new Tiger(4)); 		
		System.out.println(lhs3.size());  //6
	}
}
