/**
 * \file
 *
 * Copyright (c) 2012 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#include "gfx.h"

PROGMEM_DECLARE(gfx_color_t, smiley_data[400]) = {
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xff22, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20,
	0xff20, 0xff43, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xff22, 0xff21, 0xffb5, 0xff91,
	0xfffc, 0xff46, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff43,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff22,
	0xff20, 0xff6a, 0xfffe, 0xff48, 0xff20, 0xff20, 0xff20, 0xff20,
	0xff20, 0xff20, 0xff20, 0xff20, 0xff43, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xff22, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20,
	0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20,
	0xff20, 0xff43, 0xffff, 0xffff, 0xffff, 0xffff, 0xff20, 0xff20,
	0xffff, 0xef7d, 0x0000, 0x8bc0, 0xff20, 0xff20, 0xff20, 0xff20,
	0xef7d, 0xef7d, 0x0000, 0x8bc0, 0xff20, 0xff20, 0xffff, 0xffff,
	0xffff, 0xff22, 0xff20, 0xff20, 0xffff, 0xa534, 0x0000, 0x39a0,
	0xff20, 0xff20, 0xff20, 0xff20, 0xef7d, 0xef7d, 0x0000, 0x39a0,
	0xff20, 0xff20, 0xff43, 0xffff, 0xffff, 0xff20, 0xff20, 0xff20,
	0x0000, 0x0000, 0x0000, 0x7320, 0xff20, 0xff20, 0xff20, 0xff20,
	0x0000, 0x0000, 0x0000, 0x7320, 0xff20, 0xff20, 0xff20, 0xffff,
	0xffff, 0xff20, 0xff20, 0xff20, 0x8bc0, 0x39a0, 0x7320, 0xee80,
	0xff20, 0xff20, 0xff20, 0xff20, 0x8bc0, 0x39a0, 0x7320, 0xee80,
	0xff20, 0xff20, 0xff20, 0xffff, 0xffff, 0xff20, 0xff20, 0xff20,
	0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20,
	0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xffff,
	0xffff, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20,
	0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20,
	0xff20, 0xff20, 0xff20, 0xffff, 0xffff, 0xff20, 0xff20, 0xff20,
	0x0000, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20,
	0xff20, 0xff20, 0xff20, 0xff20, 0x0000, 0xff20, 0xff20, 0xffff,
	0xffff, 0xff20, 0xff20, 0xff20, 0x0000, 0xff20, 0xff20, 0xff20,
	0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0x0000,
	0x0000, 0xff20, 0xff20, 0xffff, 0xffff, 0xff21, 0xff20, 0xff20,
	0x0000, 0x0000, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20,
	0xff20, 0xff20, 0xff20, 0x0000, 0xff20, 0xff20, 0xff41, 0xffff,
	0xffff, 0xffff, 0xff20, 0xff20, 0xff20, 0x0000, 0x0000, 0xff20,
	0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0x0000, 0x0000,
	0xff20, 0xff20, 0xffff, 0xffff, 0xffff, 0xffff, 0xff21, 0xff20,
	0xff20, 0xff20, 0x0000, 0x0000, 0x0000, 0x0000, 0xff20, 0xff20,
	0x0000, 0x0000, 0x0000, 0xff20, 0xff20, 0xff41, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xff21, 0xff20, 0xff20, 0xff20, 0xff20,
	0xff20, 0x0000, 0x0000, 0x0000, 0x0000, 0xff20, 0xff20, 0xff20,
	0xff41, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xff21, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff20,
	0xff20, 0xff20, 0xff20, 0xff41, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff21, 0xff20,
	0xff20, 0xff20, 0xff20, 0xff20, 0xff20, 0xff41, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
};
struct gfx_bitmap smiley = {
	.width = 20, .height = 20 , .type = GFX_BITMAP_PROGMEM,
	.data.progmem = (gfx_color_t PROGMEM_PTR_T)smiley_data};
