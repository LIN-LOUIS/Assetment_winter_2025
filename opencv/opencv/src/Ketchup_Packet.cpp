#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
void detectAndProject(const std::string &imagePath) {
    // 读取图像
    cv::Mat image = cv::imread(imagePath);
    if (image.empty()) {
        std::cerr << "Could not open or find the image!" << std::endl;
        return;
    }

    // 转为灰度图
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // 高斯模糊去噪
    cv::Mat blurred;
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);     //二值化
    cv::Mat edges;
    threshold(blurred, edges, 0, 255,THRESH_OTSU);
    //定义一个 10x10 的矩形结构元素
    cv::Mat element = cv::getStructuringElement(MORPH_ELLIPSE, Size(8, 8));
    // 开运算操作
    morphologyEx(edges, edges, cv::MORPH_CLOSE, element);
    // 边缘检测
    cv::Mat edged;
    cv::Canny(edges, edged, 50, 150);
    cv::imshow("边缘检测", edged);
    // 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(edged, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 将所有轮廓连成一条线
    cv::Mat result = image.clone();  // 使用原始图像进行绘制

    // 遍历轮廓并连接
    for (size_t i = 0; i < contours.size(); i++) {
        // 绘制每个轮廓
        cv::polylines(result, contours, true, cv::Scalar(0, 255, 0), 2);
    }

    // 显示连接后的结果
    cv::imshow("所有轮廓连起来", result);
    // 查找最大面积的轮廓
    double maxArea = 0;
    int maxIndex = -1;
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            maxIndex = i;  // 记录最大轮廓的索引
        }
    }

    // 如果找到了最大面积的轮廓
    if (maxIndex != -1) {
        // 绘制最大面积轮廓
        drawContours(image, contours, maxIndex, Scalar(0, 255, 0), 2); // 使用绿色绘制最大轮廓
    }

    // 显示最大面积轮廓的图像
    imshow("最大面积轮廓", image);

    // 获取最大轮廓的外接矩形
    cv::RotatedRect rect = cv::minAreaRect(contours[maxIndex]);
    cv::Point2f vertices[4];
    rect.points(vertices);

    // 绘制外接矩形
    for (int j = 0; j < 4; j++) {
        cv::line(image, vertices[j], vertices[(j + 1) % 4], cv::Scalar(0, 255, 0), 2);
    }

    // 透视变换
    // 找到目标矩形的四个角
    float width = std::max(rect.size.width, rect.size.height);
    float height = std::min(rect.size.width, rect.size.height);
    cv::Point2f pts1[4] = { vertices[0], vertices[1], vertices[2], vertices[3] };
    cv::Point2f pts2[4] = { cv::Point2f(0, 0), cv::Point2f(width, 0), cv::Point2f(width, height), cv::Point2f(0, height) };

    // 计算透视变换矩阵
    cv::Mat matrix = cv::getPerspectiveTransform(pts1, pts2);

    // 透视变换
    cv::Mat result1;
    cv::warpPerspective(image, result1, matrix, cv::Size(width, height));

    // 显示透视变换结果
    imshow("透视变换结果", result1);
    // 保存透视变换后的图像
    bool isSaved = imwrite("transformed_image.jpg", result);
    if (isSaved) {
        std::cout << "透视变换后的图像已保存为 transformed_image.jpg" << std::endl;
    } else {
        std::cerr << "保存图像失败!" << std::endl;
    }
    // 等待按键，销毁窗口
    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main() {
    // 输入图片路径
    std::string imagePath = "../image/Ketchup_Packet.png";
    detectAndProject(imagePath);
    return 0;
}
