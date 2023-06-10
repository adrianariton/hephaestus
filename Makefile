build:
	g++-11 -std=c++17  -fopenmp main.cpp --include athena/*.cpp hephaestus/*.cpp -o para4 -fpermissive
clean:
	rm a.out