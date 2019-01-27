#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <string>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <iomanip>

using namespace std;
class statystyki {
    public:
        string nick;
        int liczbapkt;

};
//########################################################################################################################
///ZMIENNE GLOBALNE:
int menu=27,
klawisz,
klawisz2,
szerokosc=40,wysokosc=20,
zaznaczenie=1,
kolorek=10,
poziom;
bool sprawdz;
HANDLE kolor=GetStdHandle(STD_OUTPUT_HANDLE);
///LISTA FUNKCJI:
bool glowna();
void rysuj(int zmienna);
void nazwagry();
void pokazstatystyki();
void ustawienia();
bool snake();
void wyczysc();
void Wyczysc2();
bool Trudnosc();
bool GameOver(int pkt);


//########################################################################################################################
///FUNKCJA GLOWNA:
int main() {

   // srand(time(NULL));
    rysuj(menu);
    glowna();
    return 0;
}
//########################################################################################################################
///FUNKCJE:
//czytajaca klawisze:
bool glowna() {
	
	//petla nieskonczona
    for(;;) {
    	
    	//sprawdzanie czy wcisnieto jakis klawisz
        if (kbhit()) {
        	
        	// odczytanie nacisniêtego klawisza i zapisanie do zmiennej klawisz. Funkcja getch() odczytuje jeden znak.
            klawisz=getch();
            
            // wywo³anie funkcji, która wyczyœci konsole
            Wyczysc2();
            
            // wczytanie okna konsoli, na pocz¹tku zawsze jest wyœwietlane okno startowe czyli menu = 
            switch(menu) {
            	
            	// jesli menu = 27 to wyswietla siê nam okno g³owne z mo¿liwoœciami: 1 - uruchomienie gry, 2- statatystyki, 3- ustawienia, 4- informacje o autorach, esc- zakonczy gre
                case 27:
                	
                	// sprawdza wybrany klawisz
                    switch(klawisz){
                    	
                    	// 1 - uruchom gre, wywo³uje funkcjê snake()
                        case '1':
                            snake();
                            menu=27;
                            break;
                            
                        // 2 - wyswietli statystyki
                        case '2':
                            menu=2;
                            break;
                            
                        // 3 - ustawienia gry
                        case '3':
                            menu=3;
                            break;
                            
                        // 4 - wyswietli informacje o autorze
                        case '4':
                            menu=4;
                            break;
                            
                        // esc - zakonczy gre, wed³ug kodu ASCII, esc ma numer 27
                        case 27:
                            return 0;
                    }
                    break;
                    
                // wyswietla konsole z widokiem statystyk
                case 2:
                    if (klawisz==27) {
                    	// powrot do menu glowngo
                        menu=27;
                    }
                    if (klawisz==8) {
                    	// czysci statystyki wywolujac funkcje wyczysc()
                        cout<<"Wyczyszczono statystyki"<<endl;
                        wyczysc();
                    }
                    break;
                    
                // wyswietla konsole z widokiem ustawien
                case 3:
                    switch(klawisz) {
                    	
                        case 27:
                            menu=27;
                            zaznaczenie=1;
                            break;
                            
                        //s - przemieszczanie sie do gory w ustawieniach, zwiekszanie parametru zaznaczenie
                        case 's':
                            if (zaznaczenie<3) {
                                zaznaczenie++;
                            }
                            break;
                            
                        //w - przemieszcznie sie w dol w ustawieniach, zwiekszanie paramteru zaznaczanie
                        case 'w':
                            if (zaznaczenie>1) {
                                zaznaczenie--;
                            }
                            break;
                            // d -zwiekszanie ilosci - w przypadku szerokosci/wyskokosci planszy lub zmiana koloru weza
                        case 'd':
                            switch(zaznaczenie){
                                case 1:if (szerokosc<60) szerokosc++;break;
                                case 2:if (wysokosc<30) wysokosc++;break;
                                case 3:if (kolorek!=15) kolorek++;else  kolorek=1;break;
                            }
                            break;
                        
                        // a - zmiejszanie ilosci - w przypadku szerokosci/wysokosci planszy lub powrot do koloru weza
                        case 'a':
                            switch(zaznaczenie){
                                case 1:if (szerokosc>20) szerokosc--;break;
                                case 2:if (wysokosc>10) wysokosc--;break;
                                case 3:if (kolorek!=1) kolorek--;else kolorek=15;break;
                            }
                            break;
                    }
                    break;
                    
                // wyswietla konsole z informacj¹ o autorach gry
                case 4:
                    if (klawisz==27) {
                        menu=27;
                    }
                    break;
            }
            
            
            // funkcja, która wyrysuje konsole z wybranym menu
            rysuj(menu);
        }
    }

}




