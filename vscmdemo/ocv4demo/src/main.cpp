#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    std::cout << "ocv4demo start" << std::endl;

    std::vector<std::string> img_paths, img_path_buf;
    cv::glob("./*.png", img_paths, true);
    cv::glob("./*.jpg", img_path_buf, true);
    img_paths.insert(img_paths.end(), img_path_buf.begin(), img_path_buf.end());

    std::cout << "image count: " << img_paths.size() << std::endl;
    for (auto img_path : img_paths) {
        std::cout << "img:" << img_path << std::endl;
        cv::Mat in_img = cv::imread(img_path, cv::IMREAD_UNCHANGED);
        if (!in_img.empty()) {
            // cv::namedWindow(img_path, cv::WINDOW_AUTOSIZE);
            cv::imshow(img_path, in_img);
            cv::Mat gray_img;
            cv::cvtColor(in_img, gray_img, cv::COLOR_BGR2GRAY);
            cv::imshow(img_path, gray_img);
        }
    }

    //std::cin.get(); // 使用了 imshow 这类 GUI 函数不可以用标准输入，没事件循环处理。
    cv::waitKey(); // 这个里面有事件循环。

    return 0;
}
