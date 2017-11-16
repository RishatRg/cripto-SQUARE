#pragma once
#ifndef SQUARE_h
#define SQUARE_h

#include<fstream>
#include<iostream>
#include <string>
#include "BigIntegerLibrary.hh" //// длинная арифметика ( используем для ЭЦП)
#include <algorithm>
#include <cmath>
#include<ctime>
using namespace std;
typedef unsigned char byte;
#define  N 4
class square
{
protected:
	//////////////// для шифрования//////////////// 
	const byte S[256] =
	{
		0xB1,	0xCE,	0xC3,	0x95,	0x5A,	0xAD,	0xE7,	0x02,	0x4D,	0x44,	0xFB,	0x91,	0x0C,	0x87,	0xA1,	0x50,
		0xCB,	0x67,	0x54,	0xDD,	0x46,	0x8F,	0xE1,	0x4E,	0xF0,	0xFD,	0xFC,	0xEB,	0xF9,	0xC4,	0x1A,	0x6E,
		0x5E,	0xF5,	0xCC,	0x8D,	0x1C,	0x56,	0x43,	0xFE,	0x07,	0x61,	0xF8,	0x75,	0x59,	0xFF,	0x03,	0x22,
		0x8A,	0xD1,	0x13,	0xEE,	0x88,	0x00,	0x0E,	0x34,	0x15,	0x80,	0x94,	0xE3,	0xED,	0xB5,	0x53,	0x23,
		0x4B,	0x47,	0x17,	0xA7,	0x90,	0x35,	0xAB,	0xD8,	0xB8,	0xDF,	0x4F,	0x57,	0x9A,	0x92,	0xDB,	0x1B,
		0x3C,	0xC8,	0x99,	0x04,	0x8E,	0xE0,	0xD7,	0x7D,	0x85,	0xBB,	0x40,	0x2C,	0x3A,	0x45,	0xF1,	0x42,
		0x65,	0x20,	0x41,	0x18,	0x72,	0x25,	0x93,	0x70,	0x36,	0x05,	0xF2,	0x0B,	0xA3,	0x79,	0xEC,	0x08,
		0x27,	0x31,	0x32,	0xB6,	0x7C,	0xB0,	0x0A,	0x73,	0x5B,	0x7B,	0xB7,	0x81,	0xD2,	0x0D,	0x6A,	0x26,
		0x9E,	0x58,	0x9C,	0x83,	0x74,	0xB3,	0xAC,	0x30,	0x7A,	0x69,	0x77,	0x0F,	0xAE,	0x21,	0xDE,	0xD0,
		0x2E,	0x97,	0x10,	0xA4,	0x98,	0xA8,	0xD4,	0x68,	0x2D,	0x62,	0x29,	0x6D,	0x16,	0x49,	0x76,	0xC7,
		0xE8,	0xC1,	0x96,	0x37,	0xE5,	0xCA,	0xF4,	0xE9,	0x63,	0x12,	0xC2,	0xA6,	0x14,	0xBC,	0xD3,	0x28,
		0xAF,	0x2F,	0xE6,	0x24,	0x52,	0xC6,	0xA0,	0x09,	0xBD,	0x8C,	0xCF,	0x5D,	0x11,	0x5F,	0x01,	0xC5,
		0x9F,	0x3D,	0xA2,	0x9B,	0xC9,	0x3B,	0xBE,	0x51,	0x19,	0x1F,	0x3F,	0x5C,	0xB2,	0xEF,	0x4A,	0xCD,
		0xBF,	0xBA,	0x6F,	0x64,	0xD9,	0xF3,	0x3E,	0xB4,	0xAA,	0xDC,	0xD5,	0x06,	0xC0,	0x7E,	0xF6,	0x66,
		0x6C,	0x84,	0x71,	0x38,	0xB9,	0x1D,	0x7F,	0x9D,	0x48,	0x8B,	0x2A,	0xDA,	0xA5,	0x33,	0x82,	0x39,
		0xD6,	0x78,	0x86,	0xFA,	0xE4,	0x2B,	0xA9,	0x1E,	0x89,	0x60,	0x6B,	0xEA,	0x55,	0x4C,	0xF7,	0xE2,
	};
	const byte C[N][N] =
	{
		0x02, 0x03, 0x01, 0x01,
		0x01, 0x02, 0x03, 0x01,
		0x01, 0x01, 0x02, 0x03,
		0x03, 0x01, 0x01, 0x02,
	};
	const byte C_1[N][N] =
	{
		0x0e, 0x0b, 0x0d, 0x09,
		0x09, 0x0e, 0x0b, 0x0d,
		0x0d, 0x09, 0x0e, 0x0b,
		0x0b, 0x0d, 0x09, 0x0e,
	};
	byte Ck[8][4] =
	{
		0x00,0x00,0x00,power256(0x02,1),
		0x00,0x00,0x00,power256(0x02,2),
		0x00,0x00,0x00,power256(0x02,3),
		0x00,0x00,0x00,power256(0x02,4),
		0x00,0x00,0x00,power256(0x02,5),
		0x00,0x00,0x00,power256(0x02,6),
		0x00,0x00,0x00,power256(0x02,7),
		0x00,0x00,0x00,power256(0x02,8),
	};
	int blocks;			//// количество блоков сообщения 
	long size;			//// размер исходного сообщения без корректировки 
	long size1;			//// размер исходного сообщения после корректировки 
	byte*Bdata;			//// указатель на массив данных  кратный  блоку шифрования (32 бит) 
	byte S_1[256];		//// обратная подстановка 
	void S_1_create()
	{
		int i;
		byte T[256];
		for (i = 0; i < 256; i++)
		{
			byte y = S[i];
			T[(int)y] = i;
		}
		for (i = 0; i < 256; i++)
			S_1[i] = T[i];
	}
	byte key[N][N];

