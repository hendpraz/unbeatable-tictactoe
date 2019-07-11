/*	NIM/Nama    : 13517105/Muhammad Hendry Prasetya
	Nama file   : tictactoe.c
   */

#include "tictactoe.h"
#include <stdio.h>
#include <stdlib.h>

static boolean PFM; //Bernilai true jika pemain bergerak duluan. "Player First Move"
static char Cond; //Kondisi permainan. Menang, Seri, atau Berlangsung.
static char state[110]; //Menyimpan satu baris state beserta transisinya 

static int CountState; //Menghitung banyak state yang dilalui
static Daftar StateList; //Daftar berisi states yang dilalui
static FILE * tabel; //File eksternal berisi state

static int PlayerWin = 0; //Banyaknya kemenangan pemain
static int CompWin = 0; //Banyaknya kemenangan computer
static int PlaComDraw = 0; //Banyaknya game yang seri

void showScore(){
	// I.S. :
	// F.S. : Skor pemain dan computer ditampilkan ke layar
	printf("****** Scoreboard ******\n\n");
	printf("Player : %d\n", PlayerWin);
	printf("Computer : %d\n", CompWin);
	printf("Draw : %d\n\n", PlaComDraw);
}

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
	fclose(tabel);
	if(PFM){
		tabel = fopen("pfirst.txt","r");
	} else{
		tabel = fopen("cfirst.txt","r");
	}
	
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

void check(STR *S){
	// I.S. : input/output S terdefinisi
	// F.S. : permainan dapat diakhiri jika sudah final state
	// Proses : mengecek apakah kondisi state S dapat mengakhiri permainan
	//Algoritma
	process(*S);
	Elmt((*S),0) = state[0];

	//Menambah banyaknya states dan mengisi states yang dilalui ke tabel
	CountState++;
	Elmt(StateList,CountState) = *S;

	//Check apakah state sekarang sudah final state
	if(Menang(*S)){
		CompWin++;
		Cond = Win;
		printf("HAHAHA! Aku menang! Coba lagi lain kali!\n\n");
	} else if(Seri(*S)){
		PlaComDraw++;
		Cond = Tie;
		printf("IT'S A TIE! Coba lagi lain kali\n\n");
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
	//State bertransisi sesuai input
	for(i=(inp*10)+1;i<=(inp*10)+9;i++){
		Elmt((*S),i-(inp*10)) = state[i];
	}

	check(&(*S));
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

void showHelp(){
	// I.S. :
	// F.S. : Panduan bermain ditampilkan di layar
	//Kamus Lokal
	STR S;
	int i;
	//Algoritma
	printf("1. Anda menggunakan tanda 'X', sedangkan komputer menggunakan tanda 'O'\n");
	printf("2. Setiap petak ditandai dengan nomor tertentu\n");
	printf("3. Anda/computer dinyatakan menang apabila tanda Anda/computer berderet sebanyak 3 tanda\n");
	printf("   Baik secara vertikal, horizontal, maupun diagonal\n");
	printf("4. Komputer dan Anda dinyatakan seri apabila seluruh petak terisi namun kondisi nomor 3 tidak terpenuhi\n");
	printf("5. Anda/Komputer harus mengisi petak di tengah terlebih dahulu pada awal permainan\n\n");
	
	printf("Nomor tiap petak ditandai dengan sebagai berikut :\n");
	for(i=1;i<=9;i++){ //Mengisi S dengan nomor papan permainan
		Elmt(S,i) = (char) (48 + i);
	}
	TulisSTR(S);
}

void BacaSTEP(STR *S){
	// I.S. : input/output S terdefinisi
	// F.S. : Menghasilkan output nilai S baru berdasarkan input pemain dan pergerakan komputer
	// Proses : Membaca input langkah pemain,
	//Kamus Lokal
	int inp;
	//Algoritma
	//Membaca step berikutnya dari pemain
	printf("Masukan kode langkahmu berikutnya (1-9) : ");
	scanf("%d",&inp);
	while((inp > 9) || (inp < 1) || (terisi((*S),inp))){ //Validasi input
		printf("Input salah! Masukkan kembali!\n");
		printf("Masukan kode langkahmu berikutnya (1-9) : ");
		scanf("%d",&inp);
	}

	if(Cond == Cont){
		//Transisi ke state berikutnya sesuai input pemain
		printf("\nOke, giliranku!!\n\n");
		compMove(&(*S), inp);
		TulisSTR(*S);
	}
}

void ShowState(){
	// I.S. : Permainan telah selesai
	// F.S. : Menampilkan state mana saja yang telah dilalui pada suatu permainan
	int i,j;

	printf("Daftar states yang dilewati :\n");
	for(i=1;i<=CountState;i++){
		for(j=1;j<=9;j++){
			printf("%c",Elmt(Elmt(StateList,i),j));
		}
		printf("\n");
	}
	printf("\n");
}

void Play(){
	// I.S. :
	// F.S. : Permainan tictactoe dimulai
	//Kamus Lokal
	STR board;
	char fm, pa; //First Move dan Play Again
	char dump; //Tempat sampah untuk menyimpan karakter Enter.
	int i;
	//Algoritma
	printf("Permainan dimulai!!\n\n");
	printf("Apakah anda ingin memulai permainan terlebih dahulu? (Y/N)\n");
	
	scanf("%c",&fm);
	printf("\n");
	firstMove(fm);

	//Mengisi board dengan elemen awal
	Elmt(board,0) = 'S';
	for(i=1;i<=9;i++){
		Elmt(board,i) = '-';
	}

	CountState = 0;
	printf("Player (X) - CPU (O)\n");
	if(PFM){
		//Player bermain pertama
		//Membuat start state
		printf("Anda harus mengisi nilai yang di tengah terlebih dahulu\n\n");
		Elmt(board,5) = 'X';
		TulisSTR(board);
		printf("Oke, giliranku!!\n\n");
		Elmt(board,1) = 'O';
		TulisSTR(board);
		//Mencatat state yang dilewati
		CountState++;
		Elmt(StateList,CountState) = board;
		//Membuka file eksternal yang digunakan jika player bermain pertama
		tabel = fopen("pfirst.txt","r");
	} else{
		//Computer bermain pertama
		//Membuat start state
		printf("Oke, akan kumulai dari tengah!\n\n");
		Elmt(board,5) = 'O';
		TulisSTR(board);
		//Mencatat state yang dilewati
		CountState++;
		Elmt(StateList,CountState) = board;
		//Membuka file eksternal yang digunakan jika komputer bermain pertama
		tabel = fopen("cfirst.txt","r");
	}

	Cond = Cont;
	while(Cond == Cont){ //Akan terus membaca input pemain jika belum final state
		BacaSTEP(&board);
	}

	//Menampilkan hasil akhir permainan
	printf("\n****** Game Over ******\n");
	showScore();
	ShowState();
	fclose(tabel); //Menutup file eskternal

	printf("Mau main lagi? (Y/N)\n");
	scanf("%c",&dump); //Menyimpan masukan berupa Enter dari pemain
	scanf("%c",&pa);
	if((pa == 'Y') || (pa == 'y')){ //Mengulang permainan dengan skorboard terbaru
		scanf("%c",&dump); //Menyimpan masukan berupa Enter dari pemain
		Play();
	}
}