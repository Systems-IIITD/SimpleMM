default: random

libmemory.so: memory.c
	gcc -Werror -shared -O3 -fPIC -o libmemory.so memory.c

random: randomalloc.c libmemory.so
	gcc -O3 -L`pwd` -Wl,-rpath=`pwd` -o random randomalloc.c -lmemory

run: random
	/usr/bin/time -v ./random

test: random
	@/usr/bin/time -v ./random 1000000 > out 2>&1
	@/usr/bin/time -v ./random 2000000 >> out 2>&1 
	@/usr/bin/time -v ./random 3000000 >> out 2>&1
	@/usr/bin/time -v ./random 4000000 >> out 2>&1
	@egrep "Elapsed|replace|Minor|Maximum" out
	@rm out

clean:
	rm -f libmemory.so random out
