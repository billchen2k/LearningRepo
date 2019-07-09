
class Dog {
    private int size;
 
    public Dog(int s) {
        size = s;
    }      
    public int getSize() {
		return size;
	}

	public boolean equals(Object obj2)   {
    	System.out.println("Dog equals()~~~~~~~~~~~");
    	if(0==size - ((Dog) obj2).getSize()) {
    		return true;
    	} else {
    		return false;
    	}
    }
    
    public int hashCode() {
    	System.out.println("Dog hashCode()~~~~~~~~~~~");
    	return size;
    }
    
    public String toString() {
    	System.out.print("Dog toString()~~~~~~~~~~~");
        return size + "";
    }
}
