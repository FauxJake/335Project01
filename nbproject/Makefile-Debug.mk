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
CND_PLATFORM=GNU-Linux-x86
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
	${OBJECTDIR}/CApp.o \
	${OBJECTDIR}/CAquarium.o \
	${OBJECTDIR}/CDecorTreasure.o \
	${OBJECTDIR}/CFish.o \
	${OBJECTDIR}/CFishBeta.o \
	${OBJECTDIR}/CFishMolly.o \
	${OBJECTDIR}/CFishNemo.o \
	${OBJECTDIR}/CFrame.o \
	${OBJECTDIR}/CItem.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=`wx-config --cppflags` 
CXXFLAGS=`wx-config --cppflags` 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/project01_335

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/project01_335: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/project01_335 ${OBJECTFILES} ${LDLIBSOPTIONS} `wx-config --libs`

${OBJECTDIR}/CApp.o: CApp.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g `wx-config --cppflags` -MMD -MP -MF $@.d -o ${OBJECTDIR}/CApp.o CApp.cpp

${OBJECTDIR}/CAquarium.o: CAquarium.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g `wx-config --cppflags` -MMD -MP -MF $@.d -o ${OBJECTDIR}/CAquarium.o CAquarium.cpp

${OBJECTDIR}/CDecorTreasure.o: CDecorTreasure.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g `wx-config --cppflags` -MMD -MP -MF $@.d -o ${OBJECTDIR}/CDecorTreasure.o CDecorTreasure.cpp

${OBJECTDIR}/CFish.o: CFish.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g `wx-config --cppflags` -MMD -MP -MF $@.d -o ${OBJECTDIR}/CFish.o CFish.cpp

${OBJECTDIR}/CFishBeta.o: CFishBeta.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g `wx-config --cppflags` -MMD -MP -MF $@.d -o ${OBJECTDIR}/CFishBeta.o CFishBeta.cpp

${OBJECTDIR}/CFishMolly.o: CFishMolly.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g `wx-config --cppflags` -MMD -MP -MF $@.d -o ${OBJECTDIR}/CFishMolly.o CFishMolly.cpp

${OBJECTDIR}/CFishNemo.o: CFishNemo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g `wx-config --cppflags` -MMD -MP -MF $@.d -o ${OBJECTDIR}/CFishNemo.o CFishNemo.cpp

${OBJECTDIR}/CFrame.o: CFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g `wx-config --cppflags` -MMD -MP -MF $@.d -o ${OBJECTDIR}/CFrame.o CFrame.cpp

${OBJECTDIR}/CItem.o: CItem.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g `wx-config --cppflags` -MMD -MP -MF $@.d -o ${OBJECTDIR}/CItem.o CItem.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/project01_335

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
