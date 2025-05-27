#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

void showHistogram(const string& name, int* hist, int hist_cols, int hist_height);
vector<int> getHistogram(const string& img_name);
vector<float> getNormalizedHistogram(const string& img_name);
vector<int> getHistogramBins(const string& img_name, int bins);

vector<int> findPeaks(const vector<float>& pdf, int WH, float TH);
Mat applyThresholds(const Mat& img, const vector<int>& peaks);
Mat applyFloydSteinberg(const Mat& img, const vector<int>& peaks);
Mat multipleSteps(const string& img_name, int WH, float TH);
Mat floydSteinberg(const string& img_name, int WH, float TH);

int main() {
    char c;
    while (true) {
        cout << "1. Get histogram" << endl;
        cout << "2. Get normalized histogram" << endl;
        cout << "3. Show histogram" << endl;
        cout << "4. Show histogram with bins" << endl;
        cout << "5. Multiple steps algo" << endl;
        cout << "6. Floyd-Steinberg " << endl;
        cin >> c;
        if (c == 'q') {
            break;
        }

        switch (c) {
            case '1': {
                Mat img = imread("../Imagini/cameraman.bmp");
                imshow("original", img);
                auto data = getHistogram("../Imagini/cameraman.bmp");

                for (int d : data) {
                    cout << d << " ";
                }
                cout << endl;
                break;
            }
            case '2': {
                Mat img = imread("../Imagini/cameraman.bmp");
                imshow("original", img);
                auto data = getNormalizedHistogram("../Imagini/cameraman.bmp");

                float sum = 0.0f;
                for (float d : data) {
                    cout << d << " ";
                    sum += d;
                }
                cout << endl;
                cout << "sum = " << sum << endl;
                break;
            }
            case '3': {
                Mat img = imread("../Imagini/cameraman.bmp");
                imshow("original", img);
                showHistogram("histogram", getHistogram("../Imagini/cameraman.bmp").data(), img.cols, img.rows);

                break;
            }
            case '4': {
                Mat img = imread("../Imagini/cameraman.bmp");
                imshow("original", img);
                int bins;
                cout << "Bins count:" << endl;
                cin >> bins;
                showHistogram("histogram", getHistogramBins("../Imagini/cameraman.bmp", bins).data(), img.cols, img.rows);
                break;
            }
            case '5': {
                Mat img = imread("../Imagini/cameraman.bmp");
                imshow("original", img);
                Mat result = multipleSteps("../Imagini/cameraman.bmp", 5, 0.0003f);
                imshow("multiple steps", result);
                break;
            }
            case '6': {
                Mat img = imread("../Imagini/saturn.bmp");
                imshow("original", img);
                Mat result = floydSteinberg("../Imagini/saturn.bmp", 5, 0.0003f);
                imshow("floyd steps", result);
                break;
            }

            default: {
                break;
            }
        }

        waitKey();
    }

    return 0;
}

void showHistogram(const string& name, int* hist, const int hist_cols,
const int hist_height) {
    Mat imgHist(hist_height, hist_cols, CV_8UC3, CV_RGB(255, 255, 255));
    // constructs a white image
    //computes histogram maximum
    int max_hist = 0;
    for (int i = 0; i<hist_cols; i++)
        if (hist[i] > max_hist)
            max_hist = hist[i];
    double scale = 1.0;
    scale = (double)hist_height / max_hist;
    int baseline = hist_height - 1;
    for (int x = 0; x < hist_cols; x++) {
        Point p1 = Point(x, baseline);
        Point p2 = Point(x, baseline - cvRound(hist[x] * scale));
        line(imgHist, p1, p2, CV_RGB(255, 0, 255)); // histogram bins
        // colored in magenta
    }
    imshow(name, imgHist);
}

vector<int> getHistogram(const string& img_name) {
    vector<int> hist(256, 0);

    Mat img = imread(img_name, IMREAD_GRAYSCALE);

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            hist.at(img.at<uchar>(i, j))++;
        }
    }

    return hist;
}

vector<int> getHistogramBins(const string& img_name, int bins) {
    vector<int> hist(bins, 0);

    Mat img = imread(img_name, IMREAD_GRAYSCALE);
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            int pixelValue = img.at<uchar>(i, j);

            int binIndex = (pixelValue * bins) / 256;
            binIndex = min(binIndex, bins - 1);
            hist[binIndex]++;
        }
    }

    return hist;
}

