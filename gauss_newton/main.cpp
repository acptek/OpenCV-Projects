#include <bits/stdc++.h>
#include <Eigen/Eigen>
#include <Eigen/Core>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace Eigen;

// y = exp(ax^2 + bx + c) + w
// e = y - exp(ax^2 + bx + c)

const int CountNum = 100;
const int Iteration = 100;

double ra = 1.0, rb = 2.0, rc = 1.0;
double ea = 2.0, eb = -1.0, ec = 5.0;

double sigma = 1.0;
double inv_sigma = 1.0 / sigma;

cv::RNG gauss_rng;

int main() {

    vector<double> rx, ry; // Coordinate
    for(double i = 0; i < CountNum; ++i){
        double x = i/100.0;
        rx.push_back(x);
        ry.push_back(exp(ra*x*x + rb*x + rc) + gauss_rng.gaussian(sigma * sigma));
    }

    double cost = 0, lastcost = 0;

    for(int it = 0; it < Iteration; ++it){

        Matrix3d H = Matrix3d::Zero();
        Vector3d b = Vector3d::Zero();
        cost = 0;

        for(int i = 0; i < CountNum; ++i){
            double error = ry[i] - exp(ea*rx[i]*rx[i] + eb*rx[i] + ec);
            Vector3d J = Vector3d(-1 * rx[i] * rx[i] * exp(ea*rx[i]*rx[i] + eb*rx[i] + ec),
                                  -1 * rx[i] * exp(ea*rx[i]*rx[i] + eb*rx[i] + ec),
                                  -1 * exp(ea*rx[i]*rx[i] + eb*rx[i] + ec) );
            H += inv_sigma * inv_sigma * J * J.transpose();
            b += -inv_sigma * inv_sigma * J * error;

//            cout << "error : " << error << endl;
            cost += error * error; // 1/2 e^2
        }

        Vector3d dx = H.ldlt().solve(b);
        cout << "--> " << dx[0] << " " << dx[1] << " " << dx[2] << endl;
        // if equal -> break
        if((it > 0 && cost >= lastcost) || isnan(dx[0])){
            break;
        }
        ea += dx[0], eb += dx[1], ec += dx[2];
        lastcost = cost;
    }

    cout << ea << " " << eb << " " << ec <<endl;

    return 0;
}