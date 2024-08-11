#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>

class FaceRecognition {
public:
    FaceRecognition(const std::string &cascade_path);
    bool initialize();
    void detectAndDisplay(cv::Mat &frame);
    int findCameraIndex();

private:
    cv::CascadeClassifier face_cascade;
};

FaceRecognition::FaceRecognition(const std::string &cascade_path) {
    if (!face_cascade.load(cascade_path)) {
        std::cerr << "Erro ao carregar o classificador de rosto!" << std::endl;
        throw std::runtime_error("Erro ao carregar o classificador de rosto!");
    }
}

bool FaceRecognition::initialize() {
    return !face_cascade.empty();
}

void FaceRecognition::detectAndDisplay(cv::Mat &frame) {
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray, gray);

    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces);

    for (size_t i = 0; i < faces.size(); i++) {
        cv::rectangle(frame, faces[i], cv::Scalar(0, 255, 0), 2);
        std::string label = "Face found " + std::to_string(i + 1);
        int baseLine;
        cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
        cv::Point labelOrigin(faces[i].x, faces[i].y - labelSize.height - 10);
        cv::rectangle(frame, labelOrigin + cv::Point(0, baseLine), labelOrigin + cv::Point(labelSize.width, -labelSize.height), cv::Scalar(0, 255, 0), cv::FILLED);
        cv::putText(frame, label, labelOrigin, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0), 1);

        cv::Mat faceROI = gray(faces[i]);
        std::vector<std::vector<cv::Point>> contours;
        cv::Mat thresholdOutput;
        cv::threshold(faceROI, thresholdOutput, 100, 255, cv::THRESH_BINARY);
        cv::findContours(thresholdOutput, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
        cv::drawContours(frame(faces[i]), contours, -1, cv::Scalar(255, 0, 0), 2);
    }

    cv::imshow("Reconhecimento Facial", frame);
}

int FaceRecognition::findCameraIndex() {
    cv::VideoCapture cap;
    int index = -1;

    for (int i = 0; i < 10; ++i) {
        try {
            cap.open(i);
            if (cap.isOpened()) {
                cv::Mat frame;
                cap >> frame;
                if (!frame.empty()) {
                    index = i;
                    cap.release();
                    break;
                }
            }
        } catch (const cv::Exception &e) {
            std::cerr << "Erro ao tentar abrir a câmera no índice " << i << ": " << e.what() << std::endl;
        }
    }

    return index;
}

