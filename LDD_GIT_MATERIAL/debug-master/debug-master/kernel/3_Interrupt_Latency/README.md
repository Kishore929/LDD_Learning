
## What is Interrupt Latency?

Interrupt latency is the time that elapses from when an interrupt is generated to when the source of the interrupt is serviced. For many operating systems, devices are serviced as soon as the device's interrupt handler is executed. Interrupt latency may be affected by microprocessor design, interrupt controllers, interrupt masking, and the operating system's (OS) interrupt handling methods

## How to measure interrupt latency?

To measure a time interval, like interrupt latency, with any accuracy, requires a suitable instrument. The best tool to use is an oscilloscope. One approach is to use one pin on a GPIO interface to generate the interrupt. This pin can be monitored on the ‘scope. At the start of the interrupt service routine, another pin, which is also being monitored, is toggled. The interval between the two signals may be easily read from the instrument.

## How to reduce interrupt latency?

	To reduce interrupt latency ARM Cortex M4 introduce new feature “tail chain”
	ARM Cortex M4 processor reduces interrupt latency using tail-chain.
	To increase system clock frequency then instruction execution speed increase then reduce interrupt latency.

