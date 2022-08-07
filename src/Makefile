CC 			=	gcc
CFLAGS 		=	-Wall -Wextra -std=c11
GCOV_FLAGS 	= 	-fprofile-arcs -ftest-coverage
CHECK_FLAGS =	-lcheck -lm -lpthread 
FLAGS 		=	$(CFLAGS) $(CHECK_FLAGS) $(GCOV_FLAGS)
GFLAGS 		=	$(FLAGS)

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	CHECK_FLAGS += -lsubunit -lrt
endif

vpath 			%.o objs objs_test
vpath 			%.d objs objs_test

SRCS 		= 	$(wildcard s21_*.c)
OBJS 		= 	$(SRCS:%.c=objs/%.o)
DEPENDS 	= 	$(OBJS:%.o=%.d)

#SRCSTEST 	= 	$(wildcard *.c)
SRCSTEST 	= 	$(wildcard s21_*.c tests/*.c)
OBJSTEST 	= 	$(SRCSTEST:%.c=objs_test/%.o)
DEPENDSTEST = 	$(OBJSTEST:%.o=%.d)
OBJTESTDIR 	= 	objs_test objs_test/tests

NAME 		= 	test
MYLIB 		= 	s21_decimal.a
REPORT_NAME = 	report

.PHONY: all test gcov_report

all: $(MYLIB) 

test: $(OBJSTEST)
	rm -rf $(wildcard objs_test/*.gcda objs_test/tests/*.gcda)
	$(CC) $(OBJSTEST) -o $(NAME) $(GFLAGS)

-include $(DEPENDS) $(DEPENDSTEST)

clean: clean_gcov
	rm -rf objs *.a
clean_gcov:
	rm -rf objs_test *.info $(REPORT_NAME) $(NAME) finish

$(MYLIB): $(OBJS)
	ar rc $(MYLIB) $(OBJS)
	ranlib $(MYLIB)

objs/%.o: %.c
	@mkdir -p objs
	$(CC) -MMD -o $@ -c $< $(CFLAGS)

objs_test/%.o: %.c
	@mkdir -p $(OBJTESTDIR)
	$(CC) -MMD -o $@ -c $< $(FLAGS)

gcov_report: GFLAGS += -lgcov
gcov_report: test
	./$(NAME)
	lcov -t "$(REPORT_NAME)" -o objs_test/$(REPORT_NAME).info -c -d .
	genhtml objs_test/$(REPORT_NAME).info -o finish

debug: FLAGS += -fsanitize=address -g
debug: gcov_report

lint:
	cp ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py --extensions=c *.h *.c
	rm -rf CPPLINT.cfg

cppcheck:
	cppcheck --suppress=missingIncludeSystem --enable=all *.c

h:
ifeq ($(UNAME), Linux)
	firefox finish/index.html
endif
ifeq ($(UNAME), Darwin)
	open finish/index.html
endif
