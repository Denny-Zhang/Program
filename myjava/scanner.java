import java.util.*;
import java.io.*;

class Scn{
	public static void main(String... args){
		int c = 0,x = 0;
		String t="";
		Scanner scn = new Scanner(System.in);
		if(args.length == 1){
			FileInputStream fa;
			try{
				fa = new FileInputStream(args[0]);
				scn = new Scanner(fa);
			}catch(IOException e){
				e.printStackTrace();
			}
		}
		while(scn.hasNext()){
			t = scn.nextLine();
			System.out.println(t);
			c++;
			x += t.length();
		}
		System.out.println("\n\n�@�@��"+c+"��");
		System.out.println("�@�@��"+x+"�Ӧr");	
	}
}
