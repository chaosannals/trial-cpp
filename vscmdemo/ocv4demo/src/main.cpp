#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    std::cout << "ocv4demo start" << std::endl;

    std::vector<std::string> pngs;
    cv::glob("./*.png", pngs, false);

    std::cout << "png count: " << pngs.size() << std::endl;
    for (auto png : pngs) {
        std::cout << "img:" << png << std::endl;
        cv::Mat in_img = cv::imread(png, cv::IMREAD_UNCHANGED);
        if (!in_img.empty()) {
            // cv::namedWindow(png, cv::WINDOW_AUTOSIZE);
            cv::imshow(png, in_img);
            cv::Mat gray_img;
            cv::cvtColor(in_img, gray_img, cv::COLOR_BGR2GRAY);
            cv::imshow(png, gray_img);
        }
    }

    //std::cin.get(); // 使用了 imshow 这类 GUI 函数不可以用标准输入，没事件循环处理。
    cv::waitKey(); // 这个里面有事件循环。

    return 0;
}
