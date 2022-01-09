################################################################################
#
# THIS FILE IS BASIC MAKE FILE FOR
# Copyright (c) 2020-2021
# Original Author: 1107473010@qq.com
#
################################################################################

# this place define the compile and flags, CC complie should be g++ and 
# option could be add in place
CC := g++
CFLAGS  := -O3 -std=c++11 -lpthread

# this is the rule how to complie file with type .cpp to middle file .o 
# then link the object and generate the staticLibrary.
all : $(TargetFile)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IncludePath)

$(TargetFile): $(Objects)
	ar cr $@ $(Objects)
	rm $(Objects)
	mv $(TargetFile) ../
tags :
	ctags -R *

# this is the rule how to clean all the file
clean:
	rm $(Objects)
