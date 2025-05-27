#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <fstream>
using namespace std;
using namespace cv;

constexpr int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
constexpr int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};

Point2i find_start_pixel(const Mat& img);
int get_next_direction(int dir);
vector<int> extract_chain_code(const Mat& img);
void print_chain_code(const vector<int>& chain_code);
vector<int> calculate_chain_code_derivative(const vector<int>& chain_code);
void draw_chain(const vector<int>& chain_code, Mat& img, Point2i start_point);
void draw_chain_from_file(const filesystem::path& file_path, Mat& img);

int main() {
    const Mat img = imread("../files_border_tracing/triangle_up.bmp", 0);
    if (img.empty()) {
        cout << "Could not read image file" << endl;
        return -1;
    }

    const auto chain_code = extract_chain_code(img);
    print_chain_code(chain_code);
    const auto chain_code_derivative = calculate_chain_code_derivative(chain_code);
    print_chain_code(chain_code_derivative);

    Mat gray = imread("../files_border_tracing/gray_background.bmp", 0);
    draw_chain(chain_code, gray, Point2i(200, 20));

    draw_chain_from_file("../files_border_tracing/reconstruct.txt", gray);
    imshow("gray", gray);
    waitKey();
    return 0;
}

Point2i find_start_pixel(const Mat& img) {
    for (int r = 0; r < img.rows; r++) {
        for (int c = 0; c < img.cols; c++) {
            if (img.at<uchar>(r, c) == 0) {
                return {c, r};
            }
        }
    }
    return {-1, -1};
}

int get_next_direction(int dir) {
    if (dir % 2 == 0) {
        return (dir + 7) % 8;
    }
    return (dir + 6) % 8;
}

vector<int> extract_chain_code(const Mat& img) {
    vector<int> chainCode;

    const Point2i startPixel = find_start_pixel(img);
    if (startPixel.x == -1) {
        cout << "No object found in the image." << endl;
        return chainCode;
    }

    Point2i currentPixel = startPixel;
    Point2i secondPixel;
    Point2i prevPixel = startPixel;

    int currentDir = 7;
    bool firstStep = true;
    bool completedLoop = false;

    do {
        const int searchDir = get_next_direction(currentDir);
        bool foundNext = false;

        for (int i = 0; i < 8; i++) {
            int checkDir = (searchDir + i) % 8;
            const int nx = currentPixel.x + dx[checkDir];
            const int ny = currentPixel.y + dy[checkDir];

            if (img.at<uchar>(ny, nx) == 0) {
                chainCode.push_back(checkDir);
                prevPixel = currentPixel;
                currentPixel = Point2i(nx, ny);
                currentDir = checkDir;
                foundNext = true;

                if (firstStep) {
                    secondPixel = currentPixel;
                    firstStep = false;
                }

                if (chainCode.size() >= 3 && currentPixel == secondPixel && prevPixel == startPixel) {
                    completedLoop = true;
                }

                break;
            }
        }

        if (!foundNext) {
            break;
        }

    } while (!completedLoop);

    return chainCode;
}

void print_chain_code(const vector<int>& chain_code) {
    cout << "Chain Code: ";
    for (int code : chain_code) {
        cout << code << " ";
    }
    cout << endl;
    cout << "Chain Code Length: " << chain_code.size() << endl;
}

vector<int> calculate_chain_code_derivative(const vector<int>& chain_code) {
    if (chain_code.empty()) {
        return {};
    }

    vector<int> derivative;

    for (size_t i = 0; i < chain_code.size() - 1; i++) {
        int diff = (chain_code[i + 1] - chain_code[i] + 8) % 8;
        derivative.push_back(diff);
    }

    return derivative;
}

void draw_chain(const vector<int>& chain_code, Mat& img, Point2i start_point) {
    img.at<uchar>(start_point.y, start_point.x) = 0;

    Point2i current = start_point;

    for (int direction : chain_code) {
        current.x += dx[direction];
        current.y += dy[direction];

        if (current.x >= 0 && current.x < img.cols && current.y >= 0 && current.y < img.rows) {
            img.at<uchar>(current.y, current.x) = 0;
        }
    }
}

void draw_chain_from_file(const filesystem::path& file_path, Mat& img) {
    ifstream file(file_path);

    int row, col;
    file >> row >> col;
    Point2i start_point(col, row);

    int num_codes;
    file >> num_codes;

    vector<int> chain_code;
    for (int i = 0; i < num_codes; i++) {
        int code;
        if (file >> code) {
            chain_code.push_back(code);
        } else {
            cout << "Error: Could not read all chain codes" << endl;
            file.close();
            return;
        }
    }

    file.close();

    draw_chain(chain_code, img, start_point);
}