//########################################################################################################################
//rysujaca na ekranie: Zmienna - wartoœæ, która wskazuje na rodzaj menu
void rysuj(int zmienna) {
	
	// sprawdza jaka wartoœæ ma zmienna i wyrysowuje odpowiednie menu
    switch(zmienna) {
    	
    	// jesli zmienna = 27, wyrysowane jest menu startowe
        case 27:
        	
        	// wywo³anie funkcji, która wyswietla napis na ekranie startowym
            nazwagry();
            cout<<"     "<<char(26)<<" 1 - Start"<<endl;
            cout<<"     "<<char(26)<<" 2 - Statystyki"<<endl;
            cout<<"     "<<char(26)<<" 3 - Ustawienia"<<endl;
            cout<<"     "<<char(26)<<" 4 - Autor"<<endl;
            cout<<"     "<<char(26)<<" [ESC] - Wyjdz"<<endl;
            
             //wyrysowanie lini oddzielaj¹cej 
            for (int e=0;e<50;e++) cout<<char(205);
            break;
            //zmienna rowna 2, wyrysowywane jest menu ze statystykami
        case 2:
            for (int e=0;e<36;e++) cout<<char(205);
            SetConsoleTextAttribute(kolor,9);
            cout<<endl<<endl<<"            Statystyki"<<endl<<endl;
            SetConsoleTextAttribute(kolor,7);
            
            
            pokazstatystyki();
            cout<<"[ESC] - Powrot do MENU"<<endl;
            cout<<"[BS] - Resetowanie statystyk"<<endl;
            
            //wyrysowanie lini oddzielaj¹cej 
            for (int e=0;e<36;e++) cout<<char(205);
            break;
        // wyrysowywane jest menu z ustawienaimi
        case 3:
            ustawienia();
            break;
        case 4:
        	//wyrysowanie lini oddzielaj¹cej 
            for (int e=0;e<37;e++) cout<<char(205);
            cout<<endl<<"Autorzy gry: ";
            SetConsoleTextAttribute(kolor,3);
            cout<<"Ireneusz Borowski, Marcin Welpa"<<endl;
            SetConsoleTextAttribute(kolor,7);
            cout<<"Kontakt z autorem: ";
            SetConsoleTextAttribute(kolor,4);
            cout<<"iborowski1994@gmail.com"<<endl;
            SetConsoleTextAttribute(kolor,7);
            
            //wyrysowanie lini oddzielaj¹cej 
            for (int e=0;e<37;e++) cout<<char(205);
            cout<<endl<<"[ESC] - Powrot do MENU"<<endl;
            
            //wyrysowanie lini oddzielaj¹cej 
            for (int e=0;e<37;e++) cout<<char(205);
            break;
    }
}


//########################################################################################################################
//wyswietlajaca napis "snake" na ekranie g³ównym.
void nazwagry() {
	
	// dwuwymiarowa tablica, która jest odzwierciedleniem napisu SNAKE
    bool matryca[8][50]={
        {0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,1,0},
        {0,0,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0},
        {0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1,0,0,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0},
        {0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0},
        {0,0,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,1,0},
    };
    
    // pobranie koloru, jaki zosta³ wybrany i ustawienie tego koloru na tekst SNAKE
    SetConsoleTextAttribute(kolor,7);
    
    
    //wyrysowanie lini oddzielaj¹cej okno konsoli od napisu SNAKE
    for (int e=0;e<50;e++) cout<<char(205);
    cout<<endl;
    
    // Ustawienie koloru, zmienna kolor, zmienna kolorek - okresla kolor, poprzez liczbê
    SetConsoleTextAttribute(kolor,kolorek);
    
    // wyswietlanie napisu SNAKE
    for (int a=0;a<8;a++) {
        for (int b=0;b<50;b++) {
        	
        	// jesli napotykamy 1 w matrycy, wyrysowujemy znak
            if (matryca[a][b]==1) {
                cout<<char(177);
            }
            else {
                cout<<" ";
            }
        }
        cout<<endl;
    }
    
    // Ustawiamy kolor rysowanego tekstu na bia³y (7)
    SetConsoleTextAttribute(kolor,7);
    cout<<endl;
    
    //wyrysowanie lini oddzielaj¹cej okno konsoli od napisu SNAKE
    for (int e=0;e<50;e++) cout<<char(205);
    cout<<endl;
}




