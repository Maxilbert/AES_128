/*/////////////////////////////////////////////////////////

Program Title: AES_128
Purpose: To demonstrate AES 128-bit encryption
Author: MIDN 2/C Bryan Harvey

*note: This program reflects the encryption and decryption 
starting at the bottom of page 35 of the PDF that can be found at:
csrc.nist.gov/publications/fips/fips197/fips-197.pdf

Resources Used for Research:
http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf
http://www.samiam.org/galois.html
http://www.samiam.org/mix-column.html
http://www.infosecwriters.com/Papers/ABerent_AESbyExample.pdf
http://comp.ist.utl.pt/ec-csc/Code/Ciphers/AES_Encrypt.cpp
http://www.moserware.com/2009/09/stick-figure-guide-to-advanced.html
*//////////////////////////////////////////////////////////

#include <iostream> 
using namespace std;

void display(int n[4][4]);
void input_to_state(int in[4][4], int st[4][4]);
void create_next_round_key(int prev[4][4], int next [4][4], int rcon);
void add_round_key(int st[4][4], int key[4][4]);
void sub_bytes(int bytes[4][4]);
void inv_sub_bytes(int bytes[4][4]);
void sub_word(int word[4]);
void shift_rows(int bytes[4][4]);
void inv_shift_rows(int bytes[4][4]);
int gal_mul(int x, int y);
void mix_column(int word[4]);
void inv_mix_column(int word[4]);
void mix_bytes_columns(int bytes[4][4]);
void inv_mix_bytes_columns(int bytes[4][4]);

