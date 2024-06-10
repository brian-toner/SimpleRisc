#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CPU.o \
	${OBJECTDIR}/call_instructions.o \
	${OBJECTDIR}/check_instructions.o \
	${OBJECTDIR}/cond_instructions.o \
	${OBJECTDIR}/dec_instructions.o \
	${OBJECTDIR}/eload_instructions.o \
	${OBJECTDIR}/esave_instructions.o \
	${OBJECTDIR}/fath_instructions.o \
	${OBJECTDIR}/fath_tests.o \
	${OBJECTDIR}/flag_instructions.o \
	${OBJECTDIR}/half.o \
	${OBJECTDIR}/iath_instructions.o \
	${OBJECTDIR}/iath_tests.o \
	${OBJECTDIR}/inc_instructions.o \
	${OBJECTDIR}/inc_tests.o \
	${OBJECTDIR}/instructions.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/minifloat.o \
	${OBJECTDIR}/mov_instructions.o \
	${OBJECTDIR}/output.o \
	${OBJECTDIR}/pop_instructions.o \
	${OBJECTDIR}/push_instructions.o \
	${OBJECTDIR}/set_instructions.o \
	${OBJECTDIR}/set_tests.o \
	${OBJECTDIR}/tests.o \
	${OBJECTDIR}/vcpu_instructions.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lm

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/simplerisc

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/simplerisc: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/simplerisc ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/CPU.o: CPU.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CPU.o CPU.c

${OBJECTDIR}/call_instructions.o: call_instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/call_instructions.o call_instructions.c

${OBJECTDIR}/check_instructions.o: check_instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/check_instructions.o check_instructions.c

${OBJECTDIR}/cond_instructions.o: cond_instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cond_instructions.o cond_instructions.c

${OBJECTDIR}/dec_instructions.o: dec_instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dec_instructions.o dec_instructions.c

${OBJECTDIR}/eload_instructions.o: eload_instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/eload_instructions.o eload_instructions.c

${OBJECTDIR}/esave_instructions.o: esave_instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/esave_instructions.o esave_instructions.c

${OBJECTDIR}/fath_instructions.o: fath_instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fath_instructions.o fath_instructions.c

${OBJECTDIR}/fath_tests.o: fath_tests.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fath_tests.o fath_tests.c

${OBJECTDIR}/flag_instructions.o: flag_instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/flag_instructions.o flag_instructions.c

${OBJECTDIR}/half.o: half.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/half.o half.c

${OBJECTDIR}/iath_instructions.o: iath_instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/iath_instructions.o iath_instructions.c

${OBJECTDIR}/iath_tests.o: iath_tests.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/iath_tests.o iath_tests.c

${OBJECTDIR}/inc_instructions.o: inc_instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/inc_instructions.o inc_instructions.c

${OBJECTDIR}/inc_tests.o: inc_tests.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/inc_tests.o inc_tests.c

${OBJECTDIR}/instructions.o: instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/instructions.o instructions.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/minifloat.o: minifloat.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/minifloat.o minifloat.c

${OBJECTDIR}/mov_instructions.o: mov_instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mov_instructions.o mov_instructions.c

${OBJECTDIR}/output.o: output.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/output.o output.c

${OBJECTDIR}/pop_instructions.o: pop_instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pop_instructions.o pop_instructions.c

${OBJECTDIR}/push_instructions.o: push_instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/push_instructions.o push_instructions.c

${OBJECTDIR}/set_instructions.o: set_instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/set_instructions.o set_instructions.c

${OBJECTDIR}/set_tests.o: set_tests.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/set_tests.o set_tests.c

${OBJECTDIR}/tests.o: tests.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tests.o tests.c

${OBJECTDIR}/vcpu_instructions.o: vcpu_instructions.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vcpu_instructions.o vcpu_instructions.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
