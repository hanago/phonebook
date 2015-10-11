CC ?= gcc
CFLAGS_common ?= -O0 -Wall -std=gnu99 -Wl,--no-as-needed -lrt

EXEC = phonebook_orig phonebook_opt
all: $(EXEC)

SRCS_common = main.c

phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_opt: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

run_orig: $(EXEC)
	watch -d -t ./phonebook_orig

run_opt: $(EXEC)
	watch -d -t ./phonebook_opt

clean:
	$(RM) $(EXEC) *.o perf.*
