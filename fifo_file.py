import os

path = "/tmp/myfifo"
if not os.path.exists(path):
    os.mkfifo(path)

while True:
    print("presiona tecla")
    tecla = input()
    if tecla == "w":
        escribe = "arriba\n"
    if tecla == "s":
        escribe = "abajo\n"
    if tecla == "d":
        escribe = "derecha\n"
    if tecla == "a":
        escribe = "izquierda\n"
    fifo = open(path, "w")
    fifo.write(escribe)
    print("se ha escrito en el fichero")
    fifo.close()