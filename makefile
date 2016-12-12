compile: semacontrol.c
	gcc semacontrol.c -o semacontrol
	gcc semaclient.c -o semaclient

create: semacontrol
	./semacontrol -c

view: semacontrol
	./semacontrol -v

remove: semacontrol
	./semacontrol -r

stat:
	ipcs -s
	ipcs -m

clean:
	rm ./semacontrol
	rm ./semaclient
	rm *~
