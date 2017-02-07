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
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Embedded-Software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Embedded-Software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../Embedded-Software/ADCtest.c ../Embedded-Software/FixDisplay.c ../Embedded-Software/I2Ctest.c ../Embedded-Software/TestI2C.c ../Embedded-Software/display.c ../Embedded-Software/display_new.c ../Embedded-Software/main1.c ../Embedded-Software/newmainADCandI2c.c ../Embedded-Software/timertest.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1344191749/ADCtest.o ${OBJECTDIR}/_ext/1344191749/FixDisplay.o ${OBJECTDIR}/_ext/1344191749/I2Ctest.o ${OBJECTDIR}/_ext/1344191749/TestI2C.o ${OBJECTDIR}/_ext/1344191749/display.o ${OBJECTDIR}/_ext/1344191749/display_new.o ${OBJECTDIR}/_ext/1344191749/main1.o ${OBJECTDIR}/_ext/1344191749/newmainADCandI2c.o ${OBJECTDIR}/_ext/1344191749/timertest.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1344191749/ADCtest.o.d ${OBJECTDIR}/_ext/1344191749/FixDisplay.o.d ${OBJECTDIR}/_ext/1344191749/I2Ctest.o.d ${OBJECTDIR}/_ext/1344191749/TestI2C.o.d ${OBJECTDIR}/_ext/1344191749/display.o.d ${OBJECTDIR}/_ext/1344191749/display_new.o.d ${OBJECTDIR}/_ext/1344191749/main1.o.d ${OBJECTDIR}/_ext/1344191749/newmainADCandI2c.o.d ${OBJECTDIR}/_ext/1344191749/timertest.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1344191749/ADCtest.o ${OBJECTDIR}/_ext/1344191749/FixDisplay.o ${OBJECTDIR}/_ext/1344191749/I2Ctest.o ${OBJECTDIR}/_ext/1344191749/TestI2C.o ${OBJECTDIR}/_ext/1344191749/display.o ${OBJECTDIR}/_ext/1344191749/display_new.o ${OBJECTDIR}/_ext/1344191749/main1.o ${OBJECTDIR}/_ext/1344191749/newmainADCandI2c.o ${OBJECTDIR}/_ext/1344191749/timertest.o

# Source Files
SOURCEFILES=../Embedded-Software/ADCtest.c ../Embedded-Software/FixDisplay.c ../Embedded-Software/I2Ctest.c ../Embedded-Software/TestI2C.c ../Embedded-Software/display.c ../Embedded-Software/display_new.c ../Embedded-Software/main1.c ../Embedded-Software/newmainADCandI2c.c ../Embedded-Software/timertest.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Embedded-Software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP256MC506
MP_LINKER_FILE_OPTION=,--script=p33EP256MC506.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1344191749/ADCtest.o: ../Embedded-Software/ADCtest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/ADCtest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/ADCtest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/ADCtest.c  -o ${OBJECTDIR}/_ext/1344191749/ADCtest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/ADCtest.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/ADCtest.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/FixDisplay.o: ../Embedded-Software/FixDisplay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/FixDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/FixDisplay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/FixDisplay.c  -o ${OBJECTDIR}/_ext/1344191749/FixDisplay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/FixDisplay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/FixDisplay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/I2Ctest.o: ../Embedded-Software/I2Ctest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/I2Ctest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/I2Ctest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/I2Ctest.c  -o ${OBJECTDIR}/_ext/1344191749/I2Ctest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/I2Ctest.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/I2Ctest.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/TestI2C.o: ../Embedded-Software/TestI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/TestI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/TestI2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/TestI2C.c  -o ${OBJECTDIR}/_ext/1344191749/TestI2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/TestI2C.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/TestI2C.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/display.o: ../Embedded-Software/display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/display.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/display.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/display.c  -o ${OBJECTDIR}/_ext/1344191749/display.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/display.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/display.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/display_new.o: ../Embedded-Software/display_new.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/display_new.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/display_new.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/display_new.c  -o ${OBJECTDIR}/_ext/1344191749/display_new.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/display_new.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/display_new.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/main1.o: ../Embedded-Software/main1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/main1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/main1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/main1.c  -o ${OBJECTDIR}/_ext/1344191749/main1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/main1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/main1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/newmainADCandI2c.o: ../Embedded-Software/newmainADCandI2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/newmainADCandI2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/newmainADCandI2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/newmainADCandI2c.c  -o ${OBJECTDIR}/_ext/1344191749/newmainADCandI2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/newmainADCandI2c.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/newmainADCandI2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/timertest.o: ../Embedded-Software/timertest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/timertest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/timertest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/timertest.c  -o ${OBJECTDIR}/_ext/1344191749/timertest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/timertest.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/timertest.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1344191749/ADCtest.o: ../Embedded-Software/ADCtest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/ADCtest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/ADCtest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/ADCtest.c  -o ${OBJECTDIR}/_ext/1344191749/ADCtest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/ADCtest.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/ADCtest.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/FixDisplay.o: ../Embedded-Software/FixDisplay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/FixDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/FixDisplay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/FixDisplay.c  -o ${OBJECTDIR}/_ext/1344191749/FixDisplay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/FixDisplay.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/FixDisplay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/I2Ctest.o: ../Embedded-Software/I2Ctest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/I2Ctest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/I2Ctest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/I2Ctest.c  -o ${OBJECTDIR}/_ext/1344191749/I2Ctest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/I2Ctest.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/I2Ctest.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/TestI2C.o: ../Embedded-Software/TestI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/TestI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/TestI2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/TestI2C.c  -o ${OBJECTDIR}/_ext/1344191749/TestI2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/TestI2C.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/TestI2C.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/display.o: ../Embedded-Software/display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/display.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/display.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/display.c  -o ${OBJECTDIR}/_ext/1344191749/display.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/display.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/display.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/display_new.o: ../Embedded-Software/display_new.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/display_new.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/display_new.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/display_new.c  -o ${OBJECTDIR}/_ext/1344191749/display_new.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/display_new.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/display_new.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/main1.o: ../Embedded-Software/main1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/main1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/main1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/main1.c  -o ${OBJECTDIR}/_ext/1344191749/main1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/main1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/main1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/newmainADCandI2c.o: ../Embedded-Software/newmainADCandI2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/newmainADCandI2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/newmainADCandI2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/newmainADCandI2c.c  -o ${OBJECTDIR}/_ext/1344191749/newmainADCandI2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/newmainADCandI2c.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/newmainADCandI2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1344191749/timertest.o: ../Embedded-Software/timertest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344191749" 
	@${RM} ${OBJECTDIR}/_ext/1344191749/timertest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344191749/timertest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Embedded-Software/timertest.c  -o ${OBJECTDIR}/_ext/1344191749/timertest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1344191749/timertest.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344191749/timertest.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Embedded-Software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Embedded-Software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Embedded-Software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Embedded-Software.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Embedded-Software.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
