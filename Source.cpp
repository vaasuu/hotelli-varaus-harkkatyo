#include <iostream>
#include <ctime>
#include <string>
#include "Functions.h"
#include <iomanip> // pyöristykseen
using namespace std;

// vakiot 
const int OneBedRoomPrice = 100; // 1 hengen huone hinta per yö
const int TwoBedRoomPrice = 150; // 2 hengen huone hinta per yö
const int LowerRoomLimit = 40; // huoneiden määrän alaraja
const int UpperRoomLimit = 80; // huoneiden määrän yläraja
const string Password = "Hunter2"; // tietojen tulostus salasana

int main(){

    setlocale(LC_ALL, ""); // Asetetaan locale asetukset käyttäjän asetusten mukaan
    cout << fixed; // Poistetaan tieteellinen numeromuoto käytöstä. 
    cout << setprecision(0); // pyöristys kokonaisluvuiksi
    srand(time(NULL)); // asetetaan rand funktion seediksi tämänhetkinen UNIX time. 
    rand(); // workaround bugille, jossa ensimmäinen rand() oli aina joku kolmesta vaihtoehdosta. 
    // https://i.imgur.com/HWFgccQ.png

    // random parillinen luku ylä ja ala rajoilla
    int NumberOfRooms = 2*(rand() % (UpperRoomLimit/2-LowerRoomLimit/2+1) + LowerRoomLimit/2);
    // int NumberOfRooms = 4; // temp test
    int StayDuration;
    bool ReservingRooms = true;
    int BedCount;
    int AssignedRoomNumber;

    Rooms Room[NumberOfRooms]; // Taulukko huoneita

    string HotelAsciiArt = R"(
 /\   /\__ _ _ __ __ _  __ _                            
 \ \ / / _` | '__/ _` |/ _` |                           
  \ V / (_| | | | (_| | (_| |                           
   \_/ \__,_|_|  \__,_|\__,_| 
  _           _       _ _ _ _                            
 | |__   ___ | |_ ___| | (_) |__  _   _  ___  _ __   ___ 
 | '_ \ / _ \| __/ _ \ | | | '_ \| | | |/ _ \| '_ \ / _ \
 | | | | (_) | ||  __/ | | | | | | |_| | (_) | | | |  __/
 |_| |_|\___/ \__\___|_|_|_|_| |_|\__,_|\___/|_| |_|\___|
        )";

    
    do {
        ClearScreen(24); // tyhjennetään näyttö
        cout << HotelAsciiArt; // tulostetaan ascii art
        ClearScreen(3); // tehdään tilaa näytölle

        PrintRoomsAvailableMsg(NumberOfRooms, Room); //tulostetaan vapaana olevien huoneiden määrät

        cout << "Haluatko yhden (1) vai kahden (2) hengen huoneen?\n"; // kysytään huoneen kokoa

        // Syötteen tarkistus huonekoolle
        bool valid;
        do {
            cout << "Valitse huoneen koko: ";
            
            try
            {
                if(!(cin >> BedCount)) // jos input ei mene int tyyppiseen muuttujaan, niin ei ole kokonaisluku
                    {
                        cerr << "Virhe: syöte ei ole numero.\n";
                        valid = false;
                        throw ('a'); // heitetään vaikka char, jotta se menee geneeriseen catchiin
                    }
                else if ((BedCount == 1) || (BedCount == 2)) // jos huoneenkoko on 1 tai 2 niin syöte on validi, muuten ei
                    valid = true;
                else // input on kokonaisluku, mutta ei validi 
                {
                    valid = false;
                    throw (BedCount); // heitetään int tyyppinen input
                } 
            }
            catch(int x)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cerr << "Virhe: Syöte \"" << x << "\" on numero, mutta tämä numero ei ollut vaihtoehto. Valitse joko 1 tai 2.\n";
            }
            catch(...)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cerr << "Kirjoita pelkkä numero, joko 1 tai 2.\n";
            }
        } while (!valid); // kysytään huoneen kokoa uudelleen ja uudelleen, kunnes syöte on validi



        int EmptyOneBedRoomCount = CalculateEmptyRooms(NumberOfRooms, 1, Room); // laskee tyhjien 1 hengen huoneiden määrän
        int EmptyTwoBedRoomCount = CalculateEmptyRooms(NumberOfRooms, 2, Room); // laskee tyhjien 2 hengen huoneiden määrän


        // Jos kaikki huoneet täynnä -> Set flag ReservingRooms = false ja exit ohjelma
        if (EmptyOneBedRoomCount < 1 && EmptyTwoBedRoomCount < 1)
        {
            cout << "Huoneita ei ole enää saatavilla. Pahoittelut.\n";
            ReservingRooms = false;
        }
        
        else if (BedCount == 1) // Jos Valittu 1 henkilön huone
        {
            if (EmptyOneBedRoomCount < 1) // Ei ole tilaa -> skip varaus, ehdota 2 heng huonetta
                cout << "Yhden hengen huoneita ei ole enää saatavilla. Pahoittelut. "
                "Voit halutessasi koittaa kahden hengen huonetta, niitä on " << EmptyTwoBedRoomCount << " vapaana.\n";
            else // on tilaa -> anna varata
                ReserveRoom(BedCount, NumberOfRooms, Room); // varataan huone
        }

        else if (BedCount == 2) // Jos Valittu 2 henkilön huone
        {
            if (EmptyTwoBedRoomCount < 1) // Ei ole tilaa -> skip varaus, ehdota 1 heng huonetta
                cout << "Kahden hengen huoneita ei ole enää saatavilla. Pahoittelut. "
                "Voitte halutessanne koittaa yhden hengen huonetta, niitä on " << EmptyOneBedRoomCount << " vapaana.\n";
            else // on tilaa -> anna varata
                ReserveRoom(BedCount, NumberOfRooms, Room); // varataan huone
        }

    AskContinueOrQuit(ReservingRooms); // Kysyy jatketaanko varausta vai poistutaanko ohjelmasta

    } while (ReservingRooms); // Jatketaan varausta loopissa mikäli tilaa ja halua riittää 

    PrintGuestlistOrQuit(NumberOfRooms, Room); // kysyy tulostetaanko listaus varauksista ja tekee niin jos halutaan

    return 0;
}