	byte**data;
	byte k0[N][N], round_key1[N][N], round_key2[N][N],
		round_key3[N][N], round_key4[N][N],
		round_key5[N][N], round_key6[N][N],
		round_key7[N][N], round_key8[N][N];
	byte k0_1[N][N], round_key1_1[N][N], round_key2_1[N][N],
		round_key3_1[N][N], round_key4_1[N][N],
		round_key5_1[N][N], round_key6_1[N][N],
		round_key7_1[N][N], round_key8_1[N][N];

	////////////// даннные для хеша////////////// 
	byte h0[N][N];		 //// хеш
	byte h[N][N];		 //// дополнительный массив ( используется при нахождении хеша)
	byte keyhesh[N][N];  //// ключ 
	///////// данные для ЭЦП///////

	BigUnsigned x;

public:
	BigUnsigned p;		//// большое простое число 
	BigUnsigned q;		//// большое простое число делитель р-1
	BigUnsigned g;
	BigUnsigned y;
	BigUnsigned r;		//// первая часть подписи 
	BigUnsigned s;		//// вторая часть подписи 
	BigUnsigned ro;
	BigUnsigned h1;		//// представление хеша в BigUnsigned

	///// режим шифрования /////////

	byte *database;		//// расширенный массив данных 
	int SIZE;			//// размер данных  ( сообщение+хеш+ЭЦП )
	byte**C0;			//// синхропосылка


	void Bdata_create(ifstream&in);									//// создаем массив с данными кратный  блоку шифрования (32 бит) 
	square(ifstream&in, ifstream&key1);								//// конструктор с параметром 

	void trans(byte**data);											//// транспонирование матрицы
	void tetta(byte**mat);											//// функция тетта 
	void tetta_1(byte**mat);										//// обратная функция к тетта 
	byte multiply256(byte a, byte b);								//// умножение в поле 256 
	byte power256(byte a, int m);									///// возведение в степень в поле 256
	void sigma(byte**data, byte round_key[N][N]);
	void gamma(byte**data);
	void gamma_1(byte**data);
	void tetta(byte mat[N][N]);
	void tetta_1(byte mat[N][N]);
	void encryption_block();										///// зашифрование блока (32 бит) 
	void encryption_block(byte**data1, byte key1[N][N]);
	void round_key_create();										//// вычисление раундовых ключей для зашифрования 
	void square::round_key_create(byte key1[N][N])
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				k0[i][j] = key1[i][j];

