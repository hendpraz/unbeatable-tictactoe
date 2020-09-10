/*	NIM/Nama    : 13517105/Muhammad Hendry Prasetya
	Nama file   : tictactoe.c
   */

#include "tictactoe.h"
#include <stdio.h>
#include <stdlib.h>

static boolean PFM; //Bernilai true jika pemain bergerak duluan. "Player First Move"
static char Cond; //Kondisi permainan. Menang, Seri, atau Berlangsung.
static char state[110]; //Menyimpan satu baris state beserta transisinya 

static FILE * tabel; //File eksternal berisi state

static int PlayerWin = 0; //Banyaknya kemenangan pemain
static int CompWin = 0; //Banyaknya kemenangan computer
static int PlaComDraw = 0; //Banyaknya game yang seri
static int StatusCode = 0; // 0 -> OK, 1 -> Error
static STR board;

void firstMove(char c){
	// I.S. : input c terdefinisi
	// F.S. : PFM bernilai true jika (c = 'Y') atau (c = 'y'), false jika tidak
	//Algoritma
	if((c == 'Y') || (c == 'y')){
		PFM = true;
	} else{
		PFM = false;
	}
}

boolean terisi(STR S, int x){
	// I.S. : input S dan x terdefinisi
	// F.S. : Mengembalikan nilai true jika Elmt(T,x) sudah diisi 'X' atau 'O'
	//Algoritma
	return((Elmt(S,x) == 'X') || (Elmt(S,x) == 'O'));
}

boolean Seri(STR S){
	// I.S. : input S terdefinisi
	// F.S. : Mengembalikan nilai true jika Elmt(S,0) bernilai 'T'
	//Algoritma
	return(Elmt(S,0) == 'T');
}

boolean Menang(STR S){
	// I.S. : input S terdefinisi
	// F.S. : Mengembalikan nilai true jika Elmt(S,0) bernilai 'W'
	//Algoritma
	return(Elmt(S,0) == 'W');
}

void process(STR S){
	// I.S. : input S terdefinisi
	// F.S. : array state terisi dengan baris state dan transisi sesuai input S
	// Proses : mengisi array state dengan mencari baris state yang sesuai 
	// pada file eksternal
	//Kamus Lokal
	boolean sama;
	int i;
	//Algoritma
	//Memproses ulang file eksternal dari awal (untuk menghindari bug)
	if(PFM){
		tabel = fopen("pfirst.txt","r");
	} else{
		tabel = fopen("cfirst.txt","r");
	}

	if(tabel == NULL)
	{
		StatusCode = 1;
	} else {
		//searching state terbaru pada file eksternal
		sama = false;
		while(!sama){
			sama = true;
			fgets(state,110,tabel);
			for(i=1;i<=9;i++){
				if(Elmt((S),i) != state[i]){
					sama = false;
				}
			}
		}
	}
}

void check(STR *S){
	// I.S. : input/output S terdefinisi
	// F.S. : permainan dapat diakhiri jika sudah final state
	// Proses : mengecek apakah kondisi state S dapat mengakhiri permainan
	//Algoritma
	process(*S);
	if (StatusCode != 1) {
			Elmt((*S),0) = state[0];

		//Check apakah state sekarang sudah final state
		if(Menang(*S)){
			CompWin++;
			Cond = Win;
		} else if(Seri(*S)){
			PlaComDraw++;
			Cond = Tie;
		}
	}
}

void compMove(STR *S, int inp){
	// I.S. : input/output S dan input inp terdefinisi
	// F.S. : state bertransisi berdasarkan input (gerakan) pemain
	//		  computer hanya bergerak jika belum final state
	// Proses : process(*S) kemudian bergerak sesuai transisi statenya.
	//Kamus Lokal
	int i, count;
	//Algoritma
	process(*S);
	if (StatusCode != 1) {
		//State bertransisi sesuai input
		for(i=(inp*10)+1;i<=(inp*10)+9;i++){
			Elmt((*S),i-(inp*10)) = state[i];
		}
		check(&(*S));
	}
}

void TulisSTR(STR S){
	// I.S. : input S terdefinisi
	// F.S. : menulis papan permainan tictactoe berdasarkan array S 
	// dalam bentuk matriks 3x3
	//Algoritma
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", Elmt(S,1), Elmt(S,2), Elmt(S,3));

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", Elmt(S,4), Elmt(S,5), Elmt(S,6));

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", Elmt(S,7), Elmt(S,8), Elmt(S,9));
    printf("     |     |     \n\n");
}

void BacaSTEP(STR *S, int inp){
	// I.S. : input/output S terdefinisi, inp 1-9
	// F.S. : Menghasilkan output nilai S baru berdasarkan input pemain dan pergerakan komputer
	// Proses : Membaca input langkah pemain,
	//Algoritma
	//Membaca step berikutnya dari pemain
	if((inp > 9) || (inp < 1) || (terisi((*S),inp))){ //Validasi input
		// TulisSTR(*S);
		StatusCode = 1;
	} else {
		if(Cond == Cont){
			//Transisi ke state berikutnya sesuai input pemain
			compMove(&(*S), inp);
			// TulisSTR(*S);
		}
	}
}

void Play(char* inpState, char fm, int inp){
	// I.S. :
	// F.S. : Permainan tictactoe dimulai
	//Kamus Lokal
	int i;
	//Algoritma
	firstMove(fm);

	//Mengisi board dengan elemen awal
	for(i=0;i<=9;i++){
		Elmt(board,i) = inpState[i];
	}

	Cond = Cont;
	BacaSTEP(&board, inp);
	fclose(tabel); //Menutup file eskternal
	
	// Return Data
	// Cond, After State
}

int main(int argc,char* argv[]){
	// Extra args: PFM, STEP, BOARD

	char fm = argv[1][0];
	int inp = argv[2][0];
	char* inpState = argv[3];
	int i;

	inp = inp - 48;
	Play(inpState, fm, inp);

	printf("StatusCode: %d\n", StatusCode);
	printf("Condition: %c\n", Cond);
	// TulisSTR(board);
	printf("State: ");
	for(i=0;i<=9;i++) {
		printf("%c",Elmt(board,i));
	}
	printf("\n");

	// Return Data
	// StatusCode, Cond, After State
}