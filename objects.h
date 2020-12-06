#define _OBJECTS__H
#include <stdio.h>
#include "quaternion.h"

#define PI 3.1416
extern class Terrain;

struct StanObiektu
{
	int iID;                  // identyfikator obiektu
	Wektor3 wPol;             // polozenie obiektu (�rodka geometrycznego obiektu) 
	kwaternion qOrient;       // orientacja (polozenie katowe)
	Wektor3 wV, wA;            // predkosc, przyspiesznie liniowe
	Wektor3 wV_kat, wA_kat;   // predkosc i przyspeszenie liniowe
	float masa_calk;          // masa ca�kowita (wa�na przy kolizjach)
	long pieniadze;
	float ilosc_paliwa;
	int iID_wlasc;
	int czy_autonom;
};


class MovableObject
{
public:
	int iID;                  // identyfikator obiektu

	// parametry stanu:
	Wektor3 wPol;             // polozenie obiektu
	kwaternion qOrient;       // orientacja (polozenie katowe)
	Wektor3 wV, wA;            // predkosc, przyspiesznie liniowe
	Wektor3 wV_kat, wA_kat;   // predkosc i przyspeszenie liniowe
	long pieniadze;
	float ilosc_paliwa;

	// parametry akcji:
	float F;                  // F - si�a pchajaca do przodu (do ty�u ujemna)
	float ham;                // stopie� hamowania Fh_max = tarcie*Fy*ham
	float alfa;               // kat skretu kol w radianach (w lewo - dodatni)



	// decyzje zwi�zane z trwa�� wsp�prac� polegaj�c� na dzieleniu si�
	// paliwem i got�wk� p� na p�:
	bool wyslanie_zaproszenia_do_dzielenia;
	bool zgoda_na_dzielenie;
	bool koniec_dzielenia;
	int ID_koalicjanta;       // identyfikator obiektu, z kt�rym chcemy nawi�za� wsp�prac� (-1 z nikim)

	// decyzje zwi�zane z kupnem 10 kg paliwa:
	long cena_od_kupca_paliwa;     // cena zaproponowana przez chc�cego kupi� paliwo
	bool chec_sprzedazy_paliwa;    // ch�� sprzeda�y paliwa po zaproponowanej cenie 
	int ID_kupca_paliwa;           // identyfikator kupca paliwa, gdy podejmiemy decyzj� o sprzeda�y (-1 brak takiej decyzji)
	int ID_przedawcy_paliwa;       // identyfikator sprzedawcy paliwa, gdy podejmiemy decyzj� o jego kupnie

	// decyzje zwi�zane z podniesieniem ci�kiej monety:
	int nr_przedm_do_podniesienia;        // numer przedmiotu do podniesienia
	bool czy_przelew_polowy_wartosci;     // decyzja o przelewie w zwi�zku z pomoc�


	// parametry sta�e:
	float umiejetn_sadzenia,    // umiej�tno�� sadzenia drzew (1-pe�na, 0- brak)
		umiejetn_zb_paliwa,   // umiej�tno�� zbierania paliwa
		umiejetn_zb_monet;

	bool czy_zazn;            // czy obiekt zaznaczony  

	// parametry fizyczne pojazdu:
	float F_max;
	float alfa_max;
	float Fy;                 // si�a nacisku na podstaw� pojazdu - gdy obiekt styka si� z pod�o�em (od niej zale�y si�a hamowania)
	float masa_wlasna;		  // masa w�asna obiektu (bez paliwa)	
	float masa_calk;          // masa ca�kowita (wa�na przy kolizjach)
	float dlugosc, szerokosc, wysokosc; // rozmiary w kierunku lokalnych osi x,y,z
	float promien;            // promien minimalnej sfery, w ktora wpisany jest obiekt
	float przeswit;           // wysoko�� na kt�rej znajduje si� podstawa obiektu
	float dl_przod;           // odleg�o�� od przedniej osi do przedniego zderzaka 
	float dl_tyl;             // odleg�o�� od tylniej osi do tylniego zderzaka 

	// inne: 
	int iID_kolid;            // identyfikator pojazdu z kt�rym nast�pi�a kolizja (-1  brak kolizji)
	Wektor3 wdV_kolid;        // poprawka pr�dko�ci pojazdu koliduj�cego
	int iID_wlasc;
	bool czy_autonom;         // czy obiekt jest autonomiczny
	long nr_wzietego_przedm;   // numer wzietego przedmiotu
	float wartosc_wzieta;   // wartosc wzietego przedmiotu
	long nr_odnowionego_przedm;