		for (int i = 1; i <= 8; i++)
			switch (i)
			{
			case 1:
				psi(k0, round_key1, 0);
				break;
			case 2:
				psi(round_key1, round_key2, 1);
				break;
			case 3:
				psi(round_key2, round_key3, 2);
				break;
			case 4:
				psi(round_key3, round_key4, 3);
				break;
			case 5:
				psi(round_key4, round_key5, 4);
				break;
			case 6:
				psi(round_key5, round_key6, 5);
				break;
			case 7:
				psi(round_key6, round_key7, 6);
				break;
			case 8:
				psi(round_key7, round_key8, 7);

				break;
			}

	}
	void round_key_create_1();										//// вычисление раундовых ключей для дешифрования 
	void psi(byte key_round1[N][N], byte key_round2[N][N],int k);	
	byte**rotl(byte round_key[N][N]);								//// Циклический сдвиг строки   на N позиций 	

	void decryption_block(byte**data1, byte key1[N][N]);			///// дешифрование блока (32 бит) 
	
	//// Хеш  ////////////
	void h_0();														//// Инициализация хеша
	void get_hesh();												//// Получить хеш
	void mult_matrix(byte a[N][N], byte b[N][N]);					//// Произведение матриц
	void swap_matrix(byte a[N][N], byte b[N][N]);					
	void swap_matrix(byte**a, byte b[N][N]);
	void swap_matrix(byte a[N][N], byte**b);
	void hesh_show(ofstream&);										//// записать хеш в файл 
	//// цифровая подпись /////
	byte* BigUnsignedToByteArray(BigUnsigned&R1,int arraySize)
	{
		byte *mass= new byte[arraySize];
		for (int i = 0; i <arraySize; i++)
		{
			string tmp;
			tmp = bigUnsignedToString(R1 % 256);
			byte x = (byte)stoi(tmp);
			R1 = R1 - (int)x;
			R1 /= 256;
			// cout << R1 << endl;
			mass[arraySize-1 - i] = x;
			// else R1 / 256;
		}
		return mass;
	}
	BigUnsigned ByteArrayToBigUnsigned(byte*mass, int arraySize)
	{
		BigUnsigned R1;
		for (int i = 0; i <arraySize; i++)
			if (i == 0)
				R1 = mass[i];
			else R1 = R1 * 256 + mass[i];
			return  R1;
	}
	void digit_sign();												//// вычисление ЭЦП
	void show_sign(ofstream&out);										//// вывод в файл ЭЦП
	void sign_check();				//// проверка подписи 

	//// Режим шифрования ////
	char cname_file[80];
	void create_database_for_encryption();									//// создается расширенный массив данных
	void create_database_for_decryption(ifstream&in);						//// ввод массивы данных через файл 
	void Encryption_mode(ifstream&in);									//// зашифрование текста в режиме 							
	void Decryption_mode(ifstream&in);									//// расшифрование теста 
	void database_show(ofstream&out);			            //// показать массив данных в файле 	
	string readFile( ifstream&f) 
	{
		
		f.seekg(0, ios::end);
		size_t size = f.tellg();
		string s(size, ' ');
		f.seekg(0);
		f.read(&s[0], size); 
		f.seekg(0);
		return s;
	}
};
	/////// Реализация шифра ///////////////
