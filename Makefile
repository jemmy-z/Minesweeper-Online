# Specify the compiler
CC = g++

# Specify compiler flags
CFLAGS = -Iinc -Idep -w -std=c++11 -lboost_system -lboost_filesystem -lpthread

# Specify folder structure of project
IDIR = inc
ODIR = obj
BDIR = bin
SDIR = src

# Specify name of app executable
PROGRAM = server

H_FILES := $(wildcard $(SDIR)/*.cpp)

SRC_FILES := $(wildcard $(SDIR)/*.cpp)
OBJ := $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SRC_FILES))

NEEDED_FILES := $(filter-out $(SDIR)/app.cpp, $(SRC_FILES))

$(ODIR)/%.o: $(SDIR)/%.cpp $(H_FILES)
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROGRAM): $(OBJ) 
	$(CC) $^ -o $(BDIR)/$@ $(CFLAGS)

clean:
	$(RM) $(BDIR)/*
	$(RM) $(ODIR)/*.o
	$(RM) $(TDIR)/$(ODIR)/*.o
