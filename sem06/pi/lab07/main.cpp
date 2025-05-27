#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat dilate(const Mat& src, const Mat& kernel);
Mat erode(const Mat& src, const Mat& kernel);
Mat applyMorphSequence(const Mat& src, const Mat& kernel, const string& sequence);
Mat opening(const Mat& src, const Mat& kernel);
Mat closing(const Mat& src, const Mat& kernel);
Mat extractContour(const Mat& src, const Mat& kernel);

int main() {
    Mat img = imread("../Images/1_Dilate/mon1thr1_bw.bmp", 0);
    imshow("original", img);
    Mat kernel4 = (Mat_<uchar>(3, 3) <<
        0, 1, 0,
        1, 1, 1,
        0, 1, 0);

    string input;
    cin >> input;

    Mat newimg = applyMorphSequence(img, kernel4, input);
    imshow("newimg", newimg);
    waitKey();
    return 0;
}

Mat dilate(const Mat& src, const Mat& kernel) {
    Mat result = Mat::ones(src.size(), src.type()) * 255;

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            if (src.at<uchar>(i, j) == 0) {
                for (int ki = -kernel.rows/2; ki <= kernel.rows/2; ki++) {
                    for (int kj = -kernel.cols/2; kj <= kernel.cols/2; kj++) {
                        if (ki + i >= 0 && ki + i < src.rows &&
                            kj + j >= 0 && kj + j < src.cols) {
                            if (kernel.at<uchar>(ki + kernel.rows/2, kj + kernel.cols/2) > 0) {
                                result.at<uchar>(i + ki, j + kj) = 0;
                            }
                        }
                    }
                }
            }
        }
    }

    return result;
}

Mat erode(const Mat& src, const Mat& kernel) {
    Mat result = Mat::ones(src.size(), src.type()) * 255;

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            if (src.at<uchar>(i, j) > 0) continue;

            bool keepAsObject = true;

            for (int ki = -kernel.rows/2; ki <= kernel.rows/2 && keepAsObject; ki++) {
                for (int kj = -kernel.cols/2; kj <= kernel.cols/2 && keepAsObject; kj++) {
                    if (kernel.at<uchar>(ki + kernel.rows/2, kj + kernel.cols/2) == 0)
                        continue;

                    if (ki + i < 0 || ki + i >= src.rows || kj + j < 0 || kj + j >= src.cols) {
                        keepAsObject = false;
                        continue;
                    }

                    if (src.at<uchar>(i + ki, j + kj) > 0) {
                        keepAsObject = false;
                    }
                }
            }

            if (keepAsObject) {
                result.at<uchar>(i, j) = 0;
            }
        }
    }

    return result;
}

Mat applyMorphSequence(const Mat& src, const Mat& kernel, const string& sequence) {
    Mat result = src.clone();
    Mat temp;

    for (char op : sequence) {
        switch (op) {
            case 'e':
            temp = erode(result, kernel);
            temp.copyTo(result);
            break;

            case 'd':
            temp = dilate(result, kernel);
            temp.copyTo(result);
            break;

            case 'o':
            temp = opening(result, kernel);
            temp.copyTo(result);
            break;

            case 'c':
            temp = closing(result, kernel);
            temp.copyTo(result);
            break;

            case 'b':
            temp = extractContour(result, kernel);
            temp.copyTo(result);
            break;

            default:
                cerr << "Warning: Unknown operation '" << op << "', skipping." << endl;
            break;
        }
    }

    return result;
}

Mat opening(const Mat& src, const Mat& kernel) {
    Mat eroded = erode(src, kernel);

    Mat result = dilate(eroded, kernel);

    return result;
}

Mat closing(const Mat& src, const Mat& kernel) {
    Mat dilated = dilate(src, kernel);

    Mat result = erode(dilated, kernel);

    return result;
}

Mat extractContour(const Mat& src, const Mat& kernel) {
    Mat eroded = erode(src, kernel);

    Mat result = Mat::ones(src.size(), src.type()) * 255;

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            if (src.at<uchar>(i, j) == 0 && eroded.at<uchar>(i, j) == 255) {
                result.at<uchar>(i, j) = 0;
            }
        }
    }

    return result;
}