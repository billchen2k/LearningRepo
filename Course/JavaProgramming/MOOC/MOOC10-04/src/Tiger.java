
public class Tiger implements Comparable{
	private int size;
	 
    public Tiger(int s) {
        size = s;    
    }    
    
    public int getSize() {
		return size;
	}
    
	public int compareTo(Object o) {
    	System.out.println("Tiger compareTo()~~~~~~~~~~~");
        return size - ((Tiger) o).getSize();
    }
}
