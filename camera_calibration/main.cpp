#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

string image_file = "/home/acptek/CLionProjects/Undistort/distorted.jpg";

int main() {
    // 畸变参数
    //double k1 = -0.28340811, k2 = 0.07395907, p1 = 0.00019359, p2 = 1.76187114e-05;
    double k1 = 3.1034798426584559e-01, k2 = -2.0786957426704977e+00, k3 = -1.0609337486972263e-04,
    p1 = 8.9378670231977356e-04, p2 = 4.5757692246876669e+00;
    // 相机内参
    //double fx = 458.654, fy = 457.296, cx = 367.215, cy = 248.375;
    double fx =  5.2613206736361440e+02, fy = 5.2613206736361440e+02, cx = 3.2098890050291874e+02, cy = 2.4713409435784283e+02;

    Mat image = imread(image_file, 0);

    int rows = image.rows, cols = image.cols;
    Mat image_undistort = Mat(rows*2, cols*2, CV_8UC1);

    for(int v = 0; v < rows*2; v++){
        for(int u = 0; u < cols*2; u++){
            double x = (u - cx)/fx, y = (v - cy)/fy; // X/Z , Y/Z -> 归一化坐标 （X/Z Y/Z 1）-> 映射到二维 -> (x y) -> 写成极坐标形式 （r theta）
            double r = sqrt(x*x + y*y); // 极坐标 长度
            double x_distorted = x * (1 + k1*r*r + k2*r*r*r*r) + 2*p1*x*y + p2*(r*r + 2*x*x);
            double y_distorted = y * (1 + k1*r*r + k2*r*r*r*r) + p1*(r*r + 2*y*y) + 2*p2*x*y;
            double u_distort = fx * x_distorted + cx;
            double v_distort = fy * y_distorted + cy;

            // 最邻近插值直接赋值
            if (u_distort >= 0 && v_distort >= 0 && u_distort < cols && v_distort < rows){
                image_undistort.at<uchar>(v, u) = image.at<uchar>((int) v_distort, (int) u_distort);
            } else {
                image_undistort.at<uchar>(v, u) = 255;
            }
        }
    }

    imshow("distorted", image);
    imshow("undistorted", image_undistort);

    waitKey(0);

    return 0;
}