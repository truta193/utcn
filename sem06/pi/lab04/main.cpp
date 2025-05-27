#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void callback(int event, int x, int y, int flags, void* param);
int area(Vec3b color, Mat img);
tuple<int,int> mass_center(Vec3b color, Mat img);
int perimeter(Vec3b color, Mat img);
double thinning_factor(Vec3b color, Mat img);
double aspect_ratio(Vec3b color, Mat img);
//double roll_axis(Vec3b color, Mat img);
void projection_horizontal(Vec3b color, Mat img);
void projection_vertical(Vec3b color, Mat img);

void display_details(Vec3b color, Mat img);
void display_limited_area(Mat img, int max_area);

int main() {
    Mat img = imread("../Objects/oval_oriz.bmp");
    imshow("img", img);
    setMouseCallback("img", callback, &img);
    int max_area = 0;
    //cin >> max_area;

    waitKey();
    return 0;
}

void callback(int event, int x, int y, int flags, void* param) {
    const auto src = static_cast<Mat *>(param);
    if (event == EVENT_LBUTTONDOWN) {
        const auto color = src->at<Vec3b>(y,x);
        cout << "Pos(x,y): " << x << ", " << y << endl;
        cout << "Area: " << area(color, *src) << endl;

        int mc_r = 0;
        int mc_c = 0;
        tie(mc_r, mc_c) = mass_center(color, *src);
        cout << "Center of mass: " << mc_r << "," << mc_c << endl;

        cout << "Perimeter: " << perimeter(color, *src) << endl;
        cout << "Thinning: " << thinning_factor(color, *src) << endl;
        cout << "Aspect Ratio: " << aspect_ratio(color, *src) << endl;

        projection_horizontal(color, *src);
        projection_vertical(color, *src);

        display_details(color, *src);
        display_limited_area(*src, 6000);
    }
}

int area(Vec3b color, Mat img) {
    int width = img.cols;
    int height = img.rows;

    int area = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (img.at<Vec3b>(y, x)[0] == color[0] &&
                img.at<Vec3b>(y, x)[1] == color[1] &&
                img.at<Vec3b>(y, x)[2] == color[2]) {
                area++;
            }
        }
    }

    return area;
}

tuple<int,int> mass_center(Vec3b color, Mat img) {
    int width = img.cols;
    int height = img.rows;

    int area = 0;
    int sum_x = 0;
    int sum_y = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (img.at<Vec3b>(y, x)[0] == color[0] &&
                img.at<Vec3b>(y, x)[1] == color[1] &&
                img.at<Vec3b>(y, x)[2] == color[2]) {
                area++;
                sum_x += x;
                sum_y += y;
                }
        }
    }

    if (area > 0) {
        int center_x = sum_x / area;
        int center_y = sum_y / area;

        circle(img, Point(center_x, center_y), 5, Scalar(0, 0, 255), -1);

        return {center_x, center_y};
    }

    return {0,0};
}

int perimeter(Vec3b color, Mat img) {
    int width = img.cols;
    int height = img.rows;

    int perimeter_count = 0;

    int dx[8] = {-1, -1, -1,  0,  0,  1, 1, 1};
    int dy[8] = {-1,  0,  1, -1,  1, -1, 0, 1};

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (img.at<Vec3b>(y, x)[0] == color[0] &&
                img.at<Vec3b>(y, x)[1] == color[1] &&
                img.at<Vec3b>(y, x)[2] == color[2]) {

                for (int i = 0; i < 8; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];

                    if (nx < 0 || nx >= width || ny < 0 || ny >= height ||
                        img.at<Vec3b>(ny, nx)[0] != color[0] ||
                        img.at<Vec3b>(ny, nx)[1] != color[1] ||
                        img.at<Vec3b>(ny, nx)[2] != color[2]) {
                        perimeter_count++;
                        break;
                    }
                }
                }
        }
    }

    return perimeter_count;
}

double thinning_factor(Vec3b color, Mat img) {
    int a = area(color, img);
    int p = perimeter(color, img);

    return a / (static_cast<double>(p)*p) * 4.0 * 3.1415;
}

double aspect_ratio(Vec3b color, Mat img) {
    int width = img.cols;
    int height = img.rows;

    int c_max = 0;
    int c_min = INT_MAX;
    int r_max = 0;
    int r_min = INT_MAX;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (img.at<Vec3b>(y, x)[0] == color[0] &&
                img.at<Vec3b>(y, x)[1] == color[1] &&
                img.at<Vec3b>(y, x)[2] == color[2]) {
                if (x > c_max) c_max = x;
                if (x < c_min) c_min = x;
                if (y > r_max) r_max = y;
                if (y < r_min) r_min = y;
            }
        }
    }

    int bbox_width = c_max - c_min + 1;
    int bbox_height = r_max - r_min + 1;

    return static_cast<double>(bbox_width) / bbox_height;
}

