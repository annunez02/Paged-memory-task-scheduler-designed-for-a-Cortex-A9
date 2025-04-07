CHAIN=arm-none-eabi
VM=qemu-system-arm
VM=qemu-system-arm
BOARD=realview-pb-a8
VMFLGS=-M $(BOARD) -m 32M -no-reboot -nographic -monitor telnet:127.0.0.1:1234,server,nowait
CFLAGS=-std=gnu99 -Wall -mcpu=cortex-a8

OBJ_DIR=obj
BIN_DIR=bin
INC_DIR=inc
SRC_DIR=src
LST_DIR=lst

#nombre del archivo .c o .s y su .o

STARTFS = reset startup handlers tables low_level_cpu_access

OBJ_SFILES := $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(STARTFS)))

STARTFC = mmu mmu_tools_ gic timer board_init kernel_handler_irq scheduler tarea_1 tarea_2 tarea_3 tarea_idle 

OBJ_CFILES := $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(STARTFC)))


#nombre del .elf y .bin para el .c y .s
BINF=bios

# $^ is a automatic variable that represents the list of all prerequisites of a target
# $@ is another automatic variable that represents the target being built
# $< is another automatic variable that represents the first prerequisite of a target.

all: $(BIN_DIR)/$(BINF).bin $(OBJ_DIR)/$(BINF).elf

$(BIN_DIR)/$(BINF).bin: $(OBJ_DIR)/$(BINF).elf
	$(CHAIN)-objcopy -O binary $< $@

$(OBJ_DIR)/$(BINF).elf: $(OBJ_SFILES) $(OBJ_CFILES)
	@echo "Linkeando ... "
	mkdir -p $(OBJ_DIR)
	mkdir -p $(LST_DIR)
	# $(CHAIN)-ld $^ -o $@ -Map $(LST_DIR)/$(BINF).map
	$(CHAIN)-ld -T memmap.ld $^ -o $@ -Map $(LST_DIR)/$(BINF).map
	@echo "Linkeo finalizado!"
	@echo ""
	@echo "Generando archivos de información: mapa de memoria y símbolos"
	readelf -a $@ >>$(LST_DIR)/$(BINF)_elf.txt
	$(CHAIN)-objdump -D $@ >>$(LST_DIR)/$(BINF).lst

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@echo ""
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(LST_DIR)
	@echo "Ensamblando $<..."
	$(CHAIN)-as $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst
	@echo "Compilando $<..."
	$(CHAIN)-gcc -g -marm $(CFLAGS) -c $< -o $@

run:
	$(VM) $(VMFLGS) -kernel $(BIN_DIR)/$(BINF).bin -S -gdb tcp::2159

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(OBJ_DIR)/*.elf
	rm -rf $(BIN_DIR)/*.bin
	rm -rf $(LST_DIR)/*.lst
	rm -rf $(LST_DIR)/*.txt
	rm -rf $(LST_DIR)/*.map



