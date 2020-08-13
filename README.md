# Driver para acelerómetro MMA8652
## Este driver fue hecho para la materia de implementación de manejadores de dispositivos para la maestría en sistemas embebidos de la UBA.
### Utiliza el framework misc para registrar el char_driver. Requiere el uso de un DTB específico en el que incluye la definición del periferíco a utilizar.
### Fue probado con una Orange Pi Zero de 512MB de RAM.

## PARA COMPILAR:
arm-linux-gnueabi-gcc lectura.c -o lectura
## PARA EJECUTAR:
### En test_app escribir:
./lectura [args]
./lectura --help muestra los posibles parámetros de configuración
