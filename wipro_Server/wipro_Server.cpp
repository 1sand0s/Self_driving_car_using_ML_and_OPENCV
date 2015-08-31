#include <stdio.h>
#include <math.h>

//libusb libs
#include <libusb.h>

// opencv libs
#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// user libs
#include "all_theta.h"

#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
double epsilon = 1e-6;
bool double_equal(double a, double b)
{
    if (fabs(a-b) < epsilon)
        return true;
    return false; 
}

int commonProcessing(int cnt, char *buf, IplImage* p2, IplImage* p3, char mode);
int transferIn(unsigned char data);
int transferOut();

//----------------------------------------------------------------------
using namespace std;
using namespace cv;
int main(int argc, char **argv)
{
   
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("------- Welcome to the AID Car ---------");

    int sockfd, newsockfd, portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
   
  
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0)
      {
      perror("ERROR opening socket");
      exit(1);
      }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 5001;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
 
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
      {
      perror("ERROR on binding");
      exit(1);
      }
      
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
   if (newsockfd < 0)
      {
      perror("ERROR on accept");
      exit(1);
      }
   
   /* If connection is established then start communicating */
   
      
   
}
    

    printf("\n\n\n");
    printf("...1 In main\n");

	int HH,SH,VH,HL,SL,VL;	
	char buf[1000];
    printf("theta0=%g \n", all_theta0[0]);


//--------------------- OpenCV ------------------


//	cvNamedWindow("CAM_VIEW_WIPRO",CV_WINDOW_AUTOSIZE); ... corsp destroyWindow()  present below

	//cvCreateTrackbar("HH","CAM_VIEW_WIPRO",&HH,179);
	//cvCreateTrackbar("SH","CAM_VIEW_WIPRO",&SH,255);
	//cvCreateTrackbar("VH","CAM_VIEW_WIPRO",&VH,255);
	//cvCreateTrackbar("HL","CAM_VIEW_WIPRO",&HL,179);
	//cvCreateTrackbar("SL","CAM_VIEW_WIPRO",&SL,255);
	//cvCreateTrackbar("VL","CAM_VIEW_WIPRO",&VL,255);

	CvCapture* c;
	IplImage* p;
	IplImage* p1;
	
	cvNamedWindow("TRAIN_IMAGE_WIPRO",CV_WINDOW_AUTOSIZE);

    printf("...2 Creating Camera Capture\n");

	c=cvCreateCameraCapture(0);
	
	
	if(c==NULL)
	{
		printf("NO RECORDING DEVICES PRESENT");
		//getch();
	}
    p=cvQueryFrame(c);
	p1=cvCreateImage(CvSize(cvGetSize(p)),IPL_DEPTH_8U,3);
	IplImage* p2;
	p2=cvCreateImage(CvSize(cvGetSize(p)),IPL_DEPTH_8U,1);
	IplImage* p3;
	p3=cvCreateImage(cvSize(20,20),IPL_DEPTH_8U,1);

    printf("...3 Entering While loop\n");


