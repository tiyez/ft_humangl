NAME=humangl

UNAME_S := $(shell uname -s)

DEPDIR=.dep
OBJDIR=.obj
SRCDIR=src

SRC = glad/src/glad.c
CPPSRC = $(addprefix $(SRCDIR)/,\
	main.cpp\
	shaders.cpp\
	input.cpp\
	initialization.cpp\
	mvp.cpp\
	time.cpp\
	skeleton/Node.cpp\
	skeleton/NodeSerializer.cpp\
	skeleton/Skeleton.cpp\
	skeleton/HardSkeleton.cpp\
	skeleton/HardSkeleton_serialized2.cpp\
	matrix_stack/MatrixStack.cpp\
	render/RenderObject.cpp\
	console/Console.cpp\
	ft_math/utils.cpp\
	ft_math/camera.cpp\
	ft_math/matrix.cpp\
	\
	)
MSRC = 
ALL_SRC= $(MSRC) $(CPPSRC) $(SRC)


OBJ1=$(ALL_SRC:.c=.o)
OBJ2=$(OBJ1:.m=.o)
OBJ3=$(OBJ2:.cpp=.cpp.o)
OBJ=$(addprefix $(OBJDIR)/,$(OBJ3))

WARNINGS_ = -Wno-sizeof-array-argument -Wno-unknown-warning-option -Wno-sizeof-pointer-div -Wno-unneeded-internal-declaration -Wno-unused-parameter -Wno-unused-variable -Wno-unused-private-field
ifeq ($(UNAME_S),Linux)
	INCLUDES_ = -Iglfw/include -Iglad/include -Iglm -Isrc -Isrc/matrix_stack -Isrc/render -Isrc/skeleton -Isrc/console -Isrc/ft_math
endif
ifeq ($(UNAME_S),Darwin)
	INCLUDES_ = -Iglfw/glfw-3.3.4/include -Iglad/include -Iglm -Isrc -Isrc/matrix_stack -Isrc/render -Isrc/skeleton -Isrc/console -Isrc/ft_math
endif


CFLAGS += -Wall -Wextra -Werror $(WARNINGS_) $(INCLUDES_) -g
CPPFLAGS += -Wall -Wextra -Werror $(WARNINGS_) $(INCLUDES_) -std=c++11 -g
MFLAGS += -g

CC = gcc
MC = clang
CPPC = g++
LINKER = g++

all: $(OBJDIR) $(DEPDIR) $(NAME)

run: $(OBJDIR) $(DEPDIR) $(NAME)
	./$(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(DEPDIR):
	mkdir $(DEPDIR)

$(NAME): $(OBJ)
ifeq ($(UNAME_S),Linux)
	cd glfw && cd glfw-3.3.4 && cmake . && make --silent
	$(LINKER) $(OBJ) -L./glfw/glfw-3.3.4/src -lglfw3 -pthread -lGL -ldl -lm -lXi -lXcursor -lX11 -o $(NAME)
endif
ifeq ($(UNAME_S),Darwin)
# 	OpenGL
	$(LINKER) -framework Cocoa -framework OpenGL -framework QuartzCore -framework IOKit -Lglfw/lib-universal -lglfw3 $(OBJ) -o $(NAME)
# 	Metal
# 	$(LINKER) -framework Cocoa -framework Metal -framework MetalKit -framework QuartzCore $(OBJ) -o $(NAME) -I. -g
endif


clean:
	rm -rf $(OBJDIR)
	rm -rf $(DEPDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all


$(DEPDIR)/%.cd.compiled: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MM $< | sed -E 's_[A-Za-z_]*\.o_obj/&_' > "$@.compiled"

$(DEPDIR)/%.cpp.cd.compiled: %.cpp
	mkdir -p $(dir $@)
	$(CPPC) $(CPPFLAGS) -MM $< | sed -E 's_[A-Za-z_]*\.o_obj/&_' > "$@.compiled"

$(DEPDIR)/%.md.compiled: %.m
	mkdir -p $(dir $@)
	$(MC) $(CFLAGS) -MM $< | sed -E 's_[A-Za-z_]*\.o_obj/&_' > "$@.complied"

DEPFLAGS=-MT $@ -MMD -MP

$(OBJDIR)/%.cpp.o : %.cpp
$(OBJDIR)/%.cpp.o : %.cpp $(DEPDIR)/%.cpp.cd | .dep
	mkdir -p $(dir $@)
	mkdir -p $(dir $(DEPDIR)/$*.cpp.cd)
	$(CPPC) -c $(CPPFLAGS) $(DEPFLAGS) -MF $(DEPDIR)/$*.cpp.cd.compiled $< -o $@
	mv -f $(DEPDIR)/$*.cpp.cd.compiled $(DEPDIR)/$*.cpp.cd
$(OBJDIR)/%.o : %.c
$(OBJDIR)/%.o : %.c $(DEPDIR)/%.cd | .dep
	mkdir -p $(dir $@)
	mkdir -p $(dir $(DEPDIR)/$*.cd)
	$(CC) -c $(CFLAGS) $(DEPFLAGS) -MF $(DEPDIR)/$*.cd.compiled $< -o $@
	mv -f $(DEPDIR)/$*.cd.compiled $(DEPDIR)/$*.cd
$(OBJDIR)/%.o : %.m
$(OBJDIR)/%.o : %.m $(DEPDIR)/%.md | .dep
	mkdir -p $(dir $@)
	mkdir -p $(dir $(DEPDIR)/$*.cd)
	$(MC) -c $(MFLAGS) $(DEPFLAGS) -MF $(DEPDIR)/$*.md.compiled $< -o $@
	mv -f $(DEPDIR)/$*.md.compiled $(DEPDIR)/$*.md

$(DEPDIR)/%.md: ;
$(DEPDIR)/%.cd: ;
.PRECIOUS: $(DEPDIR)/%.md $(DEPDIR)/%.cd

include $(shell find .dep -type f -name '*.md') $(shell find .dep -type f -name '*.cd')







