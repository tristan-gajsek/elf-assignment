PARAMS = -Wall -Wextra -Wpedantic -Werror

all: build run
build: build_elf_changer build_hello
build_elf_changer:
	@gcc $(PARAMS) -m32 -o elf_changer elf_changer.c
	@chmod u+x elf_changer
build_hello:
	@gcc $(PARAMS) -m32 -o hello hello.c
	chmod u+x hello
run:
	@./elf_changer
clean:
	@rm -f elf_changer hello
