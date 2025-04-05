# Import the RPi.GPIO and OS
import RPi.GPIO as GPIO
import os
import sys
import time

# GPIO port setup
GPIO.setmode(GPIO.BCM)

GPIO.setup(4, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(14, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(15, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(25, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(23, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(24, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(17, GPIO.OUT)

def pamentModule(coins):
    for _ in range(coins):
        # print('Pay qty ->')
        # print(coins)
        GPIO.output(17, GPIO.HIGH)
        time.sleep(0.3)
        GPIO.output(17, GPIO.LOW)
        time.sleep(0.3)

def coinPayment(channel):
    print('Port ->')
    print(channel)

    # channel 18
    if channel == 18:
        print("Winnig x2")
        pamentModule(2)

    # channel 14
    elif channel == 14:
        print("Winnig x2")
        pamentModule(2)
        
    # channel 15
    elif channel == 15:
        print("Winnig x3")
        pamentModule(3)

    # channel 25
    elif channel == 25:
        print("Winnig x3")
        pamentModule(3)

    # channel 24
    elif channel == 24:
        print("Winnig x4")
        pamentModule(4)

    # channel 23
    elif channel == 23:
        print("Winnig x4")
        pamentModule(4)

    # channel 4
    elif channel == 4:
        print("Winnig x5")
        pamentModule(5)

    else:
        print("Unknown channel")
    
        

GPIO.add_event_detect(18, GPIO.RISING, callback=coinPayment, bouncetime=1250) # 2 * 2 * 300 + 50
GPIO.add_event_detect(14, GPIO.RISING, callback=coinPayment, bouncetime=1250) # 2 * 2 * 300 + 50
GPIO.add_event_detect(15, GPIO.RISING, callback=coinPayment, bouncetime=1850) # 3 * 2 * 300 + 50
GPIO.add_event_detect(25, GPIO.RISING, callback=coinPayment, bouncetime=1850) # 3 * 2 * 300 + 50
GPIO.add_event_detect(24, GPIO.RISING, callback=coinPayment, bouncetime=2450) # 4 * 2 * 300 + 50
GPIO.add_event_detect(23, GPIO.RISING, callback=coinPayment, bouncetime=2450) # 4 * 2 * 300 + 50
GPIO.add_event_detect(4,  GPIO.RISING, callback=coinPayment, bouncetime=3050) # 5 * 2 * 300 + 50

# And... nothing more to do. let's wait.
while True:
    time.sleep(10)
