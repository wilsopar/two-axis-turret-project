def calculate_direction(error, deadzone):
    if error > deadzone:
        return "POSITIVE"
    elif error < -deadzone:
        return "NEGATIVE"
    else:
        return "STOP"
