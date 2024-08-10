
# Face Recognition


## Overview

This project is a study of the OpenCV library, focusing on real-time face detection. The implementation detects faces in real-time using a webcam, drawing rectangles around each detected face and labeling them with their detection order (e.g., "Face finded 1"). Additionally, the code attempts to outline the head shape by using contour detection within the face region. The program also handles camera selection automatically and allows for graceful shutdown if the user closes the window or presses the 'q' key.

## Features

- **Real-Time Face Detection**: Detects faces from a webcam feed in real-time.
- **Labeling**: Labels each detected face with its order of detection.
- **Head Shape Outline**: Attempts to draw the head's shape using contour detection.
- **Automatic Camera Selection**: Automatically identifies and selects the first available webcam.
- **Graceful Shutdown**: The application can be exited by pressing 'q' or closing the window.

## Requirements

- OpenCV (version 4.x or later)
- C++11 or later
- A webcam connected to your computer

## Installation

1. **Install OpenCV**: Follow the instructions on the [OpenCV installation guide](https://docs.opencv.org/master/df/d65/tutorial_table_of_content_introduction.html).
2. **Clone the Repository**:
    ```sh
    git clone https://github.com/yourusername/face_recognition.git
    cd face_recognition
    ```
3. **Build the Project**:
    ```sh
    make
    ```
4. **Run the Application**:
    ```sh
    make run
    ```

## How It Works

1. **Initialization**: The program loads the Haar cascade classifier for face detection (`haarcascade_frontalface_default.xml`).
2. **Camera Selection**: The application automatically identifies the first available webcam.
3. **Face Detection**: For each frame captured by the webcam, the program converts the image to grayscale, equalizes the histogram, and detects faces.
4. **Labeling and Contours**: Detected faces are labeled with their detection order, and contours are drawn to approximate the shape of the head.
5. **Display**: The processed frame, with labels and contours, is displayed in a window.
6. **Shutdown**: The program exits if the user closes the window or presses the 'q' key.

## Example

After running the program, you will see a window displaying the webcam feed. Detected faces will be outlined with a green rectangle, labeled with "Face finded [number]", and the contours of the head will be highlighted in blue.

## Troubleshooting

- **Camera Not Found**: If the program cannot find a camera, ensure that your webcam is properly connected and accessible.
- **Low Detection Accuracy**: The contour detection is a simple method and may not perfectly outline the head in all cases. Improving lighting and camera angles can help.
- **OpenCV Errors**: Make sure you have installed the correct version of OpenCV and that your compiler supports C++11 or later.

