BLD_DIR_REL =../../..
include $(BLD_DIR_REL)/config.mk
include $(BLD_DIR)/util/config.mk
include $(BLD_DIR)/pscf/config.mk
include $(SRC_DIR)/pscf/patterns.mk
include $(SRC_DIR)/util/sources.mk
include $(SRC_DIR)/pscf/sources.mk
include $(SRC_DIR)/pscf/tests/homogeneous/sources.mk

TEST=pscf/tests/homogeneous/Test

all: $(pscf_tests_homogeneous_OBJS) $(BLD_DIR)/$(TEST)

includes:
	echo $(INCLUDES)

run: $(pscf_tests_homogeneous_OBJS) $(BLD_DIR)/$(TEST)
	$(BLD_DIR)/$(TEST) $(SRC_DIR)/pscf/tests/homogenous/ > log
	@echo `grep failed log` ", "\
              `grep successful log` "in pscf/tests/log" > count
	@cat count

clean:
	rm -f $(pscf_tests_homogeneous_OBJS) $(pscf_tests_homogeneous_OBJS:.o=.d)
	rm -f $(BLD_DIR)/$(TEST) $(BLD_DIR)/$(TEST).d
	rm -f log count 

-include $(pscf_tests_homogeneous_OBJS:.o=.d)
-include $(pscf_tests_homogeneous_OBJS:.o=.d)
