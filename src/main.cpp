#include "face_recognition.hpp"

int main() {
    FaceRecognition face_recognition("src/haarcascade_frontalface_default.xml");

    if (!face_recognition.initialize()) {
        std::cerr << "Erro ao carregar o classificador de rosto!" << std::endl;
        return -1;
    }

    int cameraIndex = face_recognition.findCameraIndex();
    if (cameraIndex == -1) {
        std::cerr << "Nenhuma câmera disponível!" << std::endl;
        return -1;
    }

    std::cout << "Câmera encontrada no índice: " << cameraIndex << std::endl;

    try {
        cv::VideoCapture cap(cameraIndex);
        if (!cap.isOpened()) {
            std::cerr << "Erro ao abrir a webcam!" << std::endl;
            return -1;
        }

        cv::Mat frame;
        while (true) {
            cap >> frame;

            if (frame.empty()) {
                std::cerr << "Erro ao capturar frame!" << std::endl;
                break;
            }

            face_recognition.detectAndDisplay(frame);

            if (cv::waitKey(30) == 'q') {
                break;
            }
        }
    } catch (const cv::Exception& e) {
        std::cerr << "Exceção capturada: " << e.what() << std::endl;
        return -1;
    } catch (const std::runtime_error& e) {
        std::cerr << "Programa encerrado: " << e.what() << std::endl;
    }

    return 0;
}
