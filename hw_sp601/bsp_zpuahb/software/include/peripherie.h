#ifndef PERIPHERIE_H
#define PERIPHERIE_H

#include <types.h>



////////////////////
// hardware types

// gpio
typedef struct {
    volatile uint32_t iodata;   // 000
    volatile uint32_t ioout;    // 001
    volatile uint32_t iodir;    // 010, for bidir port bits
    volatile uint32_t irqmask;  // 011
    volatile uint32_t irqpol;   // 100
    volatile uint32_t irqedge;  // 101
    volatile uint32_t bypass;   // 110
} grgpio_t;


// uart
#define UART_STATUS_DATA_READY               (1<< 0)
#define UART_STATUS_TX_SHREG_EMPT            (1<< 1)
#define UART_STATUS_TX_REG_EMPTY             (1<< 2)
#define UART_STATUS_BREAK_RECEIVED           (1<< 3)
#define UART_STATUS_OVERRUN                  (1<< 4)
#define UART_STATUS_PARITY_ERROR             (1<< 5)
#define UART_STATUS_FRAMING_ERROR            (1<< 6)
#define UART_STATUS_TX_FIFO_HALF_FULL        (1<< 7)
#define UART_STATUS_RX_FIFO_HALF_FULL        (1<< 8)
#define UART_STATUS_TX_FIFO_FULL             (1<< 9)
#define UART_STATUS_RX_FIFO_FULL             (1<<10)

#define UART_CONTROL_RX_ENABLE               (1<< 0)
#define UART_CONTROL_TX_ENABLE               (1<< 1)
#define UART_CONTROL_RX_INT_ENABLE           (1<< 2)
#define UART_CONTROL_TX_INT_ENABLE           (1<< 3)
#define UART_CONTROL_PARITY_SELECT           (1<< 4)
#define UART_CONTROL_PARITY_ENABLE           (1<< 5)
#define UART_CONTROL_FLOW_CONTROL            (1<< 6)
#define UART_CONTROL_LOOP_BACK               (1<< 7)
#define UART_CONTROL_EXTERNAL_CLOCK          (1<< 8)
#define UART_CONTROL_TX_FIFO_INT_ENABLE      (1<< 9)
#define UART_CONTROL_RX_FIFO_INT_ENABLE      (1<<10)
#define UART_CONTROL_FIFO_DEBUG_MODE         (1<<11)
#define UART_CONTROL_BREAK_INT_ENABLE        (1<<12)
#define UART_CONTROL_DELAYED_INT_ENABLE      (1<<13)
#define UART_CONTROL_TX_REG_EMPTY_INT_ENABLE (1<<14)
#define UART_CONTROL_FIFO_AVAILIBLE          (1<<31)

typedef struct {
    volatile uint32_t data;         // 000000
    volatile uint32_t status;       // 000001 
    volatile uint32_t ctrl;         // 000010 
    volatile uint32_t scaler;       // 000011
    volatile uint32_t fifo_debug;   // 000100
} apbuart_t;


// timer (grip.pdf p. 279)
#define TIMER_ENABLE                (1<<0)
#define TIMER_RESTART               (1<<1)
#define TIMER_LOAD                  (1<<2)
#define TIMER_INT_ENABLE            (1<<3)
#define TIMER_INT_PENDING           (1<<4)
#define TIMER_CHAIN                 (1<<5)
#define TIMER_DEBUG_HALT            (1<<6)
typedef struct {
    volatile uint32_t value;
    volatile uint32_t reload;
    volatile uint32_t ctrl;
    volatile uint32_t unused;
} gptimer_element_t;

#define TIMER_CONFIG_DISABLE_FREEZE (1<<8)
typedef struct {
    volatile uint32_t scaler;          // 00000
    volatile uint32_t scaler_reload;   // 00001
    volatile uint32_t config;          // 00010 ntimers, pirq
    volatile uint32_t unused;          // 00011
    gptimer_element_t e[8];
} gptimer_t;

#define CLOCKS_PER_SECOND         (1000)
void usleep( uint32_t nsec);
void msleep( uint32_t msec);
void sleep( uint32_t sec);
void timer_init( void);


