SHELL := /bin/bash

.PHONY : test

all:
	g++ -o clip main.cpp
install:
	cp clip /usr/loca/bin/clip
test:
	bash ./test/test.sh
