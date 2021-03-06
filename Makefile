latest_target:=$(shell ls *.cpp -1rt|tail -n 1|sed 's/\.cpp//')

CXXFLAGS = -Wall -Wshadow -gdwarf-2 -O0
LDFLAGS  = -O0

ifeq ($(PROF), 1)
	CXXFLAGS += -pg
	LDFLAGS  += -pg
endif

ifeq ($(CPP98), 1)
    CC = /usr/bin/g++-4.6
else
    CXXFLAGS += -std=c++1z
    CC = g++
endif

.PHONY: latest clean clean-temp
latest:
	make $(latest_target)

%: %.cpp
	$(CC) -c $(CXXFLAGS) $<
	$(CC) $(LDFLAGS) -o $@ $@.o
    
clean:
	ls *.cpp|sed 's/\.cpp/.o/'|xargs rm -f
	ls *.cpp|sed 's/\.cpp//'|xargs rm -f

clean-temp:
	rm -f input*.txt
	rm -f out*.txt
	rm -f gmon.out
	rm -f prof.txt
