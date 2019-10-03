//
// Created by acptek on 2019/10/3.
//

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#define Width 1000
using namespace cv;

const int ChessSize = 7;
const int SingleSize = 100;
const Point Start = Point(150, 150);

int main()
{
    Mat ChessImage = Mat(Width, Width, CV_8UC3, Scalar(255, 255, 255));

    //rectangle(ChessImage, Point(50, 50), Point(100, 100), Scalar(255, 255, 0), -1);
    for(int i = 0; i < ChessSize; i++){
        for(int j = 0; j < ChessSize; j++){
            if(!((i+j)%2)) rectangle(ChessImage, Point(Start.x+i*SingleSize, Start.y+j*SingleSize),
                                     Point(Start.x+(i+1)*SingleSize-1, Start.y+(j+1)*SingleSize-1),
                                     Scalar(0, 0, 0), -1);
        }
    }

    rectangle(ChessImage, Start, Point(Start.x + ChessSize*SingleSize-1, Start.y + ChessSize*SingleSize-1),
              Scalar(0,0,0), 1);

    imshow("Chess", ChessImage);
    waitKey( 0 );

    return 0;
}