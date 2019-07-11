import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Scanner;

public class WordReader {
	public static void main(String[] args){
		Path p = Paths.get("data/word.txt");
		HashMap<String, String> wordData = new HashMap<>();
		try (BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(p.toString())))) {
			String thisLine;
			while((thisLine = reader.readLine())!= null){
				String[] lineData = thisLine.replace(" ", "").split(",");
				wordData.put(lineData[0].toLowerCase(), lineData[1]);
			}
		} catch (IOException e){
			System.out.println("Error occured while opening file: " + e.getMessage());
		}
		Scanner sc = new Scanner(System.in);
		while(sc.hasNext()){
			if(sc.hasNextInt()){
				if(sc.nextInt() == -1){
					System.out.println("Bye.");
					System.exit(0);
				}
				else{
					System.out.println("未知指令。");
				}
			}
			else if (sc.hasNextLine()){
				String line = sc.nextLine();
				if(line != null){
					String chinese = wordData.get(line.toLowerCase());
					if(chinese == null){
						System.out.println("未找到。");
					}
					else{
						System.out.println(chinese);
					}
				}
			}
		}
	}
}
