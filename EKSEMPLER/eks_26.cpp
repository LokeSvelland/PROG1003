/**
 *   Programeksempel nr 26 - St�rre programeksempel.
 *
 *   Eksemplet viser bruken av sv�rt mye av det TOTALE pensumet i emnet.
 *   Bl.a vises:  pekere, objekter, arv, virtueller, filh�ndtering,
 *                string, lambda-funksjoner, og fra STL:
 *                <vector>, <queue>, <list> og <map>, samt <algorithm>.
 *   Sammen med EKS_28.CPP og EKS_29.CPP vises NIV�ET p� en eksamensoppgave
 *   (men dette eksemplet er i OMFANG st�rre).
 *
 *   Programmet:
 *     - h�ndterer objekter av typene 'Alpinist' og 'Snowboarder'
 *     - inneholder en heisk� (queue), selve skiheisen (queue),
 *       gr�nn l�ype (map) og r�d l�ype (list)
 *     - lar objekter flytte seg mellom disse fire ulike containerne
 *     - skriver ut innholdet i de fire containerne
 *     - lar brukeren:   - opprette nye objekter
 *                       - skrive detaljerte data om ETT objekt
 *                       - slette objekter
 *                       - (endre dataene i ETT objekt)
 *     - leser fra og skriver ALLE 4x containerne til fil
 *
 *   @file     EKS_26.CPP
 *   @author   Frode Haug, NTNU
 */

#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <iomanip>                 //  setw
#include <string>                  //  string
#include <vector>                  //  vector    |
#include <queue>                   //  queue     | (stack det eneste av l�rte
#include <list>                    //  list      | containere som IKKE brukes)
#include <map>                     //  map       |
#include <algorithm>               //  algorithm
#include "LesData2.h"              //  Verkt�ykasse for lesing av diverse data
using namespace std;


/**
 *  Korttype (med dagskort, helge-/weekendkort og �rskort).
 */
enum KortType  {  Dag,  Helg,  Aar };


/**
 *  Operasjon (med � SE en kj�rers DETALJERTE data eller � ENDRE dataene).
 */
enum Operasjon {  Detaljer, Endre  };


//  NB:  I hele eksemplet er det brukt 'G' og 'R' for gr�nn og r�d l�ype.
//       Dette kunne selvsagt, og like naturlig/bra, v�rt erstattet av 'enum'.


/**
 *  Kj�rer (med unikt nummer/ID, navn, korttype og kj�rte gr�nne/r�de l�yper).
 */
class Kjorer {
  private:
      int       nr;
      string    navn;
      KortType  kort;
      vector <char> loyperKjort;

  public:
      Kjorer() { nr = 0; kort = Dag; }    //  Denne constructoren brukes ikke.
      Kjorer(const int nr);
      Kjorer(ifstream & inn);
      virtual ~Kjorer() {  }    //  Tom destructor. Ikke noe � si 'delete' om.

                           //  'hentID' M� LAGES I ALLE PROGRAM DER OBJEKTER
                           //   LIGGER I CONTAINERNE <map> OG/ELLER <list> !!!
                           //   DENNE RETURNERER KUN KEYEN/DET OBJEKTET SKAL
                           //   SORTERES ETTER:  EN 'int' ELLER EN 'string'.
      int   hentID()    {    return nr;    }
      void  registrerLoype(const char loype);
      virtual void endreData();
      virtual void lesData();
      virtual void skrivData() const;
      virtual void skrivDetaljer() const;
      virtual void skrivTilFil(ofstream & ut) const;
};


/**
 *  Alpinist (med om har twintip ski eller ei, og tightsdress eller ei).
 */
class Alpinist : public Kjorer {
  private:
    bool twinTipSki,
         tightsDress;
  public:
    Alpinist() { twinTipSki = tightsDress = false; }      //  Brukes ikke her.
    Alpinist(const int nr);
    Alpinist(ifstream & inn);
    virtual ~Alpinist() {  }    //  Tom destructor. Ikke noe � si 'delete' om.
    virtual void endreData();
    virtual void lesData();
    virtual void skrivData() const;
    virtual void skrivDetaljer() const;
    virtual void skrivTilFil(ofstream & ut) const;
};


/**
 *  Snowboarder (med om har saggebukse eller ei, og m�rk hjelm eller ei).
 */
class Snowboarder : public Kjorer {
  private:
    bool saggeBukse,
         morkHjelm;
  public:
    Snowboarder() {  saggeBukse = morkHjelm = false; }    //  Brukes ikke her.
    Snowboarder(const int nr);
    Snowboarder(ifstream & inn);
    virtual ~Snowboarder() {  }  // Tom destructor. Ikke noe � si 'delete' om.
    virtual void endreData();
    virtual void lesData();
    virtual void skrivData() const;
    virtual void skrivDetaljer() const;
    virtual void skrivTilFil(ofstream & ut) const;
};