//########################################################################################################################
//funkcja wywolywana w funkcji draw(),czyli rysuje statystyki, czytajac z pliku:
void pokazstatystyki(){
    string nazwa;
    string score;
    
    //wczytuje plik statystyki
    ifstream statystyki("statystyki.txt");
    
    //wyrysowuje linie oddzielajace
    cout<<char(201);
    for (int e=0;e<34;e++) cout<<char(205);
    cout<<char(187)<<endl;
    cout<<char(186)<<" NR "<<char(179)<<" NAZWA                "<<char(179)<<"PUNKTY"<<char(186)<<endl;
    
    //przepisuje na konsole odnowienie informacje z pliku: nick uzytkownika oraz liczbe punktów
    for (int c=1;c<=10;c++) {
        cout<<char(204)<<"----"<<char(197)<<"----------------------"<<char(197)<<"------"<<char(185)<<endl;
        getline(statystyki,nazwa);
        getline(statystyki,score);
        cout<<char(186)<<setw(3)<<c<<" "<<char(179)<<" "<<nazwa;
        for (int d=nazwa.size();d<=20;d++) cout<<" ";
        cout<<char(179)<<setw(4)<<score<<"  "<<char(186)<<endl;
    }
    cout<<char(200);
    for (int e=0;e<34;e++) cout<<char(205);
    cout<<char(188)<<endl;
    statystyki.close();
}
//########################################################################################################################
//funckja wywolywana w funkcji draw(), czyli rysuje menu ustawien:
void ustawienia(){
	
	//czysci konsole
    Wyczysc2();
    
    //wyrysowuje linie oddzielejaca
    for (int e=0;e<36;e++) cout<<char(205);
    cout<<endl<<endl<<"            Ustawienia"<<endl<<endl;
    
    		//podkresla zaznaczona czesc ustawien, poczatkowo jest to szerokosc planszy
            switch (zaznaczenie) {
                case 1:
                    SetConsoleTextAttribute(kolor,kolorek);
                    cout<<"       Szerokosc planszy: "<<szerokosc<<endl;
                    SetConsoleTextAttribute(kolor,7);
                    cout<<"        Wysokosc planszy: "<<wysokosc<<endl;
                    cout<<"           Kolor wezyka"<<endl;
                    break;
                case 2:
                    cout<<"       Szerokosc planszy: "<<szerokosc<<endl;
                    SetConsoleTextAttribute(kolor,kolorek);
                    cout<<"        Wysokosc planszy: "<<wysokosc<<endl;
                    SetConsoleTextAttribute(kolor,7);
                    cout<<"           Kolor wezyka"<<endl;
                    break;
                case 3:
                    cout<<"       Szerokosc planszy: "<<szerokosc<<endl;
                    cout<<"        Wysokosc planszy: "<<wysokosc<<endl;
                    SetConsoleTextAttribute(kolor,kolorek);
                    cout<<"           Kolor wezyka"<<endl;
                    break;
            }
            SetConsoleTextAttribute(kolor,7);
            for (int e=0;e<36;e++) cout<<char(205);
            cout<<endl<<"[ESC] - Powrot do MENU"<<endl;
            for (int e=0;e<36;e++) cout<<char(205);
}