int main() 
{
	int key[4][4] = 
	{
		{0x00, 0x04, 0x08, 0x0c},
    {0x01, 0x05, 0x09, 0x0d},
    {0x02, 0x06, 0x0a, 0x0e},
    {0x03, 0x07, 0x0b, 0x0f}
	};
	
	int input[4][4] = 
  {
      {0x00, 0x44, 0x88, 0xcc},
      {0x11, 0x55, 0x99, 0xdd},
      {0x22, 0x66, 0xaa, 0xee},
      {0x33, 0x77, 0xbb, 0xff}
  };
  
  int rcon[11] = {0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};
  
  int state[4][4];
  int rkey1[4][4], rkey2[4][4], rkey3[4][4], rkey4[4][4], rkey5[4][4], rkey6[4][4];
  int rkey7[4][4], rkey8[4][4], rkey9[4][4], rkey10[4][4];
  
  //////////////////////////////////////////////////////////////////////
  
  cout << "Input:" << endl;
  display(input);
  
  cout << "Key:" << endl;
  display(key);
  
  input_to_state(input, state);
  cout << "State:" << endl;
  display(state);
  
  add_round_key(state, key);
  
  //Create Round Keys for entire encryption
  create_next_round_key(key, rkey1, rcon[1]);
  create_next_round_key(rkey1, rkey2, rcon[2]);
  create_next_round_key(rkey2, rkey3, rcon[3]);
  create_next_round_key(rkey3, rkey4, rcon[4]);
  create_next_round_key(rkey4, rkey5, rcon[5]);
  create_next_round_key(rkey5, rkey6, rcon[6]);
  create_next_round_key(rkey6, rkey7, rcon[7]);
  create_next_round_key(rkey7, rkey8, rcon[8]);
  create_next_round_key(rkey8, rkey9, rcon[9]);
  create_next_round_key(rkey9, rkey10, rcon[10]);

	cout << "Start of round 1" << endl;
	display(state);
	sub_bytes(state);
	shift_rows(state);
	mix_bytes_columns(state);
	add_round_key(state, rkey1);

	cout << "Start of round 2" << endl;
	display(state);
	sub_bytes(state);
	shift_rows(state);
	mix_bytes_columns(state);
	add_round_key(state, rkey2);

	cout << "Start of round 3" << endl;
	display(state);
	sub_bytes(state);
	shift_rows(state);
	mix_bytes_columns(state);
	add_round_key(state, rkey3);
	
	cout << "Start of round 4" << endl;
	display(state);
	sub_bytes(state);
	shift_rows(state);
	mix_bytes_columns(state);
	add_round_key(state, rkey4);

	cout << "Start of round 5" << endl;
	display(state);
	sub_bytes(state);
	shift_rows(state);
	mix_bytes_columns(state);
	add_round_key(state, rkey5);

	cout << "Start of round 6" << endl;
	display(state);
	sub_bytes(state);
	shift_rows(state);
	mix_bytes_columns(state);
	add_round_key(state, rkey6);

	cout << "Start of round 7" << endl;
	display(state);
	sub_bytes(state);
	shift_rows(state);
	mix_bytes_columns(state);
	add_round_key(state, rkey7);

	cout << "Start of round 8" << endl;
	display(state);
	sub_bytes(state);
	shift_rows(state);
	mix_bytes_columns(state);
	add_round_key(state, rkey8);
	
	cout << "Start of round 9" << endl;
	display(state);
	sub_bytes(state);
	shift_rows(state);
	mix_bytes_columns(state);
	add_round_key(state, rkey9);
	
	cout << "Start of round 10" << endl;
	display(state);
	sub_bytes(state);
	shift_rows(state);
	add_round_key(state, rkey10);

	cout << "Final Output" << endl;
	display(state);
	display(state);
	
	cout << "Begin Decryption!" << endl;
	add_round_key(state, rkey10);
	
	cout << "Begin Round 1!" << endl;
	display(state);
	inv_shift_rows(state);
	inv_sub_bytes(state);
	add_round_key(state, rkey9);
	inv_mix_bytes_columns(state);
	
	cout << "Begin Round 2!" << endl;
	display(state);
	inv_shift_rows(state);
	inv_sub_bytes(state);
	add_round_key(state, rkey8);
	inv_mix_bytes_columns(state);
	
	cout << "Begin Round 3!" << endl;
	display(state);
	inv_shift_rows(state);
	inv_sub_bytes(state);
	add_round_key(state, rkey7);
	inv_mix_bytes_columns(state);
	
	cout << "Begin Round 4!" << endl;
	display(state);
	inv_shift_rows(state);
	inv_sub_bytes(state);
	add_round_key(state, rkey6);
	inv_mix_bytes_columns(state);
	
	cout << "Begin Round 5!" << endl;
	display(state);
	inv_shift_rows(state);
	inv_sub_bytes(state);
	add_round_key(state, rkey5);
	inv_mix_bytes_columns(state);
	
	cout << "Begin Round 6!" << endl;
	display(state);
	inv_shift_rows(state);
	inv_sub_bytes(state);
	add_round_key(state, rkey4);
	inv_mix_bytes_columns(state);
	
	cout << "Begin Round 7!" << endl;
	display(state);
	inv_shift_rows(state);
	inv_sub_bytes(state);
	add_round_key(state, rkey3);
	inv_mix_bytes_columns(state);
	
	cout << "Begin Round 8!" << endl;
	display(state);
	inv_shift_rows(state);
	inv_sub_bytes(state);
	add_round_key(state, rkey2);
	inv_mix_bytes_columns(state);
	
	cout << "Begin Round 9!" << endl;
	display(state);
	inv_shift_rows(state);
	inv_sub_bytes(state);
	add_round_key(state, rkey1);
	inv_mix_bytes_columns(state);
	
	cout << "Begin Round 10!" << endl;
	display(state);
	inv_shift_rows(state);
	inv_sub_bytes(state);
	add_round_key(state, key);
	
	cout << "Final output!" << endl;
	display(state);
	
  return 0;
}

