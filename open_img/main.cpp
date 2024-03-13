#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core.hpp>
#include <cmath>

int main(int argc, char **argv) {
    cv::Mat image = cv::imread("../img.jpg");
    cv::imshow("image ", image);
    cv::waitKey();
}