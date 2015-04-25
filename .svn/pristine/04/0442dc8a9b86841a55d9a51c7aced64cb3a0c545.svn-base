/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu_0' in SOPC Builder design 'sopc_2013_receiver'
 * SOPC Builder design path: /home/ucart/Desktop/microcart-f2013/BasicPrograms/LABET_SYSTEM/hw/sopc_2013_receiver.sopcinfo
 *
 * Generated: Wed Mar 12 16:35:42 CDT 2014
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x820
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x0
#define NIOS2_CPU_IMPLEMENTATION "small"
#define NIOS2_DATA_ADDR_WIDTH 28
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x8004020
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 32768
#define NIOS2_INST_ADDR_WIDTH 28
#define NIOS2_RESET_ADDR 0x8004000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SPI
#define __ALTERA_AVALON_SYSID
#define __ALTERA_AVALON_TIMER
#define __ALTERA_AVALON_UART
#define __ALTERA_NIOS2
#define __ALTMEMDDR
#define __WIFI_TOP


/*
 * Prog_timer configuration
 *
 */

#define ALT_MODULE_CLASS_Prog_timer altera_avalon_timer
#define PROG_TIMER_ALWAYS_RUN 0
#define PROG_TIMER_BASE 0x1000
#define PROG_TIMER_COUNTER_SIZE 64
#define PROG_TIMER_FIXED_PERIOD 0
#define PROG_TIMER_FREQ 50000000u
#define PROG_TIMER_IRQ 5
#define PROG_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PROG_TIMER_LOAD_VALUE 49999ULL
#define PROG_TIMER_MULT 0.0010
#define PROG_TIMER_NAME "/dev/Prog_timer"
#define PROG_TIMER_PERIOD 1
#define PROG_TIMER_PERIOD_UNITS "ms"
#define PROG_TIMER_RESET_OUTPUT 0
#define PROG_TIMER_SNAPSHOT 1
#define PROG_TIMER_SPAN 64
#define PROG_TIMER_TICKS_PER_SEC 1000u
#define PROG_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define PROG_TIMER_TYPE "altera_avalon_timer"


/*
 * System configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2"
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_NAME "cpu_0"
#define ALT_DEVICE_FAMILY "CYCLONEIII"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x1110
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x1110
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x1110
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "sopc_2013_receiver"


/*
 * altera_extended_hal_bsp configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK PROG_TIMER
#define ALT_TIMESTAMP_CLK TIMER_0


/*
 * altmemddr_0 configuration
 *
 */

#define ALTMEMDDR_0_BASE 0x4000000
#define ALTMEMDDR_0_IRQ -1
#define ALTMEMDDR_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ALTMEMDDR_0_NAME "/dev/altmemddr_0"
#define ALTMEMDDR_0_SPAN 67108864
#define ALTMEMDDR_0_TYPE "altmemddr"
#define ALT_MODULE_CLASS_altmemddr_0 altmemddr


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x1110
#define JTAG_UART_0_IRQ 3
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * onchip_memory2_0 configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory2_0 altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_0_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_0_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_0_BASE 0x8004000
#define ONCHIP_MEMORY2_0_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_0_DUAL_PORT 0
#define ONCHIP_MEMORY2_0_GUI_RAM_BLOCK_TYPE "Automatic"
#define ONCHIP_MEMORY2_0_INIT_CONTENTS_FILE "onchip_memory2_0"
#define ONCHIP_MEMORY2_0_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY2_0_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY2_0_IRQ -1
#define ONCHIP_MEMORY2_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY2_0_NAME "/dev/onchip_memory2_0"
#define ONCHIP_MEMORY2_0_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_0_RAM_BLOCK_TYPE "Auto"
#define ONCHIP_MEMORY2_0_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY2_0_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_0_SIZE_VALUE 16384u
#define ONCHIP_MEMORY2_0_SPAN 16384
#define ONCHIP_MEMORY2_0_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY2_0_WRITABLE 1


/*
 * pio_aile configuration
 *
 */

#define ALT_MODULE_CLASS_pio_aile altera_avalon_pio
#define PIO_AILE_BASE 0x10c0
#define PIO_AILE_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_AILE_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_AILE_CAPTURE 0
#define PIO_AILE_DATA_WIDTH 32
#define PIO_AILE_DO_TEST_BENCH_WIRING 0
#define PIO_AILE_DRIVEN_SIM_VALUE 0x0
#define PIO_AILE_EDGE_TYPE "NONE"
#define PIO_AILE_FREQ 50000000u
#define PIO_AILE_HAS_IN 0
#define PIO_AILE_HAS_OUT 1
#define PIO_AILE_HAS_TRI 0
#define PIO_AILE_IRQ -1
#define PIO_AILE_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_AILE_IRQ_TYPE "NONE"
#define PIO_AILE_NAME "/dev/pio_aile"
#define PIO_AILE_RESET_VALUE 0x0
#define PIO_AILE_SPAN 16
#define PIO_AILE_TYPE "altera_avalon_pio"


