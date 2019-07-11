import java.io.File;
import java.io.IOException;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.*;
import java.util.concurrent.LinkedBlockingQueue;

public class ls {
	final static String path = "/Users/billchen/Movies";
	final static int rFlag = 1;

	public static void main(String[] args) {
		Path p = Paths.get(path);
		LinkedBlockingQueue<Path> temp = new LinkedBlockingQueue<Path>();
		int indent = 0;
		List<Path> allFiles = new LinkedList<Path>();
		try {
			Files.walkFileTree(p, new SimpleFileVisitor<>() {
				@Override
				public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {
					if (file.toString().endsWith(".mp4") || file.toString().endsWith(".mkv")) {
						System.out.println("Visiting file: " + file.toString());
						allFiles.add(file);
					}
					return super.visitFile(file, attrs);
				}
			});
		} catch (IOException e) {
			System.out.printf("Error occured while listing. - " + e.getMessage());
		}
		System.out.println("");
	}

}
