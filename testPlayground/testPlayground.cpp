//#include <Windows.h>

//#include <opencv2/objdetect.hpp>
//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <iostream>

//using namespace cv;

using namespace std;

#include <chrono>
#include <string>
#include <vector>
using namespace std::chrono;


#include "rs232.h"
#include "rs232lib.h"
#include <Windows.h>

//int main() {
//
//	std::cout << "Hello World!\n";
//	std::vector<int> vect1{ 1, 2, 3, 4 };
//	std::vector<int> vect2;
//	std::vector<int> vect3;
//
//	vect3 = vect2;
//	
//	cout << "Vector 1 : ";
//	for (int i = 0; i < vect1.size(); i++)
//		cout << vect1[i] << " ";
//	cout << endl;
//	
//	cout << "Vector 2 : ";
//	for (int i = 0; i < vect2.size(); i++)
//		cout << vect2[i] << " ";
//	cout << endl;
//
//	cout << "Vector 3 : ";
//	for (int i = 0; i < vect3.size(); i++)
//		cout << vect3[i] << " ";
//	cout << endl;
//	
//	return 0;
//}


 //RS232 test
int main() {
	
	// Rx
 //   int cPortNr = 1; /* COM2 */
 //   int bdrate = 9600; /* 9600 baud */
 //   
	//char mode[] = { '8', 'N', '1', 0 };
	////std::string mode = "8N1";
  //  if (rs232::openComport(cPortNr, bdrate, modeStr, 0)) {
  //      printf("Can not open comport\n");

  //      return (0);
  //  }

  //  while (1) {
		//auto start = high_resolution_clock::now();
  //      n = rs232::pollComport(cPortNr, buf, bufLen - 1);

  //      if (n > 0) {
		//	auto stop = high_resolution_clock::now();
  //          buf[n] = 0; /* always put a "null" at the end of a string! */

  //          for (i = 0; i < n; i++) {
  //              if (buf[i] < 32) /* replace unreadable control-codes by dots */ {
  //                  buf[i] = '.';
  //              }
  //          }

  //          printf("received %i bytes: %s\n", n, (char*)buf);
		//	cout << "Time taken by function: "
		//		<< duration_cast<microseconds>(stop - start).count()
		//		<< " microseconds" << endl;
  //      }

  //      Sleep(10);

  //  }
	
	//test with rs232lib
	std::string port = "COM3";
	int baudrate = 9600;
	std::string mode = "7N1";
	try
	{
		rs232lib manager_COM2(port, baudrate, mode);
		while (true)
		{
			manager_COM2.write("Hello World!\n");
			Sleep(5000);
			std::string msg = manager_COM2.read();
			std::cout << msg << std::endl;

			Sleep(5000);
		}
	}
	catch (const std::exception&)
	{

	}
    return 0;
}


// OpenCV test
//int main()
//{
//    
//    // open the first webcam plugged in the computer
//    auto start = high_resolution_clock::now();
//    cv::VideoCapture camera;
//    camera.set(cv::CAP_PROP_BUFFERSIZE, 3);
//    
//    //my phone
//    const char* address = "http://rchone:1234@192.168.0.16:8080/video?x.mjpeg";
//
//
//    //ip camera tests
//    //const char* address = "rtsp://admin:123456@192.168.0.27:554/live/mpeg4";
//    //const char* address = "rtsp://admin:123456@192.168.123.123:554/live/mpeg4";
//
//    if (!camera.open(address)) {
//               std::cout << "\nError opening video stream or file\n";
//               return -1;
//    }
//    auto stop = high_resolution_clock::now();
//    cv::Mat frame;
//
//    cv::namedWindow("Webcam", cv::WINDOW_AUTOSIZE);
//	//std::cin >> a;
//    // display the frame until you press a key
//
//    
//    while (1) {
//        // show the image on the window
//        camera >> frame;
//        cv::imshow("Webcam", frame);
//        // wait (10ms) for a key to be pressed
//        if (cv::waitKey(1) == 's') {
//            //save image to file
//			//save it with the date and time as filename
//			auto now = std::chrono::system_clock::now();
//			auto in_time_t = std::chrono::system_clock::to_time_t(now);
//			std::stringstream ss;
//			ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
//			std::string s = ss.str();
//			std::replace(s.begin(), s.end(), ':', '-');
//			std::replace(s.begin(), s.end(), ' ', '_');
//			std::string filename =  s + ".jpg";
//			cv::imwrite(filename, frame);
//			break;
//        }
//    }
//    auto duration = duration_cast<milliseconds>(stop - start);
//    std::cout << "\n\nTime taken by function: " << duration.count() << "milliseconds" << std::endl;
//    
//    return 0;
//}


//barcode
//int main() {
//    std::cout << "OpenCV version : " << CV_VERSION << std::endl;
//	cv::Mat image = cv::imread("qr2.png", cv::IMREAD_GRAYSCALE);
//    cv::Mat image = cv::imread("barcode4.jpeg", cv::IMREAD_GRAYSCALE);
//    
//    cv::Ptr<cv::BarCodeReader> barcodeDecoder = cv::createBarCodeReader();
//    std::vector<cv::Point> barcodeLocations;
//    std::string data = barcodeDecoder->detectAndDecode(image, barcodeLocations);
//    if (data.length() > 0) {
//        std::cout << "Decoded data: " << data << std::endl;
//        for (auto& point : barcodeLocations) {
//            std::cout << "Barcode found at: " << point.x << ", " << point.y << std::endl;
//        }
//    }
//    else {
//        std::cout << "Barcode not detected" << std::endl;
//    }
//    
//    cv:namedWindow("Display window", cv::WINDOW_AUTOSIZE);
//    cv::imshow("Display window", image);
//    cv::waitKey(0);
//    
//    return 0;
//}