/*
 * pio_elev configuration
 *
 */

#define ALT_MODULE_CLASS_pio_elev altera_avalon_pio
#define PIO_ELEV_BASE 0x10d0
#define PIO_ELEV_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_ELEV_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_ELEV_CAPTURE 0
#define PIO_ELEV_DATA_WIDTH 32
#define PIO_ELEV_DO_TEST_BENCH_WIRING 0
#define PIO_ELEV_DRIVEN_SIM_VALUE 0x0
#define PIO_ELEV_EDGE_TYPE "NONE"
#define PIO_ELEV_FREQ 50000000u
#define PIO_ELEV_HAS_IN 0
#define PIO_ELEV_HAS_OUT 1
#define PIO_ELEV_HAS_TRI 0
#define PIO_ELEV_IRQ -1
#define PIO_ELEV_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_ELEV_IRQ_TYPE "NONE"
#define PIO_ELEV_NAME "/dev/pio_elev"
#define PIO_ELEV_RESET_VALUE 0x0
#define PIO_ELEV_SPAN 16
#define PIO_ELEV_TYPE "altera_avalon_pio"


/*
 * pio_gear configuration
 *
 */

#define ALT_MODULE_CLASS_pio_gear altera_avalon_pio
#define PIO_GEAR_BASE 0x10f0
#define PIO_GEAR_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_GEAR_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_GEAR_CAPTURE 0
#define PIO_GEAR_DATA_WIDTH 32
#define PIO_GEAR_DO_TEST_BENCH_WIRING 0
#define PIO_GEAR_DRIVEN_SIM_VALUE 0x0
#define PIO_GEAR_EDGE_TYPE "NONE"
#define PIO_GEAR_FREQ 50000000u
#define PIO_GEAR_HAS_IN 0
#define PIO_GEAR_HAS_OUT 1
#define PIO_GEAR_HAS_TRI 0
#define PIO_GEAR_IRQ -1
#define PIO_GEAR_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_GEAR_IRQ_TYPE "NONE"
#define PIO_GEAR_NAME "/dev/pio_gear"
#define PIO_GEAR_RESET_VALUE 0x0
#define PIO_GEAR_SPAN 16
#define PIO_GEAR_TYPE "altera_avalon_pio"


/*
 * pio_length configuration
 *
 */

#define ALT_MODULE_CLASS_pio_length altera_avalon_pio
#define PIO_LENGTH_BASE 0x10a0
#define PIO_LENGTH_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_LENGTH_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_LENGTH_CAPTURE 0
#define PIO_LENGTH_DATA_WIDTH 32
#define PIO_LENGTH_DO_TEST_BENCH_WIRING 0
#define PIO_LENGTH_DRIVEN_SIM_VALUE 0x0
#define PIO_LENGTH_EDGE_TYPE "NONE"
#define PIO_LENGTH_FREQ 50000000u
#define PIO_LENGTH_HAS_IN 1
#define PIO_LENGTH_HAS_OUT 0
#define PIO_LENGTH_HAS_TRI 0
#define PIO_LENGTH_IRQ -1
#define PIO_LENGTH_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_LENGTH_IRQ_TYPE "NONE"
#define PIO_LENGTH_NAME "/dev/pio_length"
#define PIO_LENGTH_RESET_VALUE 0x0
#define PIO_LENGTH_SPAN 16
#define PIO_LENGTH_TYPE "altera_avalon_pio"


/*
 * pio_rudd configuration
 *
 */

#define ALT_MODULE_CLASS_pio_rudd altera_avalon_pio
#define PIO_RUDD_BASE 0x10e0
#define PIO_RUDD_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_RUDD_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_RUDD_CAPTURE 0
#define PIO_RUDD_DATA_WIDTH 32
#define PIO_RUDD_DO_TEST_BENCH_WIRING 0
#define PIO_RUDD_DRIVEN_SIM_VALUE 0x0
#define PIO_RUDD_EDGE_TYPE "NONE"
#define PIO_RUDD_FREQ 50000000u
#define PIO_RUDD_HAS_IN 0
#define PIO_RUDD_HAS_OUT 1
#define PIO_RUDD_HAS_TRI 0
#define PIO_RUDD_IRQ -1
#define PIO_RUDD_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_RUDD_IRQ_TYPE "NONE"
#define PIO_RUDD_NAME "/dev/pio_rudd"
#define PIO_RUDD_RESET_VALUE 0x0
#define PIO_RUDD_SPAN 16
#define PIO_RUDD_TYPE "altera_avalon_pio"


/*
 * pio_thro configuration
 *
 */

