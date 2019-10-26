#include <iostream>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <chrono>

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
    if(argc != 3) return 1;
    Mat img_1 = imread(argv[1], CV_LOAD_IMAGE_COLOR); //CV_LOAD_IMAGE_COLOR 将输入的图片转为三通道
    Mat img_2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);
    assert(img_1.data != nullptr && img_2.data != nullptr);

    // init
    vector<KeyPoint> keypoints_1, keypoints_2; //OpenCV中关键点类型：pt,size,angle,response,octacv,classid
    Mat descriptors_1, descriptors_2;
    Ptr<FeatureDetector> detector = ORB::create(); //特征检测的智能指针，特征点
    Ptr<DescriptorExtractor> descriptor = ORB::create(); //描述子
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming(2)");

    // 1 检测O-FAST角点位置
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    detector->detect(img_1, keypoints_1);
    detector->detect(img_2, keypoints_2);

    // 2 计算BRIEF描述子
    descriptor->compute(img_1, keypoints_1, descriptors_1);
    descriptor->compute(img_2, keypoints_2, descriptors_2);
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << " 提取时间 ： " << time_used.count() <<endl;

    Mat outimg1;
    drawKeypoints(img_1, keypoints_1, outimg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    imshow("ORB features", outimg1);

    // 3 匹配
    vector<DMatch> matches;
    t1 = chrono::steady_clock::now();
    matcher->match(descriptors_1, descriptors_2, matches);
    t2 = chrono::steady_clock::now();
    time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "ORB匹配时间 ： " << time_used.count() << endl;

    // 4 匹配对筛选
    auto min_max = minmax_element(matches.begin(), matches.end(),
            [](const DMatch &m1, const DMatch &m2){ return m1.distance < m2.distance; });
    //使用了 lambda表达式 是一个匿名函数，是对汉明距离的筛选（个数差异）
    double min_dist = min_max.first->distance;
    double max_dist = min_max.second->distance;

    printf("-- 最大距离 ： %f\n", max_dist);
    printf("-- 最小距离 ： %f\n", min_dist);

    // 控制匹配误差
    vector<DMatch> good_matches;
    for(int i = 0; i < descriptors_1.rows; ++i){
        if(matches[i].distance <= max(2 * min_dist, 30.0)){
            good_matches.push_back(matches[i]);
        }
    }

    // 绘制结果
    Mat img_match;
    Mat img_goodmatch;
    drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_match);
    drawMatches(img_1, keypoints_1, img_2, keypoints_2, good_matches, img_goodmatch);

    imshow("all matches", img_match);
    imshow("good matches", img_goodmatch);
    waitKey(0);

    return 0;
}