CFLAGS ?= -O2 -g

CFLAGS += -std=gnu99

CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
	-Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
	-Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
	-Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
	-Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value

CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error

CC += -m32 -no-pie -fno-pie

LDLIBS = -lm

OBJECTSASM = f1.o f2.o f3.o df1.o df2.o df3.o
OBJECTSC = integral.o main.o

.PHONY: all

all: integral clean

integral: $(OBJECTSASM) $(OBJECTSC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

$(OBJECTSASM):	%.o: %.asm
	nasm -f elf32 -o $@ $<

$(OBJECTSC): %.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm *.o 

test:
	./integral --test
