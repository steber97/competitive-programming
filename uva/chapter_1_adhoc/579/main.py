if __name__ == "__main__":
    while True:
        text = input()
        if text == "0:00":
            break
        hour, minute = [int(x) for x in text.split(":")]
        minute_angle = 6 * minute
        hour_angle = hour * 30 + (minute/60 * 30)
        angle = min(
            abs(minute_angle - hour_angle),
            (360 - minute_angle + hour_angle),
            360 - hour_angle + minute_angle
        )
        print("%.3f" % angle)
