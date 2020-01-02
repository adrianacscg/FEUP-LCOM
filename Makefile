PROG=proj

SRCS = proj.c video_card.c keyboard.c utils.c mouse.c timer.c main_functions.c loading_xpms.c rtc.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
