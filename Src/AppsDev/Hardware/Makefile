################################################################################
#
# THIS FILE IS BASIC MAKE FILE FOR
# Copyright (c) 2020-2021
# Original Author: 1107473010@qq.com
#
################################################################################

# This is object should be build and will link to generate
# the executables
Objects = main.o \
		device.o \
		FileReaderHw.o \
		../Common/FileReader.o \
		led.o \
		beep.o

CurrentPath = $(shell pwd)

StaticLibs = ../Common/ExternalPackages/libjason

IncludePath = -I $(CurrentPath)/../Common/

# This is the file name of the executables and path where 
# place the executables
TargetFile = hw_process
TargetFilePath = ../../Executables/

# Including this file allows access to the Build System.
include ../../../Build/buildRules.mk