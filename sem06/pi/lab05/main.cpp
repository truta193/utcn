#include <iostream>
#include <opencv2/opencv.hpp>
#include <random>

using namespace std;
using namespace cv;

enum NEIGHBOR_TYPE {
    N4,
    N8
};

Mat bfsTraversal(const Mat& src, NEIGHBOR_TYPE type);
Mat connectedComponentLabeling(const Mat& img, NEIGHBOR_TYPE type);
Mat assign_color(const Mat& src);


int main() {
    Mat img = imread("../imagini_etichetare/letters.bmp", 0);
    //Mat label = bfsTraversal(img, NEIGHBOR_TYPE::N8);
    Mat label = connectedComponentLabeling(img, NEIGHBOR_TYPE::N8);
    Mat labeled = assign_color(label);

    imshow("labeled", labeled);
    waitKey();
    return 0;
}



Mat bfsTraversal(const Mat& src, NEIGHBOR_TYPE type) {
    int rows = src.rows;
    int cols = src.cols;

    Mat dst = Mat::zeros(rows, cols, CV_32SC1);
    queue<Point2i> q;

    int k = type == N4 ? 4 : 8;
    vector<int> di = {-1, 0, 1, 0, -1, -1, 1, 1};
    vector<int> dj = {0, 1, 0, -1, -1, 1, -1, 1};
    di.resize(k);
    dj.resize(k);

    int label = 0;

    for (int i = 1; i < rows-1; i++) {
        for (int j = 1; j < cols-1; j++) {
            if (src.at<uchar>(i, j) == 0 && dst.at<int>(i, j) == 0) {
                label++;

                q.push(Point2i(j, i));
                dst.at<int>(i, j) = label;

                while (!q.empty()) {
                    Point2i current = q.front();
                    q.pop();

                    for (int d = 0; d < k; d++) {
                        int ni = current.y + di[d];
                        int nj = current.x + dj[d];

                        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                            if (src.at<uchar>(ni, nj) == 0 && dst.at<int>(ni, nj) == 0) {
                                dst.at<int>(ni, nj) = label;
                                q.push(Point2i(nj, ni));
                            }
                        }
                    }
                }
            }
        }
    }

    cout << label << endl;

    return dst;
}

Mat connectedComponentLabeling(const Mat& img, NEIGHBOR_TYPE type) {
    int height = img.rows;
    int width = img.cols;

    int k = type == N4 ? 4 : 8;
    vector<int> di = {-1, 0, 1, 0, -1, -1, 1, 1};
    vector<int> dj = {0, 1, 0, -1, -1, 1, -1, 1};
    di.resize(k);
    dj.resize(k);

    Mat labels = Mat::zeros(height, width, CV_32SC1);

    int label = 0;
    std::vector<std::vector<int>> edges(height * width + 1);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (img.at<uchar>(i, j) == 0 && labels.at<int>(i, j) == 0) {
                std::vector<int> L;

                for (int count = 0; count < k; count++) {
                    int ni = i + di[count];
                    int nj = j + dj[count];

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
                        if (labels.at<int>(ni, nj) > 0) {
                            L.push_back(labels.at<int>(ni, nj));
                        }
                    }
                }

                if (L.empty()) {
                    label++;
                    labels.at<int>(i, j) = label;
                } else {
                    int x = *std::min_element(L.begin(), L.end());
                    labels.at<int>(i, j) = x;

                    for (int y : L) {
                        if (y != x) {
                            edges[x].push_back(y);
                            edges[y].push_back(x);
                        }
                    }
                }
            }
        }
    }

    int newlabel = 0;
    std::vector<int> newlabels(label + 1, 0);

    for (int i = 1; i <= label; i++) {
        if (newlabels[i] == 0) {
            newlabel++;
            std::queue<int> Q;
            newlabels[i] = newlabel;
            Q.push(i);

            while (!Q.empty()) {
                int x = Q.front();
                Q.pop();

                for (int y : edges[x]) {
                    if (newlabels[y] == 0) {
                        newlabels[y] = newlabel;
                        Q.push(y);
                    }
                }
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (labels.at<int>(i, j) > 0) {
                labels.at<int>(i, j) = newlabels[labels.at<int>(i, j)];
            }
        }
    }

    return labels;
}

Mat assign_color(const Mat& src) {
    default_random_engine gen;
    uniform_int_distribution<int> di(0, 255);

    vector<Vec3b> colors(100);
    for (int i = 0; i < 100; i++) {
        colors[i][0] = di(gen);
        colors[i][1] = di(gen);
        colors[i][2] = di(gen);
    }

    Mat result = Mat::zeros(src.rows, src.cols, CV_8UC3);

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            int label = src.at<int>(i, j);
            if (label > 0 && label < 100) {
                result.at<Vec3b>(i, j) = colors[label];
            }
        }
    }

    return result;
}