//------------------------ CAR STARTUP ------------------------------------

    int mode = 999;
    int modeLast = 999;

    
    printf("Enter the mode in which the car must work\n");
    //printf(" 'a' for automatic, 'm' for manual, 't' for testing/debugging\n"); 
   // mode=cvWaitKey(10000);
    int once=0;
    // @ show a message sayinng which mod it's in ... display on ulk? mode - truning descision
    int actuatemotors=-1;

    /*
    ASCII Values: 
    a = 97 
    c = 99
    m = 109
    t = 116
    esc = 27
    space = 32
    */

    int cnt=0;
    int counter=0;
        while(1)
	    {
          printf("...4 Upcounter: %d\n", counter++);
	      p1=cvQueryFrame(c);
	      cvShowImage("CAM_VIEW_WIPRO",p1);
	      cvSmooth(p,p,CV_GAUSSIAN,9,9);
          	  cvCvtColor(p,p1,CV_BGR2HSV);
	      //cvInRangeS(p1,cvScalar(HL,SL,VL),cvScalar(HH,SH, VH),p2);
	      //cvInRangeS(p1,cvScalar(HL,SL,VL),cvScalar(HH,SH, VH),p2);
	      
	      cvInRangeS(p1,cvScalar(0,0,0),cvScalar(179,254, 70),p2);
	      cvShowImage("TRAIN_IMAGE_WIPRO",p2);
	      
	      if (once) // skips to take the reading during the first loop
	      {mode = cvWaitKey(100);
	        if(mode == -1)//&& mode != 't')...fixed by setting modeLast 't' to 'T'
	        {
	            mode = modeLast;
	            printf("Current mode of opperation: %c \n", modeLast);     // If no new key is pressed, continus with the  Last mode of opperation	  
		    }
	      	printf("...4.5 after waitkey\n"); // was at 30ms
          	}
          	once = 1;
bzero(buffer,256);
   n = read( newsockfd,buffer,255 );
   
   if (n < 0)
      {
      perror("ERROR reading from socket");
      exit(1);
      }
   
  
            if(buffer[0]=='m')
            {
                transferIn('m'); // mode
                transferIn('n'); // direction - none
                
                // accept confirmation character from ulk even w/o actuation
                char noActuateMotors = transferOut();
                    
                modeLast = 'm';
            }
            else if(buffer[0]=='t')
            {
                commonProcessing(cnt, buf, p2, p3, 't');
                //mode = 'T'; // Thus this block gets activated if and only if 't' is pressed again
                  
                //common process beginning
                //common process ending
                  
                actuatemotors = transferOut();
                  
                modeLast = 'T'; //....so that it doesn't behve the same as 'a'
            }
     		else if(buffer[0]=='a')
            {

                pthread_create(thread,NULL,commonProcessing(cnt, buf, p2, p3, 'a'),NULL);
                actuatemotors = transferOut();    
                modeLast = 'a';
            }
     	    else if(buffer[0]==27) // escape = emergency exit/close the application
          	break;
	       
	       printf("Here is the message: %s\n",buffer);
   
  
   n = write(newsockfd,"I got your message",18);
   
   if (n < 0)
      {
      perror("ERROR writing to socket");
      exit(1);
      }
         
              
    


	    if(actuatemotors == 'c')
	    {
		    printf("ACTUATION COMPLETE \n");
	    }
	    else
	    printf("DIDN'T actuate: %d \n", actuatemotors);

	    } // end of while


    printf("...8 Exited the while\n");

    cvReleaseCapture(&c);
    cvReleaseImage(&p);
    cvReleaseImage(&p1);
    cvReleaseImage(&p2);
    cvReleaseImage(&p3);
    //cvDestroyWindow("CAM_VIEW_WIPRO");
    cvDestroyWindow("TRAIN_IMAGE_WIPRO");

    return 0;

}




//------------------------- COMMON PROCESSING ------------


int commonProcessing(int cnt, char *buf, IplImage* p2, IplImage* p3, char mode)
{
        //common process beginning
          //printf("Saving%d ", cnt++);
		  cvResize(p2,p3);
		  sprintf(buf,"/home/linux/Downloads/wipro/opencv-2.4.9/mystuff/images/realImg%d.jpg",cnt++);
          //printf("%s\n", buf);
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


//------------------- Machine Learning ----------------------------


// multiply and calc max
        double result[] = { 0, 0, 0 };
        double mult0[401];
        double mult1[401];
        double mult2[401];
        for (int i = 0; i<401; i++)
        { 
             mult0[i] = image[i]*all_theta0[i];
             mult1[i] = image[i]*all_theta1[i];
             mult2[i] = image[i]*all_theta2[i];
        }
        
        for (int j = 0; j<401; j++)
        {
            result[0] = result[0] + mult0[j];
            result[1] = result[1] + mult1[j];
            result[2] = result[2] + mult2[j];     
        }
        printf("probabilities: %g, %g, %g; ", result[0], result[1], result[2]);  
        
        // sigmoid
        result[0] = 1.0/(1.0 + exp(-result[0]));
        result[1] = 1.0/(1.0 + exp(-result[1]));
        result[2] = 1.0/(1.0 + exp(-result[2]));
        
// send result using libusb

        double max1 = std::max(result[0], result[1]);
        double prediction = std::max(max1, result[2]);
        printf("prediction: %g\n", prediction);
               
        // set the data that has to be sent

        unsigned char data = 'x';
        if (double_equal(result[0], prediction))
            data ='l';
        else if (double_equal(result[1], prediction))
            data = 's';
        else if (double_equal(result[2], prediction))
            data = 'r';
            
        printf ("Direction: %c %c %c %c %c %c %c %c %c %c \n\n", data,data,data,data,data,data,data,data,data,data);

//----------------- Libusb ------------------

    transferIn(mode);
    transferIn(data);
    
    

//-------------------------------------------------

	 printf("\n");
		  cvReleaseImage(&p3);
		  p3=cvCreateImage(cvSize(20,20),IPL_DEPTH_8U,1);
		  //cvSaveImage(buf,p3);

		  
		  //common process ending
		  
	     return 0;
}





