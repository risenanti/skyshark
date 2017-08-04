CXX ?= g++

NAVIO = ../Navio2/C++/Navio
INCLUDES = -I ../Navio2/C++/
CFLAGS = -std=gnu++11

all:
	$(CXX) $(CFLAGS) $(INCLUDES) $(NAVIO)/gpio.cpp $(NAVIO)/RGBled.cpp $(NAVIO)/PWM.cpp $(NAVIO)/Util.cpp main.cpp -o TEST

clean:
	rm -f TEST
