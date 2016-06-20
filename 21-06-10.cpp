#include <iostream>
#include <fstream>
using namespace std;
struct libro{
	char titolo[80];
	char autore[80];
	int pagine;
	libro *succ;
};
typedef libro* biblioteca;
// Questa procedura legge da tastiera il nome del file da caricare o da salvare
void leggiNomeFile(char nomeFile[])
{
	int car=2;
	do
	{
	int i=0;
	cout << "Inserisci il nome del file ";
	cin >> nomeFile;
	while(nomeFile[i]!='\0')
	{
		if(nomeFile[i]=='.')
		{
			if (nomeFile[i+1]=='b'&& nomeFile[i+2]=='i' && nomeFile[i+3]=='b')
			{
				car=0;// è stata inserita l'estensione giusta
			}
		else {
			cout << "Nome di file non valido. Prova ancora." << endl;
			car=1; //estensione sbagliata
		} 
		}
		i++;
	}
}
while(car!=0);
}
bool ordine_alf(libro l,libro f) //ordina le parole  in ordine alfabetico 
{
	int r=(int)l.titolo[0]; //converto la prima lettera del nome in int
	int q=(int)f.titolo[0]; //converto la prima lettera del nome in int
	if (r<q) return true; //se r è minore di q,sono in ordine alfabetico
	else return false; // ...altrimenti no
}
// Questa procedura inserisce ordinatamente un libro nella biblioteca
void inserisciLibro(biblioteca& b,libro l )
{
	biblioteca p,q,d;
	for (q=b;q!=0 && ordine_alf(*q,l);q=q->succ) p=q;
	d=new libro;
	*d=l;
	d->succ=q;
	if(q==b)b=d;
	else p->succ=d;
}
// Questa procedura stampa un elenco dei libri presenti nella biblioteca
void elencoLibri(biblioteca b)
{
	while(b!=0)
	{
		cout << "\"" << b->titolo << "\",di " << b->autore << ", " << b->pagine << " pagine" << endl;
		b=b->succ;  
	}
}
// Questa procedura carica una biblioteca salvata su file
void caricaBiblioteca( biblioteca& b, char file[] )
{
	fstream input;
	libro a;
	input.open(file,ios::in);
	while (input.good())
	{
	input >> a.titolo >> a.autore >> a.pagine;
	inserisciLibro(b,a);
}
input.close();
}
// Questa procedura salva una biblioteca su file
void salvaBiblioteca(biblioteca b, char file[] )
{
	fstream output;
	output.open(file,ios::out);
	while (b!=0)
	{
	output << b->titolo << " " << b->autore << " " << b->pagine << endl;
	b=b->succ;	
}
output.close();
}
int main()
{
	char nome[16];
	biblioteca b=0;
	libro l;
	int r;
do
{
	cout << "Biblioteca elettronica\n-- Menu principale --\n"
"1. Inserisci un nuovo libro\n"
"2. Elenco dei libri\n"
"3. Carica biblioteca\n"
"4. Salva biblioteca\n"
"5. Esci\n"
"Inserisci un comando: ";
cin >> r;
switch (r)
{
	case 1:{
		cout << "Inserisci il titolo del libro: ";
		cin >> l.titolo;
		cout << "Inserisci l'autore del libro: ";
		cin >> l.autore;
		cout << "Numero di pagine: ";
		cin >> l.pagine;
		inserisciLibro(b,l);
	}break;
	case 2:{
		elencoLibri(b);
	}break;
	case 3:{
	leggiNomeFile(nome);
	caricaBiblioteca(b,nome);
	}break;
	case 4:{
	leggiNomeFile(nome);
	salvaBiblioteca(b,nome);
	}break;
	case 5:{}break;
	default : cout << "comando non consentito" << endl;
}
}
	while(r!=5); 	
}
