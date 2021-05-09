#include "peripherals/watchdog.h"
#include "utils.h"
#include "reset.h"

void hw_watchdog_disable(void) {}

static void __reset_cpu(struct bcm2835_wdog_regs *wdog_regs, unsigned int ticks)
{
	unsigned int rstc, timeout;

	if (ticks == 0) {
		hw_watchdog_disable();
		timeout = RESET_TIMEOUT;
	} else
		timeout = ticks & BCM2835_WDOG_MAX_TIMEOUT;

	rstc = get32(&wdog_regs->rstc);
	rstc &= ~BCM2835_WDOG_RSTC_WRCFG_MASK;
	rstc |= BCM2835_WDOG_RSTC_WRCFG_FULL_RESET;

	put32(&wdog_regs->wdog, BCM2835_WDOG_PASSWORD | timeout);
	put32(&wdog_regs->rstc, BCM2835_WDOG_PASSWORD | rstc);
}

void reset_cpu(void)
{
	struct bcm2835_wdog_regs *regs =
		(struct bcm2835_wdog_regs *)BCM2835_WDOG_PHYSADDR;

	__reset_cpu(regs, 0);
}
