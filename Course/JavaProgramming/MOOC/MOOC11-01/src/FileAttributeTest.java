
import java.io.*;
public class FileAttributeTest{
  public static void main(String[] args){
	//创建目录
	File d=new File("c:/temp");
	if(!d.exists())
	{
		d.mkdirs();  //mkdir 创建单级目录  mkdirs 连续创建多级目录
	}
	System.out.println("Is d directory? " + d.isDirectory());
	
	//创建文件  
    File f=new File("C:/temp/abc.txt");    
    if(!f.exists())
    {    	
      try
      {
        f.createNewFile(); //创建abc.txt
      }
      catch(IOException e){ //可能会因为权限不足或磁盘已满报错
    	  e.printStackTrace();
      }
    }  
    
    //输出文件相关属性
    System.out.println("Is f file? " + f.isFile());
    System.out.println("Name: "+f.getName());
    System.out.println("Parent: "+f.getParent());
    System.out.println("Path: "+f.getPath());
    System.out.println("Size: "+f.length()+" bytes");
    System.out.println("Last modified time: "+f.lastModified()+"ms");
    
    //遍历d目录下所有的文件信息
    System.out.println("list files in d directory");
    File[] fs = d.listFiles();  //列出d目录下所有的子文件，不包括子目录下的文件
    for(File f1:fs)
    {
    	System.out.println(f1.getPath());
    }
    
    //f.delete(); //删除此文件
    //d.delete(); //删除目录
  }
}
