#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 识别 V 形灯条
vector<Point2f> detectVShapeLightStrip(const Mat &inputImage, Mat &outputImage) {
    // 复制输入图像
    outputImage = inputImage.clone();
    
    // 1. 预处理（灰度化、高斯模糊、边缘检测）
    Mat gray, blurred, edges;
    cvtColor(inputImage, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, blurred, Size(5, 5), 0);
    Canny(blurred, edges, 50, 150);

    // 2. 形态学闭运算（填充小的断裂）
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(edges, edges, MORPH_CLOSE, kernel);

    // 3. 查找轮廓
    vector<vector<Point>> contours;
    findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 4. 筛选 V 形轮廓
    vector<Point2f> vShapePoints;
    for (const auto &contour : contours) {
        // 逼近多边形
        vector<Point> approx;
        approxPolyDP(contour, approx, 10, true);

        if (approx.size() == 6) { // 6 个角点符合 V 形
            vShapePoints.assign(approx.begin(), approx.end());
            drawContours(outputImage, vector<vector<Point>>{approx}, -1, Scalar(0, 255, 0), 2);
            break; // 找到一个 V 形后退出
        }
    }

    // 返回 V 形角点
    return vShapePoints;
}

int main() {
    // 读取图像
    string imagePath = "../box/b1.jpg"; 
    Mat inputImage = imread(imagePath);
    if (inputImage.empty()) {
        cerr << "无法读取图像！" << endl;
        return -1;
    }

    // 识别 V 形灯条
    Mat outputImage;
    vector<Point2f> vPoints = detectVShapeLightStrip(inputImage, outputImage);

    // 输出角点坐标
    if (!vPoints.empty()) {
        cout << "V 形灯条角点坐标：" << endl;
        for (const auto &p : vPoints) {
            cout << "(" << p.x << ", " << p.y << ")" << endl;
        }
    } else {
        cout << "未找到 V 形灯条！" << endl;
    }

    // 显示结果
    imshow("V 形灯条识别", outputImage);
    imwrite("box/detected_v_shape.jpg", outputImage); // 保存结果
    waitKey(0);

    return 0;
}
