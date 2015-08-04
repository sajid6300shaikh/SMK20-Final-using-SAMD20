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
//! [timeout]
#define EEPTIMEOUT 1000
//! [timeout]

/* Init software module. */
//! [dev_inst]
struct i2c_master_module i2c_master_instance;
//! [dev_inst]

void configure_EEPROM(void);

//! [initialize_i2c]
void configure_EEPROM(void)
{
	
	pinMode(WP, OUTPUT);
	PinSet(WP);
	/* Initialize config structure and software module. */
	//! [init_conf]
	struct i2c_master_config config_i2c_master;
	i2c_master_get_config_defaults(&config_i2c_master);
	//! [init_conf]

	/* Change buffer timeout to something longer. */
	//! [conf_change]
	config_i2c_master.buffer_timeout = 10000;
	config_i2c_master.generator_source=GCLK_GENERATOR_0;
	config_i2c_master.pinmux_pad0=PINMUX_PA12C_SERCOM2_PAD0;
	config_i2c_master.pinmux_pad1=PINMUX_PA13C_SERCOM2_PAD1;
	//! [conf_change]

	/* Initialize and enable device with config. */
	//! [init_module]
	i2c_master_init(&i2c_master_instance, SERCOM2, &config_i2c_master);
	
	/*BAUD=GCLK0freq(48Mhz)*Thigh
	/i.e SCLfreq=GCLK/(2*Baud)*/
	REG_SERCOM2_I2CM_BAUD=200;				//force baud rate after above setting gives around 100Khz
	

	//! [enable_module]
	i2c_master_enable(&i2c_master_instance);
	//! [enable_module]
	
}

bool EEP_NACK(){
	if (NotACK)			//if eeprom doesn't send ACK
	{
		//lcd.disp(eep error)
		return 1;
	}
	else
		return 0;
}

void EEP_Reset()
{
	i2c_master_disable(&i2c_master_instance);
	pinMux(SCL, Disablemux);
	pinMux(SDA, Disablemux);
	pinMode(SDA,INPUT);
	for (uint8_t i=0;i<9; i++)
	{
		PinSet(SCL);
		delay_us(10);
		if(PinRead(SDA))
		{	
			break;	
		}		
		PinClr(SCL);
	}
	
	pinMux(SCL, CSERCOMmux);
	pinMode(SDA,OUTPUT);
	pinMux(SDA, CSERCOMmux);
	i2c_master_enable(&i2c_master_instance);
	I2C_STATUS|=(1<<4);
	
}
bool EEP_timeout()
{
	uint16_t try=0;
	while (!(I2C_INTFLAG&1) && !(I2C_INTFLAG&2))
	{
		try++;
		if (try==EEPTIMEOUT)
		{	
			LCD_Setcursor(1,2);
			LCD_disp("EEP MB SB fault");
			delay_sec(1);
			EEP_Reset();
			return 1;
		}
	}
	return 0;
}
void I2C_State(){
//if I2C bus state is unknown or busy then force it to idle
		//0 means Unknown
	if(((I2C_STATUS&0x30)== 0)) 
	I2C_STATUS|=(1<<4);  //force idle
		//3 means eeprom is owner of bus
	if (((I2C_STATUS&0x30)== 0x30))
	{	//eeprom is holding SDA pin and needs to be reset
		EEP_Reset();
	}	
}



bool EEP_WriteByte(uint8_t addr, uint8_t data)
{	int count=0;
	I2C_State();
	PinClr(WP);		//disable write protect
	bool EEP_Err=0;
	do 
	{
		I2C_ADDR=(EEP_ADDR | WRITE); //EEProm addr
	} while (EEP_NACK());

	EEP_timeout();
	
	do 
	{
		I2C_DATA=addr;	//byte addr
	} while (EEP_NACK());
	
	EEP_timeout();
	
	do 
	{
		I2C_DATA=data;	//data write
	} while (EEP_NACK());
	
	EEP_timeout();
	
	I2C_CTRLB |=(3<<16);		//stop	
	delay_ms(10);
	PinSet(WP);	
	return EEP_Err;		//not implemented
}





uint8_t EEP_ReadByte(uint8_t addr)
{
	I2C_State();
	uint32_t count=0;
	do 
	{
		I2C_ADDR	=(EEP_ADDR | WRITE);	//i2c addr
		count++;
		if (count==10000);
		break;		
	} while (EEP_NACK());
	
	EEP_timeout();

		I2C_DATA=addr;				//addr
	
	
	EEP_timeout();
	
	do 
	{
		I2C_ADDR	=(EEP_ADDR | READ);	//repeat start
		count++;
	} while (EEP_NACK());
	
	EEP_timeout();
	
	
	volatile uint8_t RData= I2C_DATA;	//read data
	EEP_timeout();
	
	I2C_CTRLB |=(3<<16)|(1<<18);		//stop with nack
	
	return(RData);
	
	
}

void EEP_WriteInt(uint8_t addr, uint16_t data){
	
	uint8_t lsB = (uint8_t)(data & 0xFFu);				//LS byte
	uint8_t msB = (uint8_t)((data >> 8) & 0xFFu);		//MS byte
	EEP_WriteByte(addr, msB);
	EEP_WriteByte(addr+1, lsB);	
}

uint16_t EEP_ReadInt(uint8_t addr){
	
	uint8_t msB = EEP_ReadByte(addr);		//LS byte
	uint8_t lsB = EEP_ReadByte(addr+1);		//MS byte
	return((msB<<8)|(lsB));
}