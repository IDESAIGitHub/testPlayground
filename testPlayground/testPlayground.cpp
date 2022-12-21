// testPlayground.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "Front.h"


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


int main()
{
    
	std::cout << "Hello World!\n";
    cv::VideoCapture vcap;
    //mi movil sin pw(funciona)
    //const std::string videoStreamAddress = "http://192.168.0.27:8080/video";
    
    //mi movil con pw(funciona)
    //const std::string videoStreamAddress = "http://rchone:1234@192.168.0.27:8080/video";
    
    //const std::string videoStreamAddress = "http://192.168.0.50:18320/video?x.mjpeg";
    // NNNhttp://USER:PWD@IPADDRESS:8088/mjpeg.cgi?user=USERNAME&password=PWD&channel=0&.mjpg
    
    
    const std::string videoStreamAddress = "http://admin:admin@192.168.0.50:8080/video";
    
    //open the video stream and make sure it's opened
    if (!vcap.open(videoStreamAddress)) {
        std::cout << "\nError opening video stream or file\n";
        return -1;
    }
    cv::namedWindow("First OpenCV Application", cv::WINDOW_AUTOSIZE);
    int key = 0;
	cv::Mat frame;
    while (true)
    {
		bool s = vcap.read(frame);
        if (!s) {
            std::cout << "Can't read";
            break;
        }
        cv::imshow("guapisimos", frame);
        
        if (cv::waitKey(30) == 27) {
            std::cout << "Bye bitch!\n";
            break;
        }
    }
    cv::destroyAllWindows();
    return 0;
    
   
    /*
    //play Black Adam Trailer
    using namespace cv;
    Mat frame;
    VideoCapture cap = VideoCapture("Images//Rock.mp4");
    if (!cap.isOpened()) {
        std::cout << "Error opening video stream or file\n";
    }
    bool finish = true;
    while (finish)
    {
        finish = cap.read(frame);
        cv::imshow("guapisimos", frame);
        if (cv::waitKey(30) == 27) {
            std::cout << "Bye bitch!\n";
            finish = false;
        }
    }
    cv::destroyAllWindows();
    */
    return 0;
}