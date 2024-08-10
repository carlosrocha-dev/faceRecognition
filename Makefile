CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++11 `pkg-config --cflags opencv4`
LDFLAGS = `pkg-config --libs opencv4`
SRC = src/face_recognition.cpp src/main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = face_recognition

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)
