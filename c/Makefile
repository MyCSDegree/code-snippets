default:
	@echo "huh?"

RM = rm -rf
MKDIR = mkdir -p
CSTD = c++0x

CORE_FILES = \
	gulma_virus.cpp

gulma: clean
	g++ \
		-Wall \
		--std=$(CSTD) \
		-O2 \
		$(CORE_FILES) \
		-o "test/gulma"

clean:
	$(RM) test
	$(MKDIR) test