// i2c
// control register
#define I2C_CORE_ENABLE              (1<<7)
#define I2C_INT_ENABLE               (1<<6)
// command register
#define I2C_START                    (1<<7)
#define I2C_STOP                     (1<<6)
#define I2C_READ                     (1<<5)
#define I2C_WRITE                    (1<<4)
#define I2C_ACK                      (1<<3)
#define I2C_INT_ACK                  (1<<0)
// status register
#define I2C_RX_ACK                   (1<<7)
#define I2C_BUSY                     (1<<6)
#define I2C_ARB_LOST                 (1<<5)
#define I2C_TIP                      (1<<1)
#define I2C_INT                      (1<<0)

typedef struct {
    volatile uint32_t clock_prescaler;  // prer 0x00
    volatile uint32_t control;          // ctr  0x04
    volatile uint32_t data;             // xr   0x08 write -> transmit, read -> receive
    volatile uint32_t command;          // csr  0x0c write -> command,  read -> status
} i2cmst_t; // i2cmstregs


// vga
typedef struct {
    volatile uint32_t data;
    volatile uint32_t background_color;
    volatile uint32_t foreground_color;
} apbvga_t;


// ethernet
#define ETHER_DESCRIPTOR_ENABLE              (1<<11)
#define ETHER_DESCRIPTOR_WRAP                (1<<12)
#define ETHER_DESCRIPTOR_INT_ENABLE          (1<<13)
#define ETHER_DESCRIPTOR_UNDERRUN_ERR        (1<<14)
#define ETHER_DESCRIPTOR_ATTEMEPT_LIMIT_ERR  (1<<15)
typedef struct {
    volatile uint32_t control;
    volatile uint32_t address;
} greth_tx_descriptor_t;

#define ETHER_CONTROL_TX_ENABLE              (1<< 0)
#define ETHER_CONTROL_RX_ENABLE              (1<< 1)
#define ETHER_CONTROL_TX_INT                 (1<< 2)
#define ETHER_CONTROL_RX_INT                 (1<< 3)
#define ETHER_CONTROL_FULL_DUPLEX            (1<< 4)
#define ETHER_CONTROL_PROMISCUOUS_MODE       (1<< 5)
#define ETHER_CONTROL_RESET                  (1<< 6)
#define ETHER_CONTROL_SPEED                  (1<< 7)
#define ETHER_CONTROL_EDCL_AVAILABLE         (1<<31)

#define ETHER_STATUS_RX_ERROR                (1<< 0)
#define ETHER_STATUS_TX_ERROR                (1<< 1)
#define ETHER_STATUS_RX_INT                  (1<< 2)
#define ETHER_STATUS_TX_INT                  (1<< 3)
#define ETHER_STATUS_RX_AHB_ERROR            (1<< 4)
#define ETHER_STATUS_TX_AHB_ERROR            (1<< 5)
#define ETHER_STATUS_RX_TOO_SMALL            (1<< 6)
#define ETHER_STATUS_INVALID_ADDRESS         (1<< 7)

#define ETHER_MDIO_WR                        (1<< 0)
#define ETHER_MDIO_RD                        (1<< 1)
#define ETHER_MDIO_LINKFAIL                  (1<< 2)
#define ETHER_MDIO_BUSY                      (1<< 3)
#define ETHER_MDIO_NOT_VALID                 (1<< 4)

typedef struct {
    volatile uint32_t control;          // 0x00
    volatile uint32_t status;           // 0x04
    volatile uint32_t mac_msb;          // 0x08
    volatile uint32_t mac_lsb;          // 0x0C
    volatile uint32_t mdio_control;     // 0x10
    volatile uint32_t tx_pointer;       // 0x14
    volatile uint32_t rx_pointer;       // 0x18
    volatile uint32_t edcl_ip;          // 0x1C
    volatile uint32_t hash_msb;         // 0x20
    volatile uint32_t hash_lsb;         // 0x24
} greth_t;


struct udp_header_st {
    uint16_t source_port;
    uint16_t dest_port;
    uint16_t length;
    uint16_t checksum;
    uint8_t  data[1500];//[data_length];
} __attribute((packed));

typedef struct udp_header_st udp_header_t;


//uint32_t data_length       = 64; // minimum size is 46 (w/o vlan tag) or 42 (with vlan tag)

