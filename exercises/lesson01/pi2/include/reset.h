#ifndef	_RESET_H
#define	_RESET_H

#define RESET_TIMEOUT 10

#define BCM2835_WDOG_PASSWORD			    0x5a000000
#define BCM2835_WDOG_RSTC_WRCFG_MASK		0x00000030
#define BCM2835_WDOG_RSTC_WRCFG_FULL_RESET	0x00000020
#define BCM2835_WDOG_WDOG_TIMEOUT_MASK		0x0000ffff
#define BCM2835_WDOG_MAX_TIMEOUT	        0x000fffff

struct bcm2835_wdog_regs {
	unsigned int unknown0[7];
	unsigned int rstc;
	unsigned int rsts;
	unsigned int wdog;
};

void reset_cpu(void);

#endif