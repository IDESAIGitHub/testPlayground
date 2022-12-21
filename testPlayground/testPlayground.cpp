// testPlayground.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "Front.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


#include <iostream>
#include <chrono>
#include <string>

std::string get_current_time_and_date()
{
    auto const time = std::chrono::current_zone()
        ->to_local(std::chrono::system_clock::now());
    return std::format("{:%Y-%m-%d %X}", time);
}

int main()
{
	std::cout << "Hello World!\n";
    cv::VideoCapture vcap;
    //mi movil sin pw(funciona)
    //const std::string videoStreamAddress = "http://192.168.0.27:8080/video";
    
    //mi movil con pw(funciona)
    const std::string videoStreamAddress = "http://rchone:1234@192.168.0.27:8080/video";
    
    //const std::string videoStreamAddress = "http://192.168.0.50:18320/video?x.mjpeg";
    // NNNhttp://USER:PWD@IPADDRESS:8088/mjpeg.cgi?user=USERNAME&password=PWD&channel=0&.mjpg
    
    //const std::string videoStreamAddress = "http://admin:admin@192.168.0.50:8080/video";
    
    //open the video stream and make sure it's opened
    if (!vcap.open(videoStreamAddress)) {
        std::cout << "\nError opening video stream or file\n";
        return -1;
    }
    cv::namedWindow("First OpenCV Application", cv::WINDOW_AUTOSIZE);
    int key = 0;
	cv::Mat frame;
	using namespace std::chrono;
	seconds sec(0);
    int num_img = 0;
    bool save_flag = true;
    while (true)
    {
		
		bool s = vcap.read(frame);
        if (!s) {
            std::cout << "Can't read";
            break;
        }
        cv::imshow("First OpenCV Application", frame);
        sec = duration_cast<seconds>(system_clock::now().time_since_epoch());
		if (sec % seconds(10) == seconds(0)) {
            if (save_flag)
            {
				save_flag = false;
                std::string save_str = "";
                num_img++;
                save_str += "SaveImages//safuu" + std::to_string(num_img) + ".jpg";
                cv::imwrite(save_str, frame);
            }
        }
        else {
            save_flag = true;
        }
        
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