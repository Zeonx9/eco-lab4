ifeq ($(OS), Windows_NT)
	#WINDOWS USE THESE DEFINITIONS
	RM = -rm -f
	SLASH = \\
	SWALLOW_OUTPUT = >nul 2>nul
else
	#LINUX USE THESE DEFINITIONS
	RM = -rm -f
	SLASH = /
	SWALLOW_OUTPUT =
endif 

INCLUDES = \
-I ..$(SLASH)..$(SLASH)..$(SLASH)HeaderFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)SharedFiles \
-I C:/EcoFramework/Projects/lab4/Eco.Lab4$(SLASH)Eco.MemoryManager1Lab$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.IPCC.Mailbox1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.CGI1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.VFB1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.Core1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.InterfaceBus1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.Timer1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.InterruptController1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.TaskScheduler1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.MemoryManager1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.FileSystemManagement1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.String1$(SLASH)SharedFiles

LIB = \
-L ..$(SLASH)..$(SLASH)..$(SLASH)BuildFiles$(SLASH)BCM283x$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L C:/EcoFramework/Projects/lab4/Eco.Lab4$(SLASH)Eco.MemoryManager1Lab$(SLASH)BuildFiles$(SLASH)BCM283x$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.IPCC.Mailbox1$(SLASH)BuildFiles$(SLASH)BCM283x$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.VFB1$(SLASH)BuildFiles$(SLASH)BCM283x$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.Timer1$(SLASH)BuildFiles$(SLASH)BCM283x$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.InterruptController1$(SLASH)BuildFiles$(SLASH)BCM283x$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.InterfaceBus1$(SLASH)BuildFiles$(SLASH)BCM283x$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.TaskScheduler1$(SLASH)BuildFiles$(SLASH)BCM283x$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.FileSystemManagement1$(SLASH)BuildFiles$(SLASH)BCM283x$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.MemoryManager1$(SLASH)BuildFiles$(SLASH)BCM283x$(SLASH)arm64-v8a$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.String1$(SLASH)BuildFiles$(SLASH)BCM283x$(SLASH)arm64-v8a$(SLASH)StaticRelease

Pi3-64: CFLAGS = -Wall -std=gnu89 -Wno-missing-braces -march=armv8-a+simd -mtune=cortex-a53 -mstrict-align -fno-tree-loop-vectorize -fno-tree-slp-vectorize -DECO_LIB -DECO_BCM283X -DUGUID_UTILITY $(INCLUDES)
Pi3-64: IMGFILE = kernel8.img
#Pi3-64: ARMGNU  = $(ECO_TOOLCHAIN)$(SLASH)gcc-linaro-7.5.0$(SLASH)bin$(SLASH)
Pi3-64: ARMGNU  = C:$(SLASH)toolchain$(SLASH)gcc-linaro-7.5.0$(SLASH)bin$(SLASH)
Pi3-64: LINKERFILE = startup.ld
Pi3-64: PISTART = ..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)entry.S


LDFLAGS = -nostartfiles -ffreestanding -fno-asynchronous-unwind-tables -fomit-frame-pointer 

LIBFLAGS=-static $(LIB) -l0000000000000000000000004D656D31 -lF10BC39A4F2143CF8A1E104650A2C302 -l84CC0A7DBABD44EEBE749C9A8312D37E -l8DB93F3DF5B947D4A67F7C100B569723 -l939B1DCDB6404F7D9C072291AF252188 -l00000000000000000000000042757331 -l81589BFED0B84B1194524BEE623E1838 -lc -lm -lgcc 

LINKERFLAGS=-Wl,-Map,kernel.map
ASMFLAGS=-nostartfiles -ffreestanding -fno-asynchronous-unwind-tables -fomit-frame-pointer -Wa,-a>list.txt"

# The directory in which source files are stored.
SOURCE = \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)MySimpleEcoOS.c


# The name of the assembler listing file to generate.
LIST = kernel.list

# The name of the map file to generate.
MAP = kernel.map

# The names of all object files that must be generated. Deduced from the 
# assembly code files in source.
C_FILES := $(filter-out $(SOURCE), $(wildcard *.c))

# Rule to make everything.
Pi3-64: $(LIST)
	
# Rule to remake everything. Does not include clean.
all: Pi3-64

# Rule to make the image & listing files.
$(LIST) : kernel.elf
	$(ARMGNU)aarch64-elf-objdump -d kernel.elf > $(LIST)
	$(ARMGNU)aarch64-elf-objcopy kernel.elf -O binary $(IMGFILE)
	$(ARMGNU)aarch64-elf-nm -n kernel.elf > $(MAP)

OBJDIR := build
target = ${OBJDIR}/$(patsubst %.c,%.o,$(notdir ${1}))
obj.c :=
define obj
  $(call target,${1}) : ${1} | 
  obj$(suffix ${1}) += $(call target,${1})
endef

define SOURCES
  $(foreach src,${1},$(eval $(call obj,${src})))
endef

$(eval $(call SOURCES,${C_FILES}))

main.c : ${obj.c}

 ${obj.c} : % :
	$(ARMGNU)aarch64-elf-gcc $(CFLAGS) $(ASMFLAGS) $(LDFLAGS) -c $^ -o $@
# Uncomment this if you want the assembler output of each object file
#	$(ARMGNU)aarch64-elf-gcc $(CFLAGS) $(LDFLAGS) -S $^ -o $(patsubst %.o,%.s,$(@))

kernel.elf : main.c
	$(ARMGNU)aarch64-elf-gcc $(CFLAGS) $(LDFLAGS) $(LINKERFLAGS) -Wl,-T,$(LINKERFILE) $(wildcard $(OBJDIR)/*.o)  -o $@ $(SOURCE) $(PISTART) $(LIBFLAGS) 

# Control silent mode  .... we want silent in clean
.silent:clean

# cleanup temp files
clean:
	$(RM) $(MAP) $(SWALLOW_OUTPUT)
	$(RM) kernel.elf $(SWALLOW_OUTPUT)
	$(RM) $(LIST) $(SWALLOW_OUTPUT)
	$(RM) $(OBJDIR)$(SLASH)*.o $(SWALLOW_OUTPUT)
	$(RM) $(OBJDIR)$(SLASH)*.s $(SWALLOW_OUTPUT)
	echo CLEAN COMPLETED
