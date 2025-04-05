from time import sleep
from adafruit_servokit import ServoKit
import busio
from board import SCL, SDA

# I2C-bussi
i2c = busio.I2C(SCL, SDA)

# PCA9685-initialisointi eri osoitteilla
kit_41 = ServoKit(channels=16, i2c=i2c, address=0x41)  # Piiri 1 (kanavat 0–15)
kit_40 = ServoKit(channels=16, i2c=i2c, address=0x40)  # Piiri 2 (kanavat 0–3 käytössä)

while True:
    for i in range(20):
        # Valitaan oikea piiri ja kanava
        if i < 16:
            kit = kit_41
            channel = i
        else:
            kit = kit_40
            channel = i - 16

        print(f"Moving servo {i} (channel {channel}) on {'0x41' if i < 16 else '0x40'}")

        if i % 2 == 0:
            # Vasemman puolen servo (normaali suunta)
            kit.servo[channel].angle = 175
            sleep(0.5)
            kit.servo[channel].angle = 45
        else:
            # Oikean puolen servo (peilattu liike)
            kit.servo[channel].angle = 45
            sleep(0.5)
            kit.servo[channel].angle = 175

        sleep(0.5)
