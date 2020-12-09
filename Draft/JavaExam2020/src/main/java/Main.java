import java.io.*;
import java.util.Scanner;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-09 12:51
 **/
public class Main {

	private static int totalLines = 0;
	private static int commentLines = 0;
	private static int blankLines = 0;
	private static int totalFiles = 0;

	// Calculate lines of File f.
	private static void countLine(File f) {
		Boolean isInComment = false;
		totalFiles++;
		try {
			BufferedReader bf = new BufferedReader(new FileReader(f));
			String line = "";
			while ((line = bf.readLine()) != null) {
				line = line.replace("\t", "").replace(" ", "");
				if (line.startsWith("/*") && !line.endsWith("*/")) {
					isInComment = true;
					commentLines++;
					continue;
				}
				if(isInComment && !line.endsWith("*/")) {
					commentLines++;
					continue;
				}
				if(isInComment && line.endsWith("*/")) {
					isInComment = false;
					commentLines++;
					continue;
				}
				if(line.length() > 0){
					totalLines++;
				}
				else {
					blankLines++;
					totalLines++;
				}
				if (line.startsWith("/*") && line.endsWith("*/")) {
					commentLines++;
				}
				if(line.startsWith("//")){
					commentLines++;
				}
			}
		}
		catch (FileNotFoundException e) {
			System.out.println("File not found.");
		}
		catch (IOException e) {
			System.out.println("Fail to read file.");
		}
	}

	private static void readFiles(File f) {
		if (!f.exists() || !f.isDirectory()) {
			System.out.println("File not exists or not a directory.");
			return;
		}
		File[] subFiles = f.listFiles();
		for(File oneFile : subFiles) {
			System.out.printf("Counting: %s\n", oneFile.getAbsolutePath());
			if (oneFile.isDirectory()) {
				readFiles(oneFile);
			}
			else {
				if (oneFile.getPath().endsWith(".java")) {
					countLine(oneFile);
				}
			}
		}
	}


	public static void main(String[] args) {
		System.out.println("Please specify a directory:");
		Scanner sc = new Scanner(System.in);
		String dir = sc.nextLine();
		File rootDirectory = new File(dir);
		readFiles(rootDirectory);
		System.out.printf("Total files: %s\n", totalFiles);
		System.out.printf("Total lines in .java files: %d\n", totalLines);
		System.out.printf("Total lines in .java files (Without Comment): %d\n", totalLines - commentLines);
		System.out.printf("Blank lines in .java files: %d\n", blankLines);
	}
}


