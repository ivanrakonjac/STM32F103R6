PROGRAM = program
BUILD_DIR = build

SRC_S_LIST = \
src/startup_code.s

SRC_C_LIST = \
src/main.c \
src/systick.c

INCLUDE_C_LIST = \
-Iinc

OBJECTS_LIST = 
OBJECTS_LIST += $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_S_LIST:.s=.o)))
OBJECTS_LIST += $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_C_LIST:.c=.o)))

vpath %.s $(sort $(dir $(SRC_S_LIST)))
vpath %.c $(sort $(dir $(SRC_C_LIST)))

CC = arm-none-eabi-gcc.exe -c 
AS = arm-none-eabi-gcc.exe -c -x assembler
LD = arm-none-eabi-ld.exe
HX = arm-none-eabi-objcopy.exe -O ihex

MCU = -mcpu=cortex-m3 -mthumb
DEBUG_FLAGS = -g -gdwarf-2 -fdebug-prefix-map==../

FLAGS_AS = 
FLAGS_AS += $(MCU)
FLAGS_AS += $(DEBUG_FLAGS)

FLAGS_CC = 
FLAGS_CC += $(MCU)
FLAGS_CC += $(DEBUG_FLAGS)
FLAGS_CC += -MMD -MP
FLAGS_CC += $(INCLUDE_C_LIST)

all : $(BUILD_DIR)/$(PROGRAM).elf $(BUILD_DIR)/$(PROGRAM).hex

$(BUILD_DIR)/$(PROGRAM).hex : $(BUILD_DIR)/$(PROGRAM).elf
	$(HX) $(<) $(@)
	
$(BUILD_DIR)/$(PROGRAM).elf : $(OBJECTS_LIST) makefile
	$(LD) -T linker_script.ld -o $(@) $(OBJECTS_LIST)
	
$(BUILD_DIR)/%.o : %.s makefile | $(BUILD_DIR)
	$(AS) $(FLAGS_AS) -o $(@) $(<)
	
$(BUILD_DIR)/%.o : %.c makefile | $(BUILD_DIR)
	$(CC) $(FLAGS_CC) -o $(@) $(<)
	
$(BUILD_DIR) :
	mkdir $(@)
	
clean:
	rm -rf $(BUILD_DIR)
	
-include $(wildcard $(BUILD_DIR)/*.d)
	