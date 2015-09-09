SHELL := /bin/bash

.PHONY : test

all:
	g++ -o clip main.cpp
install:
	cp clip /usr/local/bin/clip
test:
	bash ./test/test.sh
