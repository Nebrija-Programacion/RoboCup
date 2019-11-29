# RoboCup Nebrija 2019-20

Nebrija RoboCup Soccer 2D Simulation

## Instrucciones para instalar

### Instalar dependencias (Ubuntu 18.xx)

```
sudo apt update
sudo apt install build-essential
sudo apt install qtcreator qt5-default libqt4-dev
sudo apt install libboost-all-dev flex bison
sudo apt install libfontconfig1-dev libaudio-dev libxt-dev
sudo apt install libxi-dev
sudo apt install libxrender-dev
sudo apt install libglib2.0-0 libglib2.0-dev libglibd-2.0-dev

```

### Descargar Servidor y Monitor

  - Descargar [servidor](https://github.com/Nebrija-Programacion/RoboCup/blob/master/downloads/rcssserver-15.5.0.tar.gz)
  - Descargar [monitor](https://github.com/Nebrija-Programacion/RoboCup/blob/master/downloads/rcssmonitor-15.2.1.tar.gz)
  - Descomprimir ambos, cada uno en su carpeta correspondiente
  
### Compilar

  - Entrar en el directorio _rcssserver-15.5.0_

```
./configure
make
```

  - Entrar en el directorio _rcssmonitor-15.2.1_

```
./configure
make
```

### Lanzar servidor

```
cd rcssserver-15.5.0/src
./rcssserver
```

### Lanzar monitor
```
cd rcssmonitor-15.2.1/src/
./rcssmonitor
```

### Empezar a programar

Mira el ejemplo Hello RoboCup y empieza a programar!!
Protocolo de comunicación: [manual](https://rcsoccersim.github.io/manual/soccerserver.html)
