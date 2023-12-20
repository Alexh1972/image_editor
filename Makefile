# Copyright Cazacu Alexandru-Dan 312CA 2023-2024

CFLAGS = -Wall -Wextra

build: compile valgrind clean
compile:
	gcc -g image_editor.c application.c image.c command.c utils.c memory.c $(CFLAGS) -o image_editor -lm
run:
	./image_editor
clean: 
	rm image_editor
valgrind:
	valgrind --leak-check=full ./image_editor
gdb:
	gdb ./image_editor
pack:
	zip 312CA_CazacuAlexandruDan_Tema3.zip *.c *.h Makefile README*
git:
	touch username
	rm username
	echo Alexh1972 > username
	git add *.c *.h Makefile README*
	git commit -m "new commit"
	git push -u origin main < username
	rm username