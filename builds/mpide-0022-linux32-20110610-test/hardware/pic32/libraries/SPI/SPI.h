/*
 * Copyright (c) 2011 Digilent
 * SPI Master library for the PIC arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#define __LANGUAGE_C__

#include <plib.h>
#include <stdio.h>

/*	SPIxCON
*/
#define bnOn	15
#define bnSmp	9
#define bnCkp	6
#define bnMsten 5

/*	SPIxSTAT
*/
#define bnTbe	3
#define bnRbf	0

/*	IEC0
*/
#define bnSPI2RXIE	7
#define bnSPI2TXIE	6

/* SPI Connection
*/
#define trisSS				TRISG
#define latSS				LATG
#define	bnSS				9

#define	trisSDO				TRISG
#define	latSDO				LATG
#define	bnSDO				8

#define trisSDI				TRISG
#define	latSDI				LATG
#define bnSDI				7

#define trisSCK				TRISG
#define latSCK				LATG
#define bnSCK				6
/********************************/

#define SPI_CLOCK_DIV4 0x01
#define SPI_CLOCK_DIV16 0x7
#define SPI_CLOCK_DIV64 0x1F
#define SPI_CLOCK_DIV128 0x3F
#define SPI_CLOCK_DIV2 0x00
#define SPI_CLOCK_DIV8 0x03
#define SPI_CLOCK_DIV32 0x0F

#define SPI_MODE0 0x00  // CKP = 0 CKE = 0
#define SPI_MODE1 0x100 // CKP = 0 CKE = 1
#define SPI_MODE2 0x40  // CKP = 1 CKE = 0
#define SPI_MODE3 0x140 // CKP = 1 CKE = 1 

class SPIClass {
public:
  inline static BYTE transfer(BYTE _data);

  // SPI Configuration methods

  inline static void attachInterrupt();
  inline static void detachInterrupt(); // Default

  static void begin(); // Default
  static void end();

  static void setBitOrder(BYTE);
  static void setDataMode(WORD);
  static void setClockDivider(BYTE);
};

extern SPIClass SPI;

BYTE SPIClass::transfer(BYTE _data) {
  while( ((1 << bnTbe) & SPI2STAT) == 0 );
  SPI2BUF = _data;
  while( ((1 << bnRbf) & SPI2STAT) == 0 );
  return SPI2BUF;
}

void SPIClass::attachInterrupt() {
  IEC1SET = ( 1 << bnSPI2RXIE ) | ( 1 << bnSPI2TXIE ); // Setting Interupt Enable
}

void SPIClass::detachInterrupt() {
  IEC1CLR = ( 1 << bnSPI2RXIE ) | ( 1 << bnSPI2TXIE ); // Setting Interrupt Disable
}

#endif
