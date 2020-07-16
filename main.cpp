#include <random>

#include <chrono>
#include <thread>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#define WINDOW_NAME "window"

int defaultGlitchNumberOfTimes = 0;
int count = 0;

void glitch(int numberOfTimes, void* userData) {
    cv::Mat* glitchedImagePointer = (cv::Mat*)userData;
    cv::Mat glitchedImage = (*glitchedImagePointer).clone();
    cv::Mat tmpImage = glitchedImage.clone();

    int width = glitchedImage.cols;
    int height = glitchedImage.rows;

    std::random_device randomDevice;
    std::mt19937 engine(randomDevice());
    std::uniform_int_distribution<> range(0, 100);
    std::normal_distribution<> dist(50.0, 10.0);

    int i = 0;
    while (i < numberOfTimes) {
        tmpImage = glitchedImage.clone();

        int glitchWidth = (width / 20 - 1) * dist(engine) / 100;
        int offset = (height - 1) * range(engine) / 100;

        cv::Mat leftROISource = tmpImage(cv::Rect(0, 0, glitchWidth, offset));
        cv::Mat rightROISource = tmpImage(cv::Rect(glitchWidth, 0,  width - glitchWidth - 1, offset));
        
        cv::Mat leftROIDestination = glitchedImage(cv::Rect(0, 0, width - glitchWidth - 1, offset));
        cv::Mat rightROIDestination = glitchedImage(cv::Rect(width - glitchWidth - 1 , 0, glitchWidth, offset));
        
        leftROISource.copyTo(rightROIDestination);
        rightROISource.copyTo(leftROIDestination);

        i++;
    }

    //cv::imwrite("images/generated/image_" + std::to_string(count) + ".png", glitchedImage);
    count++;
    cv::imshow(WINDOW_NAME, glitchedImage);
}

int main(int argc, char** argv) {
    cv::Mat image = cv::imread(argv[1], 1);

    if (!image.data) {
        printf("No image data! \n");
        return -1;
    }

    cv::namedWindow(WINDOW_NAME, cv::WINDOW_KEEPRATIO);
    cv::resizeWindow(WINDOW_NAME, 800, 500);
    cv::imshow(WINDOW_NAME, image);

    cv::createTrackbar("glitchNumberOfTimes", WINDOW_NAME, &defaultGlitchNumberOfTimes, 127, &glitch, (void*)(&image));

/*     while (true) {
        std::random_device randomDevice;
        std::mt19937 engine(randomDevice());
        std::uniform_int_distribution<> range(0, 2);
        
        cv::setTrackbarPos("glitchNumberOfTimes", WINDOW_NAME, range(engine));

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        cv::waitKey(1);
    } */

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
} 