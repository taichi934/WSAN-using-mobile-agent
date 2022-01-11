import serial

portNum = "COM6"


def main():
    ser = serial.Serial(portNum, 9600)

    while True:
        motionNumber = input("Transmit the motion number -> ")

        if motionNumber == "z":  # finish
            print("Quit Serial Communication...")
            break
        if motionNumber.isalpha() or int(motionNumber) <= -1:   # or
            print("Please input a proper number...")
            continue

        ser.write(motionNumber.encode())

        # wait for result packet
        # isSuccess = -1
        # while isSuccess == -1:
        #     isSuccess = print(int(chr(int(ser.read().decode()))))

    ser.close()


if __name__ == "__main__":
    main()
