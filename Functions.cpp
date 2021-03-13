#include <iostream>
#include <string>
#include "Functions.h"
#include <ctime>
using namespace std;

// palauttaa satunnaisen vapaan huoneen numeron
int GetRandomFreeRoom(int BedCount, int NumberOfRooms, Rooms Room[]){
    int temp_room;
    
    do
    {
        if (BedCount == 1) // jos 1 hengen huone, niin huone valitaan ekasta puolistosta huoneita
            temp_room = rand() % (NumberOfRooms/2) + 1;    // ensimmäinen puolisko huoneista
        else // jos ei ole 1 hengen huone, niin se on 2 hengen huone ja valitaan huone tokasta puoliskosta 
            temp_room = rand() % (NumberOfRooms-NumberOfRooms/2) + (NumberOfRooms/2+1);  // toinen puolisko huoneista
       
    } while (Room[temp_room-1].Booked == true); // valitaan random huoneita niin kauan kunnes löytyy vapaa huone

    return temp_room; // palautaa vapaan huoneen numeron
}

// palautaa yöpymisen normaalin hinnan, kun annetaan huoneen koko ja yöpymisen kesto, (ja huoneen hinta per yö)
int GetCost(int StayDuration, int BedCount){
    int Price;  
    if (BedCount == 1) 
        Price = OneBedRoomPrice;
    else
        Price = TwoBedRoomPrice;

    int cost = StayDuration*Price;
    return cost;
}

// palauttaa vapaiden huoneiden määrän kysytylle huonekoolle
int CalculateEmptyRooms(int NumberOfRooms, int BedCount, Rooms Room[]){

    int start, stop, EmptyRoomCount=0;

    if (BedCount == 1) // jos 1 hengen huone, lasketaan vapaiden huoneiden määrä ekassa puoliskossa huoneita
    {
        start = 1;
        stop = NumberOfRooms/2;
    }
    else // jos 2 hengen huone, lasketaan vapaiden huoneiden määrä toisessa puoliskossa huoneita
    {
        start = NumberOfRooms/2+1;
        stop = NumberOfRooms;
    }
    
    for (int i = start; i <= stop; i++) // käydään huone kerrallaan läpi
    {
        if (Room[i-1].Booked == false) // katsotaan onko se tyhjä
            EmptyRoomCount++; // Jos tyhjä niin kasvatetaan laskuria
    }

    return EmptyRoomCount; // palautetaan tyhjien huoneiden määrä
}

// tulostaa vapaiden huoneiden määrän koottain
void PrintRoomsAvailableMsg(int NumberOfRooms, Rooms Room[]){
    int EmptyOneBedRoomCount = CalculateEmptyRooms(NumberOfRooms, 1, Room);
    int EmptyTwoBedRoomCount = CalculateEmptyRooms(NumberOfRooms, 2, Room);
    
    cout << EmptyOneBedRoomCount << " yhden hengen huonetta ja " << EmptyTwoBedRoomCount << " kahden hengen huonetta vapaana.\n";
}

