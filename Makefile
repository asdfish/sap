override CXXFLAGS += -Iinclude

SHARED_NAMES := flag

PROCESSED_HEADERS := $(foreach FILE,$\
										 	${SHARED_NAMES},$\
											include/sap/${FILE}.hpp.gch)
OBJECTS := $(foreach FILE,$\
					 	${SHARED_NAMES},$\
						build/${FILE}.o)

SAP_REQUIREMENTS := ${PROCESSED_HEADERS} ${OBJECTS}

define COMPILE
${CXX} -c $(1) ${CXXFLAGS} -o $(2)

endef
define REMOVE
$(if $(wildcard $(1)),$\
	rm $(1))

endef
define NEWLINE


endef

all: libsap.a

$(eval $\
	$(foreach FILE,$\
		${SHARED_NAMES},$\
		build/${FILE}.o: include/sap/${FILE}.hpp.gch ${NEWLINE}))

%.hpp.gch: %.hpp
	$(call COMPILE,$<,$@)
build/%.o: src/%.cpp
	$(call COMPILE,$<,$@)

libsap.a: ${SAP_REQUIREMENTS}
	ar rcs libsap.a ${OBJECTS}

remove/%:
	$(call REMOVE,$(patsubst remove/%,%,$@))

clean: $(foreach FILE,${SAP_REQUIREMENTS},remove/${FILE})

.PHONY: all clean
