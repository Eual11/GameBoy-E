final:
	gcc main.c -Iinclude -Llibs -lcart -o build/e
lib: 
	gcc -c libs/cart.c -o cart.o -Iinclude
	ar rc libs/libcart.a cart.o
clean: 
	rm cart.o 
	rm build/e.exe