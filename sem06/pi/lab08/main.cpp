#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

void showHistogram(const Mat &image, const string &windowName)
{
    int histSize = 256;
    float range[] = {0, 256};
    const float *histRange = {range};
    Mat hist;
    calcHist(&image, 1, 0, Mat(), hist, 1, &histSize, &histRange, true, false);

    int histWidth = 512, histHeight = 400;
    Mat histImage(histHeight, histWidth, CV_8UC3, Scalar(0, 0, 0));

    normalize(hist, hist, 0, histHeight, NORM_MINMAX);

    int binWidth = cvRound((double) histWidth / histSize);
    for (int i = 0; i < histSize; i++)
    {
        rectangle(histImage,
                  Point(i * binWidth, histHeight),
                  Point((i + 1) * binWidth, histHeight - cvRound(hist.at<float>(i))),
                  Scalar(255, 255, 255), 1);
    }

    namedWindow(windowName, WINDOW_NORMAL);
    imshow(windowName, histImage);
}

void showCumulativeHistogram(const Mat &image, const string &windowName)
{
    int histSize = 256;
    float range[] = {0, 256};
    const float *histRange = {range};
    Mat hist;
    calcHist(&image, 1, 0, Mat(), hist, 1, &histSize, &histRange, true, false);

    Mat cumulativeHist = hist.clone();
    for (int i = 1; i < histSize; i++)
    {
        cumulativeHist.at<float>(i) += cumulativeHist.at<float>(i - 1);
    }

    int histWidth = 512, histHeight = 400;
    Mat histImage(histHeight, histWidth, CV_8UC3, Scalar(0, 0, 0));

    normalize(cumulativeHist, cumulativeHist, 0, histHeight, NORM_MINMAX);

    int binWidth = cvRound((double) histWidth / histSize);
    for (int i = 0; i < histSize; i++)
    {
        rectangle(histImage,
                  Point(i * binWidth, histHeight),
                  Point((i + 1) * binWidth, histHeight - cvRound(cumulativeHist.at<float>(i))),
                  Scalar(0, 255, 0), 1);
    }

    namedWindow(windowName, WINDOW_NORMAL);
    imshow(windowName, histImage);
}


void calculateImageStatistics(const Mat &image)
{
    Scalar mean, stdDev;
    meanStdDev(image, mean, stdDev);

    cout << "\nImage Statistics:" << endl;
    cout << "Mean intensity: " << mean[0] << endl;
    cout << "Standard deviation: " << stdDev[0] << endl;

    showHistogram(image, "Histogram");
    showCumulativeHistogram(image, "Cumulative Histogram");
}

double calculateAutomaticThreshold(const Mat &image, double errorThreshold = 0.1)
{
    int histSize = 256;
    float range[] = {0, 256};
    const float *histRange = {range};
    Mat hist;
    calcHist(&image, 1, 0, Mat(), hist, 1, &histSize, &histRange, true, false);

    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(image, &minVal, &maxVal, &minLoc, &maxLoc);

    double T = (minVal + maxVal) / 2.0;
    double prevT;

    do
    {
        prevT = T;

        double sum1 = 0, sum2 = 0;
        double count1 = 0, count2 = 0;

        for (int i = 0; i <= 255; i++)
        {
            float pixelCount = hist.at<float>(i);

            if (i <= T)
            {
                sum1 += i * pixelCount;
                count1 += pixelCount;
            } else
            {
                sum2 += i * pixelCount;
                count2 += pixelCount;
            }
        }

        double mean1 = (count1 > 0) ? sum1 / count1 : 0;
        double mean2 = (count2 > 0) ? sum2 / count2 : 0;

        T = (mean1 + mean2) / 2.0;
    } while (abs(T - prevT) > errorThreshold);

    cout << "Calculated threshold: " << T << endl;
    return T;
}

Mat applyBinarization(const Mat &image, double threshold)
{
    Mat binaryImage;
    cv::threshold(image, binaryImage, threshold, 255, THRESH_BINARY);

    return binaryImage;
}


Mat calculateNegative(const Mat &image)
{
    Mat result = image.clone();

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            result.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
        }
    }

    return result;
}


Mat modifyContrast(const Mat &image, int gOutMin, int gOutMax)
{
    Mat result = image.clone();
    double gInMin, gInMax;

    minMaxLoc(image, &gInMin, &gInMax);


    double ratio = (double) (gOutMax - gOutMin) / (gInMax - gInMin);

    cout << "Contrast modification:" << endl;
    cout << "Input range: [" << gInMin << ", " << gInMax << "]" << endl;
    cout << "Output range: [" << gOutMin << ", " << gOutMax << "]" << endl;
    cout << "Ratio: " << ratio << (ratio > 1 ? " (stretching)" : " (shrinking)") << endl;

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            double newVal = gOutMin + (image.at<uchar>(i, j) - gInMin) * ratio;

            result.at<uchar>(i, j) = saturate_cast<uchar>(newVal);
        }
    }

    return result;
}

Mat gammaCorrection(const Mat &image, double gamma)
{
    Mat result = image.clone();

    cout << "Gamma correction with gamma = " << gamma << endl;
    cout << (gamma < 1 ? "Gamma encoding/compression" : "Gamma decoding/decompression") << endl;

    uchar lookUpTable[256];
    for (int i = 0; i < 256; i++)
    {
        lookUpTable[i] = saturate_cast<uchar>(pow((double) i / 255.0, gamma) * 255.0);
    }

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            result.at<uchar>(i, j) = lookUpTable[image.at<uchar>(i, j)];
        }
    }

    return result;
}