#define ALT_MODULE_CLASS_pio_thro altera_avalon_pio
#define PIO_THRO_BASE 0x10b0
#define PIO_THRO_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_THRO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_THRO_CAPTURE 0
#define PIO_THRO_DATA_WIDTH 32
#define PIO_THRO_DO_TEST_BENCH_WIRING 0
#define PIO_THRO_DRIVEN_SIM_VALUE 0x0
#define PIO_THRO_EDGE_TYPE "NONE"
#define PIO_THRO_FREQ 50000000u
#define PIO_THRO_HAS_IN 0
#define PIO_THRO_HAS_OUT 1
#define PIO_THRO_HAS_TRI 0
#define PIO_THRO_IRQ -1
#define PIO_THRO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_THRO_IRQ_TYPE "NONE"
#define PIO_THRO_NAME "/dev/pio_thro"
#define PIO_THRO_RESET_VALUE 0x0
#define PIO_THRO_SPAN 16
#define PIO_THRO_TYPE "altera_avalon_pio"


/*
 * spi_0 configuration
 *
 */

#define ALT_MODULE_CLASS_spi_0 altera_avalon_spi
#define SPI_0_BASE 0x1060
#define SPI_0_CLOCKMULT 1
#define SPI_0_CLOCKPHASE 1
#define SPI_0_CLOCKPOLARITY 1
#define SPI_0_CLOCKUNITS "Hz"
#define SPI_0_DATABITS 16
#define SPI_0_DATAWIDTH 16
#define SPI_0_DELAYMULT "1.0E-9"
#define SPI_0_DELAYUNITS "ns"
#define SPI_0_EXTRADELAY 0
#define SPI_0_INSERT_SYNC 0
#define SPI_0_IRQ 1
#define SPI_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SPI_0_ISMASTER 1
#define SPI_0_LSBFIRST 0
#define SPI_0_NAME "/dev/spi_0"
#define SPI_0_NUMSLAVES 1
#define SPI_0_PREFIX "spi_"
#define SPI_0_SPAN 32
#define SPI_0_SYNC_REG_DEPTH 2
#define SPI_0_TARGETCLOCK 1000000u
#define SPI_0_TARGETSSDELAY "0.0"
#define SPI_0_TYPE "altera_avalon_spi"


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid
#define SYSID_BASE 0x1118
#define SYSID_ID 390344556u
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1394498364u
#define SYSID_TYPE "altera_avalon_sysid"


/*
 * timer_0 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer
#define TIMER_0_ALWAYS_RUN 0
#define TIMER_0_BASE 0x1080
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_FIXED_PERIOD 0
#define TIMER_0_FREQ 50000000u
#define TIMER_0_IRQ 2
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_LOAD_VALUE 49999ULL
#define TIMER_0_MULT 0.0010
#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_PERIOD 1
#define TIMER_0_PERIOD_UNITS "ms"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_SNAPSHOT 1
#define TIMER_0_SPAN 32
#define TIMER_0_TICKS_PER_SEC 1000u
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_TYPE "altera_avalon_timer"


/*
 * uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_uart_0 altera_avalon_uart
#define UART_0_BASE 0x1040
#define UART_0_BAUD 19200
#define UART_0_DATA_BITS 8
#define UART_0_FIXED_BAUD 0
#define UART_0_FREQ 50000000u
#define UART_0_IRQ 0
#define UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define UART_0_NAME "/dev/uart_0"
#define UART_0_PARITY 'N'
#define UART_0_SIM_CHAR_STREAM ""
#define UART_0_SIM_TRUE_BAUD 0
#define UART_0_SPAN 32
#define UART_0_STOP_BITS 1
#define UART_0_SYNC_REG_DEPTH 2
#define UART_0_TYPE "altera_avalon_uart"
#define UART_0_USE_CTS_RTS 0
#define UART_0_USE_EOP_REGISTER 0


/*
 * uart_1 configuration
 *
 */

#define ALT_MODULE_CLASS_uart_1 altera_avalon_uart
#define UART_1_BASE 0x0
#define UART_1_BAUD 9600
#define UART_1_DATA_BITS 8
#define UART_1_FIXED_BAUD 1
#define UART_1_FREQ 50000000u
#define UART_1_IRQ 6
#define UART_1_IRQ_INTERRUPT_CONTROLLER_ID 0
#define UART_1_NAME "/dev/uart_1"
#define UART_1_PARITY 'N'
#define UART_1_SIM_CHAR_STREAM ""
#define UART_1_SIM_TRUE_BAUD 0
#define UART_1_SPAN 32
#define UART_1_STOP_BITS 1
#define UART_1_SYNC_REG_DEPTH 2
#define UART_1_TYPE "altera_avalon_uart"
#define UART_1_USE_CTS_RTS 0
#define UART_1_USE_EOP_REGISTER 0


/*
 * wifi_top_0 configuration
 *
 */

#define ALT_MODULE_CLASS_wifi_top_0 wifi_top
#define WIFI_TOP_0_BASE 0x1100
#define WIFI_TOP_0_IRQ 4
#define WIFI_TOP_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define WIFI_TOP_0_NAME "/dev/wifi_top_0"
#define WIFI_TOP_0_SPAN 16
#define WIFI_TOP_0_TYPE "wifi_top"

#endif /* __SYSTEM_H_ */
