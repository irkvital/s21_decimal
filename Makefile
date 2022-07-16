CC =				gcc
CFLAGS =			-Wall -Werror -Wextra -O0
GCOV_FLAGS = 		-fprofile-arcs -ftest-coverage -lgcov
CHECK_FLAGS =		-lcheck -lm -lpthread 
FLAGS =				$(CFLAGS) $(CHECK_FLAGS) $(GCOV_FLAGS)

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	CHECK_FLAGS += -lsubunit -lrt
endif

vpath 			%.o objs objs_test
vpath 			%.d objs objs_test

SRCS 		= 	$(wildcard s21_*.c)
OBJS 		= 	$(SRCS:%.c=objs/%.o)
DEPENDS 	= 	$(OBJS:%.o=%.d)

SRCSTEST 	= 	$(wildcard *.c tests/*.c)
OBJSTEST 	= 	$(SRCSTEST:%.c=objs_test/%.o)
DEPENDSTEST = 	$(OBJSTEST:%.o=%.d)
OBJTESTDIR 	= 	objs_test objs_test/tests

NAME 		= 	test
MYLIB 		= 	s21_math.a
REPORT_NAME = 	report

.PHONY: all test gcov_report

all: $(MYLIB) gcov_report

test: $(OBJSTEST)
	$(CC) $(OBJSTEST) -o $(NAME) $(FLAGS)

-include $(DEPENDS) $(DEPENDSTEST)

clean: clean_gcov
	rm -rf objs *.a
clean_gcov:
	rm -rf objs_test *.info $(REPORT_NAME) $(NAME) check_res finish

$(MYLIB): $(OBJS)
	ar rc $(MYLIB) $(OBJS)
	ranlib $(MYLIB)

objs/%.o: %.c
	@mkdir -p objs
	$(CC) -MMD -o $@ -c $< $(CFLAGS)

objs_test/%.o: %.c
	@mkdir -p $(OBJTESTDIR)
	$(CC) -MMD -o $@ -c $< $(FLAGS)

gcov_report: test
	./$(NAME)
#	geninfo $(wildcard $(OBJTESTDIR)/*.gcda) -b . -o check_res
#	genhtml check_res -o finish
	lcov -t "$(REPORT_NAME)" -o $(REPORT_NAME).info -c -d .
	genhtml $(REPORT_NAME).info -o finish
ifeq ($(UNAME), Darwin)
	open finish/index.html
endif

debug: FLAGS += -fsanitize=address -g
debug: clean_gcov gcov_report

lint:
	cp ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py --extensions=c *.h *.c
	rm -rf CPPLINT.cfg

cppcheck:
	cppcheck --suppress=missingIncludeSystem --enable=all *.c