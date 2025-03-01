#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void denoiseImage(const string &imagePath) {
    // 读取图像
    Mat image = imread(imagePath);
    if (image.empty()) {
        cerr << "无法打开或找到图像!" << endl;
        return;
    }

    // 显示原始图像
    imshow("原始图像", image);

    // 1. 先进行高斯模糊去噪
    Mat gaussianBlurred;
    GaussianBlur(image, gaussianBlurred, Size(5, 5), 0);

    // 2. 再使用双边滤波
    Mat bilateralFiltered;
    bilateralFilter(gaussianBlurred, bilateralFiltered, 15, 75, 75);

    // 显示去噪后的图像
    imshow("去噪后图像", bilateralFiltered);

    // 保存去噪后的图像
    bool isSaved = imwrite("../image/denoised_bilateral.jpg", bilateralFiltered);
    if (isSaved) {
        cout << "去噪后的图像已保存为 denoised_bilateral.jpg" << endl;
    } else {
        cerr << "保存图像失败!" << endl;
    }

    // 等待按键
    waitKey(0);
    destroyAllWindows();
}

int main() {
    // 输入图片路径
    string imagePath = "../image/enoz_noise.png";
    denoiseImage(imagePath);

    return 0;
}