//########################################################################################################################
//funkcja gry:
bool snake(){
	
	//wywo³anie funkcji, która ustawi trudnoœæ gry
    Trudnosc();
    
    //zakonczenie gry, jesli wybrano esc to zmienna sprawdz jest rowna 0. Zmienna jest oznaczana podczas wywo³ania funkcji Trudnosc()
    if (sprawdz==0) return 0;
    
    //zmianna zliczajaca punkty
    int punkty=0;
        //wyczyszczenie konsolii
        Wyczysc2();
        
        //wspolzedne startowe weza
        int x=4,y=4;
        
        //zmienne oznaczajace kierunek poruszania wêza i jego dlugosc
        int prawo=1,lewo=0,gora=0,dol=0,dlugosc=3;
        
        //pobranie i ustawienie wysokosci planszy
        const int wysokosc2=wysokosc;
        
        //pobranie i ustawienie szerokosci planszy
        const int szerokosc2=szerokosc;
        
        // wylosowanie wpsolzednej x, dla punktu do zjedzenia
        int eat1=rand()%wysokosc2;
        // wylosowanie wspolzednej y, dla punktu do zjddzenia
        int eat2=rand()%szerokosc2;
        
        // inicjalizacja tablicy, bêd¹cej plansz¹ gry o konkretnej dlugosci i szerokosci
        int plansza[wysokosc2][szerokosc2];
        
        // inicjalizacja wszystkich punktów na planszy
        for (int h=0;h<wysokosc2;h++) {
            for (int g=0;g<szerokosc2;g++) {
                plansza[h][g]=0;
            }
        }
        
        
        // petla nieskonczona
        for(;;){
        	
        	//sprawdzanie czy wcisnieto jakis klawisz
            if (kbhit()) {
            	
            	//pobranie klawisza
                klawisz2=getch();
                
                //sprawdzanie jaki klawisz wybrano
                switch(klawisz2) {
                	
                	//jesli esc, koniec gry, wywo³anie funkcji GameOver z parametrem punkty, który przechowuje aktualna ilosc punktów
                    case 27:
                        GameOver(punkty);
                        return 0;
                        
                    //w - wskazanie aby waz szedl w gore, ustawienie zmiennej gora na 1, jest to mozliwe tylko wtedy kiedy w¹¿ nie idzie w dó³
                    case 'w':
                        if (dol!=1) {
                            prawo=0;
                            lewo=0;
                            dol=0;
                            gora=1;
                        }
                        break;
                        
                    // s- wskazanie aby waz szedl w dol, ustawienie zmiennej dol na 1, jest to mozliwe tylko wtedy kiedy waz nie idzie w gore    
                    case 's':
                        if (gora!=1) {
                            prawo=0;
                            lewo=0;
                            gora=0;
                            dol=1;
                        }
                        break;
                        
                    // a- wskazanie aby waz szedl w lewo, ustawienie zmiennej lewo na 1, jest to mozliwe tylko wtedy kiedy waz nie idzie w prawo
                    case 'a':
                        if (prawo!=1) {
                            prawo=0;
                            gora=0;
                            dol=0;
                            lewo=1;
                        }
                        break;
                        
                    // d- wskazanie aby waz szedl w prawo, ustawienie zmiennej prawo na 1, jest to mozliwe tylko wtedy kiedy waz nie idzie w lewo
                    case 'd':
                        if (lewo!=1) {
                            lewo=0;
                            gora=0;
                            dol=0;
                            prawo=1;
                        }
                        break;
                }
            }
            
            //wyliczenie gdzie aktualnie znajduje siê w¹¿
            x=x-lewo+prawo;
            y=y-gora+dol;
            
            // zakonczenie gry, kiedy w¹¿, wejdzie w krawêdŸ planszy, wyso³anie funkcji GameOver z parametrem punkty, przechowujacym aktualny stan punktów gracza
            if (y>=wysokosc2 || y<0 || x>=szerokosc2 || x<0 || plansza[y][x]>1) {
                GameOver(punkty);
                
                //zakonczenie dzialania funkcji snake()
                return 0;
            }
            
            //poruszanie wêza po planszy, jesli nie trafi³ na jedzenie
            if (y!=eat1 || x!=eat2) {
                for (int h=0;h<wysokosc2;h++) {
                    for (int g=0;g<szerokosc2;g++) {
                        if (plansza[h][g]>0) {
                            plansza[h][g]--;
                        }
                    }
                }
            } // w przeciwnym wypadku, jesli waz najedzie na punkt do zjedzenia, powieksza sie jego dlugosc, zwieksza sie ilosc punktów
            else {
                dlugosc++;
                punkty++;
                
                //wylosuj nowy punkt, na którym bedzie znajdowac sie punkt do zjedzenia
                do {
                    eat1=rand()%wysokosc2;
                    eat2=rand()%szerokosc2;
                } while(plansza[eat1][eat2]!=0);
            }
            
            // oznaczenie wylosowanego punku na planszy
            plansza[eat1][eat2]=-1;
            
            //wyczyszczenie konsoli
            Wyczysc2();
            
            //wyznaczenie nowej dlugosci weza na planszy
            plansza[y][x]=dlugosc;
            
            
            
            //wyrysowanie planszy z wezem
            
            //wyrysowanie gornej krawedzi
            for (int f=szerokosc2+2;f>0;f--) {
                cout<<char(205);
            }
            cout<<endl;
            
            //wyrysowanie lewej krawedzi
            for (int g=0;g<wysokosc2;g++) {
                cout<<char(186);
                
                for (int h=0;h<szerokosc2;h++) {
                    switch(plansza[g][h]) {
                    	
                    	//pusty punkt
                        case 0:
                            cout<<" ";
                            break;
                            
                        //wyrysowanie punktu do zjedzenia
                        case -1:
                            cout<<char(4);
                            break;
                            
                        //wyrysowanie weza
                        default:
                            SetConsoleTextAttribute(kolor,kolorek);
                            cout<<char(219);
                            SetConsoleTextAttribute(kolor,7);
                            break;
                    }
                }
                //wyrysowanie prawej krawedzi
                cout<<char(186)<<endl;
            }
            
            //wyrysowanie dolnej krawedzi
            for (int f=szerokosc2+2;f>0;f--) {
                cout<<char(205);
            }
            
            //wyswietlenie liczby punktów
            cout<<endl<<"Punkty: "<<punkty;
            
            //wyswietlenie opcji powrotu do menu
            cout<<endl<<"[ESC] - Powrot do MENU"<<endl;
            
            //wyrysowanie linii oddzielajacej
            for (int f=szerokosc2+2;f>0;f--) {
                cout<<char(205);
            }
            
            //wyrysowanie planszy z podaniem poziomu (szybkoœci)
            Sleep(poziom);
        }
}


