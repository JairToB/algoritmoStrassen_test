TARGET = test

SRC = main.cpp
DATA = data.dat
PLOT = plot.gp
IMG = graficoComparacion.png

CXX = g++
CXXFLAGS = -O2

all: $(IMG)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

$(DATA): $(TARGET)
	./$(TARGET) > $(DATA)

$(IMG): $(DATA) $(PLOT)
	gnuplot $(PLOT)

clean:
	rm -f $(TARGET) $(DATA) $(IMG)
