//for SERCOM2
#define I2C_ADDR	(*(RwReg  *)0x42001024U)
#define I2C_DATA	(*(RwReg8 *)0x42001028U)
#define	I2C_CTRLB	(*(RwReg  *)0x42001004U)
#define I2C_STATUS	(*(RwReg16*)0x4200101AU)
#define I2C_INTFLAG	(*(RwReg8 *)0x42001018U)
#define READ	1
#define WRITE	0
#define NotACK		(I2C_STATUS & 0b100)

//PIN defs
#define SDA			PA12
#define SCL			PA13
#define WP			PA15

#define EEP_ADDR 0b10100000			//7 bit address, last bit will be changed according ot R/W
//! [address]

/* Number of times to try to send packet if failed. */

#define EEPTIMEOUT 1000

/* Init software module. */
//! [dev_inst]
struct i2c_master_module i2c_master_instance;
//! [timeout]

/* Init software module. */
//! [dev_inst]
//! [dev_inst]

void configure_i2c_master(void);

bool EEP_NACK(void);	//returns 1 if EEProm doesn't ACk
void EEP_Reset(void);	//generates reset sequence by bit banging
bool EEP_timeout(void);	//returns 1 and prints err on LCD if EEPROM is stuck
void I2C_State(void);	//checks I2C bus state and puts it into idle if it's unknown
bool EEP_WriteByte(uint8_t addr, uint8_t data);	
uint8_t EEP_ReadByte(uint8_t addr);	//returns byte read from EEP

void EEP_WriteInt(uint8_t addr, uint16_t data); //writes 2 byte into EEP
uint16_t EEP_ReadInt(uint8_t addr);

