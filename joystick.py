import os
import time
import socket
from sense_hat import SenseHat

sense = SenseHat()
path = "/tmp/myfifo"
if not os.path.exists(path):
    os.mkfifo(path)
	
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
		fifo = open(path, "w")
		tecla = tecla + "\n"
		fifo.write(tecla)
		print("se ha escrito en el fichero")
		fifo.close()
    time.sleep(0.5)