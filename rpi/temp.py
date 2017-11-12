#!/usr/bin/env python
import spidev
import time
import RPi.GPIO as GPIO

ledPin = 18
spi = spidev.SpiDev()
spi.open(0,0)

GPIO.setmode(GPIO.BCM)
GPIO.setup(ledPin, GPIO.OUT)
GPIO.output(ledPin, GPIO.LOW)

def readadc(adcnum):
    if ((adcnum > 7) or (adcnum < 0)):
        return -1
    r = spi.xfer2([1,(8+adcnum)<<4,0])
    adcout = ((r[1]&3) << 8) + r[2]
    return adcout

try:
  while True:
    value = readadc(0)
    voltage = value * 3.3
    voltage /= 1024.0
    tempCelsius = (voltage-0.5)*100
    print "TEMP", tempCelsius	
    time.sleep(1)

except KeyboardInterrupt:
   GPIO.cleanup()
