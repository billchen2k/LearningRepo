package net.word.count;

import java.io.IOException;
import java.nio.file.FileVisitOption;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.Map.Entry;

public class WordCounter {

	public static void main(String[] args) throws IOException {
	
		//接收目录参数和扩展名
		Path fileTree = Paths.get("/Users/billchen/D");
		Searcher walk = new Searcher("*.txt");	
		

		//查找该目录下所有的txt文件
		EnumSet<FileVisitOption> opts = EnumSet.of(FileVisitOption.FOLLOW_LINKS);
		Files.walkFileTree(fileTree, opts, Integer.MAX_VALUE, walk);
		ArrayList<String> filePaths = walk.getFilePaths();
		//System.out.println(filePaths.get(0));
		
		//解析每个文件的单词
		
		HashMap<String, Word> totalMap = new HashMap<String, Word>(); 
		
		for(String str:filePaths)
		{
			HashMap<String, Word> partMap = new FileAnalyzer(str).getWordCount();
			if(partMap != null && partMap.size() > 0)
			{
				combineMap(totalMap, partMap);
			}
		}
		
		//排序
		//Collection<Word> words = totalMap.values();
		ArrayList<Word> words = new ArrayList<Word>(totalMap.values());
		Collections.sort(words);
		
		//输出
		System.out.println("最后结果");
		for(Word w : words)
		{
			System.out.println(w.getText() + ", " + w.getTimes());
		}
	}
	
	/**
	 * combineMap 合并两个HashMap
	 * @param total
	 * @param part
	 */
	public static void combineMap(HashMap<String, Word> total, HashMap<String, Word> part)
	{
		Iterator<Entry<String, Word>> iter = part.entrySet().iterator();
		while(iter.hasNext()) {
		    Map.Entry<String, Word> entry = iter.next();
		    // 获取key
		    String partKey = entry.getKey();
		    // 获取value
		    Word partWord = entry.getValue();
		    if(total.containsKey(partKey))
		    {
		    	Word totalWord = total.get(partKey);
		    	totalWord.setTimes(totalWord.getTimes() + partWord.getTimes());
		    }
		    else
		    {
		    	total.put(partKey, partWord);
		    }
		}
	}

}
