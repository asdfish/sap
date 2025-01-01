CC ?= cc
MAKE ?= make

override CFLAGS += -std=c99
override CFLAGS += -Wall -Wextra -Wpedantic
override CFLAGS += -Iinclude

PROCESSED_HEADERS := $(subst .h,$\
	.h.gch,$\
	$(shell find include -name '*.h'))
OBJECTS := $(patsubst src/%.c,$\
	build/%.o,$\
	$(shell find src -name '*.c'))

SAP_REQUIREMENTS := ${PROCESSED_HEADERS} ${OBJECTS}

define COMPILE
${CC} ${CFLAGS} -c $1 -o $2

endef
define REMOVE
$(if $(wildcard $1),$\
	rm $1)

endef

all: libsap.a
test: libsap.a
	${MAKE} -C test

%.h.gch: %.h
	$(call COMPILE,$<,$@)
build/%.o: src/%.c
	$(call COMPILE,$<,$@)

libsap.a: ${SAP_REQUIREMENTS}
	ar rcs $@ ${OBJECTS}	

remove/%:
	$(call REMOVE,$(patsubst remove/%,%,$@))

clean: $(foreach FILE,${SAP_REQUIREMENTS} libsap.a,remove/${FILE})
	${MAKE} -C test clean

.PHONY: all clean remove/% test
