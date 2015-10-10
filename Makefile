CC ?= gcc
CFLAGS_common ?= -O0 -Wall -std=gnu99 -Wl,--no-as-needed -lrt

EXEC = phonebook_orig phonebook_opt
all: $(EXEC)


phonebook_orig: main.c phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
		main.c $@.c

phonebook_opt: main_opt.c phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
		main_opt.c $@.c

run_orig: $(EXEC)
	watch -d -t ./phonebook_orig

run_opt: $(EXEC)
	watch -d -t ./phonebook_opt

clean:
	$(RM) $(EXEC) *.o perf.*
