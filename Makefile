###############################################################################
## Configuration
###############################################################################

CXX					=	g++

CXXFLAGS			=	-std=c++20 -Wall -Wextra \
						-IExternal/SFML/include -ISource \
						-lGL \
						-lz \
						-lm \
						-LExternal/SFML/lib \
						-lsfml-graphics-s \
						-lsfml-window-s \
						-lsfml-system-s \
						-lX11 \
						-lXrandr \
						-lXcursor \
						-lXinerama \
						-ludev \
						-lXi

TARGET				=	network-abyss
SERVER_TARGET		=	network-abyss-server
PACKER_TARGET		=	network-abyss-packer

###############################################################################
## Metadata
###############################################################################

AUTHOR				=	mallory-scotton
DATE				=	
HASH				=	

###############################################################################
## Sources
###############################################################################

SOURCE_DIRECTORY	=	Source

SOURCES				=	$(shell find $(SOURCE_DIRECTORY) -name '*.cpp')

###############################################################################
## Makefile logic
###############################################################################

ifeq ($(shell git rev-parse HEAD > /dev/null; echo $$?),0)
	AUTHOR			:=	$(shell git log --format='%aN' | sort -u | awk \
						'{printf "%s, ", $$0}' | rev | cut -c 3- | rev)
	DATE			:=	$(shell git log -1 --date=format:"%Y/%m/%d %T" \
						--format="%ad")
	HASH			:=	$(shell git rev-parse --short HEAD)
endif

MFLAGS				:=	$(CXXFLAGS)

COM_COLOR			=	\033[0;34m
OBJ_COLOR			=	\033[0;36m
OK_COLOR			=	\033[0;32m
ERROR_COLOR			=	\033[0;31m
WARN_COLOR			=	\033[0;33m
NO_COLOR			=	\033[m

OBJECTS				=	$(SOURCES:.cpp=.o)

DEPENDENCIES		=	$(SOURCES:.cpp=.d)

QUIET				?=	0

SFML_COMPILATION	:=	cd External/SFML && cmake . > /dev/null && make -s

###############################################################################
## Makefile rules
###############################################################################

all:
	@make QUIET=0 -s build
	@make QUIET=1 -s server
	@make QUIET=1 -s packer

-include $(DEPENDENCIES)

external:
	@./Scripts/run.sh "$(SFML_COMPILATION)" "SFML-3.0.0"

%.o: %.cpp
	@./Scripts/progress.sh
	@./Scripts/run.sh "$(CXX) -c $< -o $@ $(CXXFLAGS)" "$@"

clear:
	@rm -f Source/Main.o

header:
	@printf "%b" "$(OK_COLOR)"
ifeq ($(QUIET),0)
	@cat .art
endif
	@echo
ifneq ($(HASH),)
	@printf "%b" "$(OBJ_COLOR)Name:	$(WARN_COLOR)$(TARGET)@$(HASH)\n"
else
	@printf "%b" "$(OBJ_COLOR)Name:	$(WARN_COLOR)$(TARGET)\n"
endif
	@printf "%b" "$(OBJ_COLOR)Author:	$(WARN_COLOR)$(AUTHOR)\n"
	@printf "%b" "$(OBJ_COLOR)Date: 	$(WARN_COLOR)$(DATE)\n\033[m"
	@printf "%b" "$(OBJ_COLOR)CC: 	$(WARN_COLOR)$(CXX)\n\033[m"
	@printf "%b" "$(OBJ_COLOR)Flags: 	$(WARN_COLOR)$(MFLAGS)\n\033[m"
	@echo

setup: header external
	@./Scripts/setup.sh "$(SOURCES)" "$(EXTENSION)"

build: CXXFLAGS += -MMD -MF $(@:.o=.d)
build: setup clear $(OBJECTS)
	@./Scripts/run.sh "$(CXX) -o $(TARGET) $(OBJECTS) $(CXXFLAGS)" "$@"
	@rm -f .build

debug: CXXFLAGS += -g3
debug: build

server: TARGET = $(SERVER_TARGET)
server: OBJECTS = $(SERVER_OBJECTS)
server: CXXFLAGS += -DNEON_SERVER
server: clear build

packer: TARGET = $(PACKER_TARGET)
packer: OBJECTS = $(PACKER_OBJECTS)
packer: CXXFLAGS += -DNEON_PACKER
packer: clear build

clean:
	@find . -type f -iname "*.o" -delete
	@find . -type f -iname "*.d" -delete
	@find . -type f -iname "*.gcda" -delete
	@find . -type f -iname "*.gcno" -delete
	@find . -type f -iname "*.html" -delete
	@find . -type f -iname "*.css" -delete

fclean: clean
	@rm -f $(TARGET)
	@rm -f $(SERVER_TARGET)

re: fclean build
res: fclean server
rep: fclean packer

.PHONY: all build debug server clean fclean re res
