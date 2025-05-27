#include <iostream>
#include <opencv2/opencv.hpp>
#include <algorithm>

using namespace std;
using namespace cv;

void negative_image(Mat img){
    for(int i=0; i<img.rows; i++){
        for(int j=0; j<img.cols; j++){
            img.at<uchar>(i,j) = 255 - img.at<uchar>(i,j);
        }
    }
    imshow("negative image",img);
}

void additive_gray(Mat img, int value){
    for(int i=0; i<img.rows; i++){
        for(int j=0; j<img.cols; j++){
            //img.at<uchar>(i,j) += value;
            img.at<uchar>(i,j) = std::min(value + img.at<uchar>(i,j),  255);
        }
    }
    imshow("gray additive image",img);
}

void multiplicative_gray(Mat img, double scalar){
    for(int i=0; i<img.rows; i++){
        for(int j=0; j<img.cols; j++){
            img.at<uchar>(i,j) = std::min(scalar * img.at<uchar>(i,j),  255.0);
        }
    }
    imwrite("img.png",img);
    imshow("gray multiplicative image",img);
}

void squares() {
    Mat matrix(256,256,CV_8UC3);

    for(int i=0; i<127; i++) {
        for(int j=0; j<127; j++) {
            matrix.at<Vec3b>(i,j)[0] = 255;
        }
    }

    for(int i=128; i<255; i++) {
        for(int j=0; j<127; j++) {
            matrix.at<Vec3b>(i,j)[1] = 255;
        }
    }

    for(int i=128; i<255; i++) {
        for(int j=128; j<255; j++) {
            matrix.at<Vec3b>(i,j)[2] = 255;
        }
    }

    for(int i=0; i<127; i++) {
        for(int j=128; j<255; j++) {
            matrix.at<Vec3b>(i,j)[2] = 100;
        }
    }

    imshow("squares image",matrix);
}

void matrix_inv() {
    Mat matrix(3,3,CV_32FC1);
    matrix.at<float>(0,0) = 5.0;
    matrix.at<float>(0,1) = 3.0;
    matrix.at<float>(0,2) = 4.0;
    matrix.at<float>(1,0) = 4.0;
    matrix.at<float>(1,1) = 6.0;
    matrix.at<float>(1,2) = 8.0;
    matrix.at<float>(2,0) = 6.0;
    matrix.at<float>(2,1) = 9.0;
    matrix.at<float>(2,2) = 7.0;

    std::cout << matrix << std::endl;

    const Mat inverse = matrix.inv();

    std::cout << inverse << std::endl;
}

int main() {
    Mat img = imread("../Imagini/saturn.bmp", IMREAD_GRAYSCALE);
    imshow("original image",img);
    //Negative
    negative_image(img);

    //Additive
    img = imread("../Imagini/saturn.bmp", IMREAD_GRAYSCALE);
    std::cout << "Enter add value: ";
    int add_value = 0;
    std::cin >> add_value;
    additive_gray(img, add_value);

    //Multiplicative
    img = imread("../Imagini/saturn.bmp", IMREAD_GRAYSCALE);
    std::cout << "Enter multiplicative value: ";
    int scalar = 0;
    std::cin >> scalar;
    multiplicative_gray(img, scalar);

    squares();

    matrix_inv();

    waitKey(0);
    return 0;
}