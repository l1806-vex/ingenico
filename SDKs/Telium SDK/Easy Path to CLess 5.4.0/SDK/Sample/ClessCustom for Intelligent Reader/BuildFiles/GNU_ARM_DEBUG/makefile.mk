#*******************************************************************************
#* makefile.mk
#*------------------------------------------------------------------------------
#* Makefile used to generate the Application binaries (GNU ARM format).
#* This file was automatically generated by IngeDev. Please, do not edit!
#*******************************************************************************

#-------------------------------------------------------------------------------
# General constants
#-------------------------------------------------------------------------------
EMPTY :=
SPACE := $(EMPTY) $(EMPTY)

#-------------------------------------------------------------------------------
# Project and file names
#-------------------------------------------------------------------------------
# Project name
PROJECT_NAME    := ClessCustom for Intelligent Reader
# Compiler version
COMPILER_VERSION	:= GNU ARM 4.3.4
# Configuration name
CFG_NAME        := GNU_ARM_DEBUG
# Target file name (without extension)
TRG_FILE_NAME   := CLESSCUSTOM
# Startup object file name
STARTUP_OBJ_NAME:= cstartup.o
CGUARD_OBJ_NAME:= __ing_cguard.o
GETRAND_OBJ_NAME:= __ing_getRand_dateXORSerial.o
# Mapping file name
MAPPING_DEF_NAME:= mapping.def


#-------------------------------------------------------------------------------
# Directories
#-------------------------------------------------------------------------------
# Binaries directory
BIN_DIR         := Bin
# Object directory
OBJ_DIR         := Obj
# Build files directory
BUILD_FILES_DIR := BuildFiles

#-------------------------------------------------------------------------------
# Input files path for the current configuration
#-------------------------------------------------------------------------------
# Build files path
BUILD_FILES_PATH:= $(BUILD_FILES_DIR)/$(CFG_NAME)

#-------------------------------------------------------------------------------
# Output files path for the current configuration
#-------------------------------------------------------------------------------
# Object files path
OBJ_PATH        := $(OBJ_DIR)/$(CFG_NAME)
# Binary files path
BIN_PATH        := $(BIN_DIR)/$(CFG_NAME)

#-------------------------------------------------------------------------------
# Compiler, linker, assembler, ...
#-------------------------------------------------------------------------------
# Gnu Compiler executable
CC              := arm-elf-gcc.exe
# Gnu Assembler executable
AS              := arm-elf-as.exe
# Gnu Linker executable
LD              := arm-elf-ld.exe
# Gnu binary file transforming executable
OBJ_COPY        := arm-elf-objcopy.exe
# Gnu binary sections size executable
SIZE            := arm-elf-size.exe
# Gnu binary Obj Dump executable
OBJ_DUMP        := arm-elf-objdump.exe

#-------------------------------------------------------------------------------
# Gnu Win32 tools
#-------------------------------------------------------------------------------
# Remove tool
RM              := rm.exe -fr
# Make directory tool
MKDIR           := mkdir.exe -p
# Copy tool
CP              := cp.exe
# Printf tool
PRINTF          := printf.exe

#-------------------------------------------------------------------------------
# Includes path used in compilation process
#-------------------------------------------------------------------------------
INCLUDES_PATH   := \
-I"Inc" \
-I"C:/Program Files/TeliumSDK/SDK 9.8.3/SDK/inc" \
-I"C:/Program Files/TeliumSDK/Easy Path to CLess 5.3.0 Beta/SDK/Inc" \


