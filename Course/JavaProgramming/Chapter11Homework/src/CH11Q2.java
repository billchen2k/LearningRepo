import java.io.*;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Random;

public class CH11Q2 {

	public static void main(String[] args) {
		long starttime = System.nanoTime();
		Path path = Paths.get("data/a.dat");
		Random r = new Random();
		try{
			if (!Files.exists(path))
				Files.createFile(path);
		}
		catch(IOException e){
			System.out.println("Can't create file: " + e.getMessage());
		}
		try(DataOutputStream writer = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(path.toString())))){
			for (int i = 0; i < 100; i++) {
				writer.writeInt(r.nextInt());
			}
		}
		catch(IOException e){
			System.out.println("Error occurred while writing file:" + e.getMessage());
		}
		BigInteger sum = new BigInteger("0");
		try{
			DataInputStream reader = new DataInputStream(new BufferedInputStream(new FileInputStream(path.toString())));
			int tmp;
			for(int i = 0;i < 100;i++){
				tmp = reader.readInt();
				sum = sum.add(new BigInteger(Integer.toString(tmp)));

			}
		}
		catch(IOException e){
			System.out.println("Error occurred while reading file: " + e.getMessage());
		}
		BigDecimal ave = new BigDecimal(sum);
		ave = ave.divide(new BigDecimal(100));
		System.out.println("The average value is: " + ave);
		System.out.println("Time usage: " + (System.nanoTime() - starttime) / 1000000.0 + "ms.");
	}
}
