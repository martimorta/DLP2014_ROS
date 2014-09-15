DLP2014_ROS
===========
Codi de la demo "Live!" al Dia de la Llibertat de Programari a la Palma de Cervelló el 19.9.2014

Muntatge Hardware
-----------------

### Pins
- 3 LED R
- 5 LED G
- 6 LED B
- 9 Servo Motor
- A0 Potenciòmetre

### Altres consideracions
- Cal afegir una resistència a les potes RGB del LED, per exemple de 10kΩ

Més informació a la presentació http://slides.com/martimorta/rrpl

Instal·lació Software
---------------------

### Arduino IDE

`sudo apt-get install arduino`
 
Es fa servir la llibreria Servo

### ROS

He fet servir la versió Hydro. Per fer servir una altra versió només cal que canvieu els noms d'Hydro a per exemple Indigo.
Seguiu els passos detallats a http://wiki.ros.org/hydro/Installation

A més, necessitareu els paquets

`sudo apt-get install ros-hydro-rosserial-python ros-hydro-rosserial-arduino ros-hydro-usb-cam`

I crear-vos un espai de treball (catkin) ROS http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment

### CODI live_demo

Heu d'afegir aquest repositori al vostre espai de treball amb

`wstool set live_demo --git https://github.com/martimorta/DLP2014_ROS`

per llençar l'aplicació podeu fer servir el launch file i si voleu els paràmetres (opcionals)

`roslaunch live_demo arduino_demo.launch parametre:=valor`

#### Paràmetres
- *node*: executar o no el node_demo (per defecte, true)
- *rosserial*: executar o no el lector de port sèrie (true)
- *cam*: executar o no la càmera (true)
- *rviz*: obrir el visualizador 3D (false)
- *plot*: obrir la finestra de gràfiques (false)
- *gui*: obrir la GUI completa (false)


Referències
-----------

### Arduino
Lectura/Escriptura port analògic:
- http://arduino.cc/en/Reference/AnalogRead
- http://arduino.cc/en/Reference/AnalogWrite

Llibreria Servo:
- http://arduino.cc/en/Reference/Servo

### ROS
Creació i configuració del workspace
- http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment

Creació d'un paquet
- http://wiki.ros.org/ROS/Tutorials/CreatingPackage

Creació Publisher/subscriber en Python:
- http://wiki.ros.org/ROS/Tutorials/WritingPublisherSubscriber(python)

Tipus de missatges standard:
- http://wiki.ros.org/std_msgs

Paquet port sèrie:
- http://wiki.ros.org/rosserial
- http://wiki.ros.org/rosserial_python
- http://wiki.ros.org/rosserial_arduino/Tutorials

Paquet webcam:
- http://wiki.ros.org/usb_cam

Ús de reconfiguració dinàmica:
- (pestanya Groovy) http://wiki.ros.org/dynamic_reconfigure/Tutorials/SettingUpDynamicReconfigureForANode%28python%29
- Alerta amb el CMakeLists.txt i a més CAL compil·lar el paquet (p.e. amb `catkin_make --only-pkg-with-deps live_demo`)
