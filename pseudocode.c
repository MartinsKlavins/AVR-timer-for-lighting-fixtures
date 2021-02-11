// =========================== */
/* pseudocode for 16bit dimmer */
/* =========================== */

#define DIM_16bit   0xFFFF

void setupPWM16(uint16_t resolution){

    /* set D9 as output */
    DDRB = DDRB | 0b00000010;

    /* Timer/Counter Control Register setup/initialisation */
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);

    ICR1 = resolution;

}

/* during start-up */
setupPWM16(DIM_16bit);

/* on DMX512 signal arrival or during operation */
uint16_t MSB = DMXslot[0];
uint8_t LSB = DMXslot[1];
MSB = MSB << 8;
OCR1A = MSB + LSB;			// also can use OCR1AH/L for direct DMXslot assignment



// ===================================================== */
/* pseudocode for strobe without fixed carrier frequency */
/* ===================================================== */

void setupPWM(){

	/* set D9 as output */
	DDRB = DDRB | 0b00000010;

	/* Timer/Counter Control Register setup/initialisation */
	TCCR1A = 1 << COM1A1 | 1 << COM1A0 | 1 << WGM11;
	TCCR1B = 1 << WGM13 | 1 << WGM12 | 1 << CS12 | 1 << CS10;

}

/* during start-up */
setupPWM();

/* Input Capture and Output Compare Register setup during operation */
OCR1A = DMXslot[0] << 8;		// flash duration (also can use OCR1AH)
ICR1 = DMXslot[1] << 8;			// flash rate time (interested in bit8-bit15, or can use
								// ICR1H = DMXslot
