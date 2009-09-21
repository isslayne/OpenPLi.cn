/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <ppcboot.h>
#include <mpc8xx.h>

flash_info_t    flash_info[CFG_MAX_FLASH_BANKS];

/*-----------------------------------------------------------------------
 */

unsigned long flash_init (void)
{
	/* All Speech Design board memory (DRAM and EPROM) initialisation is
	done in dram_init().
	The caller of ths function here expects the total size and will hang,
	if we give here back 0. So we return the EPROM size. */

	return (1024 * 1024); /* 1 MB */
}

/*-----------------------------------------------------------------------
 */

flash_info_t *addr2info (ulong addr)
{
	return (NULL);
}

/*-----------------------------------------------------------------------
 * Copy memory to flash.
 * Returns:
 * 0 - OK
 * 1 - write timeout
 * 2 - Flash not erased
 * 4 - target range includes protected sectors
 * 8 - target address not in Flash memory
 */
int flash_write (uchar *src, ulong addr, ulong cnt)
{
	return (1);	/* any other error codes are possible as well */
}

void flash_print_info (flash_info_t *info)
{
	printf("no FLASH memory in MPC823TS board\n");
	return;
}

void flash_erase (flash_info_t *info, int s_first, int s_last)
{
	return;
}

/*-----------------------------------------------------------------------
 */
