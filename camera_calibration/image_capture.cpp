//
// Created by acptek on 2019/10/4.
//

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <time.h>
using namespace cv;
using namespace std;

int main()
{

    VideoCapture capture;
    Mat frame;

    capture.open("http://admin:123@172.30.223.71:8081");

    while (true)
    {
        capture >> frame;
        imshow("Current Video", frame);

        char key = waitKey(24);
        if(key == 'Q' || key == 'q') break;
        if(key == 'C' || key == 'c'){
            string s = to_string(time(0));
            Mat img;
            cvtColor(frame, img, COLOR_BGR2GRAY);
            imwrite("/home/acptek/CLionProjects/Calibration/images/image" + s + ".jpg", img );
            cout << s + ".jpg" <<endl;
        }

    }
    return 0;
}