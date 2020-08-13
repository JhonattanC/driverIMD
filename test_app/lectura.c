#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "../MMA8652_registers.h"

/** PARA COMPILAR:
 *	arm-linux-gnueabi-gcc lectura.c -o lectura
 *	PARA EJECUTAR:
 *	./lectura [args]
 *	./lectura --help muestra los posibles parámetros de configuración
 */

const char *help = "El uso indebido de estos parámetros causará un efecto indeterminado, use con cuidado.\n"
		"Use -c o -C para especificar la cantidad de datos que quiere leer. Por ejemplo: -c 5 leería 5 datos.\n"
		"Use -t o -T para especificar el tiempo en ms entre mediciones, Por ejemplo: -T 200 leeria datos cada 200ms.\n"
		"Use -s o -S para especiciar la sensibilidad en un rango de [0-2]. En donde 0 significa +-2g; 1 significa +-4g; 2 significa +-8g.\n";

char receive[10];

int escala = FULL_SCALE_2G, tiempo_ms = 100, cantidad = 200;

char *scale_to_string[] = { "SCALE +-2G", "SCALE +-4G", "SCALE +-8G", "SCALE +-2G"};
float scale_to_multiplier[] = { 64.0f, 32.0f, 16.0f, 64.0f}; // Rango [-128, 127] => [-SCALE, SCALE]

void procesar_argumentos(int argc, char **argv);

int main(int argc, char **argv) {
	printf("Empezando programa de prueba de acelerometro MMA8652\n");

	procesar_argumentos(argc, argv);

	int ret, fd;
	int8_t acc[3];

	sleep(1); // Para que no se impriman los buffers del dmesg con estos en la consola

	printf("Abriendo el dispositivo.\n");
	fd = open("/dev/acc_IMD", O_RDWR); // Dispositivo abierto con acceso de escritura y lectura
	if (fd < 0) {
		printf("No se pudo abrir el dispositivo\n");
		return -1;
	}

	int reg = CTRL_REG2;
	int val = RST_MASK;
	printf("Reiniciando para reconfigurar\n");
	ioctl(fd, reg, val);

	printf("Usando escala: %s \n", scale_to_string[escala]);
	ioctl(fd, XYZ_DATA_CFG_REG, escala);

	reg = CTRL_REG1;
	val = ACTIVE_MASK;
	printf("Reactivando tras reconfigurar\n");
	ioctl(fd, reg, val);

	printf("Leyendo %i datos\n", cantidad);
	float mult = scale_to_multiplier[escala];
	while (cantidad--) {
		ret = read(fd, receive, 3);
		if (ret < 0) {
			printf("Failed to read the message from the device.\n");
			close(fd);
			return -1;
		} else {
			acc[0] = (int8_t) (receive[0]);
			acc[1] = (int8_t) (receive[1]);
			acc[2] = (int8_t) (receive[2]);
			printf("x:%.2f\ty:%.2f\tz:%.2f\n", acc[0] / mult, acc[1] / mult, acc[2] / mult);
		}
		usleep(tiempo_ms * 1000);
	}
	printf("End of the program\n");
	close(fd);
	return 0;
}

void procesar_argumentos(int argc, char **argv) {
	int i = 0;
	uint8_t sens = 0, time = 0, cant = 0;

	for (i = 1; i < argc; i++) { // Argumento 0 es el nombre, por eso empieza de 1
//		 printf("\targv[%d] = %s\n", i, argv[i]); // Para visualizar qué argumento le entra
		if (sens == 1) {
			sens = 0;
			escala = (argv[i][0] - 0x30) & 0x03; // Solo toma los dos primeros bytes
			printf("Nueva escala: %s\n", scale_to_string[escala]);
		}
		if (time == 1) {
			time = 0;
			tiempo_ms = atoi(argv[i]);
			/**	WARNING: USE WITH CARE
			 * The C99 standard says this also:
			 *		7.20.1
			 *		The functions atof, atoi, atol, and atoll need not affect the value of the integer
			 *		expression errno on an error. If the value of the result cannot be represented, the
			 *		behavior is undeﬁned.
			 */
			printf("Nuevo tiempo: %d\n", tiempo_ms);
		}
		if (cant == 1) {
			cant = 0;
			cantidad = atoi(argv[i]); // Solo toma los dos primeros bytes
			printf("Nueva cantidad: %d\n", cantidad);
		}
		if (strcmp(argv[i], "-S") == 0 || strcmp(argv[i], "-s") == 0) { // Retorna 0 en igual
			sens = 1;
			printf("Escala recibida en argumentos\n");
		}
		if (strcmp(argv[i], "-T") == 0 || strcmp(argv[i], "-t") == 0) {
			time = 1;
			printf("Tiempo recibido en argumentos\n");
		}
		if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "-C") == 0) {
			cant = 1;
			printf("Cantidad recibida en argumentos\n");
		}
		if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-H") == 0 || strcmp(argv[i], "-h") == 0) {
			printf("%s\n", help);
			exit(0);
		}
	}
}
