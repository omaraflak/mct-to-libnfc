GXX = g++
EXEC = converter

all : $(EXEC)

$(EXEC) : converter.cpp
	$(GXX) $< -o $@

clean :
	rm $(EXEC)
