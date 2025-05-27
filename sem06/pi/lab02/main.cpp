#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

tuple<Mat, Mat, Mat> splitIntoChannels(Mat image);
Mat convertToGray(Mat image);
Mat grayscaleToBw(Mat image, uchar threshold);
tuple<Mat, Mat, Mat> convertRGBtoHSV(Mat image);
bool isInside(Mat img, pair<int, int> pos);

int main() {
    char input;

    while (true) {
        cout << "Choose an option:" << endl;
        cout << "1. Split into channels" << endl;
        cout << "2. Color to grayscale" << endl;
        cout << "3. B/W Threshold" << endl;
        cout << "4. Color to hsv" << endl;
        cout << "5. Is inside" << endl;
        cin >> input;

        if (input == 'q') {
            break;
        }

        switch (input) {
            case '1': {
                Mat img = imread("../Imagini/kids.bmp", -1);
                imshow("original", img);

                Mat blue_channel, red_channel, green_channel;

                tie(blue_channel, green_channel, red_channel) = splitIntoChannels(img);
                imshow("blue_channel", blue_channel);
                imshow("green_channel", green_channel);
                imshow("red_channel", red_channel);
                waitKey(0);
                break;
            }
            case '2': {
                Mat img = imread("../Imagini/kids.bmp", -1);
                imshow("original", img);

                Mat res = convertToGray(img);
                imshow("to gray", res);
                waitKey(0);
                break;
            }
            case '3': {
                Mat img = imread("../Imagini/cameraman.bmp", -1);
                imshow("original", img);

                cout << "B/W Threshold (0-255): " << endl;
                int threshold;
                cin >> threshold;

                Mat res = grayscaleToBw(img, threshold);
                imshow("to bw", res);
                waitKey(0);
                break;
            }
            case '4': {
                Mat img = imread("../Imagini/Lena_24bits.bmp", -1);
                imshow("original", img);

                Mat hChannel, sChannel, vChannel;

                tie(hChannel, sChannel, vChannel) = convertRGBtoHSV(img);
                imshow("hChannel", hChannel);
                imshow("sChannel", sChannel);
                imshow("vChannel", vChannel);
                waitKey(0);
                break;
            }
            case '5': {
                Mat img = imread("../Imagini/Lena_24bits.bmp", -1);
                imshow("original", img);

                int x, y;
                cout << "Enter x y: " << endl;
                cin >> x; cin >> y;
                if (isInside(img, {x, y})) {
                    cout << "Is inside" << endl;
                } else {
                    cout << "Is not inside" << endl;
                }
            }
            default: {
                break;
            }
        }
    }

    return 0;
}

tuple<Mat, Mat, Mat> splitIntoChannels(Mat image) {
    int rows = image.rows;
    int cols = image.cols;

    Mat blueChannel(rows, cols, CV_8UC1);
    Mat greenChannel(rows, cols, CV_8UC1);
    Mat redChannel(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Vec3b pixel = image.at<Vec3b>(i, j);

            blueChannel.at<uchar>(i, j) = pixel[0];
            greenChannel.at<uchar>(i, j) = pixel[1];
            redChannel.at<uchar>(i, j) = pixel[2];
        }
    }

    return make_tuple(blueChannel, greenChannel, redChannel);
}

Mat convertToGray(Mat image) {
    int rows = image.rows;
    int cols = image.cols;
    Mat gray(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            gray.at<uchar>(i, j) = (image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] +image.at<Vec3b>(i, j)[2])/3;
        }
    }

    return gray;
}

Mat grayscaleToBw(Mat image, uchar threshold) {
    int rows = image.rows;
    int cols = image.cols;

    Mat bw(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            uchar pixel = image.at<uchar>(i, j);
            bw.at<uchar>(i, j) = pixel > threshold ? 255 : 0;
        }
    }

    return bw;
}

tuple<Mat, Mat, Mat> convertRGBtoHSV(Mat image) {
    // Check if input is a 3-channel image
    if (image.type() != CV_8UC3) {
        throw runtime_error("Input image must be CV_8UC3");
    }

    // Get image dimensions
    int rows = image.rows;
    int cols = image.cols;

    // Create three single-channel matrices for H, S, V
    Mat hChannel(rows, cols, CV_8UC1);
    Mat sChannel(rows, cols, CV_8UC1);
    Mat vChannel(rows, cols, CV_8UC1);

    // Process each pixel
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Vec3b pixel = image.at<Vec3b>(i, j);

            // Get BGR values (OpenCV stores as BGR)
            float b = (float)pixel[0] / 255.0f;
            float g = (float)pixel[1] / 255.0f;
            float r = (float)pixel[2] / 255.0f;

            // Calculate M, m, C
            float M = std::max(r, std::max(g, b));
            float m = std::min(r, std::min(g, b));
            float C = M - m;

            // Calculate V
            float V = M;

            // Calculate S
            float S = 0.0f;
            if (V != 0.0f) {
                S = C / V;
            }

            // Calculate H
            float H = 0.0f;
            if (C != 0.0f) {
                if (M == r) {
                    H = 60.0f * (g - b) / C;
                } else if (M == g) {
                    H = 120.0f + 60.0f * (b - r) / C;
                } else if (M == b) {
                    H = 240.0f + 60.0f * (r - g) / C;
                }
            }

            // Adjust H if negative
            if (H < 0.0f) {
                H += 360.0f;
            }

            // Normalize to 0-255 range
            float H_norm = H * 255.0f / 360.0f;
            float S_norm = S * 255.0f;
            float V_norm = V * 255.0f;

            // Store normalized values in output channels
            hChannel.at<uchar>(i, j) = static_cast<uchar>(std::round(H_norm));
            sChannel.at<uchar>(i, j) = static_cast<uchar>(std::round(S_norm));
            vChannel.at<uchar>(i, j) = static_cast<uchar>(std::round(V_norm));
        }
    }

    return make_tuple(hChannel, sChannel, vChannel);
}

bool isInside(Mat img, pair<int, int> pos) {
    if (pos.first < 0 || pos.second < 0) {
        return false;
    }

    int rows = img.rows;
    int cols = img.cols;

    if (pos.first >= rows || pos.second >= cols) {
        return false;
    }

    return true;
}