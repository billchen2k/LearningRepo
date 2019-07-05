
//继承自Shape抽象类
public class Rectangle extends Shape{

	int width;  //宽
	int length; //长
	
	public Rectangle(int length, int width) {
		this.length = length;
		this.width = width;
	}
	
	public void calArea() {
		System.out.println(this.length * this.width);
	}
	
	public static void main(String[] args) {
		Rectangle rect = new Rectangle(10,5);
		rect.calArea();	
	}
}