void detaljerEllerEndre(const Operasjon operasjon);
Kjorer* finnKjorer(const int nr, char & loype);
void lesFraFil();
void nyKjorer();
void skrivGronn();
void skrivKo(const string & s, queue <Kjorer*> ko);
void skrivMeny();
void skrivQueueTilFil(queue <Kjorer*> ko, ofstream & ut);
void skrivRod();
void skrivTilFil();
void slettAlleData();
void slette();
void tilHeisen();
void tilHeisKo();
void tilLoype(const char loype);


queue <Kjorer*> gHeisKo;       ///<  De som st�r i heis-k�.
queue <Kjorer*> gHeis;         ///<  De som er (p� vei opp) i heisen.
list  <Kjorer*> gRod;          ///<  De som kj�rer r�d l�ype.
map   <int, Kjorer*> gGronn;   ///<  De som kj�rer gr�nn l�ype.
int   gSisteNummer;            ///<  Nummer for siste registrerte kj�rer.


/**
 *  Hovedprogrammet:
 */
int main()  {
    char kommando;

    lesFraFil();

    skrivMeny();
    kommando = lesChar("Kommando");

    while (kommando != 'Q') {
        switch (kommando) {
          case 'K':    tilHeisKo();                      break;
          case 'H':    tilHeisen();                      break;
          case 'G': case 'R':  tilLoype(kommando);       break;
          case 'N':    nyKjorer();                       break;
          case 'D':    detaljerEllerEndre(Detaljer);     break;
          case 'E':    detaljerEllerEndre(Endre);        break;
          case 'S':    slette();                         break;
          case '1':    skrivKo("heisk�", gHeisKo);       break;
          case '2':    skrivKo("heisen", gHeis);         break;
          case '3':    skrivGronn();                     break;
          case '4':    skrivRod();                       break;
          default:     skrivMeny();                      break;
        }
        kommando = lesChar("Kommando");
    }

    skrivTilFil();

    slettAlleData();

    cout << "\n\n";
    return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Setter eget nummer/ID (ut fra parameters verdi).
 *
 *  @param   nr  - kj�rerens eget nummer/ID
 */
Kjorer::Kjorer(const int nr) {
    kort = Dag;
    this->nr = nr;                  //  M� bruke 'this' om egen verdi, n�r
}                                   //    parameteren heter EKSAKT det samme.


/**
 *  Leser ALLE egne datamedlemmer inn fra fil.
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Kjorer::Kjorer(ifstream & inn) {
    char tegn;
    inn >> nr >> tegn;                   //  Leser nummer/ID og 'D/H/A'.
    inn.ignore();                        //  Forkaster ' ' f�r navnet/tekst.
    switch (tegn)  {                     //  Konverterer bokstav til enum:
      case 'D':  kort = Dag;   break;
      case 'H':  kort = Helg;  break;
      case 'A':  kort = Aar;   break;
    }
    getline(inn, navn);                  //  Leser eget navn.
}


/**
 *  Tilbyr brukeren � endre p� aktuelle datamedlemmer.
 */
void Kjorer::endreData() {
    cout << "\n\tEndre datamedlemmer:  IKKE IMPLEMENTERT ENN�\n\n";

    //  LATER
}


/**
 *  Leser inn egne datamedlemmer fra brukeren/tastaturet.
 */
void Kjorer::lesData() {
    char tegn;

    cout << "\tNavn:     ";                //  Leser eget navn:
    getline(cin, navn);

    do {                                   //  Leser ALLTID 'D/H/A':
        tegn = lesChar("\tKorttype (D(ag), H(elg), A(ar)");
    } while (tegn != 'D'  &&  tegn != 'H'  &&  tegn != 'A');

    switch (tegn) {                        //  Konverterer bokstav til enum:
      case 'D':  kort = Dag;    break;
      case 'H':  kort = Helg;   break;
      case 'A':  kort = Aar;    break;
    }
}


/**
 *  Legger til 'G' eller 'A' bakerst i vectoren 'loyperkjort'.
 *
 *  @param   loype  - L�ypen kj�rt ('G' eller 'R')
 */
void Kjorer::registrerLoype(const char loype) {
    loyperKjort.push_back(loype);        //  Legger ny inn bakerst i vectoren.
}


/**
 *  Skriver ut ALLE egne data p� skjermen.
 */
void Kjorer::skrivData() const  {                 //  Skriver nr/ID og navn:
    cout << setw(10) << nr << ":  " << navn << ",  ";
    switch (kort) {                               //  Skriver enum som tekst:
      case Dag:   cout << "dags";    break;
      case Helg:  cout << "helge";   break;
      case Aar:   cout << "�rs";     break;
    }                                             //  Antall l�ypeturer:
    cout << "kort,  antall turer: " << loyperKjort.size() << '\n';
}


/**
 *  Teller opp og skriver antall turer i gr�nn/r�d l�ype, samt turrekkef�lgen.
 */
void Kjorer::skrivDetaljer() const {
    int antG = 0, antR = 0;            //  Nullstiller antall turer i l�ypene.

    cout << "\tL�yper kj�rt i dag:\n\t";
    for (const auto val : loyperKjort) {      //  G�r gjennom alle turene:
        if (val == 'G') antG++;  else antR++; //  Teller opp antall i G/R.
        cout << ' ' << val;                   //  Skriver 'G' eller 'R'.
    }
    cout << "\n\tAlts�: " << antG << " gang(er) i GR�NN, og "
                          << antR << " gang(er) i R�D l�ype.\n\n";
}


/**
 *  Skriver egne data til fil (untatt 'loyperKjort'!).
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 */
void Kjorer::skrivTilFil(ofstream & ut) const {
    ut << ' ' << nr << ' ';                //  Skriver ' ', eget nr/ID og ' '.
    switch (kort) {                        //  Konverterer og skriver
      case Dag:   ut << 'D';    break;     //    enum som bokstav:
      case Helg:  ut << 'H';    break;
      case Aar:   ut << 'A';    break;
    }
    ut << ' ' << navn << '\n';             //  Skriver ' ' og navnet.
}


// ---------------------------------------------------------------------------

/**
 *  Tom constructor, som bare sender parameter til baseklassen.
 *
 *  @param   nr  - Kj�rerens nummer/ID, som sendes til baseklassen
 */
Alpinist::Alpinist(const int nr) : Kjorer(nr) {
    twinTipSki = tightsDress = false;
}


/**
 *  Leser ALLE egne datamedlemmer inn fra fil (etter at baseklassen har lest).
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Alpinist::Alpinist(ifstream & inn) : Kjorer(inn)  {
    char tegn;
    inn >> tegn;                      //  Leser 2x '+/-', og gj�r om til bool:
    twinTipSki = (tegn == '+');
    inn >> tegn;    inn.ignore();
    tightsDress = (tegn == '+');
}


/**
 *  Tilbyr brukeren � endre p� aktuelle datamedlemmer.
 *
 *  @see   Kjorer::endreData()
 */
void Alpinist::endreData() {
    Kjorer::endreData();                         //  Baseklassens data endres.

    //  LATER:   Endre datamedlemmer - IKKE IMPLEMENTERT ENN�.
}


/**
 *  Leser inn egne datamedlemmer fra brukeren/tastaturet.
 *
 *  @see   Kjorer::lesData()
 */
void Alpinist::lesData() {
    Kjorer::lesData();                            //  Baseklassens data leses.
    twinTipSki = (lesChar("\tTwintip ski?  (j/N)") == 'J');    //  Egne leses:
    tightsDress = (lesChar("\tTights dress? (j/N)") == 'J');
}


/**
 *  Skriver ut ALLE egne data p� skjermen.
 *
 *  @see   Kjorer::skrivData()
 */
void Alpinist::skrivData() const  {
    Kjorer::skrivData();                    //  Baseklassens data skrives.
    cout << "\t\tAlpinist "                 //  Egne booler skrives som tekst:
         << (twinTipSki ? "med " : "uten ") << "Twintip ski og "
         << (tightsDress ? "med " : "uten ") << "Tightsdress\n";
}


/**
 *  Skriver ABSOLUTT ALLE datamedlemmer.
 *
 *  @see   skrivData()
 *  @see   Kjorer::skrivDetaljer()
 */
void Alpinist::skrivDetaljer() const {
    skrivData();                     //  Alle andre datadatamedlemmer skrives.
    Kjorer::skrivDetaljer();         //  Baseklassens detaljer skrives.
}


/**
 *  Skriver egne og baseklassens data til fil.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 *  @see     Kjorer::skrivTilFil(...)
 */
void Alpinist::skrivTilFil(ofstream & ut) const {
    ut << 'A';                              //  Subklasse av typen 'A'.
    Kjorer::skrivTilFil(ut);                //  Baseklassens data skrives.
                                            //  Egne booler skrives som '+/-':
   ut << (twinTipSki ? "+" : "-") << ' ' << (tightsDress ? "+" : "-") << '\n';
}


// ---------------------------------------------------------------------------

/**
 *  Tom constructor, som bare sender parameter til baseklassen.
 *
 *  @param   nr  - Kj�rerens nummer/ID, som sendes til baseklassen
 */
Snowboarder::Snowboarder(const int nr) : Kjorer(nr) {
    saggeBukse = morkHjelm = false;
}


/**
 *  Leser ALLE egne datamedlemmer inn fra fil (etter at baseklassen har lest).
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Snowboarder::Snowboarder(ifstream & inn) : Kjorer(inn)  {
    char tegn;
    inn >> tegn;                      //  Leser 2x '+/-', og gj�r om til bool:
    saggeBukse = (tegn == '+');
    inn >> tegn;    inn.ignore();
    morkHjelm = (tegn == '+');
}


/**
 *  Tilbyr brukeren � endre p� aktuelle datamedlemmer.
 *
 *  @see   Kjorer::endreData()
 */
void Snowboarder::endreData() {
    Kjorer::endreData();                         //  Baseklassens data endres.

    //  LATER:   Endre datamedlemmer - IKKE IMPLEMENTERT ENN�.
}


/**
 *  Leser inn egne datamedlemmer fra brukeren/tastaturet.
 *
 *  @see   Kjorer::lesData()
 */
void Snowboarder::lesData() {
    Kjorer::lesData();                            //  Baseklassens data leses.
    saggeBukse = (lesChar("\tSaggebukse?  (J/n)") != 'N');     //  Egne leses:
    morkHjelm  = (lesChar("\tM�rk hjelm?  (J/n)") != 'N');
}


/**
 *  Skriver ut ALLE egne data p� skjermen.
 *
 *  @see   Kjorer::skrivData()
 */
void Snowboarder::skrivData() const  {
    Kjorer::skrivData();                    //  Baseklassens data skrives.
    cout << "\t\tSnowboarder "              //  Egne booler skrives som tekst:
        << (saggeBukse ? "med " : "uten ") << "Saggebukse og "
        << (morkHjelm  ? "med " : "uten ") << "M�rk hjelm\n";
}


/**
 *  Skriver ABSOLUTT ALLE datamedlemmer.
 *
 *  @see   skrivData()
 *  @see   Kjorer::skrivDetaljer()
 */
void Snowboarder::skrivDetaljer() const {
    skrivData();                     //  Alle andre datadatamedlemmer skrives.
    Kjorer::skrivDetaljer();         //  Baseklassens detaljer skrives.
}


/**
 *  Skriver egne og baseklassens data til fil.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 *  @see     Kjorer::skrivTilFil(...)
 */
void Snowboarder::skrivTilFil(ofstream & ut) const {
    ut << 'S';                             //  Subklasse av typen 'S'.
    Kjorer::skrivTilFil(ut);               //  Baseklassens data skrives.
                                           //  Egne booler skrives som '+/-':
    ut << (saggeBukse ? "+" : "-") << ' ' << (morkHjelm ? "+" : "-") << '\n';

}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Skriver ALLE detaljer ELLER endrer data om EN kj�rer.
 *
 *  @param   operasjon  - 'Detaljer' eller 'Endre' - etter hva som skal gj�res
 *  @see     finnKjorer(...)
 *  @see     virtual Kjorer::skrivDetaljer()
 *  @see     virtual Kjorer::endreData()
 */
void detaljerEllerEndre(const Operasjon operasjon) {
    Kjorer* kjorer = nullptr;    //  Peker til en Kjorer INNI EN CONTAINER !!!
    char loype;                  //  M� v�re med som parameter - brukes ikke.
    int nr;                      //  �nsket kj�rernummer � se/endre.

    if (!gGronn.empty() || !gRod.empty()) {    //  Kj�rer(e) i MINST en l�ype:
        nr = lesInt("\tNr", 1, gSisteNummer);  //  Leser �nsket kj�rernummer.

        kjorer = finnKjorer(nr, loype);        //  Pr�ver � finne kj�reren i
                                               //  en av l�ypene.
        if (kjorer) {                          //  Kj�reren funnet:
            if (operasjon == Detaljer)
                kjorer->skrivDetaljer();       //  Vil se ALLE datadetaljer.
            else
                kjorer->endreData();           //  Vil endre datamedlemmer.
        } else
          cout << "\n\tUkjent nummer i begge l�ypene!\n\n";
    } else
        cout << "\n\tBegge l�ypene er tomme!\n\n";
}


/**
 *  Leter etter (og evt. returnerer peker til) en gitt kj�rer i en av l�ypene.
 *
 *  NB: LETER IKKE I DE 2x K�ENE, DA FOR TUKLETE (OG HELLER IKKE MENINGEN/
 *      POENGET MED EN QUEUE). EI HELLER ER DA ITERATORER TILGJENGELIGE.
 *
 *  @param   nr     -  Kj�rernummer det letes etter
 *  @param   loype  -  Evt. funnet i 'G'r�nn eller 'R'�d l�ype (REF.OVERF�RT)
 *  @return  Peker til funnet 'Kjorer' INNI EN AV CONTAINERNE,  evt. 'nullptr'
 *  @see     Kjorer::hentID()
 */
Kjorer* finnKjorer(const int nr, char & loype) {

    auto it1 = gGronn.find(nr);     //  Pr�ver � finne vha. medlemsfunksjon.
    if (it1 != gGronn.end()) {      //  Funn i GR�NN l�ype (<map>):
        loype = 'G';                //  Setter om hvor funnet.
        return (it1->second);       //  Returnerer peker til 'Kjorer'.
    }                               //  NB:  En 'Kjorer' er tilpekt av
                                    //       'it1->second' !!!

                                    //  Litt mer 'manuell' leting i en <list>
                                    //   vha. iteratorer og lambda-funksjon:
                                    //  NB:  Bruken av 'hentID()' !!!
    auto it2 = find_if(gRod.begin(), gRod.end(),
                   [nr] (const auto & val) { return(val->hentID() == nr); } );
    if (it2 != gRod.end()) {        //  Funn i R�D l�ype (<list>):
        loype = 'R';                //  Setter om hvor funnet.
        return *it2;                //  Retunerer peker til 'Kjorer'.
    }                               //  NB:  'it2' ER SELV EN PEKER.
                                    //       Derfor ville 'return it2' ha v�rt
                                    //       retur av en peker til en peker.
                                    //       'return *it2' blir derfor korrekt
                                    //       return av en peker til 'Kjorer'.

    loype = '-';                    //  Ikke funnet:
    return nullptr;
}


/**
 *  Leser ALLE kj�rere inn fra fil og ALLE legges rett inn i heisk�en.
 */
void lesFraFil() {
    ifstream  innfil("EKS_26.DTA");                 //  �pner aktuell fil.
    char kjorerType;                                //  'A' eller 'S'.

    if (innfil) {                                   //  Filen funnet:
        cout << "\n\nLeser fra filen 'EKS_26.DTA' .....\n\n";
        innfil >> gSisteNummer;   innfil.ignore();  //  Leser siste nr.brukt.
        innfil >> kjorerType;                       //  Pr�ver � lese 1.felt.
        while (!innfil.eof()) {       //  Enn� ikke slutt p� filen:
            switch (kjorerType) {     //  Lager og legger inn aktuell kj�rer:
              case 'A': gHeisKo.push(new Alpinist(innfil));            break;
              case 'S': gHeisKo.push(new Snowboarder(innfil));         break;
              default:  cout << "\n\tUlovlig kj�rertype p� filen!\n";  break;
            }
            innfil >> kjorerType;                   //  Pr�ver � lese 1.felt.
        }
        innfil.close();                             //  Lukker manuelt filen.
    } else
      cout << "\n\nFant ikke filen 'EKS_26.DTA'!\n\n";
}


/**
 *  Legger/setter inn en ny aktuell kj�rer i heisk�en.
 *
 *  @see   virtual Kjorer::lesData()
 */
void nyKjorer() {
    Kjorer* nyKjorer = nullptr;              //  Peker til nye aktuell kj�rer.
    char kjorerType;                         //  'A' eller 'S'.
                                //  Teller opp og skriver nytt unikt kj�rernr:
    cout << "\tNy kj�rer har nr." << ++gSisteNummer << ":\n";

    do {                                     //  Leser ALLTID 'A' eller 'S':
        kjorerType = lesChar("\tA(lpinist) eller S(nowboarder)");
    } while (kjorerType != 'A'  &&  kjorerType != 'S');

    switch (kjorerType) {                    //  Lager en ny aktuell kj�rer:
       case 'A':  nyKjorer = new Alpinist(gSisteNummer);     break;
       case 'S':  nyKjorer = new Snowboarder(gSisteNummer);  break;
    }

    nyKjorer->lesData();                   //  Leser kj�rerens datamedlemmer.
    gHeisKo.push(nyKjorer);                //  Legger inn den nye kj�reren.
}


/**
 *  Skriver ALLE kj�rerne i den GR�NNE l�ypen.
 *
 *  @see   virtual Kjorer::skrivData()
 */
void skrivGronn() {
    cout << "\nF�lgende " << gGronn.size() << " kj�rere er i GR�NN l�ype:\n";
    for (const auto & val : gGronn)        //  Range-based for-l�kke:
        (val.second)->skrivData();         //  Skriver kj�rerens data.
                                           //  'val.second' er en PEKER!
//  Alternativt vha. iterator, 'for_each(...)' og lambda-funksjon:
//    for_each(gGronn.begin(), gGronn.end(),
//                    [] (const auto & val) { (val.second)->skrivData();  } );

    cout << "\n\n";
}


/**
 *  Skriver HELE en k�s innhold.
 *
 *  @param   s  - Ledetekst i utskrift
 *  @param   ko - queue-container med Kjorer-pekere (lagret i en 'deque')
 *                NB: F�r KOPI av PEKERNE til objektene i k�en !!!
 *                    Men de TILPEKTE OBJEKTENE er de SAMME !!!
 *                    Hadde det v�rt brukt '&', s� hadde original-pekerne
 *                    v�rt brukt - og blitt borte (n�r det sies 'pop') !!!
 *  @see    virtual Kjorer::skrivData()
 */
void skrivKo(const string & s, queue <Kjorer*> ko) {
    cout << "\nF�lgende " << ko.size() << " kj�rere er i " << s << ":\n";
    while (!ko.empty()) {               //  Enn� elementer igjen:
        (ko.front())->skrivData();      //  Viser/skriver den 1.TILPEKTE.
        ko.pop();                       //  Tar ut/fjerner den 1.PEKEREN.
    }
    cout << "\n\n";
}


/**
 *  Skriver programmets menyvalg/muligheter p� skjermen.
 */
void skrivMeny() {
    cout << "\nF�lgende kommandoer er tilgjengelig:\n"
         << "\tK - inn i heisK�\n"
         << "\tH - fra heisk� til Heisen\n"
         << "\tG - fra heisen til Gr�nn l�ype\n"
         << "\tR - fra heisen til R�d l�ype\n\n"
         << "\tN - Ny kj�rer\n"
         << "\tD - Detaljer om EN kj�rer  (KUN mulig n�r er i en l�ype)\n"
         << "\tE - Endre en kj�rer        (KUN mulig n�r er i en l�ype)\n"
         << "\tS - Slett/fjern en kj�rer  (KUN mulig n�r er i en l�ype)\n\n"
         << "\t1 - skriv HEISK�\n"
         << "\t2 - skriv HEISEN\n"
         << "\t3 - skriv GR�NN l�ype\n"
         << "\t4 - skriv R�D l�ype\n\n"
         << "\tQ - Quit / avslutt\n\n";
}


/**
 *  Skriver HELE EN medsendt k� til angitt fil.
 *
 *  @param   ko - queue-container med Kjorer-pekere (lagret i en 'deque').
 *                Se ellers NB-kommentaren ifm 'ko' i 'skrivKo'-funksjonen.
 *  @param   ut - Filobjektet k�en skal skrives til
 *  @see     virtual Kjorer::skrivTilFil(...)
 */
void skrivQueueTilFil(queue <Kjorer*> ko, ofstream & ut) {
    while (!ko.empty()) {               //  Enn� elementer igjen:
        (ko.front())->skrivTilFil(ut);  //  Skriver elementet til fil.
        ko.pop();                       //  Tar ut/fjerner den 1.PEKEREN.
    }
}


/**
 *  Skriver ALLE kj�rerne i den R�DE l�ypen.
 *
 *  @see   virtual Kjorer::skrivData()
 */
void skrivRod() {
    cout << "\nF�lgende " << gRod.size() << " kj�rere er i R�D l�ype:\n";
    for (const auto & val : gRod)             //  Range-based for-l�kke:
        val->skrivData();                     //  Skriver kj�rerens data.
                                              //  'val' er en PEKER!
//  Alternativt vha. iterator, 'for_each(...)' og lambda-funksjon:
//    for_each(gRod.begin(), gRod.end(),
//                           [] (const auto & val) { val->skrivData();  } );
    cout << "\n\n";
}


/**
 *  Skriver ALLE 4x containernes innhold/kj�rere til EN OG SAMME fil.
 *
 *  @see    skrivQueueTilFil(...)
 *  @see    virtual Kjorer::skrivTilFil(...)
 */
void skrivTilFil() {
    ofstream utfil("EKS_26.DT2");                 //  �pner aktuell fil.
                                                  //  NB:  'DT2' !
    cout << "\nSkriver til filen 'EKS_26.DT2' .....\n\n";

    utfil << gSisteNummer << '\n';                //  Skriver siste nr. brukt.

    skrivQueueTilFil(gHeis, utfil);               //  Heisens innhold.

    skrivQueueTilFil(gHeisKo, utfil);             //  Heisk�ens innhold.

    for_each(gGronn.begin(), gGronn.end(),        //  Gr�nn l�ypes innhold:
        [&utfil] (const auto & val) {  (val.second)->skrivTilFil(utfil);  } );

    for_each(gRod.begin(), gRod.end(),            //  R�d l�ypes innhold:
        [&utfil] (const auto & val) {  val->skrivTilFil(utfil);  } );

    utfil.close();                                //  Lukker filen manuelt.

//  NB: NB:  ALLE ELEMENTENE ER FORTSATT UBER�RT I ALLE CONTAINERNE !!!

//  NB:  Burde EGENTLIG IKKE ha skrevet til fil de som bare har hatt dagskort,
//       eller om det er s�ndag og kj�reren har hatt helgekort.
//       Men, fin �velse � utvide koden (flere steder) med dette ......
}


/**
 *  Sletter ALLE elementene og TILPEKTE kj�rere i ALLE containerne.
 *
 *  @see   virtual Kjorer::skrivTilFil(...)
 */
void slettAlleData() {
                   //  Alle de syv innrykkede kodelinjene (til kolonne nr.25)
                   //  er "overfl�dige", s� lenge 'skrivTilFil' (rett ovenfor)
                   //  har gjort dette allerede.
                   //  Ellers m�tte/kunne filskriving ha v�rt gjort p� denne
                   //  m�ten, samtidig som ALT i ALLE containerne slettes.
                        ofstream utfil("EKS_26.DT3");
                        cout << "\nSkriver til filen 'EKS_26.DT3' .....\n\n";
                        utfil << gSisteNummer << '\n';

                                              //  HEISK�EN:
    while (!gHeisKo.empty()) {                //  Enn� elementer igjen:
                        (gHeisKo.front())->skrivTilFil(utfil);
        delete gHeisKo.front();               //  Sletter 1.TILPEKTE 'Kjorer'.
        gHeisKo.pop();                        //  Fjerner den 1.PEKEREN.
    }
    cout << "\tAntall elementer i HEISK�EN:     " << gHeisKo.size() << '\n';

                                              //  HEISEN:
    while (!gHeis.empty()) {                  //  Enn� elementer igjen:
                        (gHeis.front())->skrivTilFil(utfil);
        delete gHeis.front();                 //  Sletter 1.TILPEKTE 'Kjorer'.
        gHeis.pop();                          //  Fjerner den 1.PEKEREN.
    }
    cout << "\tAntall elementer i HEISEN:       " << gHeis.size() << '\n';


    while (!gGronn.empty()) {                 //  GR�NN L�YPE:
        Kjorer* it = (gGronn.begin())->second;  //  PEKER til 1.KJORER.
                        it->skrivTilFil(utfil);
        delete it;                            //  Sletter 1.TILPEKTE 'Kjorer'.
        gGronn.erase(gGronn.begin());         //  Sletter PARET key og PEKER.
//  Alternativt for de fire siste linjene ovenfor:
//      auto it = gGronn.begin();
//                        (it->second)->skrivTilFil(utfil);
//      delete (it->second);                  //  Sletter TILPEKTE 'Kjorer'.
//      gGronn.erase(it);                     //  Sletter PARET key og PEKER.
    }
    cout << "\tAntall elementer i GR�NN L�YPE:  " << gGronn.size() << '\n';

                                              //  R�D L�YPE:
    while (!gRod.empty()) {                   //  Enn� elementer igjen:
                        (gRod.front())->skrivTilFil(utfil);
        delete gRod.front();                  //  Sletter 1.TILPEKTE 'Kjorer'.
        gRod.pop_front();                     //  Fjerner den 1.PEKEREN.
    }
    cout << "\tAntall elementer i R�D L�YPE:    " << gRod.size() << '\n';
}


/**
 *  Sletter (om mulig) en �nsket nummerangitt kj�rer (n�r er i en av l�ypene).
 *
 *  @see   finnKjorer(...)
 *  @see   Kjorer::hentID()
 *  @see   virtual Kjorer:skrivData()
 */
void slette() {
//  NB: Denne funksjonen er MYE LIK 'tilHeisKo'. S�, de kunne til en viss grad
//      ha v�rt laget p� samme m�te som 'detaljerEllerEndre'. Men, det hadde
//      blitt s�pass mange 'if' og 'else' for � skille p� meldinger og hva
//      som skal gj�res, at derfor er det laget to ulike funksjoner.

    Kjorer* kjorer = nullptr; //  Peker til en Kjorer INNI EN CONTAINER !!!
    char loype;               //  Hvilken l�ype funnet i (evt. 'G' eller 'R').
    int nr;                   //  �nsket kj�rernummer � slette.

    if (!gGronn.empty() || !gRod.empty()) {       //  Kj�rer i minst EN l�ype:
       nr = lesInt("\tSlette nr", 0, gSisteNummer);   //  �nsket nr. � slette.

       if (nr) {                            // 'nr' er IKKE 0 (null):
          kjorer = finnKjorer(nr, loype);   //  Pr�ver � finne kj�reren i
                                            //    en av l�ypene.
          if (kjorer) {                     //  Kj�reren funnet:
             if (loype == 'G')              //  Funnet i GR�NN l�ype:
                gGronn.erase(nr);           //  Sletter PARET key og PEKER.
             else if (loype == 'R') {       //  Er i R�D l�ype:
                                            //  M� mer 'manuelt' finne:
                auto it = find_if(gRod.begin(), gRod.end(),
                     [nr](const auto & val) { return(val->hentID() == nr); });
                if (it != gRod.end())       //  Fortsatt funn:
                   gRod.erase(it);          //  Sletter SELVE PEKEREN.
             }
             cout << "\tSlettet er alts�:\n";
             kjorer->skrivData();           //  Skriver den som slettes.
             delete kjorer;          //  N� F�RST SLETTES SELVE KJ�REREN !!!
                                     //  NB:  Hadde det v�rt gjort tidligere
                                     //       (sammen med 'skrivData'), f.eks.
                                     //       rett etter 'if (kjorer)', s�
                                     //       ville setningen 'val->hentID()'
                                     //       ha blitt meningsl�s.
          } else
            cout << "\n\tUkjent nummer i begge l�ypene!\n\n";
       } else
         cout << "\n\tOK - ingen slettes.\n\n";
    } else
      cout << "\n\tBegge l�ypene er tomme!\n\n";
}


/**
 *  Flytter (om mulig) 1.kj�rer i heisk�en til inn bakerst/nederst i heisen.
 *
 *  @see   virtual Kjorer::skrivData()
 */
void tilHeisen() {
  if (!gHeisKo.empty()) {                   //  Noen i heisk�en:
      (gHeisKo.front())->skrivData();       //  Skriver den f�rste sine data.
    cout << "\n\tflyttes fra heisk�en og inn (nederst/bakerst) i heisen.\n\n";
      gHeis.push(gHeisKo.front());          //  KOPIERER pekeren til 'gHeis'.
      gHeisKo.pop();                        //  Sletter 1.pekeren i 'gHeisKo'.
  }  else
      cout << "\n\tHeisk�en er tom, s� ingen � sette inn i heisen!\n\n";
}


/**
 *  Flytter (om mulig) en kj�rer fra en av l�ypene til bakerst i heisk�en.
 *
 *  @see   finnKjorer(...)
 *  @see   virtual Kjorer::skrivData()
 *  @see   Kjorer::hentID()
 */
void tilHeisKo()  {
    Kjorer* kjorer = nullptr;    //  Kj�reren evt. funnet i en av l�ypene.
    char loype;                  //  Evt. funnet i 'G'r�nn eller 'R'�d l�ype.
    int nr;                      //  �nsket kj�rernummer fra l�ype til heisk�.

    if (!gGronn.empty()  ||  !gRod.empty()) {     //  Kj�rer i minst EN l�ype:
        cout << "\tFlytte fra en l�ype til heisk�:\n";
        nr = lesInt("\tNr", 1, gSisteNummer);     //  �nsket nr. � flytte.

        kjorer = finnKjorer(nr, loype);        //  Pr�ver � finne kj�reren i
                                               //    en av l�ypene.
        if (kjorer) {                          //  Kj�reren funnet:
            kjorer->skrivData();               //  Skriver kj�rerens data.
            if (loype == 'G') {                //  Funnet i GR�NN l�ype:
               cout << "\n\tflyttes FRA GR�NN l�ype og inn i heisk�en.\n\n";
               gHeisKo.push(kjorer);           //  Legger inn Kjorer-PEKER.
               gGronn.erase(nr);               //  Sletter PARET key og PEKER.
           } else if (loype == 'R') {          //  Funnet i R�D l�ype:
               cout << "\n\tflyttes FRA R�D l�ype og inn i heisk�en.\n\n";
               gHeisKo.push(kjorer);           //  Legger inn Kjorer-PEKER.
                                             //  M� mer 'manuelt' finne i R�D:
               auto it = find_if(gRod.begin(), gRod.end(),
                   [nr] (const auto & val) { return(val->hentID() == nr); } );
               if (it != gRod.end())           //  Funn:
                  gRod.erase(it);              //  Sletter SELVE PEKEREN.
               else    //  Kj�reren er jo funnet - s� what???:
                  cout << "\n\tSEMANTISK FEIL-1 - dette skal ikke skje!!\n\n";
           } else      //  Kj�reren er jo funnet, men IKKE 'G/R' - s� what???:
             cout << "\n\tSEMANTISK FEIL-2 - dette skal ikke skje!!\n\n";
                      // *****************************************************
                      // **   Jfr/vs. EXCEPTIONS kap.16.1 i l�reboka        **
                      // **                      (som ikke er pensum).      **
                      // *****************************************************
        } else
          cout << "\n\tUkjent nummer i begge l�ypene!\n\n";
    } else
      cout << "\n\tBegge l�ypene er tomme!\n\n";
}


/**
 *  Flytter (om mulig) fra heisen og over til gr�nn eller r�d l�ype.
 *
 *  @param   loype  - Bokstaven ('G/R') for hvilken l�ype � flytte til
 *  @see     virtual Kjorer::skrivData()
 *  @see     Kjorer::registrerLoype
 *  @see     Kjorer::hentID()
 */
void tilLoype(const char loype) {
  if (!gHeis.empty()) {                          //  Kj�rer(e) i heisen:
     (gHeis.front())->skrivData();               //  1.kj�rers data skrives.
     cout << "\n\tflyttes fra heisen og over i "
          << ((loype == 'G') ? "GR�NN" : "R�D") << " l�ype\n\n";

     gHeis.front()->registrerLoype(loype);       //  Oppdaterer kj�rerens
                                                 //    "statistikk" med 'G/R'.
     if (loype == 'G')                           //  Flyttes til GR�NN:
                                             //  N�KKEL OG PEKER LEGGES INN:
        gGronn.insert(pair <int, Kjorer*>    //  NB:  BRUKEN AV 'hentID()' !!!
                                 ((gHeis.front())->hentID(), gHeis.front()));

//   Alternativt "bare":   gGronn[gHeis.front()->hentID()] = gHeis.front();

     else {                                   //  Flyttes til R�D:
       gRod.push_back(gHeis.front());   //  Legger inn PEKER bakerst i listen:
                                        //  NB:  SORTERER !!!!!!!!!!!!!! :
       gRod.sort([](Kjorer* k1, Kjorer* k2)
                                { return (k1->hentID() < k2->hentID()); });
     }
     gHeis.pop();                             //  Fjerner PEKER fra heisen.

  } else
    cout << "\n\tHeisen er tom, s� ingen � sette inn i noen l�ype!\n\n";
}