void projection_horizontal(Vec3b color, Mat img) {
    int width = img.cols;
    int height = img.rows;

    vector<int> hist(height, 0);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (img.at<Vec3b>(y, x)[0] == color[0] &&
                img.at<Vec3b>(y, x)[1] == color[1] &&
                img.at<Vec3b>(y, x)[2] == color[2]) {
                hist[y]++;
                }
        }
    }

    Mat hist_img(height, width, CV_8UC3, Scalar(255, 255, 255));

    for (int y = 0; y < height; y++) {
        if (hist[y] > 0) {
            line(hist_img, Point(0, y), Point(hist[y], y), Scalar(0, 0, 255), 1);
        }
    }

    imshow("Horizontal Projection", hist_img);
}

void projection_vertical(Vec3b color, Mat img) {
    int width = img.cols;
    int height = img.rows;

    vector<int> hist(width, 0);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (img.at<Vec3b>(y, x)[0] == color[0] &&
                img.at<Vec3b>(y, x)[1] == color[1] &&
                img.at<Vec3b>(y, x)[2] == color[2]) {
                hist[x]++;
                }
        }
    }

    Mat hist_img(height, width, CV_8UC3, Scalar(255, 255, 255));

    for (int x = 0; x < width; x++) {
        if (hist[x] > 0) {
            int end_y = hist[x] - 1;
            if (end_y >= height) end_y = height - 1;

            line(hist_img, Point(x, 0), Point(x, end_y), Scalar(0, 255, 0), 1);
        }
    }

    imshow("Vertical Projection", hist_img);
}


void display_details(Vec3b color, Mat img) {
    Mat display_img = img.clone();
    int width = display_img.cols;
    int height = display_img.rows;

    int area = 0;
    int sum_x = 0;
    int sum_y = 0;

    vector<Point> perimeter_pixels;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (display_img.at<Vec3b>(y, x)[0] == color[0] &&
                display_img.at<Vec3b>(y, x)[1] == color[1] &&
                display_img.at<Vec3b>(y, x)[2] == color[2]) {

                area++;
                sum_x += x;
                sum_y += y;

                bool is_perimeter = false;

                int dx[8] = {-1, -1, -1,  0,  0,  1, 1, 1};
                int dy[8] = {-1,  0,  1, -1,  1, -1, 0, 1};

                for (int i = 0; i < 8; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];

                    if (nx < 0 || nx >= width || ny < 0 || ny >= height ||
                        display_img.at<Vec3b>(ny, nx)[0] != color[0] ||
                        display_img.at<Vec3b>(ny, nx)[1] != color[1] ||
                        display_img.at<Vec3b>(ny, nx)[2] != color[2]) {
                        is_perimeter = true;
                        break;
                    }
                }

                if (is_perimeter) {
                    perimeter_pixels.push_back(Point(x, y));
                }
            }
        }
    }

    if (area == 0) {
        cout << "No pixels of the selected color found." << endl;
        return;
    }

    int center_x = sum_x / area;
    int center_y = sum_y / area;

    for (const auto& pixel : perimeter_pixels) {
        display_img.at<Vec3b>(pixel.y, pixel.x) = Vec3b(0, 0, 255);
    }

    circle(display_img, Point(center_x, center_y), 1, Scalar(0, 0, 255), 1);

    imshow("Object Details", display_img);
}

void display_limited_area(Mat img, int max_area) {
    int width = img.cols;
    int height = img.rows;

    struct Vec3bComparator {
        bool operator()(const Vec3b& a, const Vec3b& b) const {
            if (a[0] != b[0]) return a[0] < b[0];
            if (a[1] != b[1]) return a[1] < b[1];
            return a[2] < b[2];
        }
    };

    set<Vec3b, Vec3bComparator> small_object_colors;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Vec3b current_color = img.at<Vec3b>(y, x);

            if (current_color == Vec3b(255, 255, 255)) {
                continue;
            }

            if (small_object_colors.find(current_color) == small_object_colors.end()) {
                int obj_area = area(current_color, img);

                if (obj_area <= max_area && obj_area > 0) {
                    small_object_colors.insert(current_color);
                }
            }
        }
    }

    Mat dupe = Mat(height, width, CV_8UC3, Scalar(255, 255, 255));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Vec3b current_color = img.at<Vec3b>(y, x);

            if (current_color == Vec3b(255, 255, 255)) {
                continue;
            }

            if (small_object_colors.find(current_color) != small_object_colors.end()) {
                dupe.at<Vec3b>(y, x) = current_color;
            }
        }
    }

    imshow("Limited Area Objects", dupe);
}