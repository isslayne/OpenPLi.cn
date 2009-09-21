/*
  *
  * File:  scc.c
  * Description:
  * 	Basic ET HW initialization and packet RX/TX routines
  *
  * NOTES  <<<IMPORTANT:  PLEASE READ>>>:
  *     1)  Specifically Designed to run on TQM823L/STK8xxL board.
  *     2)  Do not cache Rx/Tx buffers.
  *
  *
  * History
  * 8/13/99   saw    Ported driver from MPC821/MPC821ADS (SCC1)
  * 8/16/00   bor    Ported driver from MPC823FADS board
  *
  */

/*
 * MPC8260 FCC Fast Ethernet MII <-> PHY
 *
 * Cogent CMA282 CPU module
 * ------------------------
 * Uses FCC2 with an LTX970 10/100 PHY
 *
 * PB-22 --------> TXD0
 * PB-23 --------> TXD1
 * PB-24 --------> TXD2
 * PB-25 --------> TXD3
 * PB-31 <-------- TX_ER
 * PB-29 --------> TX_EN
 * PC-16 --------> TX_CLK
 * PB-21 <-------- RXD0
 * PB-20 <-------- RXD1
 * PB-19 <-------- RXD2
 * PB-18 <-------- RXD3
 *...
 */

#include <ppcboot.h>
#include <asm/cpm_8260.h>
#include <net.h>
#include <command.h>

#if defined(CONFIG_ETHER_ON_FCC) && (CONFIG_COMMANDS & CFG_CMD_NET)

#define BD_OFFSET 0x860 /* offset to begin of DPRAM + allocation for serial IF*/

/* Ethernet Transmit and Receive Buffers */
#define DBUF_LENGTH  1520

#define TX_BUF_CNT 2

#define TOUT_LOOP 1000000

/* static char rxbuf[PKTBUFSRX][ DBUF_LENGTH ]; */
static char txbuf[TX_BUF_CNT][ DBUF_LENGTH ];

static uint rxIdx;	/* index of the current RX buffer */
static uint txIdx;	/* index of the current TX buffer */

/*
  * SCC Ethernet Tx and Rx buffer descriptors allocated at the
  *  immr->udata_bd address on Dual-Port RAM
  * Provide for Double Buffering
  */

typedef volatile struct CommonBufferDescriptor {
    cbd_t rxbd[PKTBUFSRX];         /* Rx BD */
    cbd_t txbd[TX_BUF_CNT];         /* Tx BD */
} RTXBD;

static RTXBD *rtx;


int eth_send(volatile void *packet, int length)
{
	int i, j=0;
#if 0
	volatile char *in, *out;
#endif

	/* section 16.9.23.3
	 * Wait for ready
	 */
#if 0
	while (rtx->txbd[txIdx].cbd_sc & BD_ENET_TX_READY);
	out = (char *)(rtx->txbd[txIdx].cbd_bufaddr);
	in = packet;
	for(i = 0; i < length; i++) {
		*out++ = *in++;
	}
	rtx->txbd[txIdx].cbd_datlen = length;
	rtx->txbd[txIdx].cbd_sc |= (BD_ENET_TX_READY | BD_ENET_TX_LAST);
	while (rtx->txbd[txIdx].cbd_sc & BD_ENET_TX_READY) j++;

#ifdef ET_DEBUG
	printf("cycles: %d    status: %x\n", j, rtx->txbd[txIdx].cbd_sc);
#endif
	i = (rtx->txbd[txIdx++].cbd_sc & BD_ENET_TX_STATS) /* return only status bits */;

	/* wrap around buffer index when necessary */
	if (txIdx >= TX_BUF_CNT) txIdx = 0;
#endif

	while ((rtx->txbd[txIdx].cbd_sc & BD_ENET_TX_READY) && (j<TOUT_LOOP)) j++;
	if (j>=TOUT_LOOP) printf("TX not ready\n");
	rtx->txbd[txIdx].cbd_bufaddr = (uint)packet;
	rtx->txbd[txIdx].cbd_datlen = length;
	rtx->txbd[txIdx].cbd_sc |= (BD_ENET_TX_READY | BD_ENET_TX_LAST |BD_ENET_TX_WRAP);
	while ((rtx->txbd[txIdx].cbd_sc & BD_ENET_TX_READY) && (j<TOUT_LOOP)) j++;
	if (j>=TOUT_LOOP) printf("TX timeout\n");
#ifdef ET_DEBUG
	printf("cycles: %d    status: %x\n", j, rtx->txbd[txIdx].cbd_sc);
#endif
	i = (rtx->txbd[txIdx].cbd_sc & BD_ENET_TX_STATS) /* return only status bits */;
	return i;
}

