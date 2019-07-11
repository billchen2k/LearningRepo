import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class CH11Q1 {
	static TreeMap<String, Integer> wordsData = new TreeMap<String, Integer>();
	static LinkedList<Map.Entry<String, Integer>> wordsDataList;

	private static void readFile() {
		Path p = Paths.get("data/a.txt");
		if(!Files.exists(p)){
			System.out.printf("\"a.txt\" doesn't exists. Please try again.");
			System.exit(-1);
		}
		try (BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(p.toString()), "utf-8"))) {
			String thisLine;
			while ((thisLine = reader.readLine()) != null) {
				if (thisLine.contains("="))
					continue;
				String[] words = thisLine.split(" ");
				for (String item : words) {
					if (item.equals("")) continue;
					if (wordsData.containsKey(item)) {
						wordsData.put(item, wordsData.get(item) + 1);
					} else {
						wordsData.put(item, 1);
					}
				}
			}
			wordsDataList = new LinkedList<>(wordsData.entrySet());
		} catch (IOException e) {
			System.out.printf("Error occurred while reading file: " + e.getMessage());
		}
		Collections.sort(wordsDataList, new Comparator<Map.Entry<String, Integer>>() {
			@Override
			public int compare(Map.Entry<String, Integer> o1, Map.Entry<String, Integer> o2) {
				if (o1.getValue() != o2.getValue())
					return o1.getValue() > o2.getValue() ? -1 : 1;
				else
					return 0;
			}
		});
	}

	private static void writeFile() {
		Path path = Paths.get("data/b.txt");
		try {
			if (!Files.exists(path))
				Files.createFile(path);
			BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(path.toString()), "utf-8"));
			writer.write("==============\n");
			for (Map.Entry<String, Integer> item : wordsDataList) {
				writer.write(item.getKey() + ", " + item.getValue());
				writer.newLine();
			}
			writer.write("==============");
			writer.close();
		} catch (IOException e) {
			System.out.printf("Error occurred while writing file: " + e.getMessage());
		}
	}

	public static void main(String[] args) {
		long starttime = System.nanoTime();
		System.out.println("Start reading file...");
		readFile();
		System.out.println("Start writing file...");
		writeFile();
		System.out.println("Done.\nTime usage: " + (System.nanoTime() - starttime) / 1000000.0 + " ms.");
	}
}
