compile: semaphone.c
	gcc -o phonecall semaphone.c -Wall

create: phonecall
	./phonecall -c

view: phonecall
	./phonecall -v

remove: phonecall
	./phonecall -r

clean:
	rm ./phonecall
	rm *.o
	rm *~
