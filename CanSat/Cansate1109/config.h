/*=====================Configure========================*/
#define I_AM_MASTER
//#define I_AM_POWER
//#define I_AM_COMMUNICATE
//#define I_AM_LOAD

/*=======================Address========================*/
#define MASTER_BOARD 0x00
#define POWER_BOARD 0x11
#define COMMUNICATE_BOARD 0x12

/*=====================Code of Pin========================*/

/*------------------Pin of Master Board-----------------*/
#ifdef I_AM_MASTER
#define MyAdd MASTER_BOARD

#endif

/*-----------------Pin of Communicate Board---------------*/
#ifdef I_AM_COMMUNICATE
#define MyAdd COMMUNICATE_BOARD

#endif

/*-------------------Pin of Power Board------------------*/
#ifdef I_AM_POWER
#define MyAdd POWER_BOARD

#endif

/*====================Code of Command====================*/

/*----------------------Master Board---------------------*/
#define READ_TIME 0x05
#define GPS_DATE 0x06
#define BMP180_DATE 0x07
#define commandPower 0x08

/*----------------------Power Board---------------------*/


/*-------------------Communicate Board------------------*/
#define RECEIVE_COMMAND 0x19







