#include <iostream>
#include <opencv2/opencv.hpp>
#include <queue>
#include <string>

using namespace cv;
using namespace std;

pair<Mat, Mat> getSobelKernels()
{
    Mat kernelX = (Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    Mat kernelY = (Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
    return make_pair(kernelX, kernelY);
}

Mat applyKernel(const Mat &src, const Mat &kernel)
{
    Mat result;
    filter2D(src, result, CV_32F, kernel);
    return result;
}

Mat calculateMagnitude(const Mat &gradX, const Mat &gradY)
{
    Mat magnitude = Mat::zeros(gradX.size(), CV_32F);

    for (int i = 0; i < gradX.rows; i++)
    {
        for (int j = 0; j < gradX.cols; j++)
        {
            float gx = gradX.at<float>(i, j);
            float gy = gradY.at<float>(i, j);
            magnitude.at<float>(i, j) = sqrt(gx * gx + gy * gy);
        }
    }

    return magnitude;
}

Mat calculateDirection(const Mat &gradX, const Mat &gradY)
{
    Mat direction = Mat::zeros(gradX.size(), CV_32F);

    for (int i = 0; i < gradX.rows; i++)
    {
        for (int j = 0; j < gradX.cols; j++)
        {
            float gx = gradX.at<float>(i, j);
            float gy = gradY.at<float>(i, j);
            direction.at<float>(i, j) = atan2(gy, gx);
        }
    }

    return direction;
}

Mat applyThreshold(const Mat &magnitude, float threshold)
{
    Mat result = Mat::zeros(magnitude.size(), CV_8U);

    for (int i = 0; i < magnitude.rows; i++)
    {
        for (int j = 0; j < magnitude.cols; j++)
        {
            if (magnitude.at<float>(i, j) > threshold)
            {
                result.at<uchar>(i, j) = 255;
            }
        }
    }

    return result;
}

Mat quantizeDirection(const Mat &direction)
{
    Mat quantized = Mat::zeros(direction.size(), CV_8U);

    for (int i = 0; i < direction.rows; i++)
    {
        for (int j = 0; j < direction.cols; j++)
        {
            float angle = direction.at<float>(i, j);

            float angleDeg = angle * 180.0 / CV_PI;
            if (angleDeg < 0) angleDeg += 180.0;


            if ((angleDeg >= 0 && angleDeg < 22.5) || (angleDeg >= 157.5 && angleDeg <= 180))
            {
                quantized.at<uchar>(i, j) = 0;
            } else if (angleDeg >= 22.5 && angleDeg < 67.5)
            {
                quantized.at<uchar>(i, j) = 1;
            } else if (angleDeg >= 67.5 && angleDeg < 112.5)
            {
                quantized.at<uchar>(i, j) = 2;
            } else
            {
                quantized.at<uchar>(i, j) = 3;
            }
        }
    }

    return quantized;
}

Mat nonMaximumSuppression(const Mat &magnitude, const Mat &quantizedDirection)
{
    Mat result = Mat::zeros(magnitude.size(), CV_32F);


    int neighborOffsets[4][4] = {
        {0, 1, 0, -1},
        {-1, 1, 1, -1},
        {-1, 0, 1, 0},
        {-1, -1, 1, 1}
    };

    for (int i = 1; i < magnitude.rows - 1; i++)
    {
        for (int j = 1; j < magnitude.cols - 1; j++)
        {
            uchar dir = quantizedDirection.at<uchar>(i, j);
            float mag = magnitude.at<float>(i, j);

            int dy1 = neighborOffsets[dir][0];
            int dx1 = neighborOffsets[dir][1];
            int dy2 = neighborOffsets[dir][2];
            int dx2 = neighborOffsets[dir][3];

            float mag1 = magnitude.at<float>(i + dy1, j + dx1);
            float mag2 = magnitude.at<float>(i + dy2, j + dx2);

            if (mag >= mag1 && mag >= mag2)
            {
                result.at<float>(i, j) = mag;
            }
        }
    }

    return result;
}

pair<double, double> adaptiveThreshold(const Mat &suppressed, double p = 0.1)
{
    vector<int> histogram(256, 0);
    int totalNonZero = 0;
    float maxVal = 0;

    for (int i = 0; i < suppressed.rows; i++)
    {
        for (int j = 0; j < suppressed.cols; j++)
        {
            float val = suppressed.at<float>(i, j);
            if (val > maxVal) maxVal = val;
        }
    }

    for (int i = 0; i < suppressed.rows; i++)
    {
        for (int j = 0; j < suppressed.cols; j++)
        {
            float val = suppressed.at<float>(i, j);
            if (val > 0)
            {
                int bin = min(255, (int) (val * 255.0f / maxVal));
                histogram[bin]++;
                totalNonZero++;
            }
        }
    }

    int nonEdgePixels = (int) ((1.0 - p) * totalNonZero);

    int sum = 0;
    int highThresholdBin = 0;
    for (highThresholdBin = 0; highThresholdBin < 256; highThresholdBin++)
    {
        sum += histogram[highThresholdBin];
        if (sum >= nonEdgePixels) break;
    }

    double highThreshold = highThresholdBin * maxVal / 255.0;
    double lowThreshold = 0.1 * highThreshold;

    return make_pair(lowThreshold, highThreshold);
}

Mat markEdges(const Mat &suppressed, double lowThreshold, double highThreshold)
{
    Mat result = Mat::zeros(suppressed.size(), CV_8U);

    for (int i = 0; i < suppressed.rows; i++)
    {
        for (int j = 0; j < suppressed.cols; j++)
        {
            float magnitude = suppressed.at<float>(i, j);
            if (magnitude >= highThreshold)
            {
                result.at<uchar>(i, j) = 255;
            } else if (magnitude >= lowThreshold)
            {
                result.at<uchar>(i, j) = 128;
            }
        }
    }

    return result;
}

Mat hysteresisThresholding(const Mat &markedEdges)
{
    Mat result = markedEdges.clone();
    queue<Point> strongEdgeQueue;

    for (int i = 0; i < result.rows; i++)
    {
        for (int j = 0; j < result.cols; j++)
        {
            if (result.at<uchar>(i, j) == 255)
            {
                strongEdgeQueue.push(Point(j, i));
            }
        }
    }

    int dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int dy[8] = {-1, -1, -1, 0, 1, 1, 1, 0};

    while (!strongEdgeQueue.empty())
    {
        Point current = strongEdgeQueue.front();
        strongEdgeQueue.pop();

        for (int k = 0; k < 8; k++)
        {
            int ni = current.y + dy[k];
            int nj = current.x + dx[k];


            if (ni >= 0 && ni < result.rows && nj >= 0 && nj < result.cols)
            {
                if (result.at<uchar>(ni, nj) == 128)
                {
                    result.at<uchar>(ni, nj) = 255;
                    strongEdgeQueue.push(Point(nj, ni));
                }
            }
        }
    }

    for (int i = 0; i < result.rows; i++)
    {
        for (int j = 0; j < result.cols; j++)
        {
            if (result.at<uchar>(i, j) == 128)
            {
                result.at<uchar>(i, j) = 0;
            }
        }
    }

    return result;
}

void runLab1Exercises(const Mat &image)
{
    Mat sKernelX, sKernelY;
    tie(sKernelX, sKernelY) = getSobelKernels();
    Mat sobelX = applyKernel(image, sKernelX);
    Mat sobelY = applyKernel(image, sKernelY);


    Mat displaySobelX, displaySobelY;
    normalize(sobelX, displaySobelX, 0, 255, NORM_MINMAX);
    normalize(sobelY, displaySobelY, 0, 255, NORM_MINMAX);

    displaySobelX.convertTo(displaySobelX, CV_8U);
    displaySobelY.convertTo(displaySobelY, CV_8U);


    Mat sobelMag = calculateMagnitude(sobelX, sobelY);

    Mat displaySobelMag;
    normalize(sobelMag, displaySobelMag, 0, 255, NORM_MINMAX);

    displaySobelMag.convertTo(displaySobelMag, CV_8U);

    float fixedThreshold = 100.0f;
    Mat thresholdedSobel = applyThreshold(sobelMag, fixedThreshold);


    namedWindow("Lab 1 - Original Image", WINDOW_NORMAL);
    imshow("Lab 1 - Original Image", image);

    namedWindow("Lab 1 - Sobel Magnitude", WINDOW_NORMAL);
    imshow("Lab 1 - Sobel Magnitude", displaySobelMag);

    namedWindow("Lab 1 - Sobel Thresholded", WINDOW_NORMAL);
    imshow("Lab 1 - Sobel Thresholded", thresholdedSobel);
}

void runLab2Exercises(const Mat &image)
{
    Mat blurred;
    GaussianBlur(image, blurred, Size(5, 5), 0.5);

    Mat sobelX, sobelY;
    Sobel(blurred, sobelX, CV_32F, 1, 0, 3);
    Sobel(blurred, sobelY, CV_32F, 0, 1, 3);

    Mat gradientMagnitude = calculateMagnitude(sobelX, sobelY);
    Mat gradientDirection = calculateDirection(sobelX, sobelY);

    Mat displayGradient;
    normalize(gradientMagnitude, displayGradient, 0, 255, NORM_MINMAX);
    displayGradient.convertTo(displayGradient, CV_8U);

    Mat quantizedDirection = quantizeDirection(gradientDirection);

    Mat suppressed = nonMaximumSuppression(gradientMagnitude, quantizedDirection);

    Mat displaySuppressed;
    normalize(suppressed, displaySuppressed, 0, 255, NORM_MINMAX);
    displaySuppressed.convertTo(displaySuppressed, CV_8U);

    double p = 0.1;
    double lowThreshold, highThreshold;
    tie(lowThreshold, highThreshold) = adaptiveThreshold(suppressed, p);

    Mat adaptiveBinary = Mat::zeros(suppressed.size(), CV_8U);
    for (int i = 0; i < suppressed.rows; i++)
    {
        for (int j = 0; j < suppressed.cols; j++)
        {
            if (suppressed.at<float>(i, j) >= highThreshold)
            {
                adaptiveBinary.at<uchar>(i, j) = 255;
            }
        }
    }

    Mat markedEdges = markEdges(suppressed, lowThreshold, highThreshold);
    Mat finalEdges = hysteresisThresholding(markedEdges);

    namedWindow("Lab 2 - Original Image", WINDOW_NORMAL);
    imshow("Lab 2 - Original Image", image);

    namedWindow("Lab 2 - Gaussian Blurred", WINDOW_NORMAL);
    imshow("Lab 2 - Gaussian Blurred", blurred);

    namedWindow("Lab 2 - Non-Maximum Suppression", WINDOW_NORMAL);
    imshow("Lab 2 - Non-Maximum Suppression", displaySuppressed);

    namedWindow("Lab 2 - Exercise 1: Adaptive Binarization", WINDOW_NORMAL);
    imshow("Lab 2 - Exercise 1: Adaptive Binarization", adaptiveBinary);

    namedWindow("Lab 2 - Strong and Weak Edges", WINDOW_NORMAL);
    imshow("Lab 2 - Strong and Weak Edges", markedEdges);

    namedWindow("Lab 2 - Exercise 2: Final Edges", WINDOW_NORMAL);
    imshow("Lab 2 - Exercise 2: Final Edges", finalEdges);
}

int main()
{
    Mat image = imread("../saturn.bmp", IMREAD_GRAYSCALE);
    if (image.empty())
    {
        cout << "Failed to load image!" << endl;
        return -1;
    }

    runLab1Exercises(image);
    runLab2Exercises(image);

    waitKey(0);

    return 0;
}