// Kysyy tiedot ja varaa huoneen
void ReserveRoom(int BedCount, int NumberOfRooms, Rooms Room[]){

    int AssignedRoomNumber,StayDuration;
    bool valid;
    string Firstname, Lastname;

    AssignedRoomNumber = GetRandomFreeRoom(BedCount, NumberOfRooms, Room); // Haetaan vapaa huone ja lisätään se muuttujaan

    cin.ignore(1000, '\n'); // tyhjennetään cin input buffer ennen nimen kysymistä
    // Nimet voi olla lyhyitä: https://digitalcommons.butler.edu/cgi/viewcontent.cgi?article=5327&context=wordways
    do {
        cout << "Kirjoita etunimesi: ";  // kysyy etunimen
        getline(cin, Firstname);
        try // tehdään syötteen tarkistus
        {
            if (Firstname.length() < 1) // Minimi pituus 1 kirjain. 
            {    
                valid = false;
                throw(Firstname);
            }
            else // Jos 1 tai enemmän kirjainta, niin kelpaa
                valid = true;  
        }
        catch (...)
        {
            cerr << "Virhe: Nimi puuttuu. Etunimen minimi pituus on 1 merkki.\n";
        }

    } while (!valid); // toistetaan kysymistä, kunnes nimi kelpaa. 

    Room[AssignedRoomNumber-1].FirstName = Firstname; // tallennetaan etunimi taulukkoon tämän varatun huoneen numeron kohdalle

    
    do {
        cout << "Kirjoita sukunimesi: ";  // kysyy sukunimen
        getline(cin, Lastname);
        
        try // tehdään sukunimelle syötteen tarkistus
        {
            if (Lastname.length() < 1) // Minimi pituus 1 kirjain. 
            {    
                valid = false;
                throw(Lastname);
            }
            else // Jos 1 tai enemmän kirjainta, niin kelpaa
                valid = true;  
        }
        catch (...)
        {
            cerr << "Virhe: Nimi puuttuu. Sukunimen minimi pituus on 1 merkki.\n";
        }

    } while (!valid); // toistetaan kysymistä, kunnes nimi kelpaa. 

    Room[AssignedRoomNumber-1].LastName = Lastname; // tallennetaan sukunimi taulukkoon tämän varatun huoneen numeron kohdalle


    cout << "Huone #" << AssignedRoomNumber << " on vapaana, "; // tulostetaan, että huone #X on vapaana
    if (BedCount == 1)
        cout << "pääset"; // ja että henkilö/henkilöt pääsevät sinne. 
    else
        cout << "pääsette"; // Jos 2 hengen huone, niin sana väännetty monikkoon
    cout << " sinne. ";

    cout << "Kuinka monta yötä haluat varata?\n"; // kysytään varauksen kesto
    // tehdään syötteen tarkistus
    bool valid_length;
    do {
    
    cout << "Öiden määrä: ";
        try
        {
            if (!(cin >> StayDuration)) // jos input ei mene int tyyppiseen muuttujaan, niin ei ole kokonaisluku
            {    cerr << "Virhe: Syöte ei ole järkevä kesto\n";
                valid_length = false;
                throw ('a'); // heitetään vaikka char, jotta se menee geneeriseen catchiin
            }
            else if ((StayDuration > 0) && (StayDuration <= 365)) // jos kesto on positiivinen kokonaisluku, niin kelpaa, mutta muuten ei
                valid_length = true;
            else // input on kokonaisluku, mutta ei validi 
            {
                valid_length = false;
                throw (StayDuration); // heitetään int tyyppinen input
            } 
        }

        catch (int x) // Jos syöte int, mutta ei validi
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cerr << "Virhe: Kesto pitää olle välillä 1-365 yötä. Luku \"" << x << "\" ei kelpaa.\n";
        }

        catch (...) // Jos syöte esim merkkijono
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cerr << "Kirjoita öiden määrä positiivisena kokonaislukuna. Sallitut numerot: {1,2,3,...}\n"; // tulostetaan lisä apua
        }
    } while (!valid_length); // toistetaan kysymistä, kunnes luku kelpaa. 

    time_t BookRoomUnixTime = time(NULL); // aika sekunteina unix epochista
    string BookRoomLocalTime = asctime(localtime(&BookRoomUnixTime)); // aika nyt, formatoituna käyttäjän localin mukaan 
    
    Room[AssignedRoomNumber-1].StayDuration = StayDuration; // lisätään yöpymisen kesto taulukkoon talteen
    Room[AssignedRoomNumber-1].Booked = true; // merkataan huone taulukkoon varatuksi
    Room[AssignedRoomNumber-1].BookRoomUnixTime = BookRoomUnixTime; // lisätään taulukkoon varauksen teko aika (unix time)
    Room[AssignedRoomNumber-1].BookRoomLocalTime = BookRoomLocalTime; // lisätään taulukkoon varauksen teko aika (paikallinen aika)
    Room[AssignedRoomNumber-1].BedCount = BedCount; // lisätään taulukkoon huoneen koko

    int OriginalCost = GetCost(StayDuration,BedCount); // haetaan normi hinta
    cout << "Varaus maksaa " << OriginalCost << "€"; // tulostetaan normi hinta
    int DiscountedCost = GetAndPrintRandomDiscount(Firstname, AssignedRoomNumber, OriginalCost, Room); // haetaan alennettu hinta ja tulostetaan alennus syy

    cout << "\nVarausaika alkaa kulumaan varaushetkestä.\n";

    // tulostetaan yhteenveto, jossa henkilön nimi, huoneen numero, yöpymisen kesto ja hinta mahdollisten alennusten jälkeen
    cout << "\nYhteenveto: \nHenkilölle " << Firstname << ' ' << Lastname << " on varattu huone #" << AssignedRoomNumber << " " << StayDuration << ":ksi yöksi.\n";
    cout << "Lopullinen hinta: " << DiscountedCost << "€\n";
}

// tyhjentää näytön tulostamalla tyhjiä rivejä halutun määrän
void ClearScreen(int Lines){
    for (int i = 0; i < Lines; i++)
        cout << "\n";
}