Mat modifyBrightness(const Mat &image, int offset)
{
    Mat result = image.clone();

    cout << "Brightness modification with offset = " << offset << endl;

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            int newVal = image.at<uchar>(i, j) + offset;

            result.at<uchar>(i, j) = saturate_cast<uchar>(newVal);
        }
    }

    return result;
}


void showMenu()
{
    cout << "1: Calculate Image Statistics" << endl;
    cout << "2: Automatic Binarization" << endl;
    cout << "3: Negative of the Image" << endl;
    cout << "4: Modify Contrast (Stretch/Shrink)" << endl;
    cout << "5: Gamma Correction" << endl;
    cout << "6: Modify Brightness" << endl;
    cout << "0: Exit" << endl;
    cout << "Enter your choice: ";
}


int main()
{
    Mat originalImage;


    originalImage = imread("../imagini/balloons.bmp", 0);

    if (originalImage.empty())
    {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }


    Mat workingImage = originalImage.clone();

    namedWindow("Original Image", WINDOW_NORMAL);
    imshow("Original Image", workingImage);

    int choice;
    do
    {
        showMenu();
        cin >> choice;

        Mat resultImage;

        switch (choice)
        {
            case 1:
            {
                calculateImageStatistics(workingImage);
                break;
            }
            case 2:
            {
                double threshold = calculateAutomaticThreshold(workingImage);
                resultImage = applyBinarization(workingImage, threshold);

                namedWindow("Binary Image", WINDOW_NORMAL);
                imshow("Binary Image", resultImage);


                Mat histImage;
                int histSize = 256;
                float range[] = {0, 256};
                const float *histRange = {range};
                Mat hist;
                calcHist(&workingImage, 1, 0, Mat(), hist, 1, &histSize, &histRange, true, false);

                int histWidth = 512, histHeight = 400;
                histImage = Mat(histHeight, histWidth, CV_8UC3, Scalar(0, 0, 0));

                normalize(hist, hist, 0, histHeight, NORM_MINMAX);

                int binWidth = cvRound((double) histWidth / histSize);
                for (int i = 0; i < histSize; i++)
                {
                    rectangle(histImage,
                              Point(i * binWidth, histHeight),
                              Point((i + 1) * binWidth, histHeight - cvRound(hist.at<float>(i))),
                              Scalar(255, 255, 255), 1);
                }


                line(histImage,
                     Point(cvRound(threshold) * binWidth, 0),
                     Point(cvRound(threshold) * binWidth, histHeight),
                     Scalar(0, 0, 255), 2);

                namedWindow("Histogram with Threshold", WINDOW_NORMAL);
                imshow("Histogram with Threshold", histImage);
                break;
            }
            case 3:
            {
                resultImage = calculateNegative(workingImage);

                namedWindow("Negative Image", WINDOW_NORMAL);
                imshow("Negative Image", resultImage);
                showHistogram(resultImage, "Negative Histogram");
                break;
            }
            case 4:
            {
                int gOutMin, gOutMax;
                cout << "Enter output minimum intensity (0-255): ";
                cin >> gOutMin;
                cout << "Enter output maximum intensity (0-255): ";
                cin >> gOutMax;

                if (gOutMin >= 0 && gOutMin < 256 && gOutMax >= 0 && gOutMax < 256 && gOutMin < gOutMax)
                {
                    resultImage = modifyContrast(workingImage, gOutMin, gOutMax);

                    namedWindow("Contrast Modified", WINDOW_NORMAL);
                    imshow("Contrast Modified", resultImage);
                    showHistogram(resultImage, "Modified Contrast Histogram");
                } else
                {
                    cout << "Invalid range! Min must be less than max, both within 0-255." << endl;
                }
                break;
            }
            case 5:
            {
                double gamma;
                cout << "Enter gamma value (0.1-3.0, <1 for compression, >1 for decompression): ";
                cin >> gamma;

                if (gamma > 0)
                {
                    resultImage = gammaCorrection(workingImage, gamma);

                    namedWindow("Gamma Corrected", WINDOW_NORMAL);
                    imshow("Gamma Corrected", resultImage);
                    showHistogram(resultImage, "Gamma Corrected Histogram");
                } else
                {
                    cout << "Invalid gamma value! Must be positive." << endl;
                }
                break;
            }
            case 6:
            {
                int offset;
                cout << "Enter brightness offset (-255 to 255): ";
                cin >> offset;

                resultImage = modifyBrightness(workingImage, offset);

                namedWindow("Brightness Modified", WINDOW_NORMAL);
                imshow("Brightness Modified", resultImage);
                showHistogram(resultImage, "Modified Brightness Histogram");
                break;
            }
            case 7:
            {
                string imagePath;
                cout << "Enter the path to a new image: ";
                cin >> imagePath;


                originalImage = imread(imagePath, 0);

                if (originalImage.empty())
                {
                    cout << "Could not open or find the image! Using previous image." << endl;
                } else
                {
                    workingImage = originalImage.clone();


                    namedWindow("Original Image", WINDOW_NORMAL);
                    imshow("Original Image", workingImage);


                    destroyWindow("Binary Image");
                    destroyWindow("Histogram with Threshold");
                    destroyWindow("Negative Image");
                    destroyWindow("Negative Histogram");
                    destroyWindow("Contrast Modified");
                    destroyWindow("Modified Contrast Histogram");
                    destroyWindow("Gamma Corrected");
                    destroyWindow("Gamma Corrected Histogram");
                    destroyWindow("Brightness Modified");
                    destroyWindow("Modified Brightness Histogram");
                    destroyWindow("Histogram");
                    destroyWindow("Cumulative Histogram");
                }
                break;
            }
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }

        if (choice >= 1 && choice <= 6)
        {
            cout << "Press any key to continue...";
            waitKey(0);
        }
    } while (choice != 0);

    destroyAllWindows();
    return 0;
}
