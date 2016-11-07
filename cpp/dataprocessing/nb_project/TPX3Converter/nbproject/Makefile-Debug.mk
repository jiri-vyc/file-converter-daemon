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
CC=gcc-4.8
CCC=g++-4.8
CXX=g++-4.8
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
	${OBJECTDIR}/_ext/29dd86f/main.o


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
LDLIBSOPTIONS=-L/home/jiri/rootlibs/root /home/jiri/rootlibs/root/libASImage.so /home/jiri/rootlibs/root/libASImageGui.so /home/jiri/rootlibs/root/libCling.so /home/jiri/rootlibs/root/libCore.so /home/jiri/rootlibs/root/libGX11.so /home/jiri/rootlibs/root/libGX11TTF.so /home/jiri/rootlibs/root/libGed.so /home/jiri/rootlibs/root/libGpad.so /home/jiri/rootlibs/root/libGraf.so /home/jiri/rootlibs/root/libGraf3d.so /home/jiri/rootlibs/root/libGui.so /home/jiri/rootlibs/root/libGuiHtml.so /home/jiri/rootlibs/root/libHist.so /home/jiri/rootlibs/root/libHistPainter.so /home/jiri/rootlibs/root/libMathCore.so /home/jiri/rootlibs/root/libMatrix.so /home/jiri/rootlibs/root/libMinuit.so /home/jiri/rootlibs/root/libNet.so /home/jiri/rootlibs/root/libNetx.so /home/jiri/rootlibs/root/libNetxNG.so /home/jiri/rootlibs/root/libNew.so /home/jiri/rootlibs/root/libPostscript.so /home/jiri/rootlibs/root/libRIO.so /home/jiri/rootlibs/root/libRint.so /home/jiri/rootlibs/root/libThread.so /home/jiri/rootlibs/root/libTree.so /home/jiri/rootlibs/root/libTreePlayer.so /home/jiri/rootlibs/root/libcomplexDict.so /home/jiri/rootlibs/root/libdequeDict.so /home/jiri/rootlibs/root/libforward_listDict.so /home/jiri/rootlibs/root/liblistDict.so /home/jiri/rootlibs/root/libmap2Dict.so /home/jiri/rootlibs/root/libmapDict.so /home/jiri/rootlibs/root/libmultimap2Dict.so /home/jiri/rootlibs/root/libmultimapDict.so /home/jiri/rootlibs/root/libmultisetDict.so /home/jiri/rootlibs/root/libsetDict.so /home/jiri/rootlibs/root/libunordered_mapDict.so /home/jiri/rootlibs/root/libunordered_multimapDict.so /home/jiri/rootlibs/root/libunordered_multisetDict.so /home/jiri/rootlibs/root/libunordered_setDict.so /home/jiri/rootlibs/root/libvalarrayDict.so /home/jiri/rootlibs/root/libvectorDict.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libASImage.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libASImageGui.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libCling.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libCore.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libGX11.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libGX11TTF.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libGed.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libGpad.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libGraf.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libGraf3d.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libGui.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libGuiHtml.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libHist.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libHistPainter.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libMathCore.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libMatrix.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libMinuit.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libNet.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libNetx.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libNetxNG.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libNew.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libPostscript.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libRIO.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libRint.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libThread.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libTree.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libTreePlayer.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libcomplexDict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libdequeDict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libforward_listDict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/liblistDict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libmap2Dict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libmapDict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libmultimap2Dict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libmultimapDict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libmultisetDict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libsetDict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libunordered_mapDict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libunordered_multimapDict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libunordered_multisetDict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libunordered_setDict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libvalarrayDict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: /home/jiri/rootlibs/root/libvectorDict.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/29dd86f/main.o: ../../main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/29dd86f
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/home/jiri/root_build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/29dd86f/main.o ../../main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpx3converter

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
