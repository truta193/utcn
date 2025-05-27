#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat applyMedianFilter(const Mat& src, int windowSize);
Mat applyGaussianFilter(const Mat& src, int windowSize);
Mat applySeparableGaussianFilter(const Mat& src, int windowSize);

int main()
{
    Mat img = imread("../imagini_zgomot/portrait_Salt&Pepper1.bmp", IMREAD_GRAYSCALE);
    imshow("original", img);
    imshow("median_3", applyMedianFilter(img, 3));
    imshow("median_5", applyMedianFilter(img, 5));
    imshow("median_7", applyMedianFilter(img, 7));
    imshow("gaussian_3", applyGaussianFilter(img, 3));
    imshow("gaussian_5", applyGaussianFilter(img, 5));
    imshow("gaussian_7", applyGaussianFilter(img, 7));
    imshow("gaussian_separable_3", applySeparableGaussianFilter(img, 3));
    imshow("gaussian_separable_5", applySeparableGaussianFilter(img, 5));
    imshow("gaussian_separable_7", applySeparableGaussianFilter(img, 7));
    waitKey();
    return 0;
}

Mat applyMedianFilter(const Mat& src, int windowSize) {
    if (windowSize % 2 == 0) {
        windowSize += 1;
    }

    Mat dst = src.clone();

    int halfWindow = windowSize / 2;

    double startTime = (double)getTickCount();

    for (int y = halfWindow; y < src.rows - halfWindow; y++) {
        for (int x = halfWindow; x < src.cols - halfWindow; x++) {
            vector<uchar> neighborhood;

            for (int j = -halfWindow; j <= halfWindow; j++) {
                for (int i = -halfWindow; i <= halfWindow; i++) {
                    neighborhood.push_back(src.at<uchar>(y + j, x + i));
                }
            }

            sort(neighborhood.begin(), neighborhood.end());

            dst.at<uchar>(y, x) = neighborhood[neighborhood.size() / 2];
        }
    }

    double processingTime = ((double)getTickCount() - startTime) / getTickFrequency() * 1000;
    cout << "Median filter processing time (" << windowSize << "x" << windowSize << "): "
         << processingTime << " ms" << endl;

    return dst;
}

Mat applyGaussianFilter(const Mat& src, int windowSize) {
    if (windowSize % 2 == 0) {
        windowSize += 1;
    }

    double sigma = windowSize / 6.0;

    Mat dst = Mat::zeros(src.size(), src.type());

    double startTime = (double)getTickCount();

    Mat kernel = Mat::zeros(windowSize, windowSize, CV_64F);

    int center = windowSize / 2;

    double sum = 0.0;

    // Fill kernel with Gaussian values
    for (int y = 0; y < windowSize; y++) {
        for (int x = 0; x < windowSize; x++) {
            double x_squared = pow(x - center, 2);
            double y_squared = pow(y - center, 2);

            double value = (1.0 / (2.0 * M_PI * sigma * sigma)) *
                          exp(-(x_squared + y_squared) / (2.0 * sigma * sigma));

            kernel.at<double>(y, x) = value;

            sum += value;
        }
    }

    for (int y = 0; y < windowSize; y++) {
        for (int x = 0; x < windowSize; x++) {
            kernel.at<double>(y, x) /= sum;
        }
    }

    int padding = windowSize / 2;

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            double sum = 0.0;

            for (int ky = -padding; ky <= padding; ky++) {
                for (int kx = -padding; kx <= padding; kx++) {
                    int srcY = y + ky;
                    int srcX = x + kx;

                    srcY = max(0, min(srcY, src.rows - 1));
                    srcX = max(0, min(srcX, src.cols - 1));

                    uchar pixelValue = src.at<uchar>(srcY, srcX);

                    double kernelValue = kernel.at<double>(ky + padding, kx + padding);

                    sum += pixelValue * kernelValue;
                }
            }

            dst.at<uchar>(y, x) = saturate_cast<uchar>(sum);
        }
    }

    double processingTime = ((double)getTickCount() - startTime) / getTickFrequency() * 1000;
    cout << "Gaussian filter processing time (" << windowSize << "x" << windowSize <<
            "), sigma=" << sigma << ": " << processingTime << " ms" << endl;

    return dst;
}

Mat applySeparableGaussianFilter(const Mat& src, int windowSize) {
    if (windowSize % 2 == 0) {
        windowSize += 1;
    }

    double sigma = windowSize / 6.0;

    double startTime = (double)getTickCount();

    Mat kernelX = Mat::zeros(1, windowSize, CV_64F);
    int center = windowSize / 2;
    double sumX = 0.0;

    for (int x = 0; x < windowSize; x++) {
        double x_squared = pow(x - center, 2);
        double value = (1.0 / sqrt(2.0 * M_PI * sigma)) *
                       exp(-(x_squared) / (2.0 * sigma * sigma));

        kernelX.at<double>(0, x) = value;
        sumX += value;
    }

    kernelX = kernelX / sumX;

    Mat kernelY = Mat::zeros(windowSize, 1, CV_64F);
    double sumY = 0.0;

    for (int y = 0; y < windowSize; y++) {
        double y_squared = pow(y - center, 2);
        double value = (1.0 / sqrt(2.0 * M_PI * sigma)) *
                       exp(-(y_squared) / (2.0 * sigma * sigma));

        kernelY.at<double>(y, 0) = value;
        sumY += value;
    }

    kernelY = kernelY / sumY;

    Mat temp = Mat::zeros(src.size(), CV_64F);
    Mat dst = Mat::zeros(src.size(), CV_64F);

    Mat srcDouble;
    src.convertTo(srcDouble, CV_64F);

    int padding = windowSize / 2;

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            double sum = 0.0;

            for (int kx = -padding; kx <= padding; kx++) {
                int srcX = x + kx;
                srcX = max(0, min(srcX, src.cols - 1));

                double pixelValue = srcDouble.at<double>(y, srcX);
                double kernelValue = kernelX.at<double>(0, kx + padding);

                sum += pixelValue * kernelValue;
            }

            temp.at<double>(y, x) = sum;
        }
    }

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            double sum = 0.0;

            for (int ky = -padding; ky <= padding; ky++) {
                int srcY = y + ky;
                srcY = max(0, min(srcY, src.rows - 1));

                double pixelValue = temp.at<double>(srcY, x);
                double kernelValue = kernelY.at<double>(ky + padding, 0);

                sum += pixelValue * kernelValue;
            }

            dst.at<double>(y, x) = sum;
        }
    }

    Mat result;
    dst.convertTo(result, CV_8U);

    double processingTime = ((double)getTickCount() - startTime) / getTickFrequency() * 1000;
    cout << "Separable Gaussian filter time (" << windowSize << "x" << windowSize <<
            "), sigma=" << sigma << ": " << processingTime << " ms" << endl;

    return result;
}