int eth_rx(void)
{
	int length;

   for (;;)
   {
	/* section 16.9.23.2 */
	if (rtx->rxbd[rxIdx].cbd_sc & BD_ENET_RX_EMPTY) {
		length = -1;
		break;     /* nothing received - leave for() loop */
	}

	length = rtx->rxbd[rxIdx].cbd_datlen;

	if (rtx->rxbd[rxIdx].cbd_sc & 0x003f)
	{
#ifdef ET_DEBUG
		printf("err: %x\n", rtx->rxbd[rxIdx].cbd_sc);
#endif
	}
	else
	{
		/* Pass the packet up to the protocol layers. */
		NetReceive(NetRxPackets[rxIdx], length - 4);
	}


	/* Give the buffer back to the SCC. */
	rtx->rxbd[rxIdx].cbd_datlen = 0;

	/* wrap around buffer index when necessary */
	if ((rxIdx + 1) >= PKTBUFSRX) {
           rtx->rxbd[PKTBUFSRX - 1].cbd_sc = (BD_ENET_RX_WRAP | BD_ENET_RX_EMPTY);
	   rxIdx = 0;
	}
	else {
           rtx->rxbd[rxIdx].cbd_sc = BD_ENET_RX_EMPTY;
	   rxIdx++;
	}
   }
   return length;
}

/**************************************************************
  *
  * SCC Ethernet Initialization Routine
  *
  *************************************************************/

