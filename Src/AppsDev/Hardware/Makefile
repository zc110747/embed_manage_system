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
		FileProcessHw.o \
		HwManageThread.o \
		Device/device.o \
		Device/led.o \
		Device/beep.o \
		Device/ApI2c.o \
		Device/IcmSpi.o \
		../Common/FileProcess.o \
		../Common/gThread.o \
		../Common/gTimer.o

CurrentPath = $(shell pwd)

StaticLibs = ../Common/ExternalPackages/libjason.a

IncludePath = -I "$(CurrentPath)/../Common/" \
			-I "$(CurrentPath)/Device/"		 \
			-I "$(CurrentPath)"				 \
			-I "$(CurrentPath)/../Common/ExternalPackages/jsoncpp/include/"

# This is the file name of the executables and path where 
# place the executables
TargetFile = hw_process
TargetFilePath = ../../Executables/

# Including this file allows access to the Build System.
include ../../../Build/buildRules.mk