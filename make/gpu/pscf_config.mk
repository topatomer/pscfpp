#-----------------------------------------------------------------------
# This makefile fragment defines:
#
#   - A variable $(PSCF_DEFS) that is passed to the processor to define 
#     preprocessor flags that effect the code in the pscf/ directory. 
#
#   - A variable $(PSCF_SUFFIX) that indicates what other features are
#     enabled, which is also added after PSCF_MPI_SUFFIX to the file
#     name of pscf library. 
#
#   - A variable $(PSCF_LIB) that the absolute path to the pscf library 
#     file.
#
# This file must be included by every makefile in the pscf directory. 
#-----------------------------------------------------------------------
# Comments:
#
# The variable PSCF_DEFS is used to pass preprocessor definitions to
# the compiler, using the "-D" compiler option. If not empty, it must 
# consist of a list of zero or more preprocessor macro names, each 
# preceded by the compiler flag "-D". 
#
# The variable PSCF_DEFS is a recursive (normal) makefile variable, and
# may be extended using the += operator, e.g., PSCF_DEFS+=-DPSCF_THING.
# PSCF_SUFFIX is instead a non-recursive makefile variable, which may 
# be extended using the := operator, as PSCF_SUFFIX:=$(PSCF_SUFFIX)_g. 
# They are defined differently because the += operator for recursive
# variables adds a white space before an added string, which is 
# appropriate for PSCF_DEFS, but not for PSCF_SUFFIX. 
 
# Initialize macros to empty strings
PSCF_DEFS=
PSCF_SUFFIX:=

#-----------------------------------------------------------------------
# Flag to define preprocessor macros.

# Each if-block below contains a line that appends a preprocessor macro 
# definition to PSCF_DEFS, thus defining an associated C++ preprocessor 
# macro. In some blocks, a second line add a suffix to the PSCF_SUFFIX 
# or PSCF_MPI_SUFFIX variable, thus changing the name of the util library
# and other libraries and executables that depend on the util library.

# ...... (Nothing needed here, for now)

#-----------------------------------------------------------------------
# Macros related to external libraries 

# Gnu Scientific Library
PSCF_GSL=1
ifdef PSCF_GSL
  PSCF_DEFS+=-DPSCF_GSL
  PSCF_GSL_INC=-isystem /panfs/roc/msisoft/gsl/2.3.intel/include
  PSCF_GSL_LIB=-L/panfs/roc/msisoft/gsl/2.3.intel/lib -lgsl -lgslcblas -lm
  INCLUDES+=$(PSCF_GSL_INC)
endif

#-----------------------------------------------------------------------
# Path to the pscf library 
# Note: BLD_DIR is defined in config.mk in root of bld directory

pscf_LIBNAME=pscf$(PSCF_SUFFIX)$(UTIL_SUFFIX)
pscf_LIB=$(BLD_DIR)/pscf/lib$(pscf_LIBNAME).a
#-----------------------------------------------------------------------