vector<float> getNormalizedHistogram(const string& img_name) {
    Mat img = imread(img_name, IMREAD_GRAYSCALE);
    int pixel_count = img.rows * img.cols;

    auto hist = getHistogram(img_name);
    vector<float> hist_float(hist.size(), 0);

    for (int i = 0; i < hist.size(); i++) {
        hist_float[i] = (float)hist.at(i);
    }

    for (int i = 0; i < hist_float.size(); i++) {
        hist_float[i] = hist_float[i] / (float)pixel_count;
    }

    return hist_float;
}


vector<int> findPeaks(const vector<float>& pdf, int WH, float TH) {
    vector<int> peaks;

    for (int k = WH; k <= 255 - WH; k++) {
        double sum = 0;
        for (int i = k - WH; i <= k + WH; i++) {
            sum += pdf[i];
        }
        double v = sum / (2 * WH + 1);

        bool isPeak = (pdf[k] > v + TH);
        if (isPeak) {
            for (int i = k - WH; i <= k + WH; i++) {
                if (pdf[i] > pdf[k]) {
                    isPeak = false;
                    break;
                }
            }
        }

        if (isPeak) {
            peaks.push_back(k);
        }
    }

    peaks.insert(peaks.begin(), 0);
    peaks.push_back(255);

    return peaks;
}

Mat applyThresholds(const Mat& img, const vector<int>& peaks) {
    Mat result = img.clone();

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            int pixelValue = img.at<uchar>(i, j);
            int closestPeak = peaks[0];
            int minDistance = abs(pixelValue - peaks[0]);

            for (size_t k = 1; k < peaks.size(); k++) {
                int distance = abs(pixelValue - peaks[k]);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestPeak = peaks[k];
                }
            }

            result.at<uchar>(i, j) = closestPeak;
        }
    }

    return result;
}

Mat applyFloydSteinberg(const Mat& img, const vector<int>& peaks) {
    Mat result = img.clone();

    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            int oldPixel = result.at<uchar>(y, x);

            int newPixel = peaks[0];
            int minDistance = abs(oldPixel - peaks[0]);

            for (size_t i = 1; i < peaks.size(); i++) {
                int distance = abs(oldPixel - peaks[i]);
                if (distance < minDistance) {
                    minDistance = distance;
                    newPixel = peaks[i];
                }
            }

            result.at<uchar>(y, x) = newPixel;

            int error = oldPixel - newPixel;

            // pixel(x+1,y) = pixel(x+1,y) + 7*error/16
            if (x + 1 < img.cols) {
                result.at<uchar>(y, x + 1) = saturate_cast<uchar>(result.at<uchar>(y, x + 1) + (7 * error) / 16);
            }

            // pixel(x-1,y+1) = pixel(x-1,y+1) + 3*error/16
            if (x - 1 >= 0 && y + 1 < img.rows) {
                result.at<uchar>(y + 1, x - 1) = saturate_cast<uchar>(result.at<uchar>(y + 1, x - 1) + (3 * error) / 16);
            }

            // pixel(x,y+1) = pixel(x,y+1) + 5*error/16
            if (y + 1 < img.rows) {
                result.at<uchar>(y + 1, x) = saturate_cast<uchar>(result.at<uchar>(y + 1, x) + (5 * error) / 16);
            }

            // pixel(x+1,y+1) = pixel(x+1,y+1) + error/16
            if (x + 1 < img.cols && y + 1 < img.rows) {
                result.at<uchar>(y + 1, x + 1) = saturate_cast<uchar>(result.at<uchar>(y + 1, x + 1) + error / 16);
            }
        }
    }

    return result;
}


Mat multipleSteps(const string& img_name, int WH, float TH) {
    Mat img = imread(img_name, IMREAD_GRAYSCALE);
    vector<float> pdf = getNormalizedHistogram(img_name);
    vector<int> peaks = findPeaks(pdf, WH, TH);
    return applyThresholds(img, peaks);
}

Mat floydSteinberg(const string& img_name, int WH, float TH) {
    Mat img = imread(img_name, IMREAD_GRAYSCALE);
    vector<float> pdf = getNormalizedHistogram(img_name);
    vector<int> peaks = findPeaks(pdf, WH, TH);
    return applyFloydSteinberg(img, peaks);
}

