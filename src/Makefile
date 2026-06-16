FLAG=-std=c11

build:
	@mkdir ./build
	@cp *.c *.cpp *.h *.pro *.ui *.qrc *.glsl new_settings.cfg settings.cfg ./build
	@cd ./build; qmake 3DViewer.pro
	@make -C build
	@cd build; rm -rf *.c *.h *.cpp *.ui *.pro *.o Makefile

install: build
	@cp -rf build/3Dviewer.app $(HOME)/Applications/

uninstall:
	rm -rf $(HOME)/Applications/3Dviewer.app

tests: viewer.a
	gcc $(FLAG) tests.c viewer.a -lcheck -o test && ./test

viewer.o: affine_transformation.c parser.c
	@gcc $(FLAG) -c -o affine_transformation.o affine_transformation.c
	@gcc $(FLAG) -c -o parser.o parser.c

dvi:
	open info.html

dist:
	@mkdir ../DDD.0
	@mkdir ../DDD/src
	@cp -rf *.cpp *.c Makefile *.ui *.h *.pro *.user ../DDD/src
	@cd ..; tar czvf DDD.tgz DDD/*
	#@mv ../DDD.tgz $(HOME)/Desktop/
	@rm -rf ../DDD
viewer.a: viewer.o
	@ar rcs viewer.a *.o

gcov_report: clean
	@gcc $(FLAG) --coverage tests.c parser.c affine_transformation.c -o test -lcheck $(LINUX)
	@./test
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	@open ./report/index.html

clean:
	rm -rf *.o *.a *.gcba *.gcno *.gcda *.info
	rm -rf report ./test
	rm -rf build