#-------------------------------------------------------------------------------
# Libraries to be included during link operation
#-------------------------------------------------------------------------------
LIBS            := \
C:/Program\ Files/TeliumSDK/SDK\ 9.8.3/SDK/lib_gnu_434/eft30.lib \
C:/Program\ Files/TeliumSDK/SDK\ 9.8.3/SDK/lib_gnu_434/trap.lib \
C:/Program\ Files/TeliumSDK/SDK\ 9.8.3/SDK/lib_gnu_434/IAPP.lib \
C:/Program\ Files/TeliumSDK/SDK\ 9.8.3/SDK/lib_gnu_434/AVL.lib \
C:/Program\ Files/TeliumSDK/SDK\ 9.8.3/SDK/lib_gnu_434/LinkLayerExeInterface.lib \
C:/Program\ Files/TeliumSDK/SDK\ 9.8.3/SDK/lib_gnu_434/SEC.lib \
C:/Program\ Files/TeliumSDK/SDK\ 9.8.3/SDK/lib_gnu_434/dll_wifi.lib \
C:/Program\ Files/TeliumSDK/SDK\ 9.8.3/SDK/lib_gnu_434/FTP_.lib \
C:/Program\ Files/TeliumSDK/SDK\ 9.8.3/SDK/lib_gnu_434/SSL_.lib \
C:/Program\ Files/TeliumSDK/SDK\ 9.8.3/SDK/lib_gnu_434/IP_.lib \
C:/Program\ Files/TeliumSDK/SDK\ 9.8.3/SDK/lib_gnu_434/WGUI_.lib \
C:/Program\ Files/TeliumSDK/SDK\ 9.8.3/SDK/lib_gnu_434/TPass.lib \
C:/Program\ Files/TeliumSDK/SDK\ 9.8.3/SDK/lib_gnu_434/GTL.lib \
C:/Program\ Files/TeliumSDK/Easy\ Path\ to\ CLess\ 5.3.0\ Beta/SDK/lib_gnu4/SDI.lib \
C:/Program\ Files/TeliumSDK/Easy\ Path\ to\ CLess\ 5.3.0\ Beta/SDK/lib_gnu4/DEL.lib \
C:/Program\ Files/TeliumSDK/SDK\ 9.8.3/SDK/lib_gnu_434/libcpatch.o \

#-------------------------------------------------------------------------------
# System libraries to be included during link operation
#-------------------------------------------------------------------------------
SYSTEM_LIBS     := \
-L C:/Program\ Files/Ingenico/IngeDev_7/plugins/com.ingenico.ingedev.telium.bin.win32.gnuarm.v434_7.16.0.6/os/win32/GNUARM/4.3.4/arm-elf/lib/thumb/soft/interwork -lsupc++ \
-L C:/Program\ Files/Ingenico/IngeDev_7/plugins/com.ingenico.ingedev.telium.bin.win32.gnuarm.v434_7.16.0.6/os/win32/GNUARM/4.3.4/arm-elf/lib/thumb/soft/interwork -lc \
-L C:/Program\ Files/Ingenico/IngeDev_7/plugins/com.ingenico.ingedev.telium.bin.win32.gnuarm.v434_7.16.0.6/os/win32/GNUARM/4.3.4/lib/gcc/arm-elf/4.3.4/thumb/soft/interwork -lgcc 

#-------------------------------------------------------------------------------
# Compilation and link input files
#-------------------------------------------------------------------------------
# Mapping file location (used during link process)
MAP_DEF_LOCATION:= $(BUILD_FILES_PATH)/$(MAPPING_DEF_NAME)

#-------------------------------------------------------------------------------
# Result output files
#-------------------------------------------------------------------------------
# Binary file
BINARY_FILE     := $(BIN_PATH)/$(TRG_FILE_NAME).BIN

#-------------------------------------------------------------------------------
# Result Listing files
#-------------------------------------------------------------------------------
# Binary file
LST_FILE     := $(OBJ_PATH)/$(TRG_FILE_NAME).lst

#-------------------------------------------------------------------------------
# Intermediate files
#-------------------------------------------------------------------------------
# Result map file location
INTER_MAP_FILE  := $(OBJ_PATH)/$(TRG_FILE_NAME).map
# AXF file location
INTER_AXF_FILE  := $(OBJ_PATH)/$(TRG_FILE_NAME).axf
# ELF file location
INTER_ELF_FILE  := $(OBJ_PATH)/$(TRG_FILE_NAME).elf

#-------------------------------------------------------------------------------
# Default compiler, linker, assembler options
#-------------------------------------------------------------------------------
# Default compiler options
CC_DEF_OPTS     := -g -c -Wall -Wcast-align -mthumb-interwork -mlittle-endian -msoft-float -pipe -mcpu=arm920t -fomit-frame-pointer -fshort-enums -mstructure-size-boundary=8 -fno-builtin-fork
# Default assembler options
AS_DEF_OPTS     := --gdwarf2 -mthumb-interwork -EL -mfpu=softfpa -march=armv4t -mcpu=arm9tdmi
# Default linker options
LD_DEF_OPTS     :=  -Map=$(INTER_MAP_FILE)
# Default linker options
OD_DEF_OPTS     := --disassemble --source --syms

