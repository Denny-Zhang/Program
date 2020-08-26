import java.util.*;

class MyThread implements Runnable{
	int m;
	MyThread(int m){
			this.m = m;
		}
	public void run(){
		for(int i = 1;i <= 5;i++){
			try{
				Thread.sleep(m);
			}catch(Exception e){}
			System.out.println(Thread.currentThread().getName()+"共跑"+i+"公里");
		}
		
	}
}

class X{
	public static void main(String...args){
		Thread turtle = new Thread(new MyThread(500),"bitches");
		Thread turtle1 = new Thread(new MyThread(500),"trashes");
		turtle.start();
		
		try{
			turtle.join();
			turtle1.start();
			turtle1.join();
		}catch(Exception e){}
		
		
		System.out.println("程式執行結束!");
	}
	
}