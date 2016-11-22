package to.je.to;

import java.io.FileInputStream;
import java.io.IOException;
public class TestClass {

	
	public static String lala = "lala";
	
	public static void main(String[] args) throws IOException{
		
		FileInputStream in = null;

		try {
			in = new FileInputStream("1111");
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			in.close();
			System.out.println("lala");
		}
	}
	
	public static void printaj (String ja){
		
		if (ja == null)
			return;
		
		
	}
}
