#--------------------------------------------------#
#                  Usage                           #
#--------------------------------------------------#
# 1. Set the GCC compiler directory                #
# 2. Set the SDK directory                         #
#--------------------------------------------------#
# 3. Set the compiler defines                      #
# 4. Set the executable file name (without ext.)   #
#--------------------------------------------------#
# In the Build section                             #
#                                                  #
# 5. Set OBJ with your .o file names               #
# 6. Add a section for each .c to compile          #
#--------------------------------------------------#

#
# 3.4.3
#
GCC_VERSION = 3.4.3
ROOT_GCC   = C:\GCC_$(GCC_VERSION)

#
# SDK
#
ROOT_SDK   = $(MAKEDIR)\..\..\..\..\..


DEFINES    = -D_EFT30_ -D_EXPORT_
DEST_NAME  = SAMPLE


#
# 3.4.3
#
GCC_EXE    = $(ROOT_GCC)\BIN
GCC_LIB_TYPE = thumb\soft\interwork
GCC_LIB1   = $(ROOT_GCC)\arm-elf\lib\$(GCC_LIB_TYPE)
GCC_LIB2   = $(ROOT_GCC)\lib\gcc\arm-elf\$(GCC_VERSION)\$(GCC_LIB_TYPE)


#--------------------------------------------------#
#                  SDK                             #
#--------------------------------------------------#
SDK_INC    = $(ROOT_SDK)\Inc
SDK_SAMPLES_INC    = $(ROOT_SDK)\Samples\Inc
SDK_LIB    = $(ROOT_SDK)\lib_gnu


#--------------------------------------------------#
#                  Project                         #
#--------------------------------------------------#
PRJ_ROOT   = $(MAKEDIR)

#--------------------------------------------------#
#                  Source                          #
#--------------------------------------------------#
SOURCE_DIR = $(PRJ_ROOT)\..\Src

#--------------------------------------------------#
#                  Object                          #
#--------------------------------------------------#
OBJ_DIR    = $(PRJ_ROOT)\obj

#--------------------------------------------------#
#                  Target                          #
#--------------------------------------------------#
AXF_FILE   = $(OBJ_DIR)\$(DEST_NAME).AXF
BIN_FILE   = $(OBJ_DIR)\$(DEST_NAME).BIN
MAP_FILE   = $(OBJ_DIR)\$(DEST_NAME).MAP

#--------------------------------------------------#
#                  Compiler                        #
#--------------------------------------------------#
INCLUDES   = -I "$(SDK_SAMPLES_INC)" -I "$(SDK_INC)"
SYSINC     = -B "$(GCC_INC)"
CCOPT      = -Os -Wall -Wcast-align -mthumb -mthumb-interwork -mlittle-endian -msoft-float -pipe -mcpu=arm920t -fomit-frame-pointer -fshort-enums -mstructure-size-boundary=8 -g -c
COMPILE    = "$(GCC_EXE)\arm-elf-gcc" $(CCOPT) $(DEFINES) $(INCLUDES)

#--------------------------------------------------#
#                  Assembler                       #
#--------------------------------------------------#
ASMOPT     = -mthumb-interwork -EL -mno-fpu
ASSEMBLE   = "$(GCC_EXE)\arm-elf-as" $(ASMOPT)

#--------------------------------------------------#
#                  Linker                          #
#--------------------------------------------------#
LINKOPT    = --script="$(SDK_LIB)\gcc_link.txt" -Map "$(MAP_FILE)"

SYSOBJ     = "$(SDK_LIB)\cstartup.o" 
LIBS       = "$(SDK_LIB)\AVL.lib" "$(SDK_LIB)\eft30.lib" "$(SDK_LIB)\trap.lib" -L "$(GCC_LIB1)" -lc -L "$(GCC_LIB2)" -lgcc
LINK       = "$(GCC_EXE)\arm-elf-ld"
ELF        = "$(GCC_EXE)\arm-elf-objcopy"


#--------------------------------------------------#
#                  Build                           #
#--------------------------------------------------#
OBJ        =	"$(OBJ_DIR)\Entry.o" "$(OBJ_DIR)\Sample_DRM.o" "$(OBJ_DIR)\Sample_Util.o"

#--------------------------------------------------#
# Default target => request the binary file        #
#--------------------------------------------------#
build : "$(BIN_FILE)"
	@echo Build complete

#--------------------------------------------------#
# Link and generate the binary file                #
#--------------------------------------------------#
# Convert from .axf to binary
"$(BIN_FILE)" : "$(AXF_FILE)"
	@echo Generating binary file...
	@cd "$(OBJ_DIR)"
	@$(ELF) --output-target=binary "$(AXF_FILE)" "$(BIN_FILE)"

# Link
"$(AXF_FILE)" : $(OBJ)
	@echo Linking...
	@cd "$(OBJ_DIR)"
	@$(LINK) -o "$(AXF_FILE)" $(LINKOPT) $(OBJ) $(SYSOBJ) $(LIBS)

#--------------------------------------------------#
# Recompile all the source files                   #
#--------------------------------------------------#
all : clean "$(BIN_FILE)"
	@echo Rebuild complete

#--------------------------------------------------#
# Clean the object files                           #
#--------------------------------------------------#
clean :
	@echo Cleaning...
	@cd "$(OBJ_DIR)"
	@-del $(OBJ)
	@-del "$(MAP_FILE)"
	@-del "$(AXF_FILE)"
	@-del "$(BIN_FILE)"


#--------------------------------------------------#
#--------------------------------------------------#
#--------------------------------------------------#
#--------------------------------------------------#


#--------------------------------------------------#
# Compile the source files                         #
#--------------------------------------------------#
"$(OBJ_DIR)\Entry.o" : "$(SOURCE_DIR)\Entry.c"
	@echo Compiling... Entry.c
	@cd "$(OBJ_DIR)"
	@$(COMPILE) "$(SOURCE_DIR)\Entry.c"

"$(OBJ_DIR)\Sample_DRM.o" : "$(SOURCE_DIR)\Sample_DRM.c"
	@echo Compiling... Sample_DRM.c
	@cd "$(OBJ_DIR)"
	@$(COMPILE) "$(SOURCE_DIR)\Sample_DRM.c"

"$(OBJ_DIR)\Sample_Util.o" : "$(SOURCE_DIR)\Sample_Util.c"
	@echo Compiling... Sample_Util.c
	@cd "$(OBJ_DIR)"
	@$(COMPILE) "$(SOURCE_DIR)\Sample_Util.c"