void display(int n[4][4]) 
{
	cout << endl;
	for(int i = 0;  i < 4; ++ i) 
	{
		for(int j = 0; j < 4; ++j) 
		{
			if (n[i][j] == 0)
			{
				cout << "00\t";
			}
			
			else if (n[i][j] < 16)
			{
				cout << '0' << hex << n[i][j] << "\t";
			}
			
			else
			{
				cout<< hex << n[i][j] << "\t";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void input_to_state(int in[4][4], int st[4][4])
{
	for (int row = 0; row < 4; row++)
  {
  	for (int col = 0; col < 4; col++)
  	{
			st[row][col] = in[row][col];
  	}
  }
}

void add_round_key(int st[4][4], int key[4][4])
{
	//Goes byte by byte and xors all of the bits
	//and saves it in the state
	for (int row = 0; row < 4; row++)
  {
  	for (int col = 0; col < 4; col++)
  	{
			st[row][col] = st[row][col] ^ key[row][col];
  	}
  }
}

void create_next_round_key(int prev[4][4], int next [4][4], int rcon)
{
	//Declare the words used for previous and next round keys
	int w0[4], w1[4], w2[4], w3[4];
	int w4[4], w5[4], w6[4], w7[4];
	
	//Fill in words for previous
	for (int i = 0; i < 4; i++)
	{
		w0[i] = prev[i][0];
	}
	
	for (int i = 0; i < 4; i++)
	{
		w1[i] = prev[i][1];
	}
	
	for (int i = 0; i < 4; i++)
	{
		w2[i] = prev[i][2];
	}
	
	for (int i = 0; i < 4; i++)
	{
		w3[i] = prev[i][3];
	}
	
	//Take last column of previous round and move the top byte to the bottom
	w4[0] = w3[1];
	w4[1] = w3[2];
	w4[2] = w3[3];
	w4[3] = w3[0];
	
	//Run that column through sub_word
	sub_word(w4);
	
	//XOR column with round constant
	w4[0] = w4[0] ^ rcon;
	
	//XOR column with first column of previous round
	for (int i = 0; i < 4; i++)
	{
		w4[i] = w4[i] ^ w0[i];
	}
	
	//For the rest (3) of the columns, just xor the previous column with same
	//column of the previous round key
	
	//For w5
	for (int i = 0; i < 4; i++)
	{
		w5[i] = w4[i] ^ w1[i];
	}
	//For w6
	for (int i = 0; i < 4; i++)
	{
		w6[i] = w5[i] ^ w2[i];
	}
	//For w7
	for (int i = 0; i < 4; i++)
	{
		w7[i] = w6[i] ^ w3[i];
	}
	
	//Fill in words for next
	for (int i = 0; i < 4; i++)
	{
		next[i][0] = w4[i];
	}
	
	for (int i = 0; i < 4; i++)
	{
		next[i][1] = w5[i]; 
	}
	
	for (int i = 0; i < 4; i++)
	{
		next[i][2] = w6[i];
	}
	
	for (int i = 0; i < 4; i++)
	{
		next[i][3] = w7[i];
	}
}

void sub_bytes(int bytes[4][4])
{
	//Create sbox
	int sbox[16][16] = 
	{
		{0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76},
		{0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0},
		{0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15},
		{0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75},
		{0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84},
		{0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf},
		{0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8},
		{0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2},
		{0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73},
		{0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb},
		{0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79},
		{0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08},
		{0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a},
		{0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e},
		{0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf},
		{0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16}
	};
	
	//Replace each byte in block with sbox value
	for (int row = 0; row < 4; row++)
  {
  	for (int col = 0; col < 4; col++)
  	{
			int byte_value = bytes[row][col];
			int sbox_row = byte_value/16;
			int sbox_col = byte_value - (sbox_row*16);
			bytes[row][col] = sbox[sbox_row][sbox_col];
  	}
  }
}

void inv_sub_bytes(int bytes[4][4])
{
	int inv_sbox[16][16] =
	{
		{0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb},
		{0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb},
		{0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e},
		{0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25},
		{0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92},
		{0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84},
		{0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06},
		{0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b},
		{0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73},
		{0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e},
		{0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b},
		{0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4},
		{0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f},
		{0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef},
		{0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61},
		{0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d}
	};
	
	//Replace each byte in block with inv_sbox value
	for (int row = 0; row < 4; row++)
  {
  	for (int col = 0; col < 4; col++)
  	{
			int byte_value = bytes[row][col];
			int inv_sbox_row = byte_value/16;
			int inv_sbox_col = byte_value - (inv_sbox_row*16);
			bytes[row][col] = inv_sbox[inv_sbox_row][inv_sbox_col];
  	}
  }
}

void sub_word(int word[4])
{
	//Create sbox
	int sbox[16][16] = 
	{
		{0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76},
		{0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0},
		{0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15},
		{0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75},
		{0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84},
		{0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf},
		{0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8},
		{0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2},
		{0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73},
		{0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb},
		{0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79},
		{0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08},
		{0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a},
		{0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e},
		{0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf},
		{0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16}
	};
	
	//Replace each byte in block with sbox value
	for (int i = 0; i < 4; i++)
	{
		int byte_value = word[i];
		int sbox_row = byte_value/16;
		int sbox_col = byte_value - (sbox_row*16);
		word[i] = sbox[sbox_row][sbox_col];
	}
}

void shift_rows(int bytes[4][4])
{
	//Make copy of bytes
	int temp[4][4];
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			temp[row][col] = bytes[row][col];
		}
	}
	//Top row no shift
	//2nd row shift bytes left by 1
	bytes[1][0] = temp[1][1];
	bytes[1][1] = temp[1][2];
	bytes[1][2] = temp[1][3];
	bytes[1][3] = temp[1][0];
	
	//3rd row shift bytes left by 2
	bytes[2][0] = temp[2][2];
	bytes[2][1] = temp[2][3];
	bytes[2][2] = temp[2][0];
	bytes[2][3] = temp[2][1];
	
	//4th row shift bytes left by 3
	bytes[3][0] = temp[3][3];
	bytes[3][1] = temp[3][0];
	bytes[3][2] = temp[3][1];
	bytes[3][3] = temp[3][2];
}

void inv_shift_rows(int bytes[4][4])
{
	//Make copy of bytes
	int temp[4][4];
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			temp[row][col] = bytes[row][col];
		}
	}
	
	//2nd row shift bytes right by 1
	bytes[1][0] = temp[1][3];
	bytes[1][1] = temp[1][0];
	bytes[1][2] = temp[1][1];
	bytes[1][3] = temp[1][2];
	
	//3rd row shift bytes right by 2
	bytes[2][0] = temp[2][2];
	bytes[2][1] = temp[2][3];
	bytes[2][2] = temp[2][0];
	bytes[2][3] = temp[2][1];
	
	//4th row shift bytes right by 3
	bytes[3][0] = temp[3][1];
	bytes[3][1] = temp[3][2];
	bytes[3][2] = temp[3][3];
	bytes[3][3] = temp[3][0];
}

