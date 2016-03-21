##########################################################################
#
# Make include for tmos
#
# Platform: MPOS rev.2.3
#
##########################################################################

# local sources

local_csrc 	:= Sinclair_S.c Sinclair_Inverted_S.c
				
local_asrc :=

#updating global variables
asources += $(call changepath,$(local_asrc))
csources += $(call changepath,$(local_csrc))
#add current directory to include path
inc_dirs += $(subdirectory)

#submodules
#local_modules :=
#sub_modules := $(call changepath,$(local_modules))
#modules += $(sub_modules)
#include $(addsuffix /module.mk,$(sub_modules))