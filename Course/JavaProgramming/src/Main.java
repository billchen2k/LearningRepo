import java.io.*;
import java.nio.Buffer;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

class Student{
	private String id;
	private String name;

	public void setId(String id) {
		this.id = id;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getId() {
		return id;
	}

	public String getName() {
		return name;
	}

	public Student(String id, String name){
		this.id = id;
		this.name = name;
	}
}

public class Main {
	final String TEXT = "HELLOWORLD";
	public static void main(String[] args) {
		Boy boy = new Boy();
		int[] array = {1,2,3,4,5,4,3,2,1};
		ArrayList<Integer> al = new ArrayList<Integer>();
		al.add(3);
		al.add(1,4);
		al.add(1);
		al.add(6);
		al.add(5);
		Collections.sort(al);
		Iterator<Integer> iter1 = al.iterator();
		long starttime = System.nanoTime();
		while(iter1.hasNext()){
			System.out.println(iter1.next());
		}
		long endtime = System.nanoTime();
		Human boy1 = (Human) boy;
		Student cjt = new Student("10185101210", "陈俊潼");
		System.out.println(cjt.getName());
		System.out.println(endtime-starttime);
		/*
			FILE TESTING......
		 */
		File f = new File("/Users/billchen/tester");
		if(!f.exists()){
			f.mkdirs();
		}
		System.out.println(f.lastModified());
		Path p = Paths.get("/Users/billchen/tester");
		p = p.resolve("Hi");
		try {
			Files.createFile(p);
		} catch (IOException e) {
			System.out.println("Error: " + e.getMessage());
		}
		if(Files.exists(p)){
			System.out.println(p.toString() + " Exists!");
			Path src = p;
			Path news = p.resolve("Hi2");
			try{
				BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(p.toString()), "utf-8"));
				writer.write("Finally, I'm able to write something here.\nThat's exhausting.");
				writer.write("Finally, I'm able to write something here.\nThat's exhausting.");
				System.out.println("Successfully Written.");
				writer.close();
			}
			catch(IOException e){
				System.out.println("Error:\n " + e.getMessage());
			}
			try {
				Files.createDirectory(news);
				Files.copy(src, news);
			}
			catch(IOException e){
				System.out.println("Error:\n "+ e.getMessage());
			}
		}
		else{
			System.out.println(p.toString()+ " Doesn't Exist!");
		}
	}

	public static void HaveLunch(Human a){

	}
}

