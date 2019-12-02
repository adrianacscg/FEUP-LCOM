PROG=proj

SRCS = proj.c video_card.c keyboard.c utils.c mouse.c choose_char.c timer.c game.c tamagotchi.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic #-D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
