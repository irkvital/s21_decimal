CC = gcc -g -fsanitize=address

OBJECTS:= ../../../s21_decimal.a
RM:= rm -rf

all: test_int_add test_int_sub test_int_mul test_int_div test_float_add test_float_sub test_float_mul test_float_div
PHONY: all

test_int_add:  $(OBJECTS) addition_test.c
	$(CC) addition_test.c $(OBJECTS) -o $@ -lgmp -lm

test_int_sub:  $(OBJECTS) subtraction_test.c
	$(CC) subtraction_test.c $(OBJECTS) -o $@ -lgmp -lm

test_int_mul:  $(OBJECTS) multiplication_test.c
	$(CC) multiplication_test.c $(OBJECTS) -o $@ -lgmp -lm

test_int_div:  $(OBJECTS) division_test.c
	$(CC) division_test.c $(OBJECTS) -o $@ -lgmp -lm

test_float_add:  $(OBJECTS) float_addition_test.c
	$(CC) float_addition_test.c $(OBJECTS) -o $@ -lgmp -lm

test_float_sub:  $(OBJECTS) float_subtraction_test.c
	$(CC) float_subtraction_test.c $(OBJECTS) -o $@ -lgmp -lm

test_float_mul:  $(OBJECTS) float_multiplication_test.c
	$(CC) float_multiplication_test.c $(OBJECTS) -o $@ -lgmp -lm

test_float_div:  $(OBJECTS) float_division_test.c
	$(CC) float_division_test.c $(OBJECTS) -o $@ -lgmp -lm

%.o: %.c
	$(CC) -c $< -o $@ -lm

clean:
	@$(RM) ../../another/*.o \
	../../arithmetic/*.o \
	../../comparison/*.o \
	../../convertion/*.o \
	../../core/*.o \
	*out \
	*.o test_int_add test_int_sub \
	test_int_mul test_int_div \
	test_float_add test_float_sub \
	test_float_div test_float_mul

rebuild: clean test