#define PROTOCOL_UDP   (17)
#define FLAG_DF        (1<<14)
#define FLAG_MF        (1<<15)
struct ip_header_st {
    uint8_t      version; // +ihl (ip header length)
    uint8_t      tos;
    uint16_t     length;
    uint16_t     identification;
    uint16_t     fragment_offset; // +flags
    uint8_t      ttl;
    uint8_t      protocol_id; // udp = 17, tcp = 6
    uint16_t     checksum;
    uint32_t     source_ip;
    uint32_t     dest_ip;
    udp_header_t udp_header;
} __attribute((packed));

typedef struct ip_header_st ip_header_t;

#define ETHERTYPE_IPv4  (0x0800)
#define ETHERTYPE_ARP   (0x0806)
struct mac_header_st {
    uint8_t     dest_mac[6];
    uint8_t     source_mac[6];
    uint16_t    ethertype; // length or eg. 0x800 IPv4, 0x0806 ARP, 0x8892 Profinet, 0x88a4 etherCat
    ip_header_t ip_header;
} __attribute((packed));
typedef struct mac_header_st mac_header_t;


// ddr control register set
typedef struct {
    volatile uint32_t sdram_control;
    volatile uint32_t sdram_config;
    volatile uint32_t sdram_power_saving;
    volatile uint32_t reserved;
    volatile uint32_t status_read;
    volatile uint32_t phy_config_0;
    volatile uint32_t phy_config_1;
} ddrspa_t;


// debug console (for simulation)
char debug_putchar( char c);

// function pointer for putchar
extern char (* putchar_fp) ( char);


// iqr
typedef struct {
    volatile uint32_t irq_level;   // 0x00
    volatile uint32_t irq_pending; // 0x04
    volatile uint32_t irq_force;   // 0x08
    volatile uint32_t irq_clear;   // 0x0c
    volatile uint32_t mp_status;   // 0x10
    volatile uint32_t broadcast;   // 0x14 (NCPU > 1)
    volatile uint32_t dummy[10];   // 0x18 - 0x3c
    volatile uint32_t irq_mask;    // 0x40
    // open: interrupt force, extended interrupt acknowledge
} irqmp_t;


// mctrl
typedef struct {
    volatile uint32_t mcfg1; // 0x00
    volatile uint32_t mcfg2; // 0x04
    volatile uint32_t mcfg3; // 0x08
    volatile uint32_t mcfg4; // 0x0c
} mctrl_t;



////////////////////
// hardware units

// ZPU frequency
#define F_CPU           (100000000)

// set min prescaler to ntimers+1
#define TIMER_PRESCALER (8)

// scaler for uart
#define UART_BAUD_RATE  (115200)
#define UART_SCALER     (F_CPU/(8*UART_BAUD_RATE))
#define UART_FIFOSIZE   (16)

// scaler for i2c
#define I2C_PRESCALER_100K  (F_CPU/(5 * 100000)-1)
#define I2C_PRESCALER_400K  (F_CPU/(5 * 400000)-1)


extern apbuart_t         *uart0;
extern gptimer_t         *timer0;
extern irqmp_t           *irqmp0;
extern apbvga_t          *vga0;
extern grgpio_t          *gpio0;
extern greth_t           *ether0;
extern mctrl_t           *mctrl0;
volatile extern uint32_t *debug_con0;
volatile extern uint32_t *reset_reg;
extern ddrspa_t          *ddr0;

extern i2cmst_t          *i2c_dvi;
extern i2cmst_t          *i2c_fmc;

//char       *debug_con0 = (char *)       0x80000000;
//uint32_t   *reset_reg  = (uint32_t *)   0x80000004;
//apbuart_t  *uart0      = (apbuart_t *)  0x80000100;
//gptimer_t  *timer0     = (gptimer_t *)  0x80000200;
//irqmp_t    *irqmp0     = (irqmp_t *)    0x80000300; // tbd
//grgpio_t   *gpio0      = (grgpio_t *)   0x80000400;
//greth_t    *ether0     = (greth_t *)    0x80000500;
//apbvga_t   *vga0       = (apbvga_t *)   0x80000600;
//i2cmst_t   *i2c_dvi    = (i2cmst_t *)   0x80000700; // not on sp601
//i2cmst_t   *i2c_fmc    = (i2cmst_t *)   0x80000a00;
//mctrl_t    *mctrl0     = (mctrl_t *)    0x80000f00;

#endif // PERIPHERIE_H