int gal_mul(int x, int y)
{
	if ((x == 0) || (y == 0))
	{
		return 0;
	}
	
	int log_table[16][16] = 
	{
		{0x00,0x00,0xc8,0x08,0x91,0x10,0xd0,0x36,0x5a,0x3e,0xd8,0x43,0x99,0x77,0xfe,0x18},
		{0x23,0x20,0x07,0x70,0xa1,0x6c,0x0c,0x7f,0x62,0x8b,0x40,0x46,0xc7,0x4b,0xe0,0x0e},
		{0xeb,0x16,0xe8,0xad,0xcf,0xcd,0x39,0x53,0x6a,0x27,0x35,0x93,0xd4,0x4e,0x48,0xc3},
		{0x2b,0x79,0x54,0x28,0x09,0x78,0x0f,0x21,0x90,0x87,0x14,0x2a,0xa9,0x9c,0xd6,0x74},
		{0xb4,0x7c,0xde,0xed,0xb1,0x86,0x76,0xa4,0x98,0xe2,0x96,0x8f,0x02,0x32,0x1c,0xc1},
		{0x33,0xee,0xef,0x81,0xfd,0x30,0x5c,0x13,0x9d,0x29,0x17,0xc4,0x11,0x44,0x8c,0x80},
		{0xf3,0x73,0x42,0x1e,0x1d,0xb5,0xf0,0x12,0xd1,0x5b,0x41,0xa2,0xd7,0x2c,0xe9,0xd5},
		{0x59,0xcb,0x50,0xa8,0xdc,0xfc,0xf2,0x56,0x72,0xa6,0x65,0x2f,0x9f,0x9b,0x3d,0xba},
		{0x7d,0xc2,0x45,0x82,0xa7,0x57,0xb6,0xa3,0x7a,0x75,0x4f,0xae,0x3f,0x37,0x6d,0x47},
		{0x61,0xbe,0xab,0xd3,0x5f,0xb0,0x58,0xaf,0xca,0x5e,0xfa,0x85,0xe4,0x4d,0x8a,0x05},
		{0xfb,0x60,0xb7,0x7b,0xb8,0x26,0x4a,0x67,0xc6,0x1a,0xf8,0x69,0x25,0xb3,0xdb,0xbd},
		{0x66,0xdd,0xf1,0xd2,0xdf,0x03,0x8d,0x34,0xd9,0x92,0x0d,0x63,0x55,0xaa,0x49,0xec},
		{0xbc,0x95,0x3c,0x84,0x0b,0xf5,0xe6,0xe7,0xe5,0xac,0x7e,0x6e,0xb9,0xf9,0xda,0x8e},
		{0x9a,0xc9,0x24,0xe1,0x0a,0x15,0x6b,0x3a,0xa0,0x51,0xf4,0xea,0xb2,0x97,0x9e,0x5d},
		{0x22,0x88,0x94,0xce,0x19,0x01,0x71,0x4c,0xa5,0xe3,0xc5,0x31,0xbb,0xcc,0x1f,0x2d},
		{0x3b,0x52,0x6f,0xf6,0x2e,0x89,0xf7,0xc0,0x68,0x1b,0x64,0x04,0x06,0xbf,0x83,0x38},
	};

	int exp_table[16][16] = 
	{
		{0x01,0xe5,0x4c,0xb5,0xfb,0x9f,0xfc,0x12,0x03,0x34,0xd4,0xc4,0x16,0xba,0x1f,0x36},
		{0x05,0x5c,0x67,0x57,0x3a,0xd5,0x21,0x5a,0x0f,0xe4,0xa9,0xf9,0x4e,0x64,0x63,0xee},
		{0x11,0x37,0xe0,0x10,0xd2,0xac,0xa5,0x29,0x33,0x59,0x3b,0x30,0x6d,0xef,0xf4,0x7b},
		{0x55,0xeb,0x4d,0x50,0xb7,0x2a,0x07,0x8d,0xff,0x26,0xd7,0xf0,0xc2,0x7e,0x09,0x8c},
		{0x1a,0x6a,0x62,0x0b,0x5d,0x82,0x1b,0x8f,0x2e,0xbe,0xa6,0x1d,0xe7,0x9d,0x2d,0x8a},
		{0x72,0xd9,0xf1,0x27,0x32,0xbc,0x77,0x85,0x96,0x70,0x08,0x69,0x56,0xdf,0x99,0x94},
		{0xa1,0x90,0x18,0xbb,0xfa,0x7a,0xb0,0xa7,0xf8,0xab,0x28,0xd6,0x15,0x8e,0xcb,0xf2},
		{0x13,0xe6,0x78,0x61,0x3f,0x89,0x46,0x0d,0x35,0x31,0x88,0xa3,0x41,0x80,0xca,0x17},
		{0x5f,0x53,0x83,0xfe,0xc3,0x9b,0x45,0x39,0xe1,0xf5,0x9e,0x19,0x5e,0xb6,0xcf,0x4b},
		{0x38,0x04,0xb9,0x2b,0xe2,0xc1,0x4a,0xdd,0x48,0x0c,0xd0,0x7d,0x3d,0x58,0xde,0x7c},
		{0xd8,0x14,0x6b,0x87,0x47,0xe8,0x79,0x84,0x73,0x3c,0xbd,0x92,0xc9,0x23,0x8b,0x97},
		{0x95,0x44,0xdc,0xad,0x40,0x65,0x86,0xa2,0xa4,0xcc,0x7f,0xec,0xc0,0xaf,0x91,0xfd},
		{0xf7,0x4f,0x81,0x2f,0x5b,0xea,0xa8,0x1c,0x02,0xd1,0x98,0x71,0xed,0x25,0xe3,0x24},
		{0x06,0x68,0xb3,0x93,0x2c,0x6f,0x3e,0x6c,0x0a,0xb8,0xce,0xae,0x74,0xb1,0x42,0xb4},
		{0x1e,0xd3,0x49,0xe9,0x9c,0xc8,0xc6,0xc7,0x22,0x6e,0xdb,0x20,0xbf,0x43,0x51,0x52},
		{0x66,0xb2,0x76,0x60,0xda,0xc5,0xf3,0xf6,0xaa,0xcd,0x9a,0xa0,0x75,0x54,0x0e,0x01}
	};

	//Get row and col for log table
	int x_row = x/16;
	int x_col = x - (x_row*16);
	int x_log = log_table[x_row][x_col];
	int y_row = y/16;
	int y_col = y - (y_row*16);
	int y_log = log_table[y_row][y_col];
	
	int exp_value = (x_log + y_log) % 255;
	
	int exp_row = exp_value/16;
	int exp_col = exp_value - (exp_row*16);
	return exp_table[exp_row][exp_col];
}