void square::Bdata_create(ifstream&in)
{
	//in.open("Text.bin", ios::binary);
		in.seekg(0, std::ios::end);
		size = in.tellg();	
		cout << size << endl;
		in.seekg(0);

		string sf(size, ' ');
		sf= readFile(in);
	//char*b = new char[size];
	//strncpy_s(b, size + 1, sf.c_str(), size);
	if (size % 16 > 0)
	{
		size1 = size + (16 - size % 16);
		Bdata = new byte[size1];
		for (int i = 0; i < size1; i++)
		{
			if (i < size)
				Bdata[i]=sf[i];
			else
			{
				if (i == size)
					Bdata[i] = 0x80;
				else
					Bdata[i] = 0x00;
			}
		}
	}
	else
	{
		size1 = size;
		Bdata = new byte[size1];
		for (int i = 0; i < size1; i++)
			Bdata[i]=sf[i];
	}
}
square::square(ifstream&in, ifstream&key1)
{
	S_1_create();
	data = new byte*[N];
	for (int i = 0; i < N; i++)
		data[i] = new byte[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			key1>>key[i][j];

	round_key_create();
	round_key_create_1();
	//// инициализация хеша////
		
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			keyhesh[i][j] = key[i][j];
	//// инициализация цифровой подписи ////
							///// вычисляем R и S
	//////// режим шифрования СВС
								
	C0 = new byte*[N];
	for (int i = 0; i < N; i++)
		C0[i] = new byte[N];
		
	for (int i = 0; i < N; i++)
		for (int j = 0; j<N; j++)
			C0[i][j] = 0x00;
}

void square::trans(byte**data)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			byte tmp;
			tmp = data[i][j];
			data[i][j] = data[j][i];
			data[j][i] = tmp;
		}
}
void square::sigma(byte**data, byte round_key[N][N])
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			data[i][j] ^= round_key[i][j];
}
void square::gamma(byte**data)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		data[i][j] = S[(int)data[i][j]];
		

}
void square::gamma_1(byte**data)
{
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			data[i][j] = S_1[(int)data[i][j]];
			
}

byte square::multiply256(byte a, byte b)
{
	byte p = 0;
	int counter;
	byte hi_bit_set;
	for (counter = 0; counter < 8; counter++) {
		if ((b & 1) == 1)
			p ^= a;
		hi_bit_set = (a & 0x80);
		a <<= 1;
		if (hi_bit_set == 0x80)
			a ^= 0x1b; /* x^8 + x^4 + x^3 + x + 1 */
		b >>= 1;
	}
	return p;
}
byte square::power256(byte a, int m)
{
	byte c = 0x01;
	while (m > 0)
	{
		if (m % 2 != 0)
			c = multiply256(c, a);
		a = multiply256(a, a);
		m = m / 2;
	}
	return c;
}
void square::tetta(byte**mat)
{

	byte tmp[N][N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			tmp[i][j] = 0;
			for (int k = 0; k < N; k++)
				tmp[i][j] ^= multiply256(C[i][k], mat[k][j]);
		}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			mat[i][j] = tmp[i][j];
}
void square::tetta_1(byte**mat)
{
	byte tmp[N][N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			tmp[i][j] = 0;
			for (int k = 0; k < N; k++)
				tmp[i][j] ^= multiply256(C_1[i][k], mat[k][j]);
		}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			mat[i][j] = tmp[i][j];
}
void square::encryption_block(byte**data1,byte key1[N][N])
{
	tetta_1(data1);
	sigma(data1, key1);
	for (int i = 1; i < 9; i++)
	{
		tetta(data1);
		gamma(data1);
		trans(data1);
		switch (i)
		{
		case 1:
			sigma(data1, round_key1);
			break;
		case 2:
			sigma(data1, round_key2);
			break;
		case 3:
			sigma(data1, round_key3);
			break;
		case 4:
			sigma(data1, round_key4);
			break;
		case 5:
			sigma(data1, round_key5);
			break;
		case 6:
			sigma(data1, round_key6);
			break;
		case 7:
			sigma(data1, round_key7);
			break;
		case 8:
			sigma(data1, round_key8);
			break;
		}
	}

}
void square::encryption_block()
{
	tetta_1(data);
	sigma(data, key);
	for (int i = 1; i < 9; i++)
	{
		tetta(data);
		gamma(data);
		trans(data);
		switch (i)
		{
		case 1:
			sigma(data, round_key1);
			break;
		case 2:
			sigma(data, round_key2);
			break;
		case 3:
			sigma(data, round_key3);
			break;
		case 4:
			sigma(data, round_key4);
			break;
		case 5:
			sigma(data, round_key5);
			break;
		case 6:
			sigma(data, round_key6);
			break;
		case 7:
			sigma(data, round_key7);
			break;
		case 8:
			sigma(data, round_key8);
			break;
		}
	}

}

