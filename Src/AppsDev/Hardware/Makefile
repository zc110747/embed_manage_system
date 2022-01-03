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

StaticLibs = ../Common/ExternalPackages/libjason

IncludePath = ../Common/

# This is the file name of the executables and path where 
# place the executables
TargetFile = logger_event
TargetFilePath = ../../Executables/

# Including this file allows access to the Build System.
include ../../../Build/buildRules.mk