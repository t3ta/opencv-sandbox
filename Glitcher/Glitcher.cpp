#include <random>
#include <opencv2/opencv.hpp>

class Glitcher {
    cv::Mat glitch(int numberOfTimes, cv::Mat image) {
        cv::Mat tmpImage = image.clone();

        int width = image.cols;
        int height = image.rows;

        std::random_device randomDevice;
        std::mt19937 engine(randomDevice());
        std::uniform_int_distribution<> range(0, 100);

        int i = 0;
        while (i < numberOfTimes) {
            tmpImage = image.clone();

            int glitchWidth = (width - 1) * range(engine) / 100;
            int offset = (height - 1) * range(engine) / 100;

            cv::Mat leftROISource = tmpImage(cv::Rect(0, 0, glitchWidth, offset));
            cv::Mat rightROISource = tmpImage(cv::Rect(glitchWidth, 0,  width - glitchWidth - 1, offset));
            cv::Mat leftROIDestination = image(cv::Rect(0, 0, width - glitchWidth - 1, offset));
            cv::Mat rightROIDestination = image(cv::Rect(width - glitchWidth - 1 , 0, glitchWidth, offset));
            leftROISource.copyTo(rightROIDestination);
            rightROISource.copyTo(leftROIDestination);

            i++;
        }

        return image;
    }
}