import RPI.GPIO as GPIO
import time
import sys

# Measure when High or Low
def pulseIn(PIN, start=1, end=0):
    if start == 0:
        end = 1
    t_start = 0
    t_end = 0

    # Measure the time that ECHO_PIN is HIGH
    while GPIO.input(PIN) == end:
        t_start = time.time()

    while GPIO.input(PN) == start:
        t_end = time.time()
    return t_end - t_start

# Distance measurement
def calc_dist(TRIG_PIN, ECHO_PIN, num, v=34000):
    for i in range(num):
        # TRIG pin LOW by 0.3[s]
        GPIO.output(TRIG_PIN, GPIO.LOW)
        time.sleep(0.3)
        # Output TRIG pin for 0.00001[s] (ultrasonic firing)
        GPIO.output(TRIG_PIN, True)
        time.sleep(0.00001)
        GPIO.output(TRIG_PIN, False)
        # Measure the time of High
        t = pulseIn(ECHO_PIN)
        # Distance [cm] = Speed of sound [cm/s] * Time [s]/2
        distance = v * t/2
        distance *= 10
        print(distance, "mm")

    # Release the pin setting
    GPIO.cleanup()

while True:
    try:
        # GPIO numbers for TRIG and ECHO
        TRIG_PIN = 27
        ECHO_PIN = 18

        # Speed of sound [cm/s] at temperature 24[°C]
        v = 33150 + 60*24
        
        # Specify pin number in GPIO
        GPIO.setmode(GPIO.BCM)
        # Output TRIG_PIN, input ECHO_PIN
        GPIO.setup(TRIG_PIN,GPIO.OUT)
        GPIO.setup(ECHO_PIN,GPIO.IN)
        GPIO.setwarnings(False)
            
        # distance measurement(
            # TRIG pin number,
            # ECHO_PIN number,
            # number of measurements,
            # sound speed [cm/s])
        calc_distance(TRIG_PIN, ECHO_PIN, 1, v)
        
        time.sleep(1)

    # Processing when Ctrl+C key is pressed
    except KeyboardInterrupt:
        GPIO.cleanup()
        sys.exit()
