//#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "encoding.h"

#define FLL_BASE_ADDR 0x1A100000
#define CCR2_REG 0x30

//#define FPGA_EMULATION

int main(int argc, char const *argv[]) {
  #ifdef FPGA_EMULATION
  int baud_rate = 115200;
  int test_freq = 50000000;
  #else
  set_flls();
  int baud_rate = 115200;
  int test_freq = 100000000;
  #endif
  uart_set_cfg(0,(test_freq/baud_rate)>>4);

  uint32_t offset;
  uint32_t dco_byp_reg_index = 21;
  uint32_t var;

  offset = 1 << dco_byp_reg_index;
  uint32_t * cva6_dco_bypass = FLL_BASE_ADDR + CCR2_REG;

  var = pulp_read32(cva6_dco_bypass);
  printf("Default CCR2 reg value: %h\r\n",var);
  uart_wait_tx_done();
  pulp_write32(cva6_dco_bypass,var+offset); //128MB addressable

  printf("CVA6 running at 1GHz!\r\n");
  uart_wait_tx_done();
  return 0;
}
