import java.util.*;
import java.io.*;

class Ary{
	public static void main(String... args) throws IOException{
		int p = 0;
		String[] data = new String[100],sp;
		FileReader fr = new FileReader("endangeredSpeciesUTF8.txt");
		Scanner scn = new Scanner(fr);
		while(scn.hasNext()){
			sp = scn.nextLine().split(",");
			if(java.lang.Character.isDigit(sp[0].charAt(0)))
				continue;
			if(sp[3].charAt(0) == 'C')
				data[p++] = sp[0]+"/"+sp[1]+"(CR)";
			else if(sp[3].charAt(0) == 'E')
				data[p++] = sp[0]+"/"+sp[1]+"(EN)";
			else if(sp[3].charAt(0) == 'V')
				data[p++] = sp[0]+"/"+sp[1]+"(VU)";
			else if(sp[3].charAt(0) == 'N')
				data[p++] = sp[0]+"/"+sp[1]+"(NT)";
			else if(sp[3].charAt(0) == 'L')
				data[p++] = sp[0]+"/"+sp[1]+"(LC)";
			else
				data[p++] = sp[0]+"/"+sp[1]+"(Unknow)";
		}
		Arrays.sort(data);
		String word = "";
		while(word !="EXIT"){
			System.out.println("請輸入欲查詢物種(CR/EN/VU/NT/LC),輸入Exit則結束程式執行");
			word = new Scanner(System.in).next().toUpperCase();
			if(word.equals("EXIT"))
				break;
			for(String i : data){
				if(word.equals("CR") && i.charAt((i.indexOf('('))+1) == 'C')
					System.out.println(i);
				else if(word.equals("EN") && i.charAt((i.indexOf('('))+1) == 'E')
					System.out.println(i);
				else if(word.equals("VU") && i.charAt((i.indexOf('('))+1) == 'V')
					System.out.println(i);
				else if(word.equals("NT") && i.charAt((i.indexOf('('))+1) == 'N')
					System.out.println(i);
				else if(word.equals("LC") && i.charAt((i.indexOf('('))+1) == 'L')
					System.out.println(i);	
			}
			System.out.println("按任意鍵查詢全部物種,輸入Skip則跳過");
			if(!new Scanner(System.in).next().toUpperCase().equals("SKIP"))
				for(String i : data)
					System.out.println(i);
			System.out.print("請輸入欲查詢中文字:");
			word = new Scanner(System.in).next();
			for(String i : data)
				if(i.indexOf(word)!=-1)
					System.out.println(i);		
		}
	}
}