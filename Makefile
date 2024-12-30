CC ?= cc
override CFLAGS += -std=c99
override CFLAGS += -Wall -Wextra -Wpedantic
override CFLAGS += -Iinclude

PROCESSED_HEADERS := $(subst .h,$\
	.h.gch,$\
	$(shell find include -name '*.h'))
OBJECTS := $(patsubst src/%.c,$\
	build/%.o,$\
	$(shell find src -name '*.c'))

define COMPILE
${CC} ${CFLAGS} -c $1 -o $2

endef

all: libsap.a

%.h.gch: %.h
	$(call COMPILE,$<,$@)
build/%.o: src/%.c
	$(call COMPILE,$<,$@)

libsap.a: ${PROCESSED_HEADERS} ${OBJECTS}
	ar rcs $@ ${OBJECTS}	
