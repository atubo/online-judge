latest_target:=$(shell ls *.cpp -1rt|tail -n 1|sed 's/\.cpp//')

#CXXFLAGS = -Wall -Wshadow -std=c++0x -gdwarf-2 -O0
CXXFLAGS = -Wall -Wshadow -gdwarf-2 -O0
LDFLAGS  = -O0

ifeq ($(PROF), 1)
	CXXFLAGS += -pg
	LDFLAGS  += -pg
endif

.PHONY: latest clean
latest:
	make $(latest_target)

%: %.cpp
	$(CC) -c $(CXXFLAGS) $<
	$(CC) $(LDFLAGS) -o $@ $@.o
    
clean:
	ls *.cpp|sed 's/\.cpp/.o/'|xargs rm -f
	ls *.cpp|sed 's/\.cpp//'|xargs rm -f
