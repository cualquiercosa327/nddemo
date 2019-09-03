
# ---------------------------------------------------------------------------- #

################################################################################
#
# SOURCES
#
################################################################################

AS_DEPS := $(addprefix $(DEP_PATH)/, $(AS_SRCS:.s=$(DEP_SUFFIX)))
AS_OBJS := $(addprefix $(OBJ_PATH)/, $(AS_SRCS:.s=$(OBJ_SUFFIX)))

-include $(AS_DEPS)

# ---------------------------------------------------------------------------- #

C_DEPS := $(addprefix $(DEP_PATH)/, $(C_SRCS:.c=$(DEP_SUFFIX)))
C_OBJS := $(addprefix $(OBJ_PATH)/, $(C_SRCS:.c=$(OBJ_SUFFIX)))

-include $(C_DEPS)

# ---------------------------------------------------------------------------- #

CXX_DEPS := $(addprefix $(DEP_PATH)/, $(CXX_SRCS:.cpp=$(DEP_SUFFIX)))
CXX_OBJS := $(addprefix $(OBJ_PATH)/, $(CXX_SRCS:.cpp=$(OBJ_SUFFIX)))

-include $(CXX_DEPS)

# ---------------------------------------------------------------------------- #

DEPS := $(AS_DEPS) $(C_DEPS) $(CXX_DEPS)
OBJS := $(AS_OBJS) $(C_OBJS) $(CXX_OBJS)

################################################################################
#
# BUILD RULES
#
################################################################################

$(OBJ_PATH)/%$(OBJ_SUFFIX) : PROJECT := $(PROJECT)
$(OBJ_PATH)/%$(OBJ_SUFFIX) : DEP_PATH := $(DEP_PATH)
$(OBJ_PATH)/%$(OBJ_SUFFIX) : OBJ_PATH := $(OBJ_PATH)

# ---------------------------------------------------------------------------- #

# TODO build assembly source files

# ---------------------------------------------------------------------------- #

$(OBJ_PATH)/%$(OBJ_SUFFIX) : $(SRC_PATH)/%.c
	@echo $(PROJECT)\> $(notdir $<)
	@$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $(OBJ_PATH)/$*$(OBJ_SUFFIX)
	@mv -f $*$(DEP_SUFFIX) $(DEP_PATH)/$*$(DEP_SUFFIX)
	@sed -i -f "$(ROOT_PATH)/dependency.sed" $(DEP_PATH)/$*$(DEP_SUFFIX)

# ---------------------------------------------------------------------------- #

$(OBJ_PATH)/%$(OBJ_SUFFIX) : $(SRC_PATH)/%.cpp
	@echo $(PROJECT)\> $(notdir $<)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $(OBJ_PATH)/$*$(OBJ_SUFFIX)
	@mv -f $*$(DEP_SUFFIX) $(DEP_PATH)/$*$(DEP_SUFFIX)
	@sed -i -f "$(ROOT_PATH)/dependency.sed" $(DEP_PATH)/$*$(DEP_SUFFIX)

################################################################################
#
# LINK RULES
#
################################################################################

$(PROJECT) : $(PROJECT)_prebuild $(BIN_PATH)/$(TARGET) $(PROJECT)_postbuild

# ---------------------------------------------------------------------------- #

$(PROJECT)_prebuild : PROJECT := $(PROJECT)
$(PROJECT)_prebuild : TARGET := $(TARGET)
$(PROJECT)_prebuild : BIN_PATH := $(BIN_PATH)
$(PROJECT)_prebuild : DEP_PATH := $(DEP_PATH)
$(PROJECT)_prebuild : OBJ_PATH := $(OBJ_PATH)

$(PROJECT)_prebuild:
	@echo ===== Building $(PROJECT) =====
	@echo $(PROJECT)\> Creating build directories...
	@mkdir -p $(BIN_PATH)
	@mkdir -p $(DEP_PATH)
	@mkdir -p $(OBJ_PATH)
	@echo $(PROJECT)\> Compiling...

# ---------------------------------------------------------------------------- #

$(PROJECT)_postbuild : PROJECT := $(PROJECT)
$(PROJECT)_postbuild : TARGET := $(TARGET)

$(PROJECT)_postbuild:
	@echo $(PROJECT)\> $(TARGET) generated.
	@echo $(PROJECT)\> Done.

# ---------------------------------------------------------------------------- #

$(BIN_PATH)/$(TARGET) : PROJECT := $(PROJECT)
$(BIN_PATH)/$(TARGET) : TARGET := $(TARGET)
$(BIN_PATH)/$(TARGET) : LIBS := $(LIBS)

$(BIN_PATH)/$(TARGET) : $(OBJS)
ifeq ($(suffix $(LIB_SUFFIX)), $(suffix $(TARGET)))
	@echo $(PROJECT)\> Creating archive...
	@$(AR) $(ARFLAGS) $^ -o $@
else ifeq ($(suffix $(ELF_SUFFIX)), $(suffix $(TARGET)))
	@echo $(PROJECT)\> Linking executable...
	@$(LD) $(LDFLAGS) $+ $(addprefix -l, $(LIBS)) -o $@
else
	$(error Project '$(PROJECT)' is an unknown type)
endif

# ---------------------------------------------------------------------------- #
