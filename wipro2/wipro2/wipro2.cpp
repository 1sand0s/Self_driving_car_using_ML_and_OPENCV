#include<conio.h>
#include<opencv\cv.h>
#include<opencv\cvaux.h>
#include<opencv\cxcore.h>
#include<opencv\highgui.h>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
void main(char* arg,int arnc[])
{
	int HH,SH,VH,HL,SL,VL,i;
	i=0;
	char buf[1000];
	cvCreateTrackbar("HH","CAM_VIEW_WIPRO",&HH,179);
	cvCreateTrackbar("SH","CAM_VIEW_WIPRO",&SH,255);
	cvCreateTrackbar("VH","CAM_VIEW_WIPRO",&VH,255);
	cvCreateTrackbar("HL","CAM_VIEW_WIPRO",&HL,179);
	cvCreateTrackbar("SL","CAM_VIEW_WIPRO",&SL,255);
	cvCreateTrackbar("VL","CAM_VIEW_WIPRO",&VL,255);
    CvCapture* c;
	IplImage* p;
	IplImage* p1;
	cvNamedWindow("CAM_VIEW_WIPRO",CV_WINDOW_AUTOSIZE);
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
	CvSeq* q;
	CvSeq* contours=0;
	float* pxy;
	CvMemStorage* sto;
	CvMemStorage* sto1;
    while(1)
	{
	  p1=cvQueryFrame(c);
	  cvShowImage("CAM_VIEW_WIPRO",p1);
	  cvSmooth(p,p,CV_GAUSSIAN,9,9);
      cvCvtColor(p,p1,CV_BGR2HSV);
	  sto=cvCreateMemStorage(0);
	  sto1=cvCreateMemStorage(0);
	  cvInRangeS(p1,cvScalar(83,65,0),cvScalar(138,255,187),p2);
	  
	  cvShowImage("TRAIN_IMAGE_WIPRO",p2);
	  char ch=cvWaitKey(30);
	  if(ch==27)
		  break;
	  else if(ch==13)
	  {
		  printf("Saving");
		  cvResize(p2,p3);
		  sprintf(buf,"C:/ml_pgms/wipro_ml/trainingSet/test%d.jpg",i++);
		  cvSaveImage(buf,p3);
		  
	  }
	}
	cvReleaseCapture(&c);
	cvReleaseImage(&p);
	cvReleaseImage(&p1);
	cvReleaseImage(&p2);
	cvReleaseImage(&p3);
	cvDestroyWindow("CAM_VIEW_WIPRO");
	cvDestroyWindow("TRAIN_IMAGE_WIPRO");
}