package net.word.count;

/**
 * Word 单词实体，实现Comparable，可以排序
 * @author Tom
 *
 */
public class Word implements Comparable<Word> {
	private String text;  //单词文本
	private int times;    //单词次数
	
	public String getText() {
		return text;
	}
	public void setText(String text) {
		this.text = text;
	}
	public int getTimes() {
		return times;
	}
	public void setTimes(int times) {
		this.times = times;
	}	
	public Word(String text, int times)	{
		this.text = text;
		this.times = times;
	}
	
	/**
	 * 定义两个单词的排序, 逆序输出
	 */
	public int compareTo(Word a) {
		return (-1) * (this.getTimes() - a.getTimes());
	}
}