//--------------------------- TRANSFER IN -----------------------
int transferIn(unsigned char data)
{   printf(" ...TransferIn()... \n");
    //printf("....0 entered into transferIn \n");
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_device_handle *dev_handle; //a device handle
    libusb_context *ctx = NULL; //a libusb session

    int r; //for return values
    ssize_t cnt; //holding number of devices in list
	//printf(" ....1 Part Init\n");	
	
    r = libusb_init(&ctx); //initialize the library for the session we just declared
    if(r < 0) {
        printf("Init Error %d ", r); //there was an error
        return 1;
    }

    libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation
	//printf("....2 get dev list \n");

    cnt = libusb_get_device_list(ctx, &devs); //get the list of devices
    if(cnt < 0) {
        printf("Get Device Error\n"); //there was an error
        return 1;
    }
    //printf("%zd Devices in list ", cnt);
	//printf("....3 geting particular handle \n");
 
//******CHANGE Vid and Pid as Required ***********
// HP: 1008, 21255  QinHeng: 6790, 29987
    dev_handle = libusb_open_device_with_vid_pid(ctx, 6790, 29987); //these are vendorID and productID I found for my usb device
    if(dev_handle == NULL)
        printf("Cannot open device\n");
    else
        printf("Device Opened\n");
	//printf("....4 got/not got the device\n");

    libusb_free_device_list(devs, 1); //free the list, unref the devices in it
	//printf("....5 device list freed, data created, checking if kernel driver is active \n");

    int actual; //used to find out how many bytes were written
    if(libusb_kernel_driver_active(dev_handle, 0) == 1) { //find out if kernel driver is attached
        //printf("Kernel Driver Active\n");
        if(libusb_detach_kernel_driver(dev_handle, 0) == 0) //detach it
            ;//printf("Kernel Driver Detached!\n");
            
    }
	//printf("....6 Claiming interface\n");

    r = libusb_claim_interface(dev_handle, 0); //claim interface 0 (the first) of device (mine had jsut 1)
    if(r < 0) {
        printf("Cannot Claim Interface\n");
        return 1;
    }
    printf("Claimed Interface\n");
	//printf("....7 Interface claimed. Will write shortly \n");

	int pr =0;
	printf("Data-> %c <- \n", data);
	//printf("Writing Data to device...");

    r = libusb_bulk_transfer(dev_handle, (2 | LIBUSB_ENDPOINT_OUT), &data, 1, &actual, 0); //my device's out endpoint was 2, found with trial- the device had 2 endpoints: 2 and 129
    if(r == 0 && actual == 1)///data length //we wrote the 4 bytes successfully
        ;//printf("Writing Successful!\n");
    else
        printf("Write Error\n");
	//printf("....8 Writing Phase Over, releasing all interfaces\n");
     
    r = libusb_release_interface(dev_handle, 0); //release the claimed interface
	if(r!=0) {
        printf("Cannot Release Interface\n");
        return 1;
    }
    printf("Released Interface\n");
    
	libusb_close(dev_handle); //close the device we opened
    libusb_exit(ctx); //needs to be called to end the
    //delete[] data; //delete the allocated memory for data
    
	printf("....9 Releasing Phase over\n");
	
	return 0;
    
}


