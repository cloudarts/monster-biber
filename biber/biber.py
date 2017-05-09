import serial
import sys
import pygame

ser = serial.Serial()
duration = 100

def main(argv):
    if len(argv) != 2:
        print "Usage: python biber.py [SERIAL PORT NAME]"
        sys.exit(1)

    dev = argv[1]
    print "Opening serial device at " + dev

    ser = serial.Serial(dev, 115200)

    pygame.init()
    while True:
        for event in pygmae.event.get():
            if event.type == pygame.QUIT:
                sys.exit()

            elif event.type == pygame.KEYUP:
                if event.key == pygame.K_ESCAPE:
                    sys.exit()

                if event.key == pygame.K_PLUS:
                    duration += 50
                    duration = max(10000, duration)
                    print "duration is now " + duration + "ms."
                elif event.key == pygame.K_MINUS:
                    duration -= 50
                    duration = max(0, duration)
                
                if event.key == pygame.K_LEFT:
                    left(duration)
                elif event.key == pygame.K_RIGHT:
                    right(duration)

                if event.key == pygame.K_UP:
                    forward(duration)
                elif event.key == pygame.K_DOWN:
                    backward(duration)

def left(duration):
    ser.write(b'0,'+duration)

def right(duration):
    ser.write(b'1'+duration)

def forward(duration):
    ser.write(b'2'+duration)

def backward(duration):
    ser.write(b'3'+duration)

def setSpeed(speed):
    ser.write(b'4'+speed)

##############################################################
if __name__ == "__main__":
    main(sys.argv)
