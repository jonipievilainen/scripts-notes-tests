from gpiozero import DigitalInputDevice
from signal import pause
import time
from adafruit_pca9685 import PCA9685
from board import SCL, SDA
import busio

# --- PCA9685 setup for multiple addresses ---
i2c = busio.I2C(SCL, SDA)
pca_0x40 = PCA9685(i2c, address=0x40)
pca_0x41 = PCA9685(i2c, address=0x41)
pca_0x40.frequency = 50
pca_0x41.frequency = 50

# Convert pulse width in microseconds to PCA9685 duty cycle
def angle_to_pwm_pca9685(micros):
    duty_cycle = int((micros / 20000) * 65535)  # 20 ms period at 50 Hz
    return duty_cycle

# Convert angle (0–180°) to microseconds
def angle_to_micros(angle, pulse_min=1000, pulse_max=2000):
    return pulse_min + (angle / 180.0) * (pulse_max - pulse_min)

# Get correct PCA9685 and channel
def get_pca_and_channel(channel):
    config = servo_configs[channel]
    if config['address'] == 0x40:
        return pca_0x40, channel
    elif config['address'] == 0x41:
        if channel == 16:
            return pca_0x41, 15
        elif channel == 17:
            return pca_0x41, 14
        elif channel == 18:
            return pca_0x41, 13
        elif channel == 19:
            return pca_0x41, 12
    else:
        raise ValueError(f"Unsupported PCA9685 address: {config['address']}")


# Define servo ON/OFF angles (add extra servos here if needed)
servo_configs = {
    0:  {'address': 0x40, 'on_angle': -15,  'off_angle': 30},
    1:  {'address': 0x40, 'on_angle': 200,  'off_angle': 155},
    2:  {'address': 0x40, 'on_angle': -15,  'off_angle': 30},
    3:  {'address': 0x40, 'on_angle': 230,  'off_angle': 165},
    4:  {'address': 0x40, 'on_angle': 10,   'off_angle': 5},
    5:  {'address': 0x40, 'on_angle': 115,  'off_angle': 155},
    6:  {'address': 0x40, 'on_angle': -35,    'off_angle': -5},
    7:  {'address': 0x40, 'on_angle': 110,  'off_angle': 155},
    8:  {'address': 0x40, 'on_angle': 10,   'off_angle': 30},
    9:  {'address': 0x40, 'on_angle': 115,  'off_angle': 165},
    10: {'address': 0x40, 'on_angle':-15,    'off_angle': 5},
    11: {'address': 0x40, 'on_angle': 90,   'off_angle': 155},
    12: {'address': 0x40, 'on_angle': 20,   'off_angle': 30},
    13: {'address': 0x40, 'on_angle': 75,   'off_angle': 155},
    14: {'address': 0x40, 'on_angle': 90,   'off_angle': 15},
    15: {'address': 0x40, 'on_angle': 110,  'off_angle': 155},
    16: {'address': 0x41, 'on_angle': 20,   'off_angle': 155}, #15
    17: {'address': 0x41, 'on_angle': 120,  'off_angle': 30}, #14
    18: {'address': 0x41, 'on_angle': 30,   'off_angle': 155}, #13
    19: {'address': 0x41, 'on_angle': 140,  'off_angle': 30}, #12
}


# Initialize all servos to OFF angle
for channel, config in servo_configs.items():
    micros = angle_to_micros(config['off_angle'])
    pwm = angle_to_pwm_pca9685(micros)
    pca, ch = get_pca_and_channel(channel)
    pca.channels[ch].duty_cycle = pwm
    print(f"Servo {channel} set to OFF angle ({config['off_angle']}°)")

time.sleep(1)

# Release all servos
for channel in servo_configs.keys():
    pca, ch = get_pca_and_channel(channel)
    pca.channels[ch].duty_cycle = 0
    print(f"Servo {channel} released (PWM off)")

# --- Motion sensors setup ---
pins = [4, 14, 15, 25, 18, 23, 24, 17]
sensors = [DigitalInputDevice(pin) for pin in pins]

# Define current servo pair
current_servo_pair = 0

# Define servo pairs for action
servo_pairs = [
    [1, 0],
    [3, 2],
    [5, 4],
    [7, 6],
    [9, 8],
    [11, 10],
    [13, 12],
    [15, 14],
    [17, 16],
    [19, 18],
]

# Handle servo action
def pamentModule(multiplier):
    global current_servo_pair
    print(f"Pament module called with multiplier x{multiplier}")

    pair = servo_pairs[current_servo_pair]

    for _ in range(multiplier):
        for ch in pair:
            on_micros = angle_to_micros(servo_configs[ch]['on_angle'])
            off_micros = angle_to_micros(servo_configs[ch]['off_angle'])
            pca, pch = get_pca_and_channel(ch)

            pca.channels[pch].duty_cycle = angle_to_pwm_pca9685(on_micros)
            time.sleep(0.5)
            pca.channels[pch].duty_cycle = angle_to_pwm_pca9685(off_micros)
            time.sleep(0.5)

    for ch in pair:
        pca, pch = get_pca_and_channel(ch)
        pca.channels[pch].duty_cycle = 0
        print(f"Servo {ch} released (PWM off)")

    current_servo_pair = (current_servo_pair + 1) % len(servo_pairs)

# Motion detection callback
def handle_motion(channel):
    print(f"Motion detected on GPIO {channel}")
    if channel in [18, 14]:
        print("Winning x2")
        pamentModule(1)
    elif channel in [15, 25]:
        print("Winning x3")
        pamentModule(1)
    elif channel in [24, 23]:
        print("Winning x4")
        pamentModule(1)
    elif channel == 4:
        print("Winning x5")
        pamentModule(1)
    else:
        print("Unknown channel")

# Attach sensor callbacks
def sensor_callback(sensor):
    sensor.when_activated = lambda: handle_motion(sensor.pin.number)

for sensor in sensors:
    sensor_callback(sensor)

print("Waiting for motion...")
pause()