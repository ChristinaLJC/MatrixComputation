a.out: demo.cpp 
	g++ -std=c++20 $< -o $@

run: a.out 
	./a.out 