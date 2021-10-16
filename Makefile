

NAME=humangl

DEPDIR=.dep
OBJDIR=.obj

SRC = glad/src/glad.c
CPPSRC = main.cpp
MSRC = 
ALL_SRC= $(MSRC) $(CPPSRC) $(SRC)

OBJ1=$(ALL_SRC:.c=.o)
OBJ2=$(OBJ1:.m=.o)
OBJ3=$(OBJ2:.cpp=.cpp.o)
OBJ=$(addprefix $(OBJDIR)/,$(OBJ3))

WARNINGS_ = -Wno-sizeof-array-argument -Wno-unknown-warning-option -Wno-sizeof-pointer-div -Wno-unneeded-internal-declaration -Wno-unused-parameter -Wno-unused-variable
INCLUDES_ = -Iglfw/include -Iglad/include

CFLAGS += -Wall -Wextra -Werror -pedantic $(WARNINGS_) $(INCLUDES_) -g
CPPFLAGS += -Wall -Wextra -Werror -pedantic $(WARNINGS_) $(INCLUDES_) -std=c++11 -g
MFLAGS += -g

CC = gcc
MC = clang
CPPC = g++
LINKER = g++

all: $(OBJDIR) $(DEPDIR) $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(DEPDIR):
	mkdir $(DEPDIR)


$(NAME): $(OBJ)
#     Linux
# 	$(LINKER) $(OBJ) -o $(NAME) -lGL -ldl -lm -lX11 -lasound -lXi -lXcursor
#     MacOS
# 	OpenGL
	$(LINKER) -framework Cocoa -framework OpenGL -framework QuartzCore -framework IOKit -Lglfw/lib-universal -lglfw3 $(OBJ) -o $(NAME)
# 	Metal
# 	$(LINKER) -framework Cocoa -framework Metal -framework MetalKit -framework QuartzCore $(OBJ) -o $(NAME) -I. -g

clean:
	rm -rf $(wildcard $(OBJDIR)/*.o)
	rm -rf $(wildcard $(DEPDIR)/*d)

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

include $(wildcard $(DEPDIR)/*.md) $(wildcard $(DEPDIR)/*.cd)







