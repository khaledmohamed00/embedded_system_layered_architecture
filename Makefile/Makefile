

#to use makefile 
# On command line:
#  make all = make hex + make lst + make lss + make sym
#  make hex = create .hex file
#  make lst = create .lst file
#  make lss = create .lss file 
#  make sym = create .sym file 
#  make load = to load hex file into microcontroller  

#the parameter that you can change according to your project 
TARGET=main#the name of the target
INCL=adc.h lcdlib.h #all .h files
SRC=main.c adc.c lcdlib.c # all .c files
OBJ=$(SRC:.c=.o)
MCU=atmega328p #the microcontroller you use
OPT=-Os #Optimization level
AVRDUDE_PROGRAMMER = stk500 #the name of the programmer you use
AVRDUDE_MCU=m328#avrdude the type of mcu that is connected to the programmer
AVRDUDE_PORT = ttyUSB0  #the port your programmeris connected to

CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes $(OPT) -mcall-prologues

CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
NM = avr-nm





#add dependencies
$(OBJ):$(INC)
$(OBJ):$(SRC)

all: elf hex lst lss sym

elf: $(TARGET).elf
hex: $(TARGET).hex
lst: $(TARGET).lst
lss: $(TARGET).lss 
sym: $(TARGET).sym


#create .hex file from .elf file by extracting data and text section from .elf file that is the output of the linker

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

#link: create .elf file from .o object files and .map file 
%.elf:$(OBJ)
	$(CC) -g -mmcu=atmega328p -Wl,-Map,$(TARGET).map -o $(TARGET).elf $(OBJ) 

#compile :create .o object files from .c source files 
%.o:%.c 
	$(CC) -g $(OPT) -mmcu=atmega328p -c $*.c	

 


#create listing files from .elf file
%.lst: %.elf
	$(OBJDUMP) -h -S $(TARGET).elf > $(TARGET).lst

#create a symbol table from .elf file
%.sym: %.elf
	$(NM) -n $< > $@	

#create extended listing file from .elf file
%.lss: %.elf
	$(OBJDUMP) -h -S $< > $@	

#load the .hex file to microcontroller 
load: $(TARGET).hex
	avrdude -P /dev/$(AVRDUDE_PORT) -p $(AVRDUDE_MCU) -c $(AVRDUDE_PROGRAMMER) -e -U flash:w:$(TARGET).hex


 	 
