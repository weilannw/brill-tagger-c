TARGET_EXEC ?= brill_tagger
CFLAGS=-std=gnu-5 -g -fopenmp
BUILD_DIR ?= ./build
SRC_DIRS ?= ./src
LDFLAGS=-fopenmp
SRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ 

.PHONY:
	sync
	clean

clean:
	$(RM) -r $(BUILD_DIR)

sync:
	rsync -rup ./files/* $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
