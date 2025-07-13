#--------------------------------------------------#
#                  Usage                           #
#--------------------------------------------------#
# 1. Set the GCC compiler directory                #
# 2. Set the SDK directory                         #
#--------------------------------------------------#
# 3. Set the compiler defines                      #
# 4. Set the executable file name (without ext.)   #
#--------------------------------------------------#
#                                                  #
# In the Build section                             #
#                                                  #
# 5. Set OBJ with your .o file names               #
# 6. Add a section for each .c to compile          #
#--------------------------------------------------#
GCC_VERSION = 3.4.3

ROOT_ARM   = C:\GCC_$(GCC_VERSION)
ROOT_SDK   = ..\..\..

DEFINES    = -D_EFT30_ -D_EXPORT_
DEST_NAME  = Sample

#--------------------------------------------------#
#                  Compiler                        #
#--------------------------------------------------#
ARM_EXE    = $(ROOT_ARM)\BIN
ARM_LIB_TYPE = thumb\soft\interwork
ARM_LIB1   = $(ROOT_ARM)\arm-elf\lib\$(ARM_LIB_TYPE)
ARM_LIB2   = $(ROOT_ARM)\lib\gcc\arm-elf\$(GCC_VERSION)\$(ARM_LIB_TYPE)

#--------------------------------------------------#
#                  SDK                             #
#--------------------------------------------------#
SDK_INC    = $(ROOT_SDK)\Inc
SDK_SAMPLES_INC    = $(ROOT_SDK)\Samples\Inc
SDK_LIB    = $(ROOT_SDK)\Lib_GNU

#--------------------------------------------------#
#                  Project                         #
#--------------------------------------------------#
PRJ_ROOT   = ..

#--------------------------------------------------#
#                  Source                          #
#--------------------------------------------------#
SOURCE_DIR = $(PRJ_ROOT)\Src

#--------------------------------------------------#
#                  Object                          #
#--------------------------------------------------#
OBJ_DIR    = $(PRJ_ROOT)\GNU\Obj

#--------------------------------------------------#
#                  Target                          #
#--------------------------------------------------#
AXF_FILE   = "$(OBJ_DIR)\$(DEST_NAME).AXF"
SGN_FILE   = "$(OBJ_DIR)\$(DEST_NAME).SGN"
BIN_FILE   = "$(OBJ_DIR)\$(DEST_NAME).BIN"
MAP_FILE   = "$(OBJ_DIR)\$(DEST_NAME).MAP"

#--------------------------------------------------#
#                  Compiler                        #
#--------------------------------------------------#
INCLUDES   = -I "$(SDK_SAMPLES_INC)" -I "$(SDK_INC)" -I "..\..\Interface"
CCOPT      = -Os -Wall -Wcast-align -mthumb -mthumb-interwork -mlittle-endian -msoft-float -pipe -mcpu=arm920t -fomit-frame-pointer -fshort-enums -mstructure-size-boundary=8 -c
COMPILE    = "$(ARM_EXE)\arm-elf-gcc" $(CCOPT) $(DEFINES) $(INCLUDES)

#--------------------------------------------------#
#                  Assembler                       #
#--------------------------------------------------#
ASMOPT     = -mthumb-interwork -EL -mno-fpu
ASSEMBLE   = "$(ARM_EXE)\arm-elf-as" $(ASMOPT)

#--------------------------------------------------#
#                  Linker                          #
#--------------------------------------------------#
LINKOPT    = --print-map --cref --script="$(SDK_LIB)\gcc_link.txt"
SYSOBJ     = "$(SDK_LIB)\cstartup.o"  "$(SDK_LIB)\LinkLayerExeInterface.lib" "$(SDK_LIB)\AVL.lib"
LIBS       = "$(SDK_LIB)\eft30.lib" "$(SDK_LIB)\trap.lib" -L "$(ARM_LIB1)" -L "$(ARM_LIB2)" -lc -lgcc
LINK       = "$(ARM_EXE)\arm-elf-ld"
ELF        = "$(ARM_EXE)\arm-elf-objcopy"
ELF_SIZE   = "$(ARM_EXE)\arm-elf-size"


#--------------------------------------------------#
#                  Build                           #
#--------------------------------------------------#
OBJ        = "$(OBJ_DIR)\Communication.o" "$(OBJ_DIR)\Entry.o" "$(OBJ_DIR)\Menu.o" "$(OBJ_DIR)\UserInterfaceHelpers.o"

#--------------------------------------------------#
# Default target => request the binary file        #
#--------------------------------------------------#
build : $(BIN_FILE)
	@echo Build complete

#--------------------------------------------------#
# Link and generate the binary file                #
#--------------------------------------------------#
# Convert from .axf to binary
$(BIN_FILE) : $(AXF_FILE)
	@echo Generating binary file...
	@$(ELF) --output-target=binary $(AXF_FILE) $(BIN_FILE)

# Link
$(AXF_FILE) : $(OBJ)
	@echo Linking...
	@$(LINK) -o $(AXF_FILE) $(LINKOPT) $(OBJ) $(SYSOBJ) $(LIBS) > $(MAP_FILE)
	@-echo. >> $(MAP_FILE)
	@-echo. >> $(MAP_FILE)
	@-echo Sizes (total data = data + bss) >> $(MAP_FILE)
	@-echo =============================== >> $(MAP_FILE)
	@-$(ELF_SIZE) $(AXF_FILE) >> $(MAP_FILE)

#--------------------------------------------------#
# Recompile all the source files                   #
#--------------------------------------------------#
all : clean $(BIN_FILE)
	@echo Rebuild complete

#--------------------------------------------------#
# Clean the object files                           #
#--------------------------------------------------#
clean :
	@echo Cleaning...
	@-del $(OBJ) > NUL 2> NUL
	@-del $(MAP_FILE) > NUL 2> NUL
	@-del $(AXF_FILE) > NUL 2> NUL
	@-del $(BIN_FILE) > NUL 2> NUL


#--------------------------------------------------#
#--------------------------------------------------#
#--------------------------------------------------#
#--------------------------------------------------#


#--------------------------------------------------#
# Compile the source files                         #
#--------------------------------------------------#
"$(OBJ_DIR)\Communication.o" : "$(SOURCE_DIR)\Communication.c"
	@echo Compiling Communication.c
	@$(COMPILE) "$(SOURCE_DIR)\Communication.c" -o "$(OBJ_DIR)\Communication.o"
	
"$(OBJ_DIR)\Entry.o" : "$(SOURCE_DIR)\Entry.c"
	@echo Compiling Entry.c
	@$(COMPILE) "$(SOURCE_DIR)\Entry.c" -o "$(OBJ_DIR)\Entry.o"
	
"$(OBJ_DIR)\Menu.o" : "$(SOURCE_DIR)\Menu.c"
	@echo Compiling Menu.c
	@$(COMPILE) "$(SOURCE_DIR)\Menu.c" -o "$(OBJ_DIR)\Menu.o"
	
"$(OBJ_DIR)\UserInterfaceHelpers.o" : "$(SOURCE_DIR)\UserInterfaceHelpers.c"
	@echo Compiling UserInterfaceHelpers.c
	@$(COMPILE) "$(SOURCE_DIR)\UserInterfaceHelpers.c" -o "$(OBJ_DIR)\UserInterfaceHelpers.o"
