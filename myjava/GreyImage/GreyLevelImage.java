import java.util.*;
import java.io.*;

class GreyLevelImage{
	private int width,height;
	private byte[][] greyLevelImageData = new byte[512][512];
	
	public GreyLevelImage(int width, int height){
		this.width = width;
		this.height = height;
	}
	public int getWidth(){
		return this.width;
	}
	public int getHeight(){
		return this.height;
	}
	public byte[] getImgData(){
		int count = 0;
		byte[] data = new byte[262144];
		for(byte[] i : greyLevelImageData)
			for(byte j : i)
				data[count++] = j;
		return data;
	}
	public static GreyLevelImage fromFile(String filename, int width, int height){
		GreyLevelImage img = new GreyLevelImage(width,height);
		InputStream fb = null;
		int size = 0;
		byte[] buf = null;
		try{
			fb = new FileInputStream(new File(filename));
			size = fb.available();
			buf = new byte[size];
			fb.read(buf);
		}catch(IOException e){
			System.out.println("檔案不存在!");
		}finally{
			try{
				fb.close();
			}catch(Exception e){}
		}
		int row = 0,column = 0;
		for(int i = 0;i < buf.length;i++){
			if(i % 512 == 0 && i != 0){
				row++;
				column = 0;
			}
			img.greyLevelImageData[row][column++] = buf[i];
		}
		return img;
	}
	public GreyLevelImage flipHorizontal(){ //鏡像
		GreyLevelImage horizontal = new GreyLevelImage(width,height);
		for(int i = 0;i < greyLevelImageData[0].length;i++)
			for(int j = 511,column = 0;j >= 0 && column < 512;j--,column++)
				horizontal.greyLevelImageData[i][column] = greyLevelImageData[i][j];
		return horizontal;
	}
	public GreyLevelImage flipVirtical(){ //上下翻轉
		GreyLevelImage virtical = new GreyLevelImage(width,height);
		for(int i = 0,j = 511;i < greyLevelImageData[0].length && j >= 0;i++,j--)
			for(int column = 0;column < 512;column++)
				virtical.greyLevelImageData[i][column] = greyLevelImageData[j][column];
		return virtical;
	}
	public GreyLevelImage rotate90(){ //90度逆時鐘旋轉
		GreyLevelImage rotate = new GreyLevelImage(width,height);
		for(int i = 0,j = 511;i < greyLevelImageData[0].length && j >= 0;i++,j--)
			for(int column = 0;column < 512;column++)
				rotate.greyLevelImageData[i][column] = greyLevelImageData[column][j];
		return rotate;
	}
	public GreyLevelImage negative(){ //負片
		GreyLevelImage negative = new GreyLevelImage(width,height);
		for(int i = 0;i < greyLevelImageData[0].length;i++)
			for(int column = 0;column < 512;column++)
				negative.greyLevelImageData[i][column] = (byte)(255-greyLevelImageData[i][column]);
		return negative;
	}
	public GreyLevelImage blur(){ //模糊
		GreyLevelImage blur = new GreyLevelImage(width,height);
		for(int i = 1;i < 511;i++)
			for(int j = 1;j < 511;j++)
				if(i % 2 == 1 && j % 2 == 1 || i % 2 == 0 && j % 2 == 0)
					greyLevelImageData[i][j] = (byte)((greyLevelImageData[i-1][j-1]+greyLevelImageData[i-1][j]+greyLevelImageData[i-1][j+1]+greyLevelImageData[i][j-1]+greyLevelImageData[i][j]+greyLevelImageData[i][j+1]+greyLevelImageData[i+1][j-1]+greyLevelImageData[i+1][j]+greyLevelImageData[i+1][i+1])/9);
		for(int i = 0;i < greyLevelImageData[0].length;i++)
			for(int column = 0;column < 512;column++)
				blur.greyLevelImageData[i][column] = greyLevelImageData[i][column];
		return blur;
	}
}
class Test{
	public static void main(String...args){
		GreyLevelImage img = new GreyLevelImage(512,512);
		try{	
			img = GreyLevelImage.fromFile("lena",img.getWidth(),img.getHeight());
			new RawImgViewer("flipHorizontal",img.flipHorizontal());
			img = GreyLevelImage.fromFile("lena",img.getWidth(),img.getHeight());
			new RawImgViewer("flipVirtical",img.flipVirtical());
			img = GreyLevelImage.fromFile("lena",img.getWidth(),img.getHeight());
			new RawImgViewer("rotate90",img.rotate90());
			img = GreyLevelImage.fromFile("lena",img.getWidth(),img.getHeight());
			new RawImgViewer("negative",img.negative());
			img = GreyLevelImage.fromFile("lena",img.getWidth(),img.getHeight());
			new RawImgViewer("blur",img.blur());
		}catch(Exception e){
			System.out.println("無法輸出!!");
		}
		
	}
}