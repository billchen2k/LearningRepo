import java.io.File;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class PathTest {
	public static void main(String[] args) {
		// Path 和 java.io.File 基本类似
		// 获得path方法一,c:/temp/abc.txt
		Path path = FileSystems.getDefault().getPath("c:/temp", "abc.txt");
		System.out.println(path.getNameCount());

		// 获得path方法二，用File的toPath()方法获得Path对象
		File file = new File("c:/temp/abc.txt");
		Path pathOther = file.toPath();
		// 0,说明这两个path是相等的
		System.out.println(path.compareTo(pathOther));

		// 获得path方法三
		Path path3 = Paths.get("c:/temp", "abc.txt");
		System.out.println(path3.toString());

		// 合并两个path
		Path path4 = Paths.get("c:/temp");
		System.out.println("path4: " + path4.resolve("abc.txt"));

		if (Files.isReadable(path)) {
			System.out.println("it is readable");
		} else {
			System.out.println("it is not readable");
		}
	}
}
