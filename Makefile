latest_target:=$(shell ls *.cpp -1rt|tail -n 1|sed 's/\.cpp//')
.PHONY: latest clean
latest:
	make $(latest_target)

%: %.cpp
	g++ -c -Wall -Wshadow -std=c++0x -gdwarf-2 -O0 $<
	g++ -O0 -o $@ $@.o
    
clean:
	ls *.cpp|sed 's/\.cpp/.o/'|xargs rm -f
	ls *.cpp|sed 's/\.cpp//'|xargs rm -f
	ls *.java|sed 's/\.java/.class/'|xargs rm -f
	ls *.java|sed 's/\.java/.java~/'|xargs rm -f