// kysyy halutaanko huoneiden varaamista jatkaa vai lopetetaanko ohjelman suoritus
void AskContinueOrQuit(bool &ReservingRooms){
    cin.ignore(1000, '\n'); // Tyhjennetään cin input buffer, jotta edellinen vastaus ei voi vaikuttaa tähän.
    string answer;
    cout << "\nJatketaanko huoneiden varaamista? (Y/N)\n";
    cin >> answer;
    if ((answer == "Y") || (answer == "y") || (answer == "Yes") || (answer == "yes")) // Y,y,Yes,yes jatkavat varaamista
        ReservingRooms = true;
    else
        ReservingRooms = false; // muut vastaukset lopettavat
    return;
}

// arpoo ja tulostaa alennuksen suuruuden, alennuksen syyn ja mahdollisen alennetun hinnan
int GetAndPrintRandomDiscount(string FirstName, int AssignedRoomNumber, int OriginalCost, Rooms Room[]){
    int DiscountPercent;
    int DiscountedCost;

    int i = rand() % 3 + 1; // arvotaan luku 1,2,3
    if (i==1 || i==2) // jos 1 tai 2, niin sai alennuksen
    {
        if (i==1) // jos 1, niin alennus on 10%
        {
            DiscountPercent = 10;
            DiscountedCost = 0.9*OriginalCost; // alennettu hinta on 90% alkuperäisesta
        }
        if (i==2) // jos 2, niin alennus on 20%
        {
            DiscountPercent = 20;
            DiscountedCost = 0.8*OriginalCost; // alennettu hinta on 80% alkuperäisesta
        }
        cout << ", mutta koska nimesi alkaa " << FirstName.front() << "-kirjaimella, saat " << DiscountPercent << "% alennusta.\n"; // tulostetaan syy alennukselle
        cout << "Hinta alennuksen jälkeen on " << DiscountedCost << "€.\n"; // tulostetaan hinta alennuksen jälkeen          
    }
    else // jos 3, niin ei tullut alennusta
    {
        DiscountPercent = 0;
        DiscountedCost = OriginalCost; // ei alennusta, joten alenettu hinta sama kuin alkuperäinen
        cout << ".\n";
    }

    Room[AssignedRoomNumber-1].NormalPrice = OriginalCost;
    Room[AssignedRoomNumber-1].PaidPrice = DiscountedCost;
    Room[AssignedRoomNumber-1].DiscountPercent = DiscountPercent;

    return DiscountedCost; // palautetaan (mahdollisesti alennettu) hinta
}

// tulostaa taulukon tiedot
void PrintGuestDetailsList(int NumberOfRooms, Rooms Room[]){
    
    ClearScreen(24);
    cout << "Listaus huoneista:\n==================\n\n";

    for (int i = 0; i < NumberOfRooms; i++) // mennään jokainen huone läpi
    {
        if (Room[i].Booked) // jos huone on varattu, tulostetaan sen tiedot
        {
            cout << endl;
            cout << "Huone #" << i+1 << ':' << endl;
            cout << "Etunimi: " << Room[i].FirstName << endl;
            cout << "Sukunimi: " << Room[i].LastName << endl;
            cout << "Varausaika: " << Room[i].BookRoomLocalTime; // asctime() antaa perään '\n' joten nyt ei tarvitse endl
            cout << "Varausaika (UNIX timestamp): " << Room[i].BookRoomUnixTime << endl;
            cout << "Kesto: " << Room[i].StayDuration << " yötä" << endl;
            cout << "Huoneen koko: " << Room[i].BedCount << " henkeä" << endl;     
            cout << "Normaali hinta: " << Room[i].NormalPrice << " €" << endl;
            cout << "Maksettava hinta: " << Room[i].PaidPrice << " €" << endl;
            cout << "Alennusprosentti: " << Room[i].DiscountPercent << " %" << endl;
            cout << endl;
        }
        else // jos huonetta ei ole varattu, tulostetaan vain huoneen numero
            cout << "Huone #" << i+1 << endl;
    }
    return;
}

void PrintGuestlistOrQuit(int NumberOfRooms, Rooms Room[]){
    string PasswordInput;
    cin.ignore(1000, '\n'); // Tyhjennetään cin input buffer, jotta edellinen vastaus ei voi vaikuttaa tähän.
    string answer;
    cout << "Tulostetaanko listaus huoneista? (vaatii salasanan) (Y/N)\n";
    cin >> answer; // Y,y,Yes,yes ovat myönteisiä, muut lopettaa ohjelman
    if ((answer == "Y") || (answer == "y") || (answer == "Yes") || (answer == "yes"))
        {   
            cout << "Syötä salasana: "; // kysytään salasanaa
            cin >> PasswordInput;
            if (PasswordInput == Password) // jos annettu salasana ja tiedossa oleva salasana on samat, niin tulostetaan lista
                PrintGuestDetailsList(NumberOfRooms, Room);
            else
                cout << "\nPääsy evätty! Väärä salasana!\n"; // Jos väärä salasana, niin ei tulosteta listaa
        }
    return;
}
