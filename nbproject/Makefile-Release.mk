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
CC=clang
CCC=clang++
CXX=clang++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=CLang-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/squirrel/sqstdlib/sqstdaux.o \
	${OBJECTDIR}/squirrel/sqstdlib/sqstdblob.o \
	${OBJECTDIR}/squirrel/sqstdlib/sqstdio.o \
	${OBJECTDIR}/squirrel/sqstdlib/sqstdmath.o \
	${OBJECTDIR}/squirrel/sqstdlib/sqstdrex.o \
	${OBJECTDIR}/squirrel/sqstdlib/sqstdstream.o \
	${OBJECTDIR}/squirrel/sqstdlib/sqstdstring.o \
	${OBJECTDIR}/squirrel/sqstdlib/sqstdsystem.o \
	${OBJECTDIR}/squirrel/squirrel/sqapi.o \
	${OBJECTDIR}/squirrel/squirrel/sqbaselib.o \
	${OBJECTDIR}/squirrel/squirrel/sqclass.o \
	${OBJECTDIR}/squirrel/squirrel/sqcompiler.o \
	${OBJECTDIR}/squirrel/squirrel/sqdebug.o \
	${OBJECTDIR}/squirrel/squirrel/sqfuncstate.o \
	${OBJECTDIR}/squirrel/squirrel/sqlexer.o \
	${OBJECTDIR}/squirrel/squirrel/sqmem.o \
	${OBJECTDIR}/squirrel/squirrel/sqobject.o \
	${OBJECTDIR}/squirrel/squirrel/sqstate.o \
	${OBJECTDIR}/squirrel/squirrel/sqtable.o \
	${OBJECTDIR}/squirrel/squirrel/sqvm.o \
	${OBJECTDIR}/src/main.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/squirrel-binding

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/squirrel-binding: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/squirrel-binding ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/squirrel/sqstdlib/sqstdaux.o: squirrel/sqstdlib/sqstdaux.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/sqstdlib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/sqstdlib/sqstdaux.o squirrel/sqstdlib/sqstdaux.cpp

${OBJECTDIR}/squirrel/sqstdlib/sqstdblob.o: squirrel/sqstdlib/sqstdblob.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/sqstdlib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/sqstdlib/sqstdblob.o squirrel/sqstdlib/sqstdblob.cpp

${OBJECTDIR}/squirrel/sqstdlib/sqstdio.o: squirrel/sqstdlib/sqstdio.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/sqstdlib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/sqstdlib/sqstdio.o squirrel/sqstdlib/sqstdio.cpp

${OBJECTDIR}/squirrel/sqstdlib/sqstdmath.o: squirrel/sqstdlib/sqstdmath.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/sqstdlib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/sqstdlib/sqstdmath.o squirrel/sqstdlib/sqstdmath.cpp

${OBJECTDIR}/squirrel/sqstdlib/sqstdrex.o: squirrel/sqstdlib/sqstdrex.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/sqstdlib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/sqstdlib/sqstdrex.o squirrel/sqstdlib/sqstdrex.cpp

${OBJECTDIR}/squirrel/sqstdlib/sqstdstream.o: squirrel/sqstdlib/sqstdstream.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/sqstdlib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/sqstdlib/sqstdstream.o squirrel/sqstdlib/sqstdstream.cpp

${OBJECTDIR}/squirrel/sqstdlib/sqstdstring.o: squirrel/sqstdlib/sqstdstring.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/sqstdlib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/sqstdlib/sqstdstring.o squirrel/sqstdlib/sqstdstring.cpp

${OBJECTDIR}/squirrel/sqstdlib/sqstdsystem.o: squirrel/sqstdlib/sqstdsystem.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/sqstdlib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/sqstdlib/sqstdsystem.o squirrel/sqstdlib/sqstdsystem.cpp

${OBJECTDIR}/squirrel/squirrel/sqapi.o: squirrel/squirrel/sqapi.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/squirrel
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/squirrel/sqapi.o squirrel/squirrel/sqapi.cpp

${OBJECTDIR}/squirrel/squirrel/sqbaselib.o: squirrel/squirrel/sqbaselib.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/squirrel
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/squirrel/sqbaselib.o squirrel/squirrel/sqbaselib.cpp

${OBJECTDIR}/squirrel/squirrel/sqclass.o: squirrel/squirrel/sqclass.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/squirrel
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/squirrel/sqclass.o squirrel/squirrel/sqclass.cpp

${OBJECTDIR}/squirrel/squirrel/sqcompiler.o: squirrel/squirrel/sqcompiler.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/squirrel
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/squirrel/sqcompiler.o squirrel/squirrel/sqcompiler.cpp

${OBJECTDIR}/squirrel/squirrel/sqdebug.o: squirrel/squirrel/sqdebug.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/squirrel
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/squirrel/sqdebug.o squirrel/squirrel/sqdebug.cpp

${OBJECTDIR}/squirrel/squirrel/sqfuncstate.o: squirrel/squirrel/sqfuncstate.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/squirrel
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/squirrel/sqfuncstate.o squirrel/squirrel/sqfuncstate.cpp

${OBJECTDIR}/squirrel/squirrel/sqlexer.o: squirrel/squirrel/sqlexer.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/squirrel
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/squirrel/sqlexer.o squirrel/squirrel/sqlexer.cpp

${OBJECTDIR}/squirrel/squirrel/sqmem.o: squirrel/squirrel/sqmem.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/squirrel
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/squirrel/sqmem.o squirrel/squirrel/sqmem.cpp

${OBJECTDIR}/squirrel/squirrel/sqobject.o: squirrel/squirrel/sqobject.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/squirrel
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/squirrel/sqobject.o squirrel/squirrel/sqobject.cpp

${OBJECTDIR}/squirrel/squirrel/sqstate.o: squirrel/squirrel/sqstate.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/squirrel
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/squirrel/sqstate.o squirrel/squirrel/sqstate.cpp

${OBJECTDIR}/squirrel/squirrel/sqtable.o: squirrel/squirrel/sqtable.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/squirrel
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/squirrel/sqtable.o squirrel/squirrel/sqtable.cpp

${OBJECTDIR}/squirrel/squirrel/sqvm.o: squirrel/squirrel/sqvm.cpp
	${MKDIR} -p ${OBJECTDIR}/squirrel/squirrel
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/squirrel/squirrel/sqvm.o squirrel/squirrel/sqvm.cpp

${OBJECTDIR}/src/main.o: src/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

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
