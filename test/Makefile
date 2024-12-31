CC ?= cc

OBJECTS := $(patsubst src/%.c,$\
	build/%.o,$\
	$(shell find src -name '*.c'))

define REMOVE
$(if $(wildcard $1),$\
	rm $1)

endef

all: test

test: ${OBJECTS}
	${CC} ${CFLAGS} ${LDFLAGS} $< -o $@

build/%.o: src/%.c
	${CC} ${CFLAGS} -c $< -o $@

remove/%:
	$(call REMOVE,$(patsubst remove/%,%,$@))

clean: $(foreach FILE,${OBJECTS},remove/${FILE})

.PHONY: all clean remove/%
