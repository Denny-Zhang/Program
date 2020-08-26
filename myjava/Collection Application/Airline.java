import java.util.*;
import java.io.*;
import java.time.*;

class MyString implements Comparable<MyString>{
	String num,city,take;

	MyString(String num,String city,String take){
		this.num = num;
		this.city = city;
		this.take = take;
	}
	public String toString(){
		return num+" "+city+" "+take;
	}
	public int compareTo(MyString o){
		return this.num.compareTo(o.num);
	}
}
class Airline{
	public static void main(String...args){	
		Scanner scn = null;
		Set<String> set = new TreeSet<>();
		List<MyString> time = new ArrayList<>();
		List<MyString> ori = new ArrayList<>();
		Map<LocalTime,String> contact = new HashMap<>();
		try{
			scn =  new Scanner(new File("ChinaAirLine.txt"));
			while(scn.hasNext()){
				String num = scn.next();
				String city = scn.next();
				String take = scn.next();
				String arr = scn.next();
				set.add(city);
				time.add(new MyString(num,city,take));
			//	int take1 = Integer.parseInt(take.substring(0,2));
			//	int take2 = Integer.parseInt(take.substring(3,5));
				//contact.put(LocalTime.of(take1,take2),num +" "+ city +" "+ take +" "+ arr);
			}
		}catch(Exception e){
			System.out.println("檔案無法開啟!!");
		}finally{
			try{
				scn.close();
			}catch(Exception e){
			}
		}
		System.out.println("自桃機出發的航線共有 "+set.size()+" 條");
		System.out.println(set);
		System.out.println();
		
		for(int i = 0;i < time.size();i++)
			ori.add(new MyString("","",""));
		Collections.copy(ori,time);
		Collections.sort(time);
		System.out.println("預定起飛時間不相同的班機:");
		int i = 0;
		String num = time.get(i).num;
		String take = null;
		while(i < time.size()){
			take = time.get(i).take;
			num = time.get(i++).num;
			if(i != 1 && num.equals(time.get(i-2).num))
				continue;
			int c = i-1;
			for(MyString s : time){
				if(num.equals(s.num) && !(take.equals(s.take))){
					if(c == i-1)
						System.out.println(time.get(c++));
					System.out.println(s);
				}
			}
		}
		System.out.println();
		System.out.println("深夜出發的航班:");
		//for(MyString s : ori)
		//	contact.put(Integer.parseInt(LocalTime.of(s.take.substring(0,2)),Integer.parseInt(s.take.substring(3,5))),"e04");
		for(LocalTime t : contact.keySet())
			if(t.isAfter(LocalTime.of(22,0)))
				System.out.println(contact.get(t));
	}
}