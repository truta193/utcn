#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat convolution(Mat image, Mat kernel, double scalar);

void centering_transform(Mat img);
void freq_ideal_low(const Mat& src);
void freq_ideal_high(const Mat& src);
void freq_gaussian_low(const Mat& src);
void freq_gaussian_high(const Mat& src);

const Mat arithmetic = (Mat_<int32_t>(3, 3) <<
                        1, 1, 1,
                        1, 1, 1,
                        1, 1, 1
);

const Mat arithmetic2 = (Mat_<int32_t>(5, 5) <<
                         1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1
);

const Mat gaussian = (Mat_<int32_t>(3, 3) <<
                      1, 2, 1,
                      2, 4, 2,
                      1, 2, 1
);

const Mat laplace = (Mat_<int32_t>(3, 3) <<
                     0, -1, 0,
                     -1, 4, -1,
                     0, -1, 0
);

const Mat laplace2 = (Mat_<int32_t>(3, 3) <<
                      -1, -1, -1,
                      -1, 8, -1,
                      -1, -1, -1
);

const Mat high_pass = (Mat_<int32_t>(3, 3) <<
                       0, -1, 0,
                       -1, 5, -1,
                       0, -1, 0
);

const Mat high_pass2 = (Mat_<int32_t>(3, 3) <<
                        -1, -1, -1,
                        -1, 9, -1,
                        -1, -1, -1
);

int main()
{
    Mat img = imread("../cameraman.bmp", 0);
    imshow("original", img);
    // imshow("arithmetic", convolution(img, arithmetic, 1.0 / 9.0));
    // imshow("arithmetic2", convolution(img, arithmetic2, 1.0 / 25.0));
    // imshow("gaussian", convolution(img, gaussian, 1.0 / 16.0));
    // imshow("laplace", convolution(img, laplace, 1.0));
    // imshow("laplace2", convolution(img, laplace2, 1.0));
    // imshow("high_pass", convolution(img, high_pass, 1.0));
    // imshow("high_pass2", convolution(img, high_pass2, 1.0));

    freq_ideal_low(img);
    //freq_ideal_high(img);
    //freq_gaussian_high(img);
    //freq_gaussian_low(img);
    waitKey();
    std::cout << arithmetic << std::endl;
    return 0;
}

Mat convolution(Mat image, Mat kernel, double scalar)
{
    Mat result = Mat::zeros(image.rows, image.cols, CV_8UC1);
    const int border = kernel.rows / 2;

    for (int i = border; i < image.rows - border; i++)
    {
        for (int j = border; j < image.cols - border; j++)
        {
            double sum = 0.0;

            for (int k = -border; k <= border; k++)
            {
                for (int l = -border; l <= border; l++)
                {
                    const double pixel_value = image.at<uchar>(i + k, j + l);
                    const double kernel_value = kernel.at<int32_t>(k + border, l + border);

                    sum += pixel_value * kernel_value;
                }
            }

            sum *= scalar;

            sum = std::min(std::max(sum, 0.0), 255.0);

            result.at<uchar>(i, j) = static_cast<uchar>(sum);
        }
    }

    return result;
}

void centering_transform(Mat img)
{
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            img.at<float>(i, j) = ((i + j) & 1) ? -img.at<float>(i, j) : img.at<float>(i, j);
        }
    }
}


void freq_gaussian_low(const Mat& src)
{
    int H = src.cols;
    int W = src.rows;

    Mat srcf(src.rows, src.cols, CV_32FC1);
    src.convertTo(srcf, CV_32FC1);

    centering_transform(srcf);

    Mat fourier;
    dft(srcf, fourier, DFT_COMPLEX_OUTPUT);

    Mat channels[] = {Mat::zeros(src.size(),CV_32F), Mat::zeros(src.size(),CV_32F)};
    split(fourier, channels);

    Mat mag;
    magnitude(channels[0], channels[1], mag);
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            mag.at<float>(i, j) = log(mag.at<float>(i, j) + 1);
        }
    }
    normalize(mag, mag, 0, 255, NORM_MINMAX, CV_8UC1);
    imshow("magnitude", mag);

    Mat phi;
    phase(channels[0], channels[1], phi);
    normalize(phi, phi, 0, 255, NORM_MINMAX, CV_8UC1);
    imshow("phase", phi);

    int A = 20;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            channels[0].at<float>(i, j) *= exp(-((H / 2 - i) * (H / 2 - i) + (W / 2 - j) * (W / 2 - j)) / (A * A));
            channels[1].at<float>(i, j) *= exp(-((H / 2 - i) * (H / 2 - i) + (W / 2 - j) * (W / 2 - j)) / (A * A));
        }
    }

    Mat dst, dstf;
    merge(channels, 2, fourier);
    dft(fourier, dstf, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

    centering_transform(dstf);
    normalize(dstf, dst, 0, 255, NORM_MINMAX, CV_8UC1);

    imshow("final", dst);
    waitKey();
}

