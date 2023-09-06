srcDir = src
outDir = build

sources = main.cpp CustomStrings.cpp Onegin.cpp
target = CustomStrings

srcObjects = $(sources:.cpp=.o)

.PHONY: all clean prepare build_docs debug release

all: debug

debug: CXX = g++
debug: CXXFLAGS = -ICustomAssert -D_DEBUG -D_SHOW_STACK_TRACE -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla -Wno-write-strings -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr #-flto-odr-type-merging
debug: buildDir = $(outDir)/debug
debug: libObjects = CustomAssert/build/debug/Logger.o CustomAssert/build/debug/CustomAssert.o CustomAssert/ColorConsole/build/debug/ColorConsole.o
debug: prepare
debug: makeMode = debug
debug: $(buildDir)/$(target)

release: CXX = g++
release: CXXFLAGS = -ICustomAssert -std=c++17 -O3
release: buildDir = $(outDir)/release
release: libObjects = CustomAssert/build/release/Logger.o CustomAssert/build/release/CustomAssert.o CustomAssert/ColorConsole/build/release/ColorConsole.o
release: prepare
release: makeMode = release
release: $(buildDir)/$(target)

$(srcObjects): %.o: $(srcDir)/%.cpp
	@echo compile

	cd CustomAssert && make $(makeMode)
	cd CustomAssert/ColorConsole && make $(makeMode)

	@echo [CXX] -c $< -o  $(addprefix $(buildDir)/, $@)
	@$(CXX) $(CXXFLAGS) -c $< -o  $(addprefix $(buildDir)/, $@)

$(buildDir)/$(target): $(srcObjects)
	$(eval objects = $(addprefix $(buildDir)/, $(srcObjects)) $(libObjects))

	@echo [CXX] $(objects) -o $(buildDir)$@
	@$(CXX) $(CXXFLAGS) $(objects) -o $(buildDir)$@

prepare:
	@mkdir -p $(outDir)
	@mkdir -p $(buildDir)

clean:
	@rm -f $(outDir)/debug/*.o all
	@rm -f $(outDir)/debug/$(target)
	@rm -f $(outDir)/release/*.o all
	@rm -f $(outDir)/release/$(target)

	cd CustomAssert && make clean
	cd CustomAssert/ColorConsole && make clean

build_docs:
	doxygen Doxyfile
