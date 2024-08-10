#ifndef FACE_RECOGNITION_HPP
#define FACE_RECOGNITION_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

class FaceRecognition {
public:
    FaceRecognition(const std::string& cascade_path);
    bool initialize();
    void detectAndDisplay(cv::Mat& frame);
    int findCameraIndex(); 

private:
    cv::CascadeClassifier face_cascade;
};

#endif // FACE_RECOGNITION_HPP
