

import java.awt.image.*;

import javax.imageio.ImageIO;
import java.io.*;
public class wipro 
{

	public static void main(String[] args)throws IOException
	{
		new wipro();
	}
	wipro()throws IOException
	{
		int[] pix;
		File f=new File("C:/Users/Computer/Desktop/test.jpg");// Insert Image path inside the quotes
		BufferedImage i=ImageIO.read(f);
		WritableRaster r=i.getRaster();
		pix=new int[r.getHeight()*r.getWidth()];
		r.getPixels(0,0,r.getWidth(),r.getHeight(), pix);
			
		for(int y=0;y<r.getHeight();y++)
		{
			for(int x=0;x<r.getWidth();x++)
			{
				if(pix[x+y*r.getWidth()]>10)
				{
					pix[x+y*r.getWidth()]=1;
				}
				else
				{
					pix[x+y*r.getWidth()]=0;
				}
				System.out.print(pix[x+y*r.getWidth()]+" , ");
			}
			System.out.println("");
		}
	}

}
