CXX := g++
CXXFLAGS := -std=c++17 -Iincludes -Wall -Wextra
TARGET := app

SRC := \
	main.cpp \
	modules/core_rental.cpp \
	modules/priority.cpp \
	modules/reports.cpp \
	modules/transactions.cpp \
	modules/user_manager.cpp \
	utils/file_io.cpp \
	utils/validator.cpp

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
