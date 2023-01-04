// testPlayground.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>

//#include "Front.h"
//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>


#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#include <iostream>
#include <chrono>
#include <string>

#include "zbar.h"
using namespace std::chrono;

int main()
{
    cv::namedWindow("Webcam", cv::WINDOW_AUTOSIZE);
    
    char a = 2;
    
    // open the first webcam plugged in the computer
    auto start = high_resolution_clock::now();
    cv::VideoCapture camera;
    camera.set(CAP_PROP_BUFFERSIZE, 3); // internal buffer will now store only 3 frames
    
    //my phone
    //const char* address = "http://rchone:1234@192.168.0.16:8080/video?x.mjpeg";

    //const char* address = "http://192.168.0.27:8080/video?x.mjpeg";
    //const char* address = "rtsp://admin:123456@192.168.0.27:554";
    const char* address = "http://admin:123456@192.168.0.27/video";
    if (!camera.open(address)) {
               std::cout << "\nError opening video stream or file\n";
               return -1;
    }
    auto stop = high_resolution_clock::now();
    cv::Mat frame;

	std::cin >> a;
    // display the frame until you press a key
    while (1) {
        // show the image on the window
        camera >> frame;
        cv::imshow("Webcam", frame);
        // wait (10ms) for a key to be pressed
        if (cv::waitKey(10) == 's') {
            //save image to file
			cv::imwrite("test.jpg", frame);
			break;
        }
    }
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << "\n\nTime taken by function: " << duration.count() << "milliseconds" << std::endl;
    
    return 0;
}