#-------------------------------------------------------------------------------
# Specific compiler, linker, assembler options
#-------------------------------------------------------------------------------
# Specific compiler options
CC_SPEC_OPTS    := -mthumb -fno-exceptions -fstack-protector-all  -D_ING_GNU_ARM_DEBUG
CC_SPEC_OPTS    +=  -D_EXPORT_ -D_EFT30_ -D__TELIUM2__
CC_SPEC_OPTS    +=  -D_ING_APPLI_BINARY_NAME='"CLESSCUSTOM"' -D_ING_APPLI_FAMILY='"CLESSCUSTOM"' -D_ING_APPLI_TYPE=0x122 -D_ING_APPLI_CURRENT_CONFIG_NAME='"GNU_ARM_DEBUG"' -D_ING_APPLI_FULL_BINARY_NAME='"CLESSCUSTOM.AGN"' -D_ING_APPLI_TELIUM_COMPATIBILITY='"All"' -D_ING_APPLI_SIGN_MODE='"Unsigned"' $(INCLUDES_PATH)
# Specific assembler options
AS_SPEC_OPTS    := -mthumb  --defsym _ING_GNU_ARM_DEBUG=1
AS_SPEC_OPTS    +=  --defsym _EXPORT_=1 --defsym _EFT30_=1 --defsym __TELIUM2__=1
AS_SPEC_OPTS    +=  --defsym _ING_APPLI_BINARY_NAME='"CLESSCUSTOM"' --defsym _ING_APPLI_FAMILY='"CLESSCUSTOM"' --defsym _ING_APPLI_TYPE=0x122 --defsym _ING_APPLI_CURRENT_CONFIG_NAME='"GNU_ARM_DEBUG"' --defsym _ING_APPLI_FULL_BINARY_NAME='"CLESSCUSTOM.AGN"' --defsym _ING_APPLI_TELIUM_COMPATIBILITY='"All"' --defsym _ING_APPLI_SIGN_MODE='"Unsigned"' $(INCLUDES_PATH)
# Specific linker options
LD_SPEC_OPTS    := 

#-------------------------------------------------------------------------------
# Compiler, linker, assembler options
# default + specific options
#-------------------------------------------------------------------------------
# Compiler options
CC_OPTS         := $(CC_DEF_OPTS) $(CC_SPEC_OPTS)
# Assembler options
AS_OPTS         := $(AS_DEF_OPTS) $(AS_SPEC_OPTS)
# Linker options
LD_OPTS         := $(LD_DEF_OPTS) $(LD_SPEC_OPTS)
#ObjDump options
OD_OPTS         := $(OD_DEF_OPTS) 

#-------------------------------------------------------------------------------
# SRC_OBJS is the list of the project object files
#-------------------------------------------------------------------------------
SRC_OBJS        := \
$(OBJ_PATH)/CST_Batch.o \
$(OBJ_PATH)/CST_BlackList.o \
$(OBJ_PATH)/CST_Disk.o \
$(OBJ_PATH)/CST_DumpData.o \
$(OBJ_PATH)/CST_Entry.o \
$(OBJ_PATH)/CST_ExpressPay.o \
$(OBJ_PATH)/CST_FinancialCommunication.o \
$(OBJ_PATH)/CST_Menu.o \
$(OBJ_PATH)/CST_Messages.o \
$(OBJ_PATH)/CST_Parameters.o \
$(OBJ_PATH)/CST_PayPass.o \
$(OBJ_PATH)/CST_payWave.o \
$(OBJ_PATH)/CST_PinEnManagement.o \
$(OBJ_PATH)/CST_PinManagement.o \
$(OBJ_PATH)/CST_Receipt.o \
$(OBJ_PATH)/CST_Scan.o \
$(OBJ_PATH)/CST_servcomm.o \
$(OBJ_PATH)/CST_TaskStatus.o \
$(OBJ_PATH)/CST_Term.o \
$(OBJ_PATH)/CST_Tests.o \
$(OBJ_PATH)/CST_TlvTreeDel.o \
$(OBJ_PATH)/CST_TransactionFile.o \
$(OBJ_PATH)/CST_UserInterfaceHelpers.o \
$(OBJ_PATH)/CST_VisaWave.o \
$(OBJ_PATH)/CST_Common.o \
$(OBJ_PATH)/CST_Discover.o \
$(OBJ_PATH)/CST_Interac.o \

