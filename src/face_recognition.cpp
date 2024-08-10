#include "face_recognition.hpp"

FaceRecognition::FaceRecognition(const std::string& cascade_path) {
    if (!face_cascade.load(cascade_path)) {
        std::cerr << "Erro ao carregar o classificador de rosto!" << std::endl;
    }
}

bool FaceRecognition::initialize() {
    return face_cascade.empty() ? false : true;
}

void FaceRecognition::detectAndDisplay(cv::Mat& frame) {
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray, gray);
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces);
    for (size_t i = 0; i < faces.size(); i++) {
        cv::rectangle(frame, faces[i], cv::Scalar(0, 255, 0), 2);
        std::string label = "Face finded " + std::to_string(i + 1);
        int baseLine;
        cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
        cv::Point labelOrigin(faces[i].x, faces[i].y - labelSize.height - 10);
        cv::rectangle(frame, labelOrigin + cv::Point(0, baseLine), labelOrigin + cv::Point(labelSize.width, -labelSize.height), cv::Scalar(0, 255, 0), cv::FILLED);
        cv::putText(frame, label, labelOrigin, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0), 1);
    }
    cv::imshow("Reconhecimento Facial", frame);
    if (cv::getWindowProperty("Reconhecimento Facial", cv::WND_PROP_VISIBLE) < 1) {
        throw std::runtime_error("Janela fechada pelo usuário");
    }
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
        } catch (const cv::Exception& e) {
            std::cerr << "Erro ao tentar abrir a câmera no índice " << i << ": " << e.what() << std::endl;
        }
    }

    return index;
}
