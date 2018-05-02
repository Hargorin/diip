//
//  controller_tb.cpp
//
//  Created by Jan Stocker on 08/11/17.
//  Copyright © 2017 Jan Stocker. All rights reserved.
//
#include <stdlib.h>

#include "../inc/controller.h"

int main()
{
	int i;
	uint8_t memory[IN_SIZE+OUT_SIZE];
	uint8_t stream_set[WINDOW_HEIGHT*LINE_SIZE];
	uint8_t mem_set[LINE_SIZE-WINDOW_HEIGHT+1];

    apuint32_t uft_tx_memory_address;
    ap_uint<1> uft_tx_start;

    apuint32_t uft_reg[16];
    apuint32_t uft_reg_set[16];

    AXI_VALUE aval;
	AXI_STREAM outData;
	AXI_STREAM inData;


	printf("***************\n");
	printf("Start Testbench\n");
	printf("Required memory size is %d bytes\n", IN_SIZE+OUT_SIZE);
	
	//************************************************************************
	//Put data into memory
	//************************************************************************
	uint8_t val = 0;
	for(i=0; i < (WINDOW_HEIGHT*LINE_SIZE); i++)
	{
		memory[i] = val++;
	}
	// Put data into stream comming from the core
	val = 255;
	for(i=0; i < (LINE_SIZE-WINDOW_HEIGHT+1); i++)
	{
		aval.data = val--;
		if(i == (LINE_SIZE-WINDOW_HEIGHT))
			aval.last = 1;
		inData.write(aval);
	}
	// clear out uft registers
	memset(uft_reg, 0, sizeof(uft_reg));

	//************************************************************************
	//Call the hardware function
	//************************************************************************
	controller_top(memory, uft_reg, outData, inData,
			&uft_tx_memory_address, &uft_tx_start);

	//************************************************************************
	//Run a software version of the hardware function to validate results
	//************************************************************************
	int row = 0;
	int col = 0;
	for(i=0; i < WINDOW_HEIGHT*LINE_SIZE; i++)
	{
		stream_set[i] = memory[row*LINE_SIZE + col];
		row++;
		if(row == WINDOW_HEIGHT)
		{
			row = 0;
			col++;
		}
	}
	// write the stream data to memory
	val = 255;
	for(i=0; i < (LINE_SIZE-WINDOW_HEIGHT+1); i++)
	{
		mem_set[i] = val--;
	}
	// uft_reg
	memset(uft_reg_set, 0, sizeof(uft_reg_set));
	uft_reg_set[0] = 0x1;
	uft_reg_set[1] = 0x400;
	uft_reg_set[2] = 0x1;
	uft_reg_set[3] = 0x400;
	uft_reg_set[4] = 0x1;
	uft_reg_set[5] = 0x400;
	uft_reg_set[6] = 0x1;
	uft_reg_set[7] = 0x400;
	uft_reg_set[8] = 0x1;
	uft_reg_set[9] = 0x400;
	uft_reg_set[10] = 0x1;
	uft_reg_set[11] = 0x400;
	uft_reg_set[12] = 0x1;
	uft_reg_set[13] = 0x400;
	uft_reg_set[14] = 0x1;
	uft_reg_set[15] = 0x400;
	//************************************************************************
	//Compare results from output stream
	//************************************************************************
	uint8_t test;
	for(i=0; i < WINDOW_HEIGHT*LINE_SIZE; i++)
	{
		aval = outData.read();
		test = (uint8_t)aval.data;
		if(stream_set[i] != test)
		{
			printf("i = %d B = %d out= %d\n",i,stream_set[i],test);
			printf("ERROR HW and SW results mismatch\n");
			return 1;
		}
		// Assert TLAST signal
//		if(aval.last)
//			printf("i=%d last=1\n",i);
//		if(!aval.last)
//			printf("i=%d last=0\n",i);
		if (!aval.last && (i == (WINDOW_HEIGHT*LINE_SIZE-1)))
		{
			printf("ERROR: TLAST was not asserted. i=%d of=%d\n",i,WINDOW_HEIGHT*LINE_SIZE);
			return 1;
		}
		if (aval.last && (i != (WINDOW_HEIGHT*LINE_SIZE-1)))
		{
			printf("ERROR: TLAST was asserted too early. i=%d of=%d\n",i,WINDOW_HEIGHT*LINE_SIZE);
			return 1;
		}
	}

	//Compare results from memory
	for(i=0; i < (LINE_SIZE-WINDOW_HEIGHT+1); i++)
	{
		if(memory[OUT_MEMORY_BASE+i] != mem_set[i])
		{
//			printf("i = %d is = %d should= %d\n",i,memory[OUT_MEMORY_BASE+i],mem_set[i]);
			printf("ERROR HW and SW results mismatch\n");
			return 1;
		}
	}

	// Check UFT register
	for(i = 0; i < 16; i++)
	{
		if(uft_reg[i] != uft_reg_set[i])
		{
			printf("Error: uft_reg[%d] is %x should %x\n", i, (uint32_t)uft_reg[0], (uint32_t)uft_reg_set[i]);
			return 1;
		}
	}

	printf("Success! HW and SW results match\n");
	printf("End Testbench\n");
	printf("***************\n");
	return 0;
}

  