#-------------------------------------------------------------------------------
# Dependencies
#-------------------------------------------------------------------------------
DEPENDENCIES    := \
$(BUILD_FILES_PATH)/makefile.mk

#===============================================================================
# Rule to make the project
#===============================================================================
#-------------------------------------------------------------------------------
# Rule for the binary files generation
#-------------------------------------------------------------------------------
$(BINARY_FILE): $(INTER_ELF_FILE) \

	$(OBJ_COPY) -O binary $(INTER_AXF_FILE) $@
	@$(PRINTF) "'$@' binary file generated.\n"

#===============================================================================
# Rule for the link process
#===============================================================================
#-------------------------------------------------------------------------------
# Rule for the axf file generation
#-------------------------------------------------------------------------------
$(INTER_AXF_FILE): $(MAP_DEF_LOCATION) $(SRC_OBJS) $(LIBS)
	@$(PRINTF) "'$@' link in progress...\n"
	@$(CP) "C:\Program Files\Ingenico\IngeDev_7\plugins\com.ingenico.ingedev.telium.core_7.18.1.6\defaultSystemFiles\Obj\gnu_arm4\$(STARTUP_OBJ_NAME)" "$(OBJ_PATH)"
	@$(CP) "C:\Program Files\Ingenico\IngeDev_7\plugins\com.ingenico.ingedev.telium.core_7.18.1.6\defaultSystemFiles\Obj\gnu_arm4\$(CGUARD_OBJ_NAME)" "$(OBJ_PATH)"
	@$(CP) "C:\Program Files\Ingenico\IngeDev_7\plugins\com.ingenico.ingedev.telium.core_7.18.1.6\defaultSystemFiles\Obj\gnu_arm4\$(GETRAND_OBJ_NAME)" "$(OBJ_PATH)"	
	$(LD) $(LD_OPTS) -T $< -o $@ $(SRC_OBJS) $(OBJ_PATH)/$(STARTUP_OBJ_NAME) $(OBJ_PATH)/$(CGUARD_OBJ_NAME) $(OBJ_PATH)/$(GETRAND_OBJ_NAME) -\( $(LIBS) -\) $(SYSTEM_LIBS)

#-------------------------------------------------------------------------------
# Rule for the elf file generation
#-------------------------------------------------------------------------------
$(INTER_ELF_FILE): $(INTER_AXF_FILE)
	$(SIZE) -A $< > $@

#===============================================================================
# Rule for the .lst Generation
#===============================================================================
$(LST_FILE): $(INTER_AXF_FILE)
	$(OBJ_DUMP) $(OD_OPTS) $<  > $@
	@$(PRINTF) "'$@' lst file generated.\n"

