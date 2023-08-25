CXX = 	g++
CXXFLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla -Wno-write-strings -Wno-cast-qual -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr #-flto-odr-type-merging

files = main.cpp CustomStrings.cpp CustomAssert.cpp ColorConsole.cpp
objects = $(files:.cpp=.o)

buildDir = build
srcDir = src

.PHONY: all clean prepare
all: prepare StringsCustom

build_docs:
	doxygen Doxyfile

$(addprefix $(buildDir)/, $(objects)): $(buildDir)/%.o: $(srcDir)/%.cpp
	@echo [CC] $< -o $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

StringsCustom: $(addprefix $(buildDir)/, $(objects))
	@echo [CC] $^ -o $@
	@$(CXX) $(CXXFLAGS) $^ -o $(addprefix $(buildDir)/, $@)

clean:
	rm -f build/*.o all
	rm build/StringsCustom

prepare:
	@mkdir -p $(buildDir)

