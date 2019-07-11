/*	NIM/Nama    : 13517105/Muhammad Hendry Prasetya
	Nama file   : tictactoe.h
   */

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "boolean.h"
#include <stdio.h>
#include <string.h>

#define Win 'W' //Kemenangan komputer ditandai dengan 'W' pada huruf awal state
#define Tie 'T' //Game seri ditandai dengan 'T' pada huruf awal state
#define Cont 'C' //Game masih berlanjut ditandai dengan 'C' pada huruf awal state

//Tipe bentukan state
typedef struct{
	char Tab[15];
}STR;

typedef struct{
	STR Tab[10];
} Daftar;

/* Selektor elemen state */
#define Elmt(T,i) (T).Tab[(i)]

void showScore();
// I.S. :
// F.S. : Skor pemain dan computer ditampilkan ke layar

void firstMove(char c);
// I.S. : input c terdefinisi
// F.S. : PFM bernilai true jika (c = 'Y') atau (c = 'y'), false jika tidak

boolean terisi(STR S, int x);
// I.S. : input S dan x terdefinisi
// F.S. : Mengembalikan nilai true jika Elmt(T,x) sudah diisi 'X' atau 'O'

boolean Seri(STR S);
// I.S. : input S terdefinisi
// F.S. : Mengembalikan nilai true jika Elmt(S,0) bernilai 'T'

boolean Menang(STR S);
// I.S. : input S terdefinisi
// F.S. : Mengembalikan nilai true jika Elmt(S,0) bernilai 'W'

void process(STR S);
// I.S. : input S terdefinisi
// F.S. : array state terisi dengan baris state dan transisi sesuai input S
// Proses : mengisi array state dengan mencari baris state yang sesuai pada file eksternal

void check(STR *S);
// I.S. : input/output S terdefinisi
// F.S. : permainan dapat diakhiri jika sudah final state
// Proses : mengecek apakah kondisi state S dapat mengakhiri permainan

void compMove(STR *S, int inp);
// I.S. : input/output S dan input inp terdefinisi
// F.S. : state bertransisi berdasarkan input (gerakan) pemain
//		  computer hanya bergerak jika belum final state
// Proses : process(*S) kemudian bergerak sesuai transisi statenya.

void TulisSTR(STR S);
// I.S. : input S terdefinisi
// F.S. : menulis papan permainan tictactoe berdasarkan array S dalam bentuk matriks 3x3

void showHelp();
// I.S. :
// F.S. : Panduan bermain ditampilkan di layar

void BacaSTEP(STR *S);
// I.S. : input/output S terdefinisi
// F.S. : Menghasilkan output nilai S baru berdasarkan input pemain dan pergerakan komputer
// Proses : Membaca input langkah pemain,

void ShowState();
// I.S. : Permainan telah selesai
// F.S. : Menampilkan state mana saja yang telah dilalui pada suatu permainan

void Play();
// I.S. :
// F.S. : Permainan tictactoe dimulai

#endif
