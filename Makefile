all:
	g++ -o clip main.cpp
install:
	cp clip /usr/loca/bin/clip
run-tests:
	bash ./test/test.sh
