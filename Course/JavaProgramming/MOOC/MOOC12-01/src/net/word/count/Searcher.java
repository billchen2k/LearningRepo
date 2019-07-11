package net.word.count;
import java.io.IOException;
import java.nio.file.FileSystems;
import java.nio.file.FileVisitOption;
import java.nio.file.FileVisitResult;
import java.nio.file.FileVisitor;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.PathMatcher;
import java.nio.file.Paths;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.ArrayList;
import java.util.EnumSet;

/**
 * Searcher 用于搜索指定目录下、指定扩展名的文件
 * @author Tom
 *
 */
class Searcher implements FileVisitor {

	private final PathMatcher matcher;
	private ArrayList<String> filePaths = new ArrayList<String>();

	public Searcher(String ext) {
		matcher = FileSystems.getDefault().getPathMatcher("glob:" + ext);
	}

	public void judgeFile(Path file) throws IOException {
		Path name = file.getFileName();
		if (name != null && matcher.matches(name)) {
			//System.out.println("Searched file was found: " + name + " in " + file.toRealPath().toString());
			filePaths.add(file.toRealPath().toString());
		}
	}

	@Override
	public FileVisitResult postVisitDirectory(Object dir, IOException exc) throws IOException {
		//System.out.println("Visited: " + (Path) dir);
		return FileVisitResult.CONTINUE;
	}

	@Override
	public FileVisitResult preVisitDirectory(Object dir, BasicFileAttributes attrs) throws IOException {
		return FileVisitResult.CONTINUE;
	}

	@Override
	public FileVisitResult visitFile(Object file, BasicFileAttributes attrs) throws IOException {
		judgeFile((Path) file);
		return FileVisitResult.CONTINUE;
	}

	@Override
	public FileVisitResult visitFileFailed(Object file, IOException exc) throws IOException {
		return FileVisitResult.CONTINUE;
	}

	/**
	 * getFilePaths 返回满足条件的文件列表
	 * @return
	 */
	public ArrayList<String> getFilePaths() {
		return filePaths;
	}	
	
}

