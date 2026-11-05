import serial
from time import sleep

with serial.Serial("COM5", 115200, write_timeout=1) as arduino:
    sleep(2)

    commands = [
        ("90,90", "Center"),
        ("110,90", "Move pan"),
        ("90,90", "Center"),
        ("90,110", "Move tilt"),
        ("90,90", "Center"),
    ]

    for command, description in commands:
        print(description, command)
        arduino.write((command + "\n").encode("ascii"))
        arduino.flush()
        sleep(2)