	float czas_symulacji;     // czas sumaryczny symulacji obiektu   
	Terrain *terrain;             // wska�nik do terrainu, do kt�rego przypisany jest obiekt

public:
	MovableObject(Terrain *t);          // konstruktor
	~MovableObject();
	void ZmienStan(StanObiektu stan);          // zmiana stanu obiektu
	StanObiektu Stan();        // metoda zwracajaca stan obiektu
	void Symulacja(float dt);  // symulacja ruchu obiektu w oparciu o biezacy stan, przylozone sily
	// oraz czas dzialania sil. Efektem symulacji jest nowy stan obiektu 
	void Rysuj();			   // odrysowanie obiektu					
};

enum TYpyPrzedm { PRZ_MONETA, PRZ_BECZKA, PRZ_DRZEWO, PRZ_BUDYNEK, PRZ_PUNKT, PRZ_KRAWEDZ, PRZ_MIEJSCE_STARTOWE, PRZ_MUR, PRZ_BRAMKA };
//char *PRZ_nazwy[] = { "moneta", "beczka", "drzewo", "punkt", "krawedz", "miejsce startowe", "mur", "bramka" };
enum PodtypyDrzew { DRZ_TOPOLA, DRZ_SWIERK, DRZ_BAOBAB, DRZ_FANTAZJA };
//char *DRZ_nazwy[] = { "topola", "swierk", "baobab", "fantazja" };
enum PodtypyPunktow {PUN_ZWYKLY, PUN_KRAWEDZI, PUN_WODY};

struct Przedmiot
{
	Wektor3 wPol;             // polozenie obiektu
	kwaternion qOrient;       // orientacja (polozenie katowe)

	int typ;
	int podtyp;
	long indeks;                 // identyfikator - numer przedmiotu (jest potrzebny przy przesy�aniu danych z tego wzgl�du,
	//    �e wyszukiwanie przedmiot�w (np. Przedmioty_w_promieniu()) zwraca wska�niki)

	float wartosc;            // w zal. od typu nomina� monety /ilosc paliwa, itd.
	float srednica;           // np. grubosc pnia u podstawy, srednica monety
	float srednica_widocz;          // �rednica widoczno�ci - sfery, kt�ra opisuje przedmiot
	float param_f[3];        // dodatkowe parametry roznych typow
	long param_i[3];
	bool czy_zazn;            // czy przedmiot jest zaznaczony przez uzytkownika
	long grupa;               // numer grupy do kt�rej nale�y przedmiot;

	bool do_wziecia;          // czy przedmiot mozna wziac
	bool czy_ja_wzialem;      // czy przedmiot wziety przeze mnie
	bool czy_odnawialny;      // czy mo�e si� odnawia� w tym samym miejscu po pewnym czasie
	long czas_wziecia;        // czas wzi�cia (potrzebny do przywr�cenia)

	
	unsigned long nr_wyswietlenia;   // zgodny z liczba wy�wietle� po to, by nie powtarza� rysowania przedmiot�w
};

struct PunktLasso
{
	float x;
	float y;
};

class Sektor
{
public:
	long w, k;                    // wiersz i kolumna okre�laj�ce po�o�enie obszaru na nieograniczonej p�aszczy�nie
	int liczba_oczek;             // liczba oczek na mapie w poziomie i pionie (pot�ga dw�jki!) 
	//float rozmiar_sektora;        // potrzebny do obliczenia normalnych
	Przedmiot **wp;               // jednowymiarowa tablica wska�nik�w do przedmiot�w znajduj�cych si� w pewnym obszarze
	long liczba_przedmiotow;      // liczba przedmiot�w w obszarze 
	long liczba_przedmiotow_max;  // rozmiar tablicy przedmiot�w z przydzielon� pami�ci�

	float **mapa_wysokosci;         // wysoko�ci wierzcho�k�w
	int **typy_naw;                 // typy nawierzchni
	float **poziom_wody;            // poziom wody w ka�dym oczku 
	Wektor3 ****Norm;                // wektory normalne do poszczeg�lnych p�aszczyzn (rozdzielczo�� x wiersz x kolumna x 4 p�aszczyzny);

	float **mapa_wysokosci_edycja;    // mapa w trakcie edycji - powinna by� widoczna ��cznie z dotychczasow� map�
	Wektor3 ****Norm_edycja;   
	int **typy_naw_edycja;
	float **poziom_wody_edycja;
	int liczba_oczek_edycja;

