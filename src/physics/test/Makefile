#
# Alma Mater Studiorum - University of Bologna
# First cycle degree in Computer Science
# Computer Programming - 00819
#
# Author: Musiani Samuele #0001069143
#
# Makefile: A simple makefile to make tests on the physics library.
#

shell:= /bin/bash

TARGET=TEST
SRC_PHYSISCS=..
SRC_TESTS=tests
SRC_COMPUTATION_TESTS=${SRC_TESTS}/computation
SRC_JUMP_TESTS=${SRC_TESTS}/jump

all:
	@echo "Usare compute o jump per selezionare il target"

jump: 
	rm -rf ${TARGET}
	g++ $(shell find ${SRC_JUMP_TESTS}/*) ../*.cpp ../../../etc/logs/logs.cpp -lncurses -o ${TARGET}
	./${TARGET}

compute: 
	rm -rf ${TARGET}
	g++ $(shell find ${SRC_COMPUTATION_TESTS}/*.cpp) ../*.cpp -o ${TARGET}
	./${TARGET}

DIR:
	mkdir -p ${DEST_OBJECT}
	mkdir -p ${DEST_COMPUTATION_OBJECT}
	mkdir -p ${DEST_JUMP_OBJECT}

clean:
	rm -rf object/*

.PHONY: all compute DIR clean
