NAME	:=	decrypt

SRCS_ASM = 	decrypt.asm

OBJS_ASM    =  $(addprefix ${OBJDIR}/,${SRCS_ASM:.asm=.o})

ASMC    =   nasm
OBJDIR 	=	.objs

_GREY=	$'\033[30m
_RED=	$'\033[31m
_GREEN=	$'\033[32m
_YELLOW=$'\033[33m
_BLUE=	$'\033[34m
_PURPLE=$'\033[35m
_CYAN=	$'\033[36m
_WHITE=	$'\033[37m
_END= $'\033[37m

all:		${NAME}

$(OBJDIR)/%.o: %.asm
	@mkdir -p ${OBJDIR}
	@printf "%-15s ${_CYAN}${_BOLD}$<${_END}...\n" "Compiling"
	@${ASMC} -f elf64 $< -o $@

${NAME}:	init ${OBJS_ASM}
	@printf "%-15s ${_PURPLE}${_BOLD}${NAME}${_END}...\n" "Compiling"
	@ld -o ${NAME} ${OBJS_ASM}
	@printf "\n${_GREEN}${_BOLD}Compilation done !${_END}\n"

clean:		
	@printf "%-15s ${_RED}${_BOLD}${NAME}'s object files${_END}...\n" "Deleting"
	@rm -f ${OBJS}
	@printf "%-15s ${_RED}${_BOLD}${NAME}'s object directory${_END}...\n" "Deleting"
	@rm -rf ${OBJDIR}

fclean:		clean
	@printf "%-15s ${_RED}${_BOLD}${NAME}${_END}...\n" "Deleting"
	@rm -f ${NAME}

init:
	@printf "%-15s ${_GREEN}${_BOLD}${NAME}${_END}...\n" "Initiating"
	@mkdir -p ${OBJDIR}

show:
	@echo "Project configfuration:"
	@echo "  name:      ${NAME}"
	@echo "  sources:   ${SRCS}"
	@echo "  objects:   ${OBJS}"
	@echo "  includes:  ${INCS}"
	@echo "  compiler:  ${CC}"
	@echo "  flags:     ${FLAGS}"

run:		all
	@printf "${_GREEN}${_BOLD}Running ${NAME}...${_END}\n"
	@./${NAME} || true

rerun:		re
	@printf "${_GREEN}${_BOLD}Running ${NAME}...${_END}\n"
	@./${NAME} || true

re:			fclean all

help:
	@echo "Available make rules:"
	@echo "  all:       Build the executable ${NAME}."
	@echo "  clean:     Remove object files and object directory."
	@echo "  fclean:    Remove object files, object directory, and the executable ${NAME}."
	@echo "  init:      Initialize directories for object files and dependencies."
	@echo "  show:      Display information about the project configuration."
	@echo "  run:       Build and run the executable ${NAME}."
	@echo "  rerun:     Clean and rebuild, then run the executable ${NAME}."
	@echo "  re:        Rebuild the executable ${NAME}"
	@echo "  help:      Display this help message."

.PHONY:		all fclean clean init show re run rerun help