int eth_init(bd_t *bis)
{

    int i;
    scc_enet_t *pram_ptr;

    volatile immap_t *immr = (immap_t *)CFG_IMMR;

#if defined(CONFIG_FADS)
   *((uint *) BCSR4) &= ~(BCSR4_ETHLOOP|BCSR4_MODEM_EN);
   *((uint *) BCSR4) |= BCSR4_TFPLDL|BCSR4_TPSQEL|BCSR4_DATA_VOICE;
   *((uint *) BCSR1) &= ~BCSR1_ETHEN;
#endif

    pram_ptr = (scc_enet_t *)&(immr->im_cpm.cp_dparam[PROFF_ENET]);

    rxIdx = 0;
    txIdx = 0;

    /* assign static pointer to BD area */
    rtx = (RTXBD *) (immr->im_cpm.cp_dpmem + BD_OFFSET);

    /* Configure port A pins for Txd and Rxd.
    */
    immr->im_ioport.iop_papar |=  (PA_ENET_RXD | PA_ENET_TXD);
    immr->im_ioport.iop_padir &= ~(PA_ENET_RXD | PA_ENET_TXD);
    immr->im_ioport.iop_paodr &=                ~PA_ENET_TXD;

    /* Configure port C pins to enable CLSN and RENA.
    */
    immr->im_ioport.iop_pcpar &= ~(PC_ENET_CLSN | PC_ENET_RENA);
    immr->im_ioport.iop_pcdir &= ~(PC_ENET_CLSN | PC_ENET_RENA);
    immr->im_ioport.iop_pcso  |=  (PC_ENET_CLSN | PC_ENET_RENA);

    /* Configure port A for TCLK and RCLK.
    */
    immr->im_ioport.iop_papar |=  (PA_ENET_TCLK | PA_ENET_RCLK);
    immr->im_ioport.iop_padir &= ~(PA_ENET_TCLK | PA_ENET_RCLK);


    /*
     * Configure Serial Interface clock routing -- see section 16.7.5.3
     * First, clear all SCC bits to zero, then set the ones we want.
     */

    immr->im_cpm.cp_sicr &= ~SICR_ENET_MASK;
    immr->im_cpm.cp_sicr |= SICR_ENET_CLKRT;


    /*
     * Initialize SDCR -- see section 16.9.23.7
     * SDMA configuration register
     */
    immr->im_siu_conf.sc_sdcr = 0x01;


    /*
     * Setup SCC Ethernet Parameter RAM
     */

    pram_ptr->sen_genscc.scc_rfcr = 0x18;  /* Normal Operation and Mot byte ordering */
    pram_ptr->sen_genscc.scc_tfcr = 0x18;  /* Mot byte ordering, Normal access */

    pram_ptr->sen_genscc.scc_mrblr = DBUF_LENGTH;	/* max. ET package len 1520 */

    pram_ptr->sen_genscc.scc_rbase = (unsigned int)(&rtx->rxbd[0]);      /* Set RXBD tbl start at Dual Port */
    pram_ptr->sen_genscc.scc_tbase = (unsigned int)(&rtx->txbd[0]);      /* Set TXBD tbl start at Dual Port */

    /*
     * Setup Receiver Buffer Descriptors (13.14.24.18)
     * Settings:
     *     Empty, Wrap
     */

    for (i = 0; i < PKTBUFSRX; i++)
    {
      rtx->rxbd[i].cbd_sc = BD_ENET_RX_EMPTY;
      rtx->rxbd[i].cbd_datlen = 0;                                 /* Reset */
      rtx->rxbd[i].cbd_bufaddr = (uint)NetRxPackets[i];
    }

    rtx->rxbd[PKTBUFSRX - 1].cbd_sc |= BD_ENET_RX_WRAP;

    /*
     * Setup Ethernet Transmitter Buffer Descriptors (13.14.24.19)
     * Settings:
     *    Add PADs to Short FRAMES, Wrap, Last, Tx CRC
     */

    for (i = 0; i < TX_BUF_CNT; i++)
    {
      rtx->txbd[i].cbd_sc = (BD_ENET_TX_PAD | BD_ENET_TX_LAST | BD_ENET_TX_TC);
      rtx->txbd[i].cbd_datlen = 0;                                 /* Reset */
      rtx->txbd[i].cbd_bufaddr = (uint)&txbuf[i][0];
    }

    rtx->txbd[TX_BUF_CNT - 1].cbd_sc |= BD_ENET_TX_WRAP;

    /*
     * Enter Command:  Initialize Rx Params for SCC
     */

    do {				/* Spin until ready to issue command	*/
	__asm__ ("eieio");
    } while (immr->im_cpm.cp_cpcr & CPM_CR_FLG);
    /* Issue command */
    immr->im_cpm.cp_cpcr = ((CPM_CR_INIT_RX << 8) | (CPM_CR_ENET << 4) | CPM_CR_FLG);
    do {				/* Spin until command processed		*/
	__asm__ ("eieio");
    } while (immr->im_cpm.cp_cpcr & CPM_CR_FLG);

    /*
     * Ethernet Specific Parameter RAM
     *     see table 13-16, pg. 660,
     *     pg. 681 (example with suggested settings)
     */

    pram_ptr->sen_cpres  = ~(0x0);	/* Preset CRC */
    pram_ptr->sen_cmask  = 0xdebb20e3;	/* Constant Mask for CRC */
    pram_ptr->sen_crcec  = 0x0;		/* Error Counter CRC (unused) */
    pram_ptr->sen_alec   = 0x0;		/* Alignment Error Counter (unused) */
    pram_ptr->sen_disfc  = 0x0;		/* Discard Frame Counter (unused) */
    pram_ptr->sen_pads   = 0x8888;	/* Short Frame PAD Characters */

    pram_ptr->sen_retlim = 15;		/* Retry Limit Threshold */
    pram_ptr->sen_maxflr = 1518;	/* MAX Frame Length Register */
    pram_ptr->sen_minflr = 64;		/* MIN Frame Length Register */

    pram_ptr->sen_maxd1  = DBUF_LENGTH;	/* MAX DMA1 Length Register */
    pram_ptr->sen_maxd2  = DBUF_LENGTH;	/* MAX DMA2 Length Register */

    pram_ptr->sen_gaddr1 = 0x0;		/* Group Address Filter 1 (unused) */
    pram_ptr->sen_gaddr2 = 0x0;		/* Group Address Filter 2 (unused) */
    pram_ptr->sen_gaddr3 = 0x0;		/* Group Address Filter 3 (unused) */
    pram_ptr->sen_gaddr4 = 0x0;		/* Group Address Filter 4 (unused) */

#define ea bis->bi_enetaddr
    pram_ptr->sen_paddrh = (ea[5] << 8) + ea[4];
    pram_ptr->sen_paddrm = (ea[3] << 8) + ea[2];
    pram_ptr->sen_paddrl = (ea[1] << 8) + ea[0];
#undef ea

    pram_ptr->sen_pper   = 0x0;		/* Persistence (unused) */
    pram_ptr->sen_iaddr1 = 0x0;		/* Individual Address Filter 1 (unused) */
    pram_ptr->sen_iaddr2 = 0x0;		/* Individual Address Filter 2 (unused) */
    pram_ptr->sen_iaddr3 = 0x0;		/* Individual Address Filter 3 (unused) */
    pram_ptr->sen_iaddr4 = 0x0;		/* Individual Address Filter 4 (unused) */
    pram_ptr->sen_taddrh = 0x0;		/* Tmp Address (MSB) (unused) */
    pram_ptr->sen_taddrm = 0x0;		/* Tmp Address (unused) */
    pram_ptr->sen_taddrl = 0x0;		/* Tmp Address (LSB) (unused) */

    /*
     * Enter Command:  Initialize Tx Params for SCC
     */

    do {				/* Spin until ready to issue command	*/
	__asm__ ("eieio");
    } while (immr->im_cpm.cp_cpcr & CPM_CR_FLG);
    /* Issue command */
    immr->im_cpm.cp_cpcr = ((CPM_CR_INIT_TX << 8) | (CPM_CR_ENET << 4) | CPM_CR_FLG);
    do {				/* Spin until command processed		*/
	__asm__ ("eieio");
    } while (immr->im_cpm.cp_cpcr & CPM_CR_FLG);

    /*
     * Clear Events in SCCE -- Clear bits by writing 1's
     */

    immr->im_cpm.cp_scc[SCC_ENET].scc_scce = ~(0x0);



    /*
     * Initialize GSMR High 32-Bits
     * Settings:  Normal Mode
     */

   immr->im_cpm.cp_scc[SCC_ENET].scc_gsmrh = 0;

    /*
     * Initialize GSMR Low 32-Bits, but do not Enable Transmit/Receive
     * Settings:
     *     TCI = Invert
     *     TPL =  48 bits
     *     TPP = Repeating 10's
     *     MODE = Ethernet
     */

    immr->im_cpm.cp_scc[SCC_ENET].scc_gsmrl = (	SCC_GSMRL_TCI	 |	\
    						SCC_GSMRL_TPL_48 |	\
						SCC_GSMRL_TPP_10 |	\
						SCC_GSMRL_MODE_ENET);

    /*
     * Initialize the DSR -- see section 13.14.4 (pg. 513) v0.4
     */

    immr->im_cpm.cp_scc[SCC_ENET].scc_dsr = 0xd555;

    /*
     * Initialize the PSMR
     * Settings:
     *      CRC = 32-Bit CCITT
     *      NIB = Begin searching for SFD 22 bits after RENA
     *      BRO = Reject broadcast packets
     *      PROMISCOUS = Catch all packetsregardless of dest. MAC adress
     */
   immr->im_cpm.cp_scc[SCC_ENET].scc_pmsr = (SCC_PMSR_ENCRC | SCC_PMSR_NIB22
                                     /* | SCC_PMSR_BRO | SCC_PMSR_PRO */);

    /*
     * Configure Ethernet TENA Signal
     */

#if (defined(PC_ENET_TENA) && !defined(PB_ENET_TENA))
    immr->im_ioport.iop_pcpar |=  PC_ENET_TENA;
    immr->im_ioport.iop_pcdir &= ~PC_ENET_TENA;
#elif (defined(PB_ENET_TENA) && !defined(PC_ENET_TENA))
    immr->im_cpm.cp_pbpar |= PB_ENET_TENA;
    immr->im_cpm.cp_pbdir |= PB_ENET_TENA;
#else
#error Configuration Error: exactly ONE of PB_ENET_TENA, PC_ENET_TENA must be defined
#endif

    /*
     * Set the ENT/ENR bits in the GSMR Low -- Enable Transmit/Receive
     */

    immr->im_cpm.cp_scc[SCC_ENET].scc_gsmrl |= (SCC_GSMRL_ENR | SCC_GSMRL_ENT);

    return 1;
}



void eth_halt(void)
{
    volatile immap_t *immr = (immap_t *)CFG_IMMR;
    immr->im_cpm.cp_scc[SCC_ENET].scc_gsmrl &= ~(SCC_GSMRL_ENR | SCC_GSMRL_ENT);
}

#if 0
void restart(void)
{
   volatile immap_t *immr = (immap_t *)CFG_IMMR;
   immr->im_cpm.cp_scc[SCC_ENET].scc_gsmrl |= (SCC_GSMRL_ENR | SCC_GSMRL_ENT);
}
#endif

#endif	/* CONFIG_ETHER_ON_FCC && CFG_CMD_NET */
