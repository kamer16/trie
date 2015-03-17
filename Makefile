CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -pedantic -std=c++11 -O3 -g ${INC}
INC1=-I include
INC2=-I /usr/local/include
INC=${INC1} ${INC2}
DOXY=Doxyfile
DOXYLAT=docs/latex

CHK_SRC=${addprefix tests/, }
CHK_OBJ=${CHK_SRC:.cc=.o}

DIR=src/
SRC=${addprefix ${DIR}, main.cpp}
OBJ=${SRC:.cpp=.o}
OUT=textMining

all: ${OUT}

${OUT}: ${OBJ}
	${CXX} ${CXXFLAGS} ${OBJ} -o $@

check: ${OUT}
	@cd tests && ./errors.sh

doc: docs/$(DOXY)
	cd docs/ && doxygen $(DOXY)
	cd $(DOXYLAT) && gmake
	cd $(DOXYLAT) && evince refman.pdf&

distclean: clean

clean:
	${RM} ${CHK_OBJ} ${OBJ} ${OUT}
	${RM} -r docs/latex docs/html

.PHONY: all clean doc
