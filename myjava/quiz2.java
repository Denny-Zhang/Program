import java.util.*;
class your_Class{
	public static void main(String... args){
		int[] data = new int[args.length];
		int d,temp;
		if(args.length != 3)
			System.out.printf(" usage : java your_Class num1 num2 num3\n");
		for(int i = 0;i < args.length;i++)
			data[i]=Integer.parseInt(args[i]);
		Arrays.sort(data);
		d = data[1]-data[0];
		temp = d;
		do{
			for(int i = 1;i<args.length-1;i++){
				temp = data[i+1]-data[i];
				if(temp!=d)
					break;
			}
			if(temp == d){
				System.out.printf("���ƦC�����t�ƦC\n���t:%2d\n",d);
				System.out.print("�e10��:");
				for(int i = 0;i<10&&i<args.length;i++)
					System.out.printf("%4d",data[i]);
			}
			if(temp!=d){
				System.out.printf("���ƦC���D���t�ƦC\n�̤j��:%d\n�̤p��:%d",data[args.length-1],data[0]);
			}
		}while(false);
		
	}
}