	// podstawowe w�a�ciwo�ci dla ca�ego sektora, gdyby nie by�o mapy
	int typ_naw_sek;                              // typ nawierzchni gdyby nie by�o mapki
	float wysokosc_gruntu_sek;
	float poziom_wody_sek;

	MovableObject **wob;                          // tablica obiekt�w ruchomych, kt�re mog� znale�� si� w obszarze w ci�gu
	// kroku czasowego symulacji (np. obiekty b. szybkie mog� znale�� si� w wielu obszarach)
	long liczba_obiektow_ruch;
	long liczba_obiektow_ruch_max;

	float wysokosc_max;             // maksymalna wysoko�� terrainu w sektorze -> istotna dla wyznaczenia rozdzielczo�ci np. przy widoku z g�ry
	int liczba_oczek_wyswietlana;   // liczba oczek (rozdzielczo��) aktualnie wy�wietlana, w zal. od niej mo�na dopasowa� s�siednie sektory
	                                // by nie by�o dziur
	int liczba_oczek_wyswietlana_pop;  // poprzednia liczba oczek, by uzyska� pa�ne dopasowanie rozdzielczo�ci s�siaduj�cych sektor�w 
	//float promien;                // promien sektora zwykle d�ugo�� po�owy przek�tnej kwadratu, mo�e by� wi�kszy, gdy w
	                              // �rodku du�e r�nice wysoko�ci lub du�e przedmioty lub obiekty

	Sektor(){};
	Sektor(int _loczek, long _w, long _k, bool czy_mapa);
	~Sektor();
	void pamiec_dla_mapy(int __liczba_oczek, bool czy_edycja=0);
	void zwolnij_pamiec_dla_mapy(bool czy_edycja = 0);
	void wstaw_przedmiot(Przedmiot *p);
	void usun_przedmiot(Przedmiot *p);
	void wstaw_obiekt_ruchomy(MovableObject *o);
	void usun_obiekt_ruchomy(MovableObject *o);
	void oblicz_normalne(float rozmiar_sektora, bool czy_edycja=0);         // obliczenie wektor�w normalnych N do p�aszczyzn tr�jk�t�w, by nie robi� tego ka�dorazowo przy odrysowywaniu   
};

struct KomorkaTablicy  // kom�rka tablicy rozproszonej (te� mog�aby by� tablic� rozproszon�)
{
	Sektor **sektory;  // tablica wska�nik�w do sektor�w (mog� zdarza� si� konflikty -> w jednej kom�rce wiele sektor�w) 
	long liczba_sektorow; // liczba sektor�w w kom�rce
	long rozmiar_pamieci; // liczba sektor�w, dla kt�rej zarezerwowano pami��
};

class TabSektorow      // tablica rozproszona przechowuj�ca sektory
{
	//private:
public:
	long liczba_komorek;                                 // liczba kom�rek tablicy
	long ogolna_liczba_sektorow;
	long w_min, w_max, k_min, k_max;                     // minimalne i maksymalne wsp�rz�dne sektor�w (przyspieszaj� wyszukiwanie)  
	KomorkaTablicy *komorki;
	unsigned long wyznacz_klucz(long w, long k);          // wyznaczanie indeksu kom�rki

public:

	TabSektorow();        // na wej�ciu konstruktora liczba kom�rek tablicy
	~TabSektorow();

	Sektor *znajdz(long w, long k);       // znajdowanie sektora (zwraca NULL je�li nie znaleziono)
	Sektor *wstaw(Sektor *s);              // wstawianie sektora do tablicy
	void usun(Sektor *s);              // usuwanie sektora
};

struct ParamFaldy
{
	float srednica_faldy;
	float wysokosc_faldy;
	int liczba_oczek_faudy;           // liczba oczek w ka�dym sektorze, w kt�rym tworzona jest fa�da 
	bool czy_wypukla;                 // 1-wypuk�o�� w g�r�, 0 - w d�
	float wariancja_wysokosci;        // losowa wariancja wysoko�ci ka�dego wierzcho�ka fa�dy
	int ksztalt_przekroju;
	float srednica_wewnetrzna;        // pozwala na uzyskanie p�askiego miejsca na g�rze lub dole fa�dy w zal. od wypuk�o�ci
	bool czy_stale_nachylenie;        // czy stoki wa�u maj� sta�e pochylenie -> w�wczas maj� one sta�y k�t nachylenia, niezale�nie
	// od wysoko�ci (np. jak nasyp drogowy) -> nie jest brana pod uwag� �rednica fa�dy ale k�t nachylenia
	float kat_nachylenia;             // k�t nachylenia stoku w radianach np. pi/4 == 45 stopni