void freq_gaussian_high(const Mat& src)
{
    int H = src.rows;
    int W = src.cols;

    Mat srcf(src.rows, src.cols, CV_32FC1);
    src.convertTo(srcf, CV_32FC1);

    centering_transform(srcf);

    Mat fourier;
    dft(srcf, fourier, DFT_COMPLEX_OUTPUT);

    Mat channels[] = {Mat::zeros(src.size(),CV_32F), Mat::zeros(src.size(),CV_32F)};
    split(fourier, channels);

    Mat mag;
    magnitude(channels[0], channels[1], mag);
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            mag.at<float>(i, j) = log(mag.at<float>(i, j) + 1);
        }
    }
    normalize(mag, mag, 0, 255, NORM_MINMAX, CV_8UC1);
    imshow("magnitude", mag);

    Mat phi;
    phase(channels[0], channels[1], phi);
    normalize(phi, phi, 0, 255, NORM_MINMAX, CV_8UC1);
    imshow("phase", phi);

    int A = 20;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            channels[0].at<float>(i, j) *= 1.0f - (exp(-((H / 2 - i) * (H / 2 - i) + (W / 2 - j) * (W / 2 - j)) / (A * A)));
            channels[1].at<float>(i, j) *= 1.0f - (exp(-((H / 2 - i) * (H / 2 - i) + (W / 2 - j) * (W / 2 - j)) / (A * A)));
        }
    }

    Mat dst, dstf;
    merge(channels, 2, fourier);
    dft(fourier, dstf, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

    centering_transform(dstf);
    normalize(dstf, dst, 0, 255, NORM_MINMAX, CV_8UC1);

    imshow("final", dst);
    waitKey();
}

void freq_ideal_low(const Mat& src)
{
    int H = src.rows;
    int W = src.cols;

    Mat srcf(src.rows, src.cols, CV_32FC1);
    src.convertTo(srcf, CV_32FC1);

    centering_transform(srcf);

    Mat fourier;
    dft(srcf, fourier, DFT_COMPLEX_OUTPUT);

    Mat channels[] = {Mat::zeros(src.size(),CV_32F), Mat::zeros(src.size(),CV_32F)};
    split(fourier, channels);

    Mat mag;
    magnitude(channels[0], channels[1], mag);
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            mag.at<float>(i, j) = log(mag.at<float>(i, j) + 1);
        }
    }
    normalize(mag, mag, 0, 255, NORM_MINMAX, CV_8UC1);
    imshow("magnitude", mag);

    Mat phi;
    phase(channels[0], channels[1], phi);
    normalize(phi, phi, 0, 255, NORM_MINMAX, CV_8UC1);
    imshow("phase", phi);

    int R = 20;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            float distance = sqrt((H/2 - i)*(H/2 - i) + (W/2 - j)*(W/2 - j));

            float filter_value = (distance <= R) ? 1.0f : 0.0f;

            channels[0].at<float>(i, j) *= filter_value;
            channels[1].at<float>(i, j) *= filter_value;
        }
    }

    Mat dst, dstf;
    merge(channels, 2, fourier);
    dft(fourier, dstf, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

    centering_transform(dstf);
    normalize(dstf, dst, 0, 255, NORM_MINMAX, CV_8UC1);

    imshow("final", dst);
    waitKey();
}

