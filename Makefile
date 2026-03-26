CC := gcc
LD := gcc
AS := as

CFLAGS := -Oz -nostdinc -nostdlib -ffreestanding -IHeader/
LDFLAGS := -static -nostdlib

SRC_DIR := Source
TMP_DIR := Temp
OBJ_DIR := Object
BLD_DIR := Build/

RM := rm -fr
MKDIR := mkdir --parents

TMP_OBJ_DIR := $(TMP_DIR)/$(OBJ_DIR)
TMP_BLD_DIR := $(TMP_DIR)/$(BLD_DIR)

SRC := $(shell find Source -type f 2> /dev/null | grep -e \\.s -e \\.c | sed 's|^Source/||')
OBJ := $(SRC:=.o)

TARGET := $(TMP_DIR)/$(BLD_DIR)/init

.PHONY: clean default build echo target

default: build

target: $(TARGET)

$(TARGET): $(OBJ) $(TMP_BLD_DIR)
	$(LD) $(LDFLAGS) $(TMP_OBJ_DIR)/* -o $(TARGET)

clean:
	$(RM) $(TMP_DIR)

$(TMP_OBJ_DIR):
	$(MKDIR) $(TMP_OBJ_DIR)

$(TMP_BLD_DIR):
		$(MKDIR) $(TMP_BLD_DIR)

%.c.o: $(SRC_DIR)/%.c $(TMP_OBJ_DIR)
	$(CC) -c -o $(TMP_OBJ_DIR)/$@ $(CFLAGS) $<

%.s.o: $(SRC_DIR)/%.s $(TMP_OBJ_DIR)
	$(AS) -o $(TMP_OBJ_DIR)/$@ $<

echo:
	echo $(SRC)
	echo $(OBJ)
