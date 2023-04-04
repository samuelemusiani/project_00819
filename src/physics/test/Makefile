shell:= /bin/bash

TARGET=TEST
SRC_PHYSISCS=..
SRC_TESTS=tests
SRC_COMPUTATION_TESTS=${SRC_TESTS}/computation
SRC_JUMP_TESTS=${SRC_TESTS}/jump
DEST_OBJECT=object
DEST_COMPUTATION_OBJECT=${DEST_OBJECT}/computation
DEST_JUMP_OBJECT=${DEST_OBJECT}/jump

SRC_FILES=point vector body

all:
	@echo "Usare compute o jump per selezionare il target"

jump: 
	rm -rf ${TARGET}
	g++ ${SRC_JUMP_TESTS}/main.cpp $(shell find ${DEST_JUMP_OBJECT}/*) ../vector.cpp ../point.cpp -lncurses -o ${TARGET}
	./${TARGET}

compute: ${SRC_COMPUTATION_FILES}
	rm -rf ${TARGET}
	g++ ${SRC_COMPUTATION_TESTS}/main.cpp $(shell find ${DEST_COMPUTATION_OBJECT}/*) -o ${TARGET}
	./${TARGET}

# The SECONDEXPANSION is needed in order to use the $$@ macros expansion. I think there are bettere
# ways to solve the problem but I could not find any solution in a reasonable amount of time
.SECONDEXPANSION:
${SRC_COMPUTATION_FILES}: $(shell find ${SRC_PHYSISCS}/$@.*) ${SRC_COMPUTATION_TESTS}/$$@.test.cpp DIR
	g++ -c ${SRC_PHYSISCS}/$@.cpp -o ${DEST_COMPUTATION_OBJECT}/$@.o
	g++ -c ${SRC_COMPUTATION_TESTS}/$@.test.cpp -o ${DEST_COMPUTATION_OBJECT}/$@.test.o

DIR:
	mkdir -p ${DEST_OBJECT}
	mkdir -p ${DEST_COMPUTATION_OBJECT}
	mkdir -p ${DEST_JUMP_OBJECT}

clean:
	rm -rf object/*

.PHONY: all compute DIR clean