//########################################################################################################################
//funkcja wywolywana przed funkcja snake(), czyli menu wyboru trudnosci:
bool Trudnosc() {
	
	// wskazanie zaznaczonego poziomu, poczatkowo poziom ³atwy
    zaznaczenie=1;
    sprawdz=1;
    
    // petla while, konczy dzia³anie kiedy uzytkownik wcisnie spacje lub enter, wtedy przechodzi do gry
    while (klawisz2!=13 && klawisz2!=32) {
        Wyczysc2();
        
        //wyrysowanie lini oddzielaj¹cej
        for (int e=0;e<36;e++) cout<<char(205);
        
        cout<<endl<<endl<<"         Poziom trudnosci:"<<endl<<endl;
        
                // sprawdzenie, który z kolorów jest zaznaczony - jest oznaczony innym kolorem
                switch (zaznaczenie) {
                    case 1:
                        SetConsoleTextAttribute(kolor,kolorek);
                        cout<<"              Latwy"<<endl<<endl;
                        SetConsoleTextAttribute(kolor,7);
                        cout<<"              Sredni"<<endl<<endl;
                        cout<<"              Trudny"<<endl<<endl;
                        poziom=200;
                        break;
                    case 2:
                        cout<<"              Latwy"<<endl<<endl;
                        SetConsoleTextAttribute(kolor,kolorek);
                        cout<<"              Sredni"<<endl<<endl;
                        SetConsoleTextAttribute(kolor,7);
                        cout<<"              Trudny"<<endl<<endl;
                        poziom=100;
                        break;
                    case 3:
                        cout<<"              Latwy"<<endl<<endl;
                        cout<<"              Sredni"<<endl<<endl;
                        SetConsoleTextAttribute(kolor,kolorek);
                        cout<<"              Trudny"<<endl<<endl;
                        SetConsoleTextAttribute(kolor,7);
                        poziom=60;
                        break;
                }
            //wyrysowanie lini oddzielaj¹cej
            for (int e=0;e<36;e++) cout<<char(205);
            
            cout<<endl<<"[ESC] - Powrot do MENU"<<endl;
            
            //wyrysowanie lini oddzielaj¹cej
            for (int e=0;e<37;e++) cout<<char(205);
            
            // pobranie klawisza
            klawisz2=getch();
            
            // sprawdzanie wybranego klawisza, i przechodzenie pomiedzy poziomami, jesli wybranoc esc - wyjscie z ustawieñ
            switch(klawisz2) {
                case 'w':if(zaznaczenie>1)zaznaczenie--;break;
                case 's':if(zaznaczenie<3)zaznaczenie++;break;
                case 27: zaznaczenie=1;Wyczysc2();sprawdz=0; return 0;
            }
    }
    zaznaczenie=1;
    return 0;
}
//########################################################################################################################
//funkcja czyszczenia statystyk:
void wyczysc(){
	
	// strumieñ wyjœcia do pliku (zapisywanie)
    ofstream plik("Statystyki.txt");
    
    //przejscie po wszystkich wierszach pliku i wyczyszczenie ich
    for (int i=0;i<10;i++) {
        plik<<"---------------"<<endl;
        plik<<0<<endl;}
        
    //zamkniecie pliku
    plik.close();
}


