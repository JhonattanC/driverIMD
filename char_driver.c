#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/i2c.h>
#include <linux/types.h>

#include <linux/uaccess.h>

#include "MMA8652_registers.h"

/* Strings definiendo el nombre del dispositivo */
#define DEVICE_NAME 		"acc_IMD"

static struct i2c_client *slaveDevice;

static const struct of_device_id accIMD_dt_ids[] = {
			{	.compatible = "mse,acc_IMD", },
			{ }
		};

MODULE_DEVICE_TABLE(of, accIMD_dt_ids);

/*********************************************************************************
 *  Low level functions
 *********************************************************************************/
#define TAM 7

int writeRegister(char reg, char val) {
	char wreg[2] = {reg, val};
	int amount = i2c_master_send(slaveDevice, wreg, 2);
	if (amount < 0) {
		pr_info("Error writing register 0x%.2x\n", reg);
	}
	return amount;
}

int readRegister(char reg, char *val, uint8_t cantidad) {
	char wreg = reg;
	int amount = i2c_master_send(slaveDevice, &wreg, 1);
	if (amount < 0) {
		pr_info("Error writing register [0x%.2x} to read\n", reg);
	}

	amount = i2c_master_recv(slaveDevice, val, cantidad);
	if (amount < 0) {
		pr_info("Error reading register 0x%.2x\n", reg);
	}
	return amount;
}

int readRawFast (int8_t *output) {
	char data[TAM];

	char wreg = STATUS_00_REG;
	int ret = readRegister(wreg, data, TAM);

	output[0] = (int8_t)(data[1]);
	output[1] = (int8_t)(data[3]);
	output[2] = (int8_t)(data[5]);

	return ret;
}

/*********************************************************************************
 * Definiciones de funciones sobre archivos y estructura correspondiente
 *********************************************************************************/
static int accIMD_open(struct inode *inode, struct file *file) {
	int escritos;

	pr_info("open() fue invocada.\n");

	escritos = writeRegister(CTRL_REG1, ACTIVE_MASK);
	if (escritos < 0) {
		pr_info("Error al abrir el driver\n");
	} else {
		pr_info("%d bytes written in open\n", escritos);
		pr_info("Driver abierto satisfactoriamente\n");
	}

	return 0;
}

static int accIMD_close(struct inode *inode, struct file *file) {
	int escritos;

	pr_info("close() fue invocada.\n");

	escritos = writeRegister(CTRL_REG2, RST_MASK);
	if (escritos < 0) {
		pr_info("Error al cerrar el driver\n");
	} else {
		pr_info("%d bytes written in close\n", escritos);
		pr_info("Driver cerrado satisfactoriamente\n");
	}

	return 0;
}

static long accIMD_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
	int status;
	char reg, val;

	reg = cmd & 0xFF;
	val = arg & 0xFF;
	pr_info("ioctl register = 0x%.2x, val = 0x%.2x\n", reg, val);
	status = writeRegister(reg, val);

	return status;
}

static ssize_t accIMD_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset) {
	pr_info("write() fue invocada.\n");
	return 0;
}

static ssize_t accIMD_read(struct file *filep, char __user *buffer, size_t len, loff_t *offset) {
	int8_t kbuffer[3];

	if (len >= 3) {
		readRawFast(kbuffer);
	} else {
		return -EPERM;
	}

	copy_to_user(buffer, kbuffer, 3);
	return 0;
}

/* Declaración de una estructura del tipo file_operations */
static const struct file_operations my_dev_fops = {
		.owner = THIS_MODULE,
		.open = accIMD_open,
		.read = accIMD_read,
		.write = accIMD_write,
		.release = accIMD_close,
		.unlocked_ioctl = accIMD_ioctl,
};

/*--------------------------------------------------------------------------------*/

/* Declaración e inicialización de una estructura miscdevice */
static struct miscdevice accIMD_miscdevice = {
		.minor = MISC_DYNAMIC_MINOR,
		.name = DEVICE_NAME,
		.fops = &my_dev_fops, };

//************************************************************************************
/*
 * Definiciones de funciones probe y remove necesarias para el driver
 *
 * NOTA: No reemplazan las funciones init y exit, sino que se definen mediante
 * la macro module_i2c_driver() internamente
 */

static int accIMD_probe(struct i2c_client *connected_slave, const struct i2c_device_id *id) {
	int ret_val;

	pr_info("Ejecutando funcion probe()\n");
	pr_info("Informacion de dispositivo conectado:\n");

	pr_info("\tDireccion: %#x\n", connected_slave->addr);
	pr_info("\tNombre: %s\n", connected_slave->name);

	pr_info("\tDriver: %s\n", (connected_slave->dev).driver->name);

	/* Registro del dispositivo con el kernel */
	ret_val = misc_register(&accIMD_miscdevice);
	if (ret_val != 0) {
		pr_err("No se pudo registrar el dispositivo %s\n", DEVICE_NAME);
		return ret_val;
	}
	pr_info("Dispositivo %s: minor asignado: %i\n", DEVICE_NAME, accIMD_miscdevice.minor);

	/*
	 * Una vez que tenemos numeros Major y Minor, exponemos al modulo completo
	 * el puntero recibido como dispositivo esclavo conectado (cliente)
	 */
	slaveDevice = connected_slave; // Guardamos este puntero para el uso de read y write

	return 0;
}

static int accIMD_remove(struct i2c_client *client) {

	pr_info("Ejecutando funcion remove()\n");

	/* Unregister del miscDevice del kernel */
	misc_deregister(&accIMD_miscdevice);

	pr_info("Modulo removido, registro anulado");

	return 0;

}

static struct i2c_driver accIMD_driver = {
	.probe = accIMD_probe,
	.remove = accIMD_remove,
	.driver = {
			.name = "MMA8652_driver",
			.owner = THIS_MODULE,
			.of_match_table = of_match_ptr(accIMD_dt_ids),
		},
};

/*----------------------------------------------------------------------*/

/**********************************************************************
 * Esta seccion define cuales funciones seran las ejecutadas al cargar o
 * remover el modulo respectivamente. Es hecho implicitamente,
 * termina declarando probe() y remove()
 **********************************************************************/
module_i2c_driver( accIMD_driver);

/**********************************************************************
 * Seccion sobre Informacion del modulo
 **********************************************************************/
MODULE_AUTHOR("Jhonattan Camargo <u1802296@unimilitar.edu.co>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Este modulo es un driver para el acelerómetro MMA8652");
MODULE_INFO(mse_imd, "Este driver fue realizado para la matería IMD de la MSE");
