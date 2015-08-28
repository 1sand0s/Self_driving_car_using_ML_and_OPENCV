#include<opencv\cv.h>
#include<opencv\cvaux.h>
#include<opencv\cxcore.h>
#include<opencv\highgui.h>
#include<opencv2\imgproc\imgproc_c.h>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

#include<stdio.h>
#include<conio.h>

using namespace cv;
void main(char* arg,int arnc[])
{
	int HH,SH,VH,HL,SL,VL,i, cnt;
	i=0;
	cnt=0;
	char buf[1000];
	cvNamedWindow("CAM_VIEW_WIPRO",CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("HH","CAM_VIEW_WIPRO",&HH,179);
	cvCreateTrackbar("SH","CAM_VIEW_WIPRO",&SH,255);
	cvCreateTrackbar("VH","CAM_VIEW_WIPRO",&VH,255);
	cvCreateTrackbar("HL","CAM_VIEW_WIPRO",&HL,179);
	cvCreateTrackbar("SL","CAM_VIEW_WIPRO",&SL,255);
	cvCreateTrackbar("VL","CAM_VIEW_WIPRO",&VL,255);
    CvCapture* c;
	IplImage* p;
	IplImage* p1;
	
	cvNamedWindow("TRAIN_IMAGE_WIPRO",CV_WINDOW_AUTOSIZE);
	c=cvCreateCameraCapture(0);
	if(c==NULL)
	{
		printf("NO RECORDING DEVICES PRESENT");
		getch();
	}
    p=cvQueryFrame(c);
	p1=cvCreateImage(CvSize(cvGetSize(p)),IPL_DEPTH_8U,3);
	IplImage* p2;
	p2=cvCreateImage(CvSize(cvGetSize(p)),IPL_DEPTH_8U,1);
	IplImage* p3;
	p3=cvCreateImage(cvSize(20,20),IPL_DEPTH_8U,1);
    while(1)
	{
	  p1=cvQueryFrame(c);
	  cvShowImage("CAM_VIEW_WIPRO",p1);
	  cvSmooth(p,p,CV_GAUSSIAN,9,9);
      cvCvtColor(p,p1,CV_BGR2HSV);
	  //cvInRangeS(p1,cvScalar(HL,SL,VL),cvScalar(HH,SH, VH),p2);
	  cvInRangeS(p1,cvScalar(HL,SL,VL),cvScalar(HH,SH, VH),p2);
	  //cvInRangeS(p1,cvScalar(83,65,0),cvScalar(138,255, 187),p2);

	  cvShowImage("TRAIN_IMAGE_WIPRO",p2);
	  char ch=cvWaitKey(30);
	  if(ch==27)
		  break;
	  else if(ch==13)
	  {
		  printf("Saving%d ", cnt++);
		  cvResize(p2,p3);
		  sprintf(buf,"C:/temp/test%d.jpg",i++);
		  cvSaveImage(buf,p3);

		  p3=cvLoadImage(buf);

int image[401];
		  image[0] = 1;
		  int pixel = 1; // 1st element always and already set to 1

		  Mat mat(p3);
          //printf("mat: %d \t %d \n", mat.rows, mat.cols);

		  for(int i=0;i<mat.rows;i++)
		  {
			  for(int j=0;j<mat.cols;j++)
			  {
				  if(mat.at<cv::Vec3b>(i,j)==cv::Vec3b(255,255,255))
				  {	 // printf("if1if ");
					image[pixel++] =1;
				  }
				  else// if(mat.at<cv::Vec3b>(i,j)==cv::Vec3b(0,0,0))
				  {	 // printf("else0else ");
					image[pixel++] =0;
				  }

			  }
			 // printf("\n");
		  }
	      //printf("...7 image Array created\n");
	//for (int n = 0; n <401; n++)
		//printf(" %d ", image[n]);


		  cvReleaseImage(&p3);
		  p3=cvCreateImage(cvSize(20,20),IPL_DEPTH_8U,1);
		  //cvSaveImage(buf,p3);
		  
	  }
	  //cnt++;
	}
	cvReleaseCapture(&c);
	cvReleaseImage(&p);
	cvReleaseImage(&p1);
	cvReleaseImage(&p2);
	cvReleaseImage(&p3);
	cvDestroyWindow("CAM_VIEW_WIPRO");
	cvDestroyWindow("TRAIN_IMAGE_WIPRO");
}    