#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-pic32mx460_pim_e16_int_dyn.mk)" "nbproject/Makefile-local-pic32mx460_pim_e16_int_dyn.mk"
include nbproject/Makefile-local-pic32mx460_pim_e16_int_dyn.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=pic32mx460_pim_e16_int_dyn
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/TP4_USBGen.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/TP4_USBGen.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/system_config/pic32mx460_pim_e16_int_dyn/bsp/bsp.c ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/devcon/src/sys_devcon.c ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/ports/src/sys_ports_static.c ../src/system_config/pic32mx460_pim_e16_int_dyn/system_init.c ../src/system_config/pic32mx460_pim_e16_int_dyn/system_interrupt.c ../src/system_config/pic32mx460_pim_e16_int_dyn/system_exceptions.c ../src/system_config/pic32mx460_pim_e16_int_dyn/system_tasks.c ../src/app.c ../src/main.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c ../../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../../framework/usb/src/dynamic/usb_device.c ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/894922965/bsp.o ${OBJECTDIR}/_ext/757127772/sys_clk_pic32mx.o ${OBJECTDIR}/_ext/1227067107/sys_devcon.o ${OBJECTDIR}/_ext/1227067107/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/257733644/sys_ports_static.o ${OBJECTDIR}/_ext/1196730619/system_init.o ${OBJECTDIR}/_ext/1196730619/system_interrupt.o ${OBJECTDIR}/_ext/1196730619/system_exceptions.o ${OBJECTDIR}/_ext/1196730619/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ${OBJECTDIR}/_ext/692885480/usb_device.o ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/894922965/bsp.o.d ${OBJECTDIR}/_ext/757127772/sys_clk_pic32mx.o.d ${OBJECTDIR}/_ext/1227067107/sys_devcon.o.d ${OBJECTDIR}/_ext/1227067107/sys_devcon_pic32mx.o.d ${OBJECTDIR}/_ext/257733644/sys_ports_static.o.d ${OBJECTDIR}/_ext/1196730619/system_init.o.d ${OBJECTDIR}/_ext/1196730619/system_interrupt.o.d ${OBJECTDIR}/_ext/1196730619/system_exceptions.o.d ${OBJECTDIR}/_ext/1196730619/system_tasks.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o.d ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o.d ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d ${OBJECTDIR}/_ext/692885480/usb_device.o.d ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o.d ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/894922965/bsp.o ${OBJECTDIR}/_ext/757127772/sys_clk_pic32mx.o ${OBJECTDIR}/_ext/1227067107/sys_devcon.o ${OBJECTDIR}/_ext/1227067107/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/257733644/sys_ports_static.o ${OBJECTDIR}/_ext/1196730619/system_init.o ${OBJECTDIR}/_ext/1196730619/system_interrupt.o ${OBJECTDIR}/_ext/1196730619/system_exceptions.o ${OBJECTDIR}/_ext/1196730619/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ${OBJECTDIR}/_ext/692885480/usb_device.o ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o