//----------------------TRANSFER OUT -----------
int transferOut() 
{   
    printf(" ...TransferOut()... \n");	
    //printf("entered into transfer \n");
	   libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_device_handle *dev_handle; //a device handle
    libusb_context *ctx = NULL; //a libusb session

    int r; //for return values
    ssize_t cnt; //holding number of devices in list
	//printf(" ....1 Part Init\n");	
    r = libusb_init(&ctx); //initialize the library for the session we just declared

    if(r < 0) 
    {
        printf("Init Error %d ", r); //there was an error
        return -1;
    }
    libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation
	//printf("....2 get dev list \n");
    cnt = libusb_get_device_list(ctx, &devs); //get the list of devices
    if(cnt < 0) 
    {
        printf("Get Device Error\n"); //there was an error
        return -1;
    }

    //printf("%zd Devices in list ", cnt);
	//printf("....3 geting particular handle \n");
 
//******CHANGE Vid and Pid as Required ***********
// HP: 1008, 21255  QinHeng: 6790, 29987
    dev_handle = libusb_open_device_with_vid_pid(ctx, 6790, 29987); //these are vendorID and productID I found for my usb device
    if(dev_handle == NULL)
        printf("Cannot open device\n");
    else
        //printf("Device Opened\n");
	//printf("....4 got/not got the device\n");
    libusb_free_device_list(devs, 1); //free the list, unref the devices in it
//-------------------------------------------------------------------------------

//              REMOVE DATA DECLARATIONS

//----------------------------------------------------------------------------------

	//printf("....5 device list freed, data created, checking if kernel driver is active \n");

    int actual; //used to find out how many bytes were readten
    if(libusb_kernel_driver_active(dev_handle, 0) == 1)
    { //find out if kernel driver is attached
        //printf("Kernel Driver Active\n");
        if(libusb_detach_kernel_driver(dev_handle, 0) == 0) //detach it
            ;//printf("Kernel Driver Detached!\n");
    }
	//printf("....6 Claiming interface\n");
    r = libusb_claim_interface(dev_handle, 0); //claim interface 0 (the first) of device (mine had jsut 1)
    if(r < 0)
    {
        printf("Cannot Claim Interface\n");
        return -1;
    }
    //printf("Claimed Interface\n");
	//printf("....7 Interface claimed. Will read shortly \n");
//----------------------------------------------------------------------------	
	printf("Reading Data to device...");
	unsigned char data[1];
    r = libusb_bulk_transfer(dev_handle, (2 | LIBUSB_ENDPOINT_IN), data, 1, &actual, 0); //my device's out endpoint was 2, found with trial- the device had 2 endpoints: 2 and 129 ...... data OR &data, actual OR &actual
    int pr=0;
    if(r == 0 && actual == 1)///data length //we read the bytes successfully
    {
        printf("Reading Successful!\n");
	    printf("\nData-> ");//just to see the data we want to read : abcd
        for (pr=0; pr<actual; pr++)///actual data lentgth read
        printf(" %c ", data[pr]); 
    	printf(" <- \n");
	}
	  	
	else
	 {
        printf("Not fully read, amount read: \n");
        
        printf("\nData-> ");//just to see the data we want to read : abcd
        for (pr=0; pr<actual; pr++)///actual data lentgth read
	        printf(" %c ", data[pr]); 
    	printf(" <- \n");
    }
//-------------------------------------------------------------------------------
	//printf("....8 Reading Phase Over, releasing all interfaces\n");
    r = libusb_release_interface(dev_handle, 0); //release the claimed interface
	if(r!=0) {
        printf("Cannot Release Interface\n");
        return -1;
    }
    printf("Released Interface\n");
	libusb_close(dev_handle); //close the device we opened
    libusb_exit(ctx); //needs to be called to end the
    //delete[] data; //delete the allocated memory for data
	//printf("....9 Releasing Phase over\n");
	
	return 99; // returning the character 'c' for 'confirm' motor actuation
}
