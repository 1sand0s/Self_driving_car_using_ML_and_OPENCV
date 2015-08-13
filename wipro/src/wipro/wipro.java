/* Copyright (C) 2015 Rakshith Vishwanatha,Pavan Gurudatt,Aditya T
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

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