void mix_column(int word[4])
{
	int copy[4];
	
	for (int i = 0; i < 4; i++)
	{
		copy[i] = word[i];
	}
	
	word[0] = gal_mul(copy[0],2) ^ gal_mul(copy[3],1) ^ gal_mul(copy[2],1) ^ gal_mul(copy[1],3);
	word[1] = gal_mul(copy[1],2) ^ gal_mul(copy[0],1) ^ gal_mul(copy[3],1) ^ gal_mul(copy[2],3);
	word[2] = gal_mul(copy[2],2) ^ gal_mul(copy[1],1) ^ gal_mul(copy[0],1) ^ gal_mul(copy[3],3);
	word[3] = gal_mul(copy[3],2) ^ gal_mul(copy[2],1) ^ gal_mul(copy[1],1) ^ gal_mul(copy[0],3);
}

void inv_mix_column(int word[4])
{
	int copy[4];
	
	for (int i = 0; i < 4; i++)
	{
		copy[i] = word[i];
	}
	
	word[0] = gal_mul(copy[0],14) ^ gal_mul(copy[3],9) ^ gal_mul(copy[2],13) ^ gal_mul(copy[1],11);
	word[1] = gal_mul(copy[1],14) ^ gal_mul(copy[0],9) ^ gal_mul(copy[3],13) ^ gal_mul(copy[2],11);
	word[2] = gal_mul(copy[2],14) ^ gal_mul(copy[1],9) ^ gal_mul(copy[0],13) ^ gal_mul(copy[3],11);
	word[3] = gal_mul(copy[3],14) ^ gal_mul(copy[2],9) ^ gal_mul(copy[1],13) ^ gal_mul(copy[0],11);
}

