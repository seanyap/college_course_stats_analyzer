lab3: src/io_processor.cpp src/stats_extractor.cpp src/main.cpp
	g++ -std=c++11 -o lab3 src/io_processor.cpp src/stats_extractor.cpp src/main.cpp
	./lab3
	
clean:
	rm ./lab3
