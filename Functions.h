#pragma once

// extern, jotta voi käyttää muissa cpp fileissä
extern const int OneBedRoomPrice;
extern const int TwoBedRoomPrice;
extern const int LowerRoomLimit;
extern const int UpperRoomLimit;
extern const std::string Password;

struct Rooms
{
    bool Booked = false;
    int BedCount;
    int StayDuration;
    std::string FirstName;
    std::string LastName;
    std::string BookRoomLocalTime;
    time_t BookRoomUnixTime;
    double NormalPrice;
    double PaidPrice;
    int DiscountPercent;
};

int GetRandomFreeRoom(int BedCount, int NumberOfRooms, Rooms Room[]);

int GetCost(int StayDuration, int BedCount);

int CalculateEmptyRooms(int NumberOfRooms, int BedCount, Rooms Room[]);

void PrintRoomsAvailableMsg(int NumberOfRooms, Rooms Room[]);

void ReserveRoom(int BedCount, int NumberOfRooms, Rooms Room[]);

void ClearScreen(int);

void AskContinueOrQuit(bool &ReservingRooms);

int GetAndPrintRandomDiscount(std::string FirstName, int AssignedRoomNumber, int OriginalCost, Rooms Room[]);

void PrintGuestDetailsList(int NumberOfRooms, Rooms Room[]);

void PrintGuestlistOrQuit(int NumberOfRooms, Rooms Room[]);