#===============================================================================
# Rule for the compilation process
#===============================================================================
ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_Batch.d
endif
$(OBJ_PATH)/CST_Batch.o: Src/CST_Batch.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_Batch.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_Batch.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_BlackList.d
endif
$(OBJ_PATH)/CST_BlackList.o: Src/CST_BlackList.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_BlackList.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_BlackList.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_Disk.d
endif
$(OBJ_PATH)/CST_Disk.o: Src/CST_Disk.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_Disk.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_Disk.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_DumpData.d
endif
$(OBJ_PATH)/CST_DumpData.o: Src/CST_DumpData.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_DumpData.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_DumpData.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_Entry.d
endif
$(OBJ_PATH)/CST_Entry.o: Src/CST_Entry.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_Entry.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_Entry.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_ExpressPay.d
endif
$(OBJ_PATH)/CST_ExpressPay.o: Src/CST_ExpressPay.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_ExpressPay.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_ExpressPay.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_FinancialCommunication.d
endif
$(OBJ_PATH)/CST_FinancialCommunication.o: Src/CST_FinancialCommunication.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_FinancialCommunication.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_FinancialCommunication.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_Menu.d
endif
$(OBJ_PATH)/CST_Menu.o: Src/CST_Menu.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_Menu.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_Menu.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_Messages.d
endif
$(OBJ_PATH)/CST_Messages.o: Src/CST_Messages.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_Messages.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_Messages.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_Parameters.d
endif
$(OBJ_PATH)/CST_Parameters.o: Src/CST_Parameters.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_Parameters.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_Parameters.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_PayPass.d
endif
$(OBJ_PATH)/CST_PayPass.o: Src/CST_PayPass.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_PayPass.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_PayPass.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_payWave.d
endif
$(OBJ_PATH)/CST_payWave.o: Src/CST_payWave.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_payWave.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_payWave.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_PinEnManagement.d
endif
$(OBJ_PATH)/CST_PinEnManagement.o: Src/CST_PinEnManagement.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_PinEnManagement.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_PinEnManagement.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_PinManagement.d
endif
$(OBJ_PATH)/CST_PinManagement.o: Src/CST_PinManagement.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_PinManagement.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_PinManagement.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_Receipt.d
endif
$(OBJ_PATH)/CST_Receipt.o: Src/CST_Receipt.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_Receipt.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_Receipt.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_Scan.d
endif
$(OBJ_PATH)/CST_Scan.o: Src/CST_Scan.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_Scan.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_Scan.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_servcomm.d
endif
$(OBJ_PATH)/CST_servcomm.o: Src/CST_servcomm.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_servcomm.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_servcomm.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_TaskStatus.d
endif
$(OBJ_PATH)/CST_TaskStatus.o: Src/CST_TaskStatus.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_TaskStatus.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_TaskStatus.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_Term.d
endif
$(OBJ_PATH)/CST_Term.o: Src/CST_Term.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_Term.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_Term.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_Tests.d
endif
$(OBJ_PATH)/CST_Tests.o: Src/CST_Tests.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_Tests.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_Tests.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_TlvTreeDel.d
endif
$(OBJ_PATH)/CST_TlvTreeDel.o: Src/CST_TlvTreeDel.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_TlvTreeDel.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_TlvTreeDel.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_TransactionFile.d
endif
$(OBJ_PATH)/CST_TransactionFile.o: Src/CST_TransactionFile.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_TransactionFile.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_TransactionFile.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_UserInterfaceHelpers.d
endif
$(OBJ_PATH)/CST_UserInterfaceHelpers.o: Src/CST_UserInterfaceHelpers.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_UserInterfaceHelpers.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_UserInterfaceHelpers.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_VisaWave.d
endif
$(OBJ_PATH)/CST_VisaWave.o: Src/CST_VisaWave.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_VisaWave.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_VisaWave.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_Common.d
endif
$(OBJ_PATH)/CST_Common.o: Src/CST_Common.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_Common.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_Common.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_Discover.d
endif
$(OBJ_PATH)/CST_Discover.o: Src/CST_Discover.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_Discover.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_Discover.o)
	@$(PRINTF) "done!\n"
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJ_PATH)/CST_Interac.d
endif
$(OBJ_PATH)/CST_Interac.o: Src/CST_Interac.c $(DEPENDENCIES) $(EXTRA_DEPENDENCIES)
	@$(PRINTF) "'Src/CST_Interac.c' compilation in progress...\n"
	$(CC) $(CC_OPTS) -MMD -MP -o "$@" "$<"
ifeq ($(MAKECMDGOALS), $(OBJ_PATH)/CST_Interac.o)
	@$(PRINTF) "done!\n"
endif

#===============================================================================
# Rule for project name and configuration name display
#===============================================================================
.PHONY: displayInfo
displayInfo:
	@$(PRINTF) "                                     *-*-*\n"
	@$(PRINTF) "--- Project '$(PROJECT_NAME)', Configuration '$(CFG_NAME)', Compiler '$(COMPILER_VERSION)' ---\n"

#===============================================================================
# Rule for build target progress info display
#===============================================================================
.PHONY: displayBuildInProgress
displayBuildInProgress:
	@$(PRINTF) "Build in progress...\n"

#===============================================================================
# Rule for output directories creation
#===============================================================================
.PHONY: createOutputDirs
createOutputDirs:
	@$(MKDIR) "$(OBJ_PATH)"
	@$(MKDIR) "$(BIN_PATH)"

#===============================================================================
# Make build rule
#===============================================================================
.PHONY: build
build: displayInfo displayBuildInProgress createOutputDirs $(BINARY_FILE)
	@$(PRINTF) "done!\n"

#===============================================================================
# Make clean rule
#===============================================================================
.PHONY: clean
clean: displayInfo
	@$(PRINTF) "deleting intermediate files...\n"
	@$(RM) "$(BINARY_FILE)"
ifneq "$(wildcard $(OBJ_PATH)/*.*)" ""
	@$(RM) "$(OBJ_PATH)/*.*"
endif
	@$(PRINTF) "done!\n"
