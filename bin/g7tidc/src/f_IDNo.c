/*//	Copyright 2022 Karl Vincent Pierre Bertin
////
////	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
////
////	1.	Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
////
////	2.	Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
////
////	3.	Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
////
*///	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "../include/header.h"

/*typedef struct tuple_f_IDNo
{
	uint16_t integer_TID;
	uint16_t integer_SID;
	int16_t integer_TSV;
	int8_t integer_TRV;
	int32_t integer_G7TID;
	int16_t integer_G7TID;
} tuple_f_IDNo;*/

void/*tuple_f_IDNo*/ f_IDNo( uint16_t integer_TID, uint16_t integer_SID ) // generation I trainer ID number (TID): 0 <= i_TID <= 2**16 - 1; generation III secret ID number (SID): 0 <= i_SID <= 2**16 - 1;
{
	//tuple_f_IDNo tuple_IDNo;                                              // ( i_TID, i_SID, i_TSV, i_TRV, i_G7TID, i_G7SID )
	int16_t integer_G7SID;                                                // generation VII secret ID number (G7SID): 0 <= i_G7SID <= 4294, i_G7SID = floor( n / 10**( l_max - 6 ) )
	uint8_t length_G7SID;                                                 // G7SID length: l_G7SID = l_max - l_G7TID == 4
	uint8_t length_G7TID;                                                 // G7TID length: l_G7TID = 6 == l_max - l_G7SID
	uint8_t length_maximum;                                               // 32-bit unsigned maximum value length: for r = 10, l_max = floor( r - log_r( i_max ) + 1 ) == 10
	uint32_t maximum_32bitunsigned;                                       // 32-bit unsigned maximum value: 2**32 - 1 == 4294967295
	int8_t base /*radix*/;                                                // positional numeral system: decimal system ( radix = 10 )
	int32_t integer_G7TID;                                                // generation VII trainer ID number (G7TID): 0 <= i_G7TID <= 999999, i_G7TID = i_G7ID % 10**6
	int32_t million;                                                      // 'mask': 10**6 == 1000000
	uint32_t integer_IDNo;                                                // generation VII ID number (G7ID, 'IDNo'): 0 <= i_IDNo <= 2**32 - 1 == 4294967295, i_G7ID = i_TID + ( 2**16 * i_SID )
	uint8_t integer_TRV;                                                  // trainer residual value (TRV): 0 <= i_TRV <= ( min( 0x0, 0xFFFF ) ^ max( 0x0, 0xFFFF ) ) & 0xF == 15, i_TRV = ( i_TID ^ i_SID ) & 0xF
	uint16_t integer_TSV;                                                 // trainer shiny value (TSV): 0 <= i_TSV <= ( min( 0x0, 0xFFFF ) ^ max( 0x0, 0xFFFF ) ) >> 4 == 4095, i_TSV = ( i_TID ^ i_SID ) >> 4
	uint16_t result;                                                      // i_TID ^ i_SID

	result = integer_TID ^ integer_SID;
	integer_TSV = (uint16_t) ( ( result ) >> 4 );
	integer_TRV = (uint8_t) ( ( result ) & 0xF );
	integer_IDNo = (uint32_t) ( integer_TID + ( pow( 2, 16 ) * integer_SID ) );
	million = (int32_t) pow( 10, 6 );
	integer_G7TID = (int32_t) ( integer_IDNo % million );
	base = (int8_t) 10;
	maximum_32bitunsigned = (uint32_t) ( pow( 2, 32 ) - 1 );
	length_maximum = nbrlen( maximum_32bitunsigned, base );
	length_G7TID = (uint8_t) 6;
	length_G7SID = (uint8_t) length_maximum - length_G7TID;
	integer_G7SID = (int16_t) ( floor( (double) integer_IDNo / pow( 10, ( length_maximum - length_G7SID ) ) ) );
	printf("TID:\t%i\nSID:\t%i\nTSV:\t%i\nTRV:\t%i\nG7SID:\t%i\nG7TID:\t%hi\n", integer_TID, integer_SID, integer_TSV, integer_TRV, integer_G7SID, integer_G7TID );

	//return tuple_IDNo;
}

/*//	f_IDNo.c
////	G7ID Calculator
////
////	Karl V. P. B. `kvpb` AKA Karl Thomas George West `ktgw`
////	+1 (DDD) DDD-DDDD
////	+33 A BB BB BB BB
////	local-part@domain
////	local-part@domain
////	https://www.linkedin.com/in//
////	https://twitter.com/ktgwkvpb
////	https://github.com/kvpb
*///	https://vm.tiktok.com/ZSwAmcFh/
