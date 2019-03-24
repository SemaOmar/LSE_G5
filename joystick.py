import time
import socket
from sense_hat import SenseHat

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    s.connect((host, port))
except Exception as e:
    print("NO se ha conectado ",e)

sense = SenseHat()
tecla = " "
while True:
    flag_enviar = 0
    for event in sense.stick.get_events():
      if event.direction == "up" and event.action == "pressed":
        tecla = event.direction
        flag_enviar = 1
        print(event.direction, event.action)
      if event.direction == "down" and event.action == "pressed":
        tecla = event.direction
        flag_enviar = 1
        print(event.direction, event.action)
      if event.direction == "right" and event.action == "pressed":
        tecla = event.direction
        flag_enviar = 1
        print(event.direction, event.action)
      if event.direction == "left" and event.action == "pressed":
        tecla = event.direction
        flag_enviar = 1
        print(event.direction, event.action)
      if event.direction == "middle" and event.action == "pressed":
        tecla = event.direction
        flag_enviar = 1
        print(event.direction, event.action)
    if flag_enviar == 1:
      print("enviar dato " + tecla)
    time.sleep(0.5)