//########################################################################################################################
//funkcja czyszczenia okna konsoli:
void Wyczysc2() {
   COORD coordScreen = {0,0};
   DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   DWORD dwConSize;
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   GetConsoleScreenBufferInfo(hConsole, &csbi);
   dwConSize = csbi.dwSize.X*csbi.dwSize.Y;
   FillConsoleOutputCharacter(hConsole,(TCHAR)' ',dwConSize,coordScreen,&cCharsWritten);
   GetConsoleScreenBufferInfo(hConsole,&csbi);
   FillConsoleOutputAttribute(hConsole,csbi.wAttributes,dwConSize,coordScreen,&cCharsWritten);
   SetConsoleCursorPosition(hConsole,coordScreen);
}

//########################################################################################################################
//funkcja uruchamiana po przegranej lub po zakonczeniu snake():
bool GameOver(int pkt) {
	
	//deklaracja nowycj zmiennych
    int klawisz3;
    int zap=11;
    string nazwa;
    statystyki tablica[10];
    
    //czyszczeni konsoli
    Wyczysc2();
    
    //wyrysowanie linii oddzielajacej
    for (int e=0;e<36;e++) cout<<char(205);
    cout<<endl<<"Liczba uzyskanych pkt.:"<<pkt<<endl;
    
    //wyryowanie linii oddzielajacej
    for (int e=0;e<36;e++) cout<<char(205);
    
    //wpisanie nazwy uzytkownika
    cout<<endl<<"Podaj swoj nick: ";
    cin>>nazwa;
    
    //wczytanie pliku statystyki
    ifstream plik ("statystyki.txt");
    
    //odczytanie informacji o uzytkowniku i liczbie puntków, funkcja eof sprawdza czy wskaŸnik pliku znajduje siê na koñcu pliku
    for(int l=0;!plik.eof() || l<10;l++) {
        plik>>tablica[l].nick;
        plik>>tablica[l].liczbapkt;
    }
    // zamkniecie pliku
    plik.close();
    
    //sprawdzanie w jakim miejscu dopisac nowego uzytkownika do statystyk
    for(int l=0;l<10;l++) {
        if (tablica[l].liczbapkt<pkt) {
            zap=l;
            break;
        }
    }
    if (zap==11) {
        Wyczysc2();
        return 0;
        }
        
    //otworzenie pliku w celu zaisania nowego uzytkownika
    ofstream pliczek ("statystyki.txt");
    
    // dopisanie uzytkownika do pliku w odnowniedim miejscu
    for (int l=0;l<zap;l++) {
        pliczek<<tablica[l].nick<<endl;
        pliczek<<tablica[l].liczbapkt<<endl;
    }
    pliczek<<nazwa<<endl;
    pliczek<<pkt<<endl;
    for (int l=zap;l<9;l++) {
        pliczek<<tablica[l].nick<<endl;
        pliczek<<tablica[l].liczbapkt<<endl;
    }
    
    //zamkniecie pliku
    pliczek.close();
    Wyczysc2();
}
