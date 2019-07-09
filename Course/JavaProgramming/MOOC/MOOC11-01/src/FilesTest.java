import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.LinkOption;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.Date;

public class FilesTest {
	
	public static void main(String[] a)
	{
		moveFile();
		fileAttributes();
		createDirectory();
	}

	public static void moveFile() {
		Path from = Paths.get("c:/temp", "abc.txt");
		//移动c:/temp/abc.txt到c:/temp/test/def.txt，如目标文件已存在，就替换
		Path to = from.getParent().resolve("test/def.txt");
		try {
			//文件的大小bytes
			System.out.println(Files.size(from));
			//调用文件移动方法  如果目标文件已经存在，就替换
			Files.move(from, to, StandardCopyOption.REPLACE_EXISTING);
		} catch (IOException e) {
			System.err.println("移动文件错误" + e.getMessage());
		}
	}
	
	
	public static void fileAttributes(){
		Path path = Paths.get("c:/temp");
		//1
		System.out.println(Files.isDirectory(path, LinkOption.NOFOLLOW_LINKS));
		//2
		try {
			//获得文件的基础属性
			BasicFileAttributes attributes = Files.readAttributes(path, BasicFileAttributes.class);
			System.out.println(attributes.isDirectory());
			System.out.println(new Date(attributes.lastModifiedTime().toMillis()).toLocaleString());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void createDirectory(){
		Path path = Paths.get("c:/temp/test");
		try {
			//创建文件夹
			if(Files.notExists(path)){
				Files.createDirectories(path);
				System.out.println("create dir");
			}else{
				System.out.println("dir exists");
			}
			Path path2 = path.resolve("A.java"); 
			Path path3 = path.resolve("B.java");
			Path path4 = path.resolve("C.txt");
			Path path5 = path.resolve("D.jpg");
			Files.createFile(path2);
			Files.createFile(path3);
			Files.createFile(path4);
			Files.createFile(path5);
			
			//不加条件遍历
			DirectoryStream<Path> paths = Files.newDirectoryStream(path);
			for(Path p : paths){
				System.out.println(p.getFileName());
			}
			System.out.println();
			
			//创建一个带有过滤器,过滤文件名以java txt结尾的文件
			DirectoryStream<Path> pathsFilter = Files.newDirectoryStream(path, "*.{java,txt}");
			for(Path p : pathsFilter){
				System.out.println(p.getFileName());
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
