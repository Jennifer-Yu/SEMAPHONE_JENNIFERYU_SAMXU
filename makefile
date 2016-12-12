compile: semacontrol.c
	gcc semacontrol.c -o semacontrol
	gcc semaclient.c -o semaclient

create: phonecall
	./semacontrol -c

view: phonecall
	./semacontrol -v

remove: phonecall
	./semacontrol -r

clean:
	rm ./semacontrol
	rm ./semaclient
	rm *.o
	rm *~
