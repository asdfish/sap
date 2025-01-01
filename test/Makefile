CXX ?= c++
override CXXFLAGS += -std=c++11
override CXXFLAGS += -Wall -Wextra -Wpedantic
override CXXFLAGS += -I../include
override LDFLAGS += -L.. -lsap

OBJECTS := $(patsubst src/%.cpp,$\
	build/%.o,$\
	$(shell find src -name '*.cpp'))

define REMOVE
$(if $(wildcard $1),$\
	rm $1)

endef

all: test

test: ${OBJECTS} ../libsap.a
	${CXX} ${CXXFLAGS} ${LDFLAGS} ${OBJECTS} -o $@

build/%.o: src/%.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

remove/%:
	$(call REMOVE,$(patsubst remove/%,%,$@))

clean: $(foreach FILE,${OBJECTS} test,remove/${FILE})

.PHONY: all clean remove/%