void mix_bytes_columns(int bytes[4][4])
{
	int w0[4], w1[4], w2[4], w3[4];

	//Fill in words for previous
	for (int i = 0; i < 4; i++)
	{
		w0[i] = bytes[i][0];
	}
	
	for (int i = 0; i < 4; i++)
	{
		w1[i] = bytes[i][1];
	}
	
	for (int i = 0; i < 4; i++)
	{
		w2[i] = bytes[i][2];
	}
	
	for (int i = 0; i < 4; i++)
	{
		w3[i] = bytes[i][3];
	}
	
	//Do Mix column operations
	mix_column(w0);
	mix_column(w1);
	mix_column(w2);
	mix_column(w3);
	
	//Put values back into bytes
	//Fill in words for previous
	for (int i = 0; i < 4; i++)
	{
		bytes[i][0] = w0[i];
	}
	
	for (int i = 0; i < 4; i++)
	{
		bytes[i][1] = w1[i];
	}
	
	for (int i = 0; i < 4; i++)
	{
		bytes[i][2] = w2[i];
	}
	
	for (int i = 0; i < 4; i++)
	{
		bytes[i][3] = w3[i];
	}
}

void inv_mix_bytes_columns(int bytes[4][4])
{
	int w0[4], w1[4], w2[4], w3[4];

	//Fill in words for previous
	for (int i = 0; i < 4; i++)
	{
		w0[i] = bytes[i][0];
	}
	
	for (int i = 0; i < 4; i++)
	{
		w1[i] = bytes[i][1];
	}
	
	for (int i = 0; i < 4; i++)
	{
		w2[i] = bytes[i][2];
	}
	
	for (int i = 0; i < 4; i++)
	{
		w3[i] = bytes[i][3];
	}
	
	//Do Mix column operations
	inv_mix_column(w0);
	inv_mix_column(w1);
	inv_mix_column(w2);
	inv_mix_column(w3);
	
	//Put values back into bytes
	//Fill in words for previous
	for (int i = 0; i < 4; i++)
	{
		bytes[i][0] = w0[i];
	}
	
	for (int i = 0; i < 4; i++)
	{
		bytes[i][1] = w1[i];
	}
	
	for (int i = 0; i < 4; i++)
	{
		bytes[i][2] = w2[i];
	}
	
	for (int i = 0; i < 4; i++)
	{
		bytes[i][3] = w3[i];
	}
}
