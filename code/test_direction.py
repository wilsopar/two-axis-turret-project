from tracking import calculate_direction

assert calculate_direction(50, 20) == "POSITIVE"
assert calculate_direction(-50, 20) == "NEGATIVE"
assert calculate_direction(0, 20) == "STOP"

print("All direction tests passed")