# Source Files
SOURCEFILES=../src/system_config/pic32mx460_pim_e16_int_dyn/bsp/bsp.c ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/devcon/src/sys_devcon.c ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/ports/src/sys_ports_static.c ../src/system_config/pic32mx460_pim_e16_int_dyn/system_init.c ../src/system_config/pic32mx460_pim_e16_int_dyn/system_interrupt.c ../src/system_config/pic32mx460_pim_e16_int_dyn/system_exceptions.c ../src/system_config/pic32mx460_pim_e16_int_dyn/system_tasks.c ../src/app.c ../src/main.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c ../../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../../framework/usb/src/dynamic/usb_device.c ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-pic32mx460_pim_e16_int_dyn.mk ${DISTDIR}/TP4_USBGen.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX460F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/894922965/bsp.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/bsp/bsp.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/cdaa0608559ab473d529ea9025983035b5e07a08 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/894922965" 
	@${RM} ${OBJECTDIR}/_ext/894922965/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/894922965/bsp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/894922965/bsp.o.d" -o ${OBJECTDIR}/_ext/894922965/bsp.o ../src/system_config/pic32mx460_pim_e16_int_dyn/bsp/bsp.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/757127772/sys_clk_pic32mx.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/ff14859a2d07457fc942766efc57cf614748c87f .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/757127772" 
	@${RM} ${OBJECTDIR}/_ext/757127772/sys_clk_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/757127772/sys_clk_pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/757127772/sys_clk_pic32mx.o.d" -o ${OBJECTDIR}/_ext/757127772/sys_clk_pic32mx.o ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1227067107/sys_devcon.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/devcon/src/sys_devcon.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/b41f15ad086a3eb1fba0c1a7c791ab29bc71c6d9 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1227067107" 
	@${RM} ${OBJECTDIR}/_ext/1227067107/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1227067107/sys_devcon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1227067107/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/1227067107/sys_devcon.o ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/devcon/src/sys_devcon.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1227067107/sys_devcon_pic32mx.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/6ae794f7ba5756b891a2f76d2664016659cf625a .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1227067107" 
	@${RM} ${OBJECTDIR}/_ext/1227067107/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1227067107/sys_devcon_pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1227067107/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/1227067107/sys_devcon_pic32mx.o ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/257733644/sys_ports_static.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/ports/src/sys_ports_static.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/2d24535e9fb84939ea19a1b3c6480b19b70fbb90 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/257733644" 
	@${RM} ${OBJECTDIR}/_ext/257733644/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/257733644/sys_ports_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/257733644/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/257733644/sys_ports_static.o ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/ports/src/sys_ports_static.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1196730619/system_init.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/system_init.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/202cc957cd1dc811486f6b5495b4610fc07c1351 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1196730619" 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1196730619/system_init.o.d" -o ${OBJECTDIR}/_ext/1196730619/system_init.o ../src/system_config/pic32mx460_pim_e16_int_dyn/system_init.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1196730619/system_interrupt.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/system_interrupt.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/fb604c0f868956dcedad3655d603b1f5498ebdb6 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1196730619" 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1196730619/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/1196730619/system_interrupt.o ../src/system_config/pic32mx460_pim_e16_int_dyn/system_interrupt.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1196730619/system_exceptions.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/system_exceptions.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/9e5d5c96c495c611f38f92e951c1a8da6bdf15bb .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1196730619" 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1196730619/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/1196730619/system_exceptions.o ../src/system_config/pic32mx460_pim_e16_int_dyn/system_exceptions.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1196730619/system_tasks.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/system_tasks.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/f4fcef3b86bf5cce09db234942f473d683a65937 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1196730619" 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1196730619/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1196730619/system_tasks.o ../src/system_config/pic32mx460_pim_e16_int_dyn/system_tasks.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/ca4c722a108ea91f0d17821bdc773c910fa932b8 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/b52691768cffa45c3e2556f4440902d8ca4e49a7 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1585079243/drv_usbfs.o: ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/96c556491f7fe8ec5f5bd06ab5b7d604b401b8be .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1585079243" 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1585079243/drv_usbfs.o.d" -o ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o: ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/92a38fdfb15322615c6972a168663d4204fa549f .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1585079243" 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o.d" -o ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/711155467/sys_int_pic32.o: ../../../../../../framework/system/int/src/sys_int_pic32.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/20264bb4b88cd9ced613c3c0cd9d8279774f1f69 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/711155467" 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ../../../../../../framework/system/int/src/sys_int_pic32.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692885480/usb_device.o: ../../../../../../framework/usb/src/dynamic/usb_device.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/670de92f6149ff70f4574e22d4b815e45552e583 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device.o ../../../../../../framework/usb/src/dynamic/usb_device.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692885480/usb_device_cdc.o: ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/c6ad3aa4372642817c933f7bd6be8f809a9c5481 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o: ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/d7d1afba730e0a62cb4eede58ec53324614a8569 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/894922965/bsp.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/bsp/bsp.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/4d7746d8ae9416fe490711f32c2a489bd3d4f361 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/894922965" 
	@${RM} ${OBJECTDIR}/_ext/894922965/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/894922965/bsp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/894922965/bsp.o.d" -o ${OBJECTDIR}/_ext/894922965/bsp.o ../src/system_config/pic32mx460_pim_e16_int_dyn/bsp/bsp.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/757127772/sys_clk_pic32mx.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/a21e61e62bbc79cc35d8cd2d806aefc43d31b99b .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/757127772" 
	@${RM} ${OBJECTDIR}/_ext/757127772/sys_clk_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/757127772/sys_clk_pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/757127772/sys_clk_pic32mx.o.d" -o ${OBJECTDIR}/_ext/757127772/sys_clk_pic32mx.o ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/clk/src/sys_clk_pic32mx.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1227067107/sys_devcon.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/devcon/src/sys_devcon.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/982b6c64cddabb312acb453b413bd4308085254f .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1227067107" 
	@${RM} ${OBJECTDIR}/_ext/1227067107/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1227067107/sys_devcon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1227067107/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/1227067107/sys_devcon.o ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/devcon/src/sys_devcon.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1227067107/sys_devcon_pic32mx.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/80a6bb08631310508e51f704b9fa145168b25262 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1227067107" 
	@${RM} ${OBJECTDIR}/_ext/1227067107/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1227067107/sys_devcon_pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1227067107/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/1227067107/sys_devcon_pic32mx.o ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/devcon/src/sys_devcon_pic32mx.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/257733644/sys_ports_static.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/ports/src/sys_ports_static.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/6a10a55cba972fa0d93e2928144b96952908a09d .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/257733644" 
	@${RM} ${OBJECTDIR}/_ext/257733644/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/257733644/sys_ports_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/257733644/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/257733644/sys_ports_static.o ../src/system_config/pic32mx460_pim_e16_int_dyn/framework/system/ports/src/sys_ports_static.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1196730619/system_init.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/system_init.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/49a47caf4ae55508a4c8643eb2bfeab0919e78eb .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1196730619" 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1196730619/system_init.o.d" -o ${OBJECTDIR}/_ext/1196730619/system_init.o ../src/system_config/pic32mx460_pim_e16_int_dyn/system_init.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1196730619/system_interrupt.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/system_interrupt.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/1fb147caecd98355aeed110b18488ea667de30f8 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1196730619" 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1196730619/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/1196730619/system_interrupt.o ../src/system_config/pic32mx460_pim_e16_int_dyn/system_interrupt.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1196730619/system_exceptions.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/system_exceptions.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/5823f4d08e392fbdb66100bf8d247141fcfc72a4 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1196730619" 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1196730619/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/1196730619/system_exceptions.o ../src/system_config/pic32mx460_pim_e16_int_dyn/system_exceptions.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1196730619/system_tasks.o: ../src/system_config/pic32mx460_pim_e16_int_dyn/system_tasks.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/b557a8541b695f85c03be63264fe6a571d5e573e .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1196730619" 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1196730619/system_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1196730619/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1196730619/system_tasks.o ../src/system_config/pic32mx460_pim_e16_int_dyn/system_tasks.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/9172d5bcc1da9a041728ec413e8e1f4ae08cf1e .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/b188495ff2403eeb0c2e5169976850b03882b250 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1585079243/drv_usbfs.o: ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/3e5d28567d4d8d8ac46033bc1e06d1afa338a279 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1585079243" 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1585079243/drv_usbfs.o.d" -o ${OBJECTDIR}/_ext/1585079243/drv_usbfs.o ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o: ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/9a277a5ad7715c5cb7d27d3ffaed24b29f04e5b7 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1585079243" 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o.d" -o ${OBJECTDIR}/_ext/1585079243/drv_usbfs_device.o ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/711155467/sys_int_pic32.o: ../../../../../../framework/system/int/src/sys_int_pic32.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/74552b89537e1cc7a3696c2fee3aae75a7632c71 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/711155467" 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ../../../../../../framework/system/int/src/sys_int_pic32.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692885480/usb_device.o: ../../../../../../framework/usb/src/dynamic/usb_device.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/8f2d1792fa833a44181a662618d93795f432518 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device.o ../../../../../../framework/usb/src/dynamic/usb_device.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692885480/usb_device_cdc.o: ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/cbdd608753ed30d52d95d1badc9931492f80eba4 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device_cdc.o ../../../../../../framework/usb/src/dynamic/usb_device_cdc.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o: ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c  .generated_files/flags/pic32mx460_pim_e16_int_dyn/dcf8ce8306f266845aec433d7230a4656ce3d776 .generated_files/flags/pic32mx460_pim_e16_int_dyn/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../../bsp/pic32mx460_pim+e16" -I"/system_config/pic32mx460_pim_e16_int_dyn" -I"/pic32mx460_pim_e16_int_dyn" -I"/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"/system_config/pic32mx460_pim_e16_int_dyn/bsp" -I"../src" -I"../src/system_config/pic32mx460_pim_e16_int_dyn" -I"../src/pic32mx460_pim_e16_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/framework" -I"../src/system_config/pic32mx460_pim_e16_int_dyn/bsp" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device_cdc_acm.o ../../../../../../framework/usb/src/dynamic/usb_device_cdc_acm.c    -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/TP4_USBGen.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../bin/framework/peripheral/PIC32MX460F512L_peripherals.a  
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/TP4_USBGen.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/TP4_USBGen.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../bin/framework/peripheral/PIC32MX460F512L_peripherals.a 
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/TP4_USBGen.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_pic32mx460_pim_e16_int_dyn=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/TP4_USBGen.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