void square::round_key_create()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			k0[i][j] = key[i][j];

	for (int i = 1; i <= 8; i++)
		switch (i)
		{
		case 1:
			psi(k0, round_key1, 0);
			break;
		case 2:
			psi(round_key1, round_key2, 1);
			break;
		case 3:
			psi(round_key2, round_key3, 2);
			break;
		case 4:
			psi(round_key3, round_key4, 3);
			break;
		case 5:
			psi(round_key4, round_key5, 4);
			break;
		case 6:
			psi(round_key5, round_key6, 5);
			break;
		case 7:
			psi(round_key6, round_key7, 6);
			break;
		case 8:
			psi(round_key7, round_key8, 7);

			break;
		}

}
void square::round_key_create_1()
{
	for (int i = 0; i <= 8; i++)
		switch (i)
	{
		case 0:
		{
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					k0_1[i][j] = k0[i][j];
			tetta(k0_1);
		}
		break;
		case 1:
		{
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
				round_key1_1[i][j] = round_key1[i][j];
			tetta(round_key1_1);
		}
			break;
		case 2:
		{
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					round_key2_1[i][j] = round_key2[i][j];
			tetta(round_key2_1);
		}
			break;
		case 3:
		{
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					round_key3_1[i][j] = round_key3[i][j];
			tetta(round_key3_1);
		}
			break;
		case 4:
		{
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					round_key4_1[i][j] = round_key4[i][j];
			tetta(round_key4_1);
		}
			break;
		case 5:
		{
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					round_key5_1[i][j] = round_key5[i][j];
			tetta(round_key5_1);
		}
			break;
		case 6:
		{
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					round_key6_1[i][j] = round_key6[i][j];
			tetta(round_key6_1);
		}
			break;
		case 7:
		{
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					round_key7_1[i][j] = round_key7[i][j];
			tetta(round_key7_1);
		}
			break;
		case 8:
		{
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					round_key8_1[i][j] = round_key8[i][j];
			tetta(round_key8_1);
		}
		break;
		
	}

}
byte**square::rotl(byte round_key[N][N])
{
	byte**mat = new byte*[N];
	for (int i = 0; i < N; i++)
		mat[i] = new byte[N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			mat[i][j] = round_key[i][j];
	byte tmp = mat[3][0];
	for (int i = 0; i < N - 1; i++)
		mat[3][i] = mat[3][i + 1];
	mat[3][N - 1] = tmp;
	return mat;
}
void square::psi(byte key_roud1[N][N], byte key_roud2[N][N], int k)
{
	byte**mat;
	mat = rotl(key_roud1);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == 0)
				key_roud2[i][j] = mat[i][j] ^ mat[3][j] ^ Ck[k][j];
			else
				key_roud2[i][j] = key_roud2[i - 1][j] ^ mat[i][j];
		}
	}
}
void square::decryption_block(byte**data1, byte key1[N][N])
{
	
	tetta(data1);
	sigma(data1, round_key8_1);
	for (int i = 7; i >= 0; i--)
	{
		switch (i)
		{
		case 0:

			tetta_1(data1);
			gamma_1(data1);
			trans(data1);
			sigma(data1, k0_1);
			break;
		case 1:

			tetta_1(data1);
			gamma_1(data1);
			trans(data1);
			sigma(data1, round_key1_1);
			break;
		case 2:

			tetta_1(data1);
			gamma_1(data1);
			trans(data1);
			sigma(data1, round_key2_1);
			break;
		case 3:

			tetta_1(data1);
			gamma_1(data1);
			trans(data1);
			sigma(data1, round_key3_1);
			break;
		case 4:

			tetta_1(data1);
			gamma_1(data1);
			trans(data1);
			sigma(data1, round_key4_1);
			break;
		case 5:

			tetta_1(data1);
			gamma_1(data1);
			trans(data1);
			sigma(data1, round_key5_1);
			break;
		case 6:

			tetta_1(data1);
			gamma_1(data1);
			trans(data1);
			sigma(data1, round_key6_1);
			break;
		case 7:
			tetta_1(data1);
			gamma_1(data1);
			trans(data1);
			sigma(data1, round_key7_1);
			break;
		}
	}
}

