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

using namespace std::chrono;

int main()
{
	std::cout << "Hello World!\n";
    cv::VideoCapture vcap;
    vcap.set(cv::CAP_PROP_BUFFERSIZE, 1); // internal buffer will now store only 3 frames
    //mi movil sin pw(funciona)
    //const std::string videoStreamAddress = "http://192.168.0.27:8080/video";
    
    //mi movil con pw(funciona)
    const std::string videoStreamAddress = "http://rchone:1234@192.168.0.16:8080/video";
    
    //pruebas
    //const std::string videoStreamAddress = "http://192.168.0.50:18320/video?x.mjpeg";
    // NNNhttp://USER:PWD@IPADDRESS:8088/mjpeg.cgi?user=USERNAME&password=PWD&channel=0&.mjpg
    
    //pruebas
    //const std::string videoStreamAddress = "rtsp://admin:admin@192.168.0.21:554/1";
    
    
    
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
    
    while (true)
    {
        auto start = high_resolution_clock::now();
		bool s = vcap.read(frame);
        if (!s) {
            std::cout << "Can't read";
            break;
        }
        cv::imshow("First OpenCV Application", frame);
        
        if (cv::waitKey(10) == 's') {
            std::string save_str = "";
            num_img++;
            save_str += "SaveImages//safuu" + std::to_string(num_img) + ".jpg";
            
            cv::imwrite(save_str, frame);
            
            auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			std::cout << "Time taken by function: "
				<< duration.count() << " microseconds" << std::endl;
            std::cout << "Bye bitch!\n";
            break;
        }

    }
    cv::destroyAllWindows();
    
    
    
    /*while (true)
    {
        auto start = high_resolution_clock::now();
        bool s = vcap.read(frame);
        if (!s) {
            std::cout << "Can't read";
            break;
        }
        if (cv::waitKey(20) == 's') {
            std::string save_str = "";
            num_img++;
            save_str += "SaveImages//safuu" + std::to_string(num_img) + ".jpg";

            cv::imwrite(save_str, frame);

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            std::cout << "Time taken by function: "
                << duration.count() << " microseconds" << std::endl;
            std::cout << "Bye bitch!\n";
            break;
        }
    }*/
    
    
    return 0;
    
    //cv::Mat img;
    //const std::string imgPath = "Images/rock.jpg";
    //img = cv::imread(imgPath, cv::IMREAD_COLOR);
    //
    //if (img.empty())
    //{
    //    std::cout << "Could not read the image: " << std::endl;
    //    return 1;
    //}
    //imshow("Display window", img);
    //int k = cv::waitKey(0); // Wait for a keystroke in the window
    //if (k == 's')
    //{
    //    imwrite("starry_night.png", img);
    //}
    
    
    ////play Black Adam Trailer
    //using namespace cv;
    //Mat frame;
    //VideoCapture cap = VideoCapture("Images//Rock.mp4");
    //if (!cap.isOpened()) {
    //    std::cout << "Error opening video stream or file\n";
    //}
    //bool finish = true;
    //while (finish)
    //{
    //    finish = cap.read(frame);
    //    cv::imshow("guapisimos", frame);
    //    if (cv::waitKey(30) == 27) {
    //        std::cout << "Bye bitch!\n";
    //        finish = false;
    //    }
    //}
    //cv::destroyAllWindows();
    

    //copilot do something!!
    
    
    return 0;
}