void freq_ideal_high(const Mat& src)
{
    int H = src.rows;
    int W = src.cols;

    Mat srcf(src.rows, src.cols, CV_32FC1);
    src.convertTo(srcf, CV_32FC1);

    centering_transform(srcf);

    Mat fourier;
    dft(srcf, fourier, DFT_COMPLEX_OUTPUT);

    Mat channels[] = {Mat::zeros(src.size(),CV_32F), Mat::zeros(src.size(),CV_32F)};
    split(fourier, channels);

    Mat mag;
    magnitude(channels[0], channels[1], mag);
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            mag.at<float>(i, j) = log(mag.at<float>(i, j) + 1);
        }
    }
    normalize(mag, mag, 0, 255, NORM_MINMAX, CV_8UC1);
    imshow("magnitude", mag);

    Mat phi;
    phase(channels[0], channels[1], phi);
    normalize(phi, phi, 0, 255, NORM_MINMAX, CV_8UC1);
    imshow("phase", phi);

    int R = 20;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            float distance = sqrt((H/2 - i)*(H/2 - i) + (W/2 - j)*(W/2 - j));

            float filter_value = (distance > R) ? 1.0f : 0.0f;

            channels[0].at<float>(i, j) *= filter_value;
            channels[1].at<float>(i, j) *= filter_value;
        }
    }

    Mat dst, dstf;
    merge(channels, 2, fourier);
    dft(fourier, dstf, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

    centering_transform(dstf);
    normalize(dstf, dst, 0, 255, NORM_MINMAX, CV_8UC1);

    imshow("final", dst);
    waitKey();
}

Mat sablon(Mat src)
{
    Mat srcf(src.rows, src.cols, CV_32FC1); //stocam imaginea sursa ca float
    src.convertTo(srcf, CV_32FC1);

    centering_transform(srcf); //centram imaginea, pentru a o putea procesa in domeniul frecvential

    Mat fourier; //cream o matrice de numere complexe in care sa stocam transformata fourier directa
    dft(srcf, fourier, DFT_COMPLEX_OUTPUT);
    //aplicam transformata fourier directa pe imaginea sursa si rezultatul va fi stocat in matricea "fourier" de numere complexe

    //dorim sa desfacem numerele complexe din matricea "fourier" in doua matrici, una cu partile reale si una cu partile imaginare ale numerelor
    Mat channels[] = {Mat::zeros(src.size(),CV_32F), Mat::zeros(src.size(),CV_32F)};
    split(fourier, channels); //separam partea reala de partea imaginara
    //in matricea channels[0] avem matricea care contine partile reale ale numerelor din "fourier"
    //in matricea channels[1] avem partea imaginara a numerelor

    //calculul magnitudinii
    Mat mag;
    magnitude(channels[0], channels[1], mag);
    //parcurgem matricea "mag" si aplicam log(mag.at<float>(i, j) + 1) pe fiecare element
    //aplicam functia normalize pe matricea mag si o afisam
    //calculul fazei
    Mat phi;
    phase(channels[0], channels[1], phi);

    //aici aplicam filtre (R=20 sau A=20)
    //parcurgem imaginea (0->H, 0->W) si aplicam modificarile pe channels[0] si channels[1]
    //pentru gauss putem folosi functia exp(exponent)

    //exemplu pentru filtru gaussian low pass
    int H = src.rows;
    int W = src.cols;
    int A = 20;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            channels[0].at<float>(i, j) *= exp(-((H / 2 - i) * (H / 2 - i) + (W / 2 - j) * (W / 2 - j)) / (A * A));
            channels[1].at<float>(i, j) *= exp(-((H / 2 - i) * (H / 2 - i) + (W / 2 - j) * (W / 2 - j)) / (A * A));
        }
    }

    Mat dst, dstf;
    merge(channels, 2, fourier);
    //reunim cele doua canale (real si imaginar), pentru a pregati matricea de revenirea in domeniul spatial
    dft(fourier, dstf, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);
    //aplicam transformata fourier inversa pentru a reveni in domeniul spatial
    //in matricea dstf avem rezultatul transformatei fourier inverse

    centering_transform(dstf); //recentram imaginea, pentru a o vizualiza usor in domeniul spatial
    normalize(dstf, dst, 0, 255, NORM_MINMAX, CV_8UC1);
    //normalizam matricea, ca sa nu avem valori in afara intervalului 0-255; punem rezultatul in dst

    imshow("initial", src);
    imshow("final", dst);
    waitKey();

    return dst;
}