void square::tetta(byte mat[N][N])
{

	byte tmp[N][N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			tmp[i][j] = 0;
			for (int k = 0; k < N; k++)
				tmp[i][j] ^= multiply256(C[i][k], mat[k][j]);
		}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			mat[i][j] = tmp[i][j];
}
void square::tetta_1(byte mat[N][N])
{
	byte tmp[N][N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			tmp[i][j] = 0;
			for (int k = 0; k < N; k++)
				tmp[i][j] ^= multiply256(C_1[i][k], mat[k][j]);
		}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			mat[i][j] = tmp[i][j];
}
			/////// Хеш //////////
void square::h_0()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			h0[i][j] = 0x00;
			h[i][j] = 0x00;
		}
}
void square::get_hesh()
{
	int k = 0;
	int i = 0;
	blocks = size1 / 16;
	int count;
	h_0();
	for (count = 1; count <= blocks; count++)
	{

		for (int i = 0, j = k * 16; i < N *N, j < N*N*count; i++, j++)
		{
			data[i / N][i % N] = Bdata[j];
		}
		swap_matrix(h, h0);
		swap_matrix(keyhesh, data);
		round_key_create(keyhesh);
		swap_matrix(data, h0);
		encryption_block(data,keyhesh);
		swap_matrix(h0, data);
		mult_matrix(h0, h);
		k++;
	}
	
	round_key_create();
}
void square::swap_matrix(byte a[N][N], byte**b)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			a[i][j] = b[i][j];
		}
}
void  square::swap_matrix(byte**a, byte b[N][N])
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			byte tmp = a[i][j];
			a[i][j] = b[i][j];
			b[i][j] = tmp;
		}
}
void square::swap_matrix(byte a[N][N], byte b[N][N])
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			byte tmp = a[i][j];
			a[i][j] = b[i][j];
			b[i][j] = tmp;
		}
}
void square::mult_matrix(byte a[N][N], byte b[N][N])
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			a[i][j] ^= b[i][j];
}
void square::hesh_show(ofstream&out)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			out.write((char*)&h0[i][j],sizeof(byte));

}
	///////	Цифровая подпись ///////////////
void square::digit_sign()
{
	string p1 = "97553607833069877720851753590758150859523200990282982100522379573651322066419";
	p = stringToBigUnsigned(p1);
	

	string q1 = "286684287275266243736166399217868759773";
	q = stringToBigUnsigned(q1);

	srand(time(0));
	x = BigUnsigned(2 + 197); 

	g = modexp(265, ((p - 1) / q), p);

	y = modexp(g, x, p);

	get_hesh();

	BigUnsigned k;
	srand(time(0));
	k = BigUnsigned(1 + 197);

	r = modexp(g, k, p); 
	cout << " r=" << r << endl;

	string a = "";
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			a += h0[i][j];
	h1 = stringToBigUnsigned(a);
	ro = r%q;
	s = ((ro*k) % q) - ((h1*x) % q);
	cout << " s=" << s << endl;

}
void square::show_sign(ofstream&out)
{
	out.write((char*)&r, sizeof(r));
	out.write((char*)&s, sizeof(s));
}
void square::sign_check()
{
	byte *R32, *S16;
	R32 = new byte[32];
	S16 = new byte[16];

	for (int i = 0; i < 32; i++)
	{
		R32[i] = database[SIZE - 48 + i];
	}
	for (int i = 0; i < 16; i++)
	{
		S16[i] = database[SIZE - 16 + i];
	}
	BigUnsigned R1 = ByteArrayToBigUnsigned(R32, 32);
	BigUnsigned S1 = ByteArrayToBigUnsigned(S16, 16);

	cout << " R1=" << R1 << endl;
	cout << " S1=" << S1 << endl;

	if ((modexp(R1, ro, p)) == (modexp(g, S1, p)*(modexp(y, h1, p))) % p)
		 cout<<"text is original!";
	else  cout<<" text was corrected!";
}
	////// Режим шифрования //////////////