	int sposob_laczenia_faudy;        // spos�b ��czenia nowoutworzonej fa�dy z obecn� powierzchni� terrainu 
};

class Terrain
{
public:
	void WstawPrzedmiotWsektory(Przedmiot *prz);
	void UsunPrzedmiotZsektorow(Przedmiot *prz);
public:

	long liczba_przedmiotow;      // liczba przedmiot�w na planszy
	long liczba_przedmiotow_max;  // rozmiar tablicy przedmiot�w

	TabSektorow *ts;

	

	// inne istotne w�a�ciwo�ci terrainu:
	float rozmiar_sektora;        // w [m] zamiast rozmiaru pola
	float czas_odnowy_przedm;     // czas w [s] po kt�rym nast�puje odnowienie si� przedmiotu 
	bool czy_toroidalnosc;        // inaczej cyklicznosc -> po dojsciu do granicy przeskakujemy na
	                              // pocz�tek terrainu, zar�wno w pionie, jak i w poziomie (gdy nie ma granicy, terrain nie mo�e by� cykliczny!)
	float granica_x, granica_z;   // granica terrainu (je�li -1 - terrain niesko�czenie wielki)

	// parametry wy�wietlania:
	float szczeg;                 // stopie� szczeg�owo�ci w przedziale 0,1 
	unsigned long liczba_wyswietlen;   // potrzebne do unikania podw�jnego rysowania przedmiot�w
	long *zazn_przedm;     // tablica numer�w zaznaczonych przedmiot�w (dodatkowo ka�dy przedmiot posiada pole z informacj� o zaznaczeniu)
	long liczba_zazn_przedm,      // liczba aktualnie zaznaczonych przedmiot�w
		liczba_zazn_przedm_max;   // liczba miejsc w tablicy 

	ParamFaldy pf_rej[10];        // parametry edycji fa�d (s� tu tylko ze wzgl�du na konieczno�� zapisu do pliku

	Przedmiot *p;          // tablica przedmiotow roznego typu

	Terrain();
	~Terrain();
	float WysokoscGruntu(float x, float z);      // okre�lanie wysoko�ci gruntu dla punktu o wsp. (x,z)
	float WysokoscNaPrzedmiocie(Wektor3 pol, Przedmiot *prz); // wysoko�� na jakiej znajdzie si� przeci�cie pionowej linii przech. przez pol na g�rnej powierzchni przedmiotu
	float Wysokosc(Wektor3 pol);                 // okre�lenie wysoko�ci nad najbli�szym przedmiotem lub gruntem patrz�c w d� od punktu pol
	void WspSektora(long *w, long *k, float x, float z);  // na podstawie wsp. po�o�enia punktu (x,z) zwraca wsp. sektora 
	void PolozeniePoczSektora(float *x, float *z, long w, long k); // na podstawie wsp�rz�dnych sektora (w,k) zwraca po�o�enie punktu pocz�tkowego
	float wysokosc_na_najw_zazn_przedm(Wektor3 pol);
	Wektor3 wspolrzedne_kursora3D_bez_paralaksy(int X, int Y);
	void Rysuj();	      // odrysowywanie terrainu 
	void PoczatekGrafiki();               // tworzenie listy wy�wietlania
	int Zapis(char nazwa_pliku[]);        // zapis mapy w pliku o podanej nazwie
	int Odczyt(char nazwa_pliku[]);       // odczyt mapy z pliku
	void UmieszczeniePrzedmiotuWterrainie(Przedmiot *prz);     // m.i. ustalenie wysoko�ci, na kt�rej le�y przedmiot w zal. od ukszta�t. terrainu
	long WstawPrzedmiot(Przedmiot prz);   // wstawia przedmiot do tablic, zwraca numer przedmiotu w tablicy p[]
	void ZaznaczOdznaczPrzedmiotLubGrupe(long nr_prz);// wpisywanie w pole �e jest zaznaczony lub nie, dodawanie/usuwanie do/z listy zaznaczonych 
	void UsunZaznPrzedmioty();
	void NowaMapa();                      // tworzenie nowej mapy (zwolnienie pami�ci dla starej)
	
	long Przedmioty_w_promieniu(Przedmiot*** wsk_prz, Wektor3 pol, float promien);
	void WstawObiektWsektory(MovableObject *ob);
	void UsunObiektZsektorow(MovableObject *ob);
	long Obiekty_w_promieniu(MovableObject*** wsk_ob, Wektor3 pol, float promien);
};