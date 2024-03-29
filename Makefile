################################################################################
# These are variables for the GBA toolchain build
# You can add others if you wish to
# ***** Mahesh Khanwalkar *****
################################################################################

# The name of your desired GBA game
# This should be a just a name i.e MyFirstGBAGame
# No SPACES AFTER THE NAME.
PROGNAME = DesertDino

# Here you must put a list of all of the object files
# that will be compiled into your program. For example
# if you have main.c and myLib.c then in the following
# line you would put main.o and myLib.o
OFILES = main/main.o \
		 drivers/video/video.o drivers/video/image.o \
		 drivers/font/font.o drivers/font/font_raw.o \
		 assets/img/dino/dinosaur.o assets/img/dino/dinosaur_left.o \
		 assets/img/dino/dinosaur_right.o assets/img/dino/dinosaur_none.o \
		 assets/img/ground/ground.o assets/img/cactus/cactus.o \
		 assets/img/bg/bg_main.o assets/img/bg/bg_dark.o\
		 lib/libg.o lib/frame.o
		 
################################################################################
# These are various settings used to make the GBA toolchain work
# DO NOT EDIT BELOW.
################################################################################

.PHONY: all
all : CFLAGS += $(CRELEASE) -I../shared
all : LDFLAGS += $(LDRELEASE)
all: $(PROGNAME).gba
	@echo "[FINISH] Created $(PROGNAME).gba"

include /opt/cs2110-tools/GBAVariables.mak

debug : CFLAGS += $(CDEBUG) -I../shared
debug : LDFLAGS += $(LDDEBUG)
debug : $(PROGNAME).gba
	@echo "[FINISH] Created $(PROGNAME).gba"

$(PROGNAME).gba : $(PROGNAME).elf
	@echo "[LINK] Linking objects together to create $(PROGNAME).gba"
	@$(OBJCOPY) -O binary $(PROGNAME).elf $(PROGNAME).gba

$(PROGNAME).elf : crt0.o $(GCCLIB)/crtbegin.o $(GCCLIB)/crtend.o $(GCCLIB)/crti.o $(GCCLIB)/crtn.o $(OFILES) libc_sbrk.o
	$(CC) -o $(PROGNAME).elf $^ $(LDFLAGS)

.PHONY : vba
vba : CFLAGS += $(CRELEASE) -I../shared
vba : LDFLAGS += $(LDRELEASE)
vba : $(PROGNAME).gba
	@echo "[EXECUTE] Running Emulator VBA-M"
	vbam $(VBAOPT) $(PROGNAME).gba >emulator.log 2>&1

.PHONY : med
med : CFLAGS += $(CRELEASE) -I../shared
med : LDFLAGS += $(LDRELEASE)
med : $(PROGNAME).gba
	@echo "[EXECUTE] Running emulator Mednafen"
	@mednafen $(MEDOPT) $(PROGNAME).gba >emulator.log 2>&1

.PHONY : clean
clean :
	@echo "[CLEAN] Removing all compiled files"
	rm -f *.o *.elf *.gba *.log