void square::create_database_for_encryption()
{
	SIZE = size1 + 16 + 32 + 16;
	database = new byte[SIZE];

	byte *Sn;
	Sn = BigUnsignedToByteArray(s, 16);
	

	byte*Rn;
	Rn = BigUnsignedToByteArray(r, 32);
	


	for (int i = 0; i < size1; i++)
	{
		database[i] = Bdata[i];
	}
	for (int i = size1, j = 0; i < (size1 + 16), j<16; i++, j++)
	{
		database[i] = h0[j / N][j % N];
	}
	for (int i = (size1 + 16), j = 0; i <(size1 + 48), j<32; i++, j++)
	{
		database[i] = Rn[j];
	}
	for (int i = (size1 + 48), j = 0; i < (size1 + 64), j<16; i++, j++)
	{
		database[i] = Sn[j];
	}



}
void square::create_database_for_decryption(ifstream&in)
{
	
	in.seekg(0, in.end);
	SIZE = in.tellg();
	in.seekg(0);
	if (SIZE % 16 != 0)
	{
		cout << "Error, file was corrected !" << endl;
		system("pause");
		exit(-1);
	}
	string sf = readFile(in);
	database = new byte[SIZE];
		for (int i = 0; i < SIZE; i++)
	{
		database[i]= sf[i];
	}
}
void square::Encryption_mode(ifstream&in)
{
	Bdata_create(in);
	digit_sign();
	
	create_database_for_encryption();
	sign_check();
	       //вычисление цифровой подписи
	int k = 0;
	int i = 0;

	for (int i = 0; i < N; i++)
		for (int j = 0; j<N; j++)
			C0[i][j] = 0x00;

	blocks = SIZE / 16;
	int count;
	for (count = 1; count <= blocks; count++)
	{
		for (int i = 0, j = k * 16; i < N *N, j < N*N*count; i++, j++)
		{
			C0[i / N][i % N] = C0[i / N][i % N] ^ database[j];
		}
		encryption_block(C0, key);
		for (int i = 0, j = k * 16; i < N *N, j < N*N*count; i++, j++)
		{
			database[j] = C0[i / N][i % N];
		}
		k++;
	}

}
void square::Decryption_mode(ifstream&in)
{
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j<N; j++)
			C0[i][j] = 0x00;

	create_database_for_decryption(in);
	
	byte g[N][N];
	int k = 0;
	blocks = SIZE / 16;
	int count;
	byte*database1 = new byte[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		database1[i] = database[i];
	}
	for (count = 1; count <= blocks; count++)
	{
		for (int i = 0, j = k * 16; i < N *N, j < N*N*count; i++, j++)
		{
			data[i / N][i % N] = database[j];
			if (j >= 16)
				g[i / N][i % N] = database1[j - 16];

		}

		decryption_block(data, key);
		for (int i = 0, j = k * 16; i < N *N, j < N*N*count; i++, j++)
		{
			if (j < 16)
				database[j] = C0[i / N][i % N] ^ data[i / N][i % N];
			else
				database[j] = data[i / N][i % N] ^ g[i / N][i % N];
		}
		k++;
	}

	size1 = SIZE - 64;
	Bdata = new byte[size1];
	for (int i = 0; i < size1; i++)
		Bdata[i] = database[i];
	
	digit_sign();
	sign_check();
}
void square::database_show(ofstream&out)
{
	for(int i=0;i<SIZE;i++)
	out.write((char*)&database[i], sizeof(byte));
}
#endif