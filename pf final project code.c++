#include <iostream> // Provides input and output functionality (cin, cout, etc.)
#include <fstream> // Allows file handling operations (reading and writing files)
#include <iomanip> // Provides functions for manipulating the input/output format (e.g., setting precision, width)
#include <vector> // Provides the vector container for dynamic arrays. This library provides the vector container, which is a dynamic array in C++. 
                 // Vectors allow you to store a collection of elements (like integers, strings, etc.) and automatically resize as elements are added or removed, unlike regular arrays. 
                 // It makes managing dynamic collections much easier than using fixed-size arrays.
#include <string> // Allows string manipulation and handling
#include <ctime> // Provides functions to deal with date and time
#include <sstream> // For stringstream and ostringstream
#include <algorithm> // For all_of
#include <regex>  // Include regex library for email validation
#include <limits> // Defines limits for data types (e.g., numeric limits for int, float)
#include <stdexcept>  // For exceptions, allowing you to handle errors in a more controlled manner.


using namespace std;

// Room Structure
struct Room {
    int roomNumber;  // Room number (e.g., 10,20 ,etc.)
    bool isBooked;  // Boolean flag to indicate if the room is booked or not
    string customerName; // Name of the customer who booked the room
    string contactNumber;
    string emailAddress;
    string numberOfDays;
    string type;  // Room type (e.g., Single, Double, Suite)
    int pricePerDay;  // Price for the room per day
    string paymentMethod; // "Cash" or "Credit"
    vector<string> amenities;
    string checkInTime;
    string checkOutTime;

    // Constructor
    Room(int num, bool booked, const string& name, const string& roomType )
        : roomNumber(num), isBooked(booked), customerName(name),type(roomType), checkInTime(""), checkOutTime("") {}
}; 
// Function to get the current date and time as a string
string getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

// Function to display the welcome screen
void displayWelcomeScreen() {
    cout << "\033[38;5;223m*************************************************" << endl;
    cout << "*                                               *" << endl;
    cout << "*               WELCOME TO                      *" << endl;
    cout << "*              Sunset Resort                    *" << endl;
    cout << "*                                               *" << endl;
    cout << "*************************************************\033[0m" << endl;
    cout << "\033[90mPress Enter to continue...\033[0m" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
}

// Function to display hotel description
void displayHotelDescription() {
   
   
    cout << "\033[38;5;218mSUNSET RESORT is one of the newest hotels in Islamabad." << endl;
    cout << "The hotel is equipped with all the general amenities and" << endl;
    cout << "facilities to ensure a memorable stay.\033[0m" << endl;
    cout << "\033[90mPress Enter to continue...\033[0m" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
 
// Function to display room details
void displayRoomDetails(Room& room) {
    cout << "\033[38;5;129m*************************************************" << endl;
    cout << "*              FEATURES OF THIS ROOM            *" << endl;
    cout << "*************************************************\033[0m" << endl;
    cout << "\033[38;5;214mRoom Number: " << room.roomNumber << endl;
    cout << "Room Type: " << room.type << endl;
    cout << "Price Per Day: Rs:" << room.pricePerDay << endl;
    cout << "\033[38;5;214mAmenities:" << endl;
    for (size_t i = 0; i < room.amenities.size(); ++i) {
        cout << i + 1 << ". \033[0m" << room.amenities[i] << endl;
    }

    cout << "\033[38;5;129m*************************************************\033[0m" << endl;
}

// Function to display all rooms
void displayRooms(const vector<Room>& rooms) {
    cout << "\n\033[38;5;223mRoom Availability:\033[0m" << endl;
    for (size_t i = 0; i < rooms.size(); ++i) {
        if (i % 10 == 0) cout << endl; // New row every 10 rooms
        cout << "|Room" << setw(3) << rooms[i].roomNumber;
        cout << (rooms[i].isBooked ? "\033[31m(Booked)\033[0m| " : "\033[32m(Free)\033[0m| ");
    }
    cout << endl;

}

// Function to update check-in time in the file
void updateCheckInTime(const string& filename, int roomNumber, const string& checkInTime) {
    ifstream file(filename);
    vector<string> lines;
    bool entryUpdated = false;

    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            string name, roomNo, checkIn, checkOut, contactNumber, emailAddress, numberOfDays;

            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, roomNo, ',');
            getline(ss, checkIn, ',');
            getline(ss, checkOut, ',');
            getline(ss, contactNumber, ',');
            getline(ss, emailAddress, ',');
            getline(ss, numberOfDays, ',');

            if (to_string(roomNumber) == roomNo) {
                checkIn = checkInTime;
                ostringstream updatedLine;
                updatedLine << name << "," << roomNo << "," << checkIn << "," << checkOut << "," << contactNumber << "," << emailAddress << "," << numberOfDays;
                lines.push_back(updatedLine.str());
                entryUpdated = true;
            } else {
                lines.push_back(line);
            }
        }
        file.close();
    }

    if (!entryUpdated) {
        cout << "\033[31mError: Room number not found in the file.\033[0m" << endl;
        return;
    }

    ofstream outFile(filename, ios::trunc);
    if (outFile.is_open()) {
        for (size_t i = 0; i < lines.size(); ++i) {
            const string& updatedLine = lines[i];

            outFile << updatedLine << "\n";
        }
        outFile.close();
        
    } else {
        cout << "\033[31mError: Could not open file for writing.\033[0m" << endl;
    }
}

// Function to update the checkout time in the file
void updateCheckOutTime(const string& filename, int roomNumber, const string& checkoutTime) {
    ifstream file(filename);
    vector<string> lines;
    bool entryUpdated = false;

    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string name, roomNo, checkInTime, checkOutTime, contactNumber, emailAddress, numberOfDays;

            getline(ss, name, ',');
            getline(ss, roomNo, ',');
            getline(ss, checkInTime, ',');
            getline(ss, checkOutTime, ',');
            getline(ss, contactNumber, ',');
            getline(ss, emailAddress, ',');
            getline(ss, numberOfDays, ',');

            if (to_string(roomNumber) == roomNo) {
                checkOutTime = checkoutTime;
                ostringstream updatedLine;
                updatedLine << name << "," << roomNo << "," << checkInTime << "," << checkOutTime << "," << contactNumber << "," << emailAddress << "," << numberOfDays;
                lines.push_back(updatedLine.str());
                entryUpdated = true;
            } else {
                lines.push_back(line);
            }
        }
        file.close();
    }

    if (!entryUpdated) {
        cout << "\033[31mError: Room number not found in the file.\033[0m" << endl;
        return;
    }

    ofstream outFile(filename, ios::trunc);
    if (outFile.is_open()) {
        for (size_t i = 0; i < lines.size(); ++i) {
             const string& updatedLine = lines[i];
            outFile << updatedLine << "\n";
        }
        outFile.close();
        
    } else {
        cout << "\033[31mError: Could not open file for writing.\033[0m" << endl;
    }
}

// Function to book a room
void bookRoom(vector<Room>& rooms) {
    int roomNumber;
    string customerName;
    string contactNumber;
    string emailAddress;
    string numberOfDays;
    
    cout << "\033[34mEnter Room Number to Book: ";
   


    try {
        // Error handling for non-integer input
        if (!(cin >> roomNumber)) {
            throw invalid_argument("\033[31mInvalid input! Please enter a valid room number (integer).\033[0m");
        }


    for (size_t i = 0; i < rooms.size(); ++i)
    {
        Room& room = rooms[i];
        if (room.roomNumber == roomNumber) {
            if (room.isBooked) {
                cout << "\033[34mRoom " << roomNumber << " is already booked!" << endl;
            } else {
                        cout << "\033[38;5;141mEnter Customer Name: ";
                        while (true) {
                      try {
                     cin.ignore(); // Clear input buffer before taking string input
                         getline(cin, customerName);

                   // Validate customer name: must not be empty and must only contain valid characters
                   if (customerName.empty()) {
                  throw invalid_argument("\033[31mCustomer name cannot be empty! Please enter a valid name.\033[0m");
                  }
                for (size_t i = 0; i < customerName.size(); ++i) {
                     char c = customerName[i];
                    if (!(isalpha(c) || isspace(c) || c == '-')) {
                 throw invalid_argument("\033[31mInvalid characters in name! Use letters, spaces, or hyphens only.\033[0m");
             }
                 }

                  break; // Exit loop if valid
                  } catch (const invalid_argument& e) {
                 cout << e.what() << endl;
              cout << "Please re-enter Customer Name: ";
                 }
                }
                
            
             while (true) {
                        cout << "\033[33mEnter Contact Number: ";
                        try {
                            getline(cin, contactNumber);

                            // Validate contact number (digits only, length between 7 and 15)
                            if (contactNumber.empty() || contactNumber.length() < 7 || contactNumber.length() > 15 ||
                                !all_of(contactNumber.begin(), contactNumber.end(), ::isdigit)) {
                                throw invalid_argument("\033[31mInvalid contact number! Enter digits only (7-15 characters).\033[0m");
                            }
                            break; // Exit loop if valid
                        } catch (const invalid_argument& e) {
                            cout << e.what() << endl;
                        }
                    } 
                        // Enter email with validation
                        while (true) {
                        cout << "\033[38;5;111mEnter Email Address: ";
                         getline(cin, emailAddress);

                             // Check if email contains '@' and '.' in valid positions
                          size_t atPos = emailAddress.find('@');
                              size_t dotPos = emailAddress.find('.');

                          if (atPos != string::npos && dotPos != string::npos && atPos < dotPos && dotPos != emailAddress.length() - 1) {
                             break; // Valid email, exit the loop
                               } else {
                              cout << "\033[31mInvalid email address. Please enter a valid email.\033[0m" << endl;
                              }
                            }

                // Input validation for number of days (string input)
                while (true) {
                    cout << "\033[38;5;45mEnter Number of Days for Stay: ";
                    getline(cin, numberOfDays); // Keep as string input

                    // Validate if numberOfDays contains only digits and is a positive integer
                    if (all_of(numberOfDays.begin(), numberOfDays.end(), ::isdigit) && !numberOfDays.empty()) {
                        // Valid input, break out of the loop
                        break;
                    } else {
                        cout << "\033[31mInvalid input! Enter a valid positive integer.\033[0m" << endl;
                    }
                }
                             // Inside the bookRoom function after gathering other details:
                            while (true) {
                         cout << "\033[38;5;141mEnter Payment Method (Cash/Credit): ";
                     getline(cin, room.paymentMethod);  // Read the payment method

                              // Validate payment method
                       if (room.paymentMethod == "Cash" || room.paymentMethod == "Credit") {
                          break;  // Valid input, exit the loop
                       } else {
                       cout << "\033[31mInvalid payment method. Please enter 'Cash' or 'Credit'.\033[0m" << endl;
                     }
}

                room.isBooked = true;
                room.customerName = customerName;
                room.contactNumber = contactNumber;  // Store the contact number
                room.emailAddress = emailAddress;    // Store the email address
                room.numberOfDays = numberOfDays;    
                room.checkInTime = "";
                cout << "\033[32mRoom " << roomNumber << " has been booked successfully!\033[0m" << endl;

                // Save booking details
                ofstream file("CustomerData.txt", ios::app);
                if (file.is_open()) {
                    
                    file << customerName << "," << roomNumber << "," << room.checkInTime << "," << room.checkOutTime << "," << contactNumber << "," << emailAddress << "," << numberOfDays  << "\n";
                    file.close();
                } else {
                    cout << "\033[31mError: Could not open file!\033[0m" << endl;
                }
            }
            return;
        }
    }
    cout << "\033[31mRoom " << roomNumber << " does not exist!\033[0m" << endl;
}
   catch (const invalid_argument& e) {
        cout << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}

// Function to validate email (move this outside of displayCustomerDetails)
bool isValidEmail(const string& emailAddress) {
    const regex email_regex("^[\\w-]+(\\.[\\w-]+)*@[a-zA-Z0-9-]+(\\.[a-zA-Z]{2,})+$");
    return regex_match(emailAddress, email_regex);
}


/*void clearFileAndAddNewData(const std::string& filename)
 {
    // Open the file in write mode with truncation (this clears the file)
    std::ofstream file(filename, std::ios::trunc);

    if (file.is_open()) {
        // Now the file is empty. You can start adding new data.
       

        // Close the file after adding new data
        file.close();
    } else {
        std::cerr  << std::endl;
    }
 }
 */


// Function to display customer details
void displayCustomerDetails() {
    
    ifstream file("CustomerData.txt");
    string line;
    cout << "\033[38;5;111mCustomer Details:" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
     cout << setw(20) << "Customer Name" << setw(13) << "Room No" << setw(21) << "Check-in Time" << setw(27) << "Check-out Time"<< setw(26) << "Contact Number"
         << setw(26) << "Email Address" << setw(20) << "Days Stay" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------\033[0m" << endl;
    if (file.is_open()) {
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            size_t pos4 = line.find(',', pos3 + 1);
            size_t pos5 = line.find(',', pos4 + 1);
            size_t pos6 = line.find(',', pos5 + 1);
          

            // Extract the fields using substrings
            string name =  "\033[33m" + line.substr(0, pos1)+ "\033[0m";                          // Field 1
             string roomNo = line.substr(pos1 + 1, pos2 - pos1 - 1);      // Field 2
            string checkInTime =  line.substr(pos2 + 1, pos3 - pos2 - 1); // Field 3
            string checkOutTime =  line.substr(pos3 + 1, pos4 - pos3 - 1) ;  // Field 4
            if (checkOutTime == "-") {
                checkOutTime = "\033[31m\t\tNot Checked Out\033[0m";  // Mark rooms not checked out
            }
            string contactNumber = "\033[32m" + line.substr(pos4 + 1, pos5 - pos4 - 1)+ "\033[0m";  // Field 5
            string emailAddress = "\033[34m" + line.substr(pos5 + 1, pos6 - pos5 - 1) + "\033[0m" ;       // Field 6
            string numberOfDays = "\033[35m" + ((pos6 != string::npos) ? line.substr(pos6 + 1) : "") + "\033[0m";


            // Print formatted data
            cout << setw(25) << name << setw(15) << roomNo << setw(25) << checkInTime << setw(27) << checkOutTime 
            << setw(31) << contactNumber << setw(36) <<  emailAddress 
            << setw(27) << numberOfDays  << endl;

        }
        file.close();
    } else {
        cout << "\033[31mNo customer data available!\033[0m" << endl;
    }
     
    
}



// Simulating credit card validation function
bool validateCreditCard(const string& cardNumber) {
    // Simulate basic validation: check if the card number is 16 digits long
    if (cardNumber.length() == 16) {
        for (size_t i = 0; i < cardNumber.size(); ++i) {
             char c = cardNumber[i];
            if (!isdigit(c)) {
                return false;  // Invalid if any character is not a digit
            }
        }
        return true;
    }
    return false;
}

// Function to process the payment
bool processPayment(const Room& room, int totalBill) {
    string paymentMethod = room.paymentMethod;

    if (paymentMethod == "Cash") {
        cout << "\033[32mPlease pay the total bill amount of Rs. " << totalBill << " in cash.\033[0m" << endl;
        cout << "\033[32mPayment successful. Receipt generated.\033[0m" << endl;
        return true;  // Return true since payment was successful
    }
    else if (paymentMethod == "Credit") {
        cout << "\033[32mPlease provide your credit card details.\033[0m" << endl;

        // Simulate credit card input
        string creditCardNumber;
        cout << "\033[38;5;141mEnter your 16-digit credit card number: \033[0m";
        cin >> creditCardNumber;

        bool paymentSuccessful = validateCreditCard(creditCardNumber);  // Simulated card validation

        if (paymentSuccessful) {
            cout << "\033[32mPayment successful via credit card. Receipt generated.\033[0m" << endl;
            return true;  // Payment is successful
        }
        else {
            cout << "\033[31mPayment failed. Invalid card number. Please check your credit card details or try another method.\033[0m" << endl;
             return false;  // Payment failed
        }
    } else {
        cout << "\033[31mError: Unknown payment method.\033[0m" << endl;
        return false;
    }
}


// Function to generate the bill
void generateBill(const Room& room, int days) {
    if (!room.isBooked) {
        cout << "\033[31mRoom " << room.roomNumber << " is not booked. No bill to generate.\033[0m" << endl;
        return;
    }
    
    int totalBill = room.pricePerDay * days;

    cout << "\n\033[38;5;112mBilling Details:\033[0m" << endl;
    cout << "\033[32mCustomer Name: \033[0m" << room.customerName << endl;
    cout << "\033[32mRoom Number: \033[0m" << room.roomNumber << endl;
    cout << "\033[32mRoom Type: \033[0m" << room.type << endl;
    cout << "\033[32mPrice Per Day: Rs. \033[0m" << room.pricePerDay << endl;
    cout << "\033[32mNumber of Days: \033[0m" << days << endl;
    cout << "\033[38;5;214mTotal Bill: Rs. \033[0m" << totalBill << endl;
    cout << "\033[32mPayment Method: \033[0m" << room.paymentMethod << endl;

     
}




// Function to handle check-in
void checkInRoom(vector<Room>& rooms) {
    int roomNumber;
    string numberOfDays;
    cout << "\033[38;5;141mEnter Room Number to Check In: \033[0m";
    try {
        if (!(cin >> roomNumber)) {
            throw invalid_argument("\033[31mInvalid input! Please enter a valid room number (integer).\033[0m");
        }

        for (size_t i = 0; i < rooms.size(); ++i) {
            Room& room = rooms[i];
            if (room.roomNumber == roomNumber) {
                if (!room.isBooked) {
                    cout << "\033[34mRoom " << roomNumber << " is not booked yet!\033[0m" << endl;
                } else {
                    if (room.checkInTime.empty()) {
                           // Convert numberOfDays from string to integer here
                        int days = 0;
                        try {
                            days = stoi(room.numberOfDays);  // Convert to integer
                            if (days <= 0) {
                                throw invalid_argument("\033[31mNumber of days must be a positive integer!\033[0m");
                            }
                        } catch (const std::invalid_argument& e) {
                            cout << "\033[31mInvalid number of days: " << room.numberOfDays << ". Please enter a valid positive integer.\033[0m" << endl;
                            return;
                        }
                         generateBill(room, days);
                        room.checkInTime = getCurrentTime();  // Set check-in time when the guest checks in
                        bool paymentSuccessful = processPayment(room, room.pricePerDay * days);  // Check payment status

                        if (paymentSuccessful) {
                          
                            cout << "\033[32mRoom " << roomNumber << " has been checked-in successfully at " << room.checkInTime << "!\033[0m" << endl;
                            // Update check-in time in the file
                            updateCheckInTime("CustomerData.txt", roomNumber, room.checkInTime);
                        } else {
                            cout << "\033[31mCheck-in failed due to payment failure.\033[0m" << endl;
                            room.checkInTime.clear();
                        }
                        
                    } else {
                        cout << "\033[34mRoom " << roomNumber << " is already checked-in.\033[0m" << endl;
                    }
                }
                return;
            }
        }
        cout << "\033[31mRoom " << roomNumber << " does not exist!\033[0m" << endl;
    } catch (const invalid_argument& e) {
        cout << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Function to check out a room

void checkOutRoom(vector<Room>& rooms) 
{
    int roomNumber;
    string customerName;
    string contactNumber;
    string emailAddress;
    string numberOfDays;
   

    try
     {
        cout << "\033[38;5;141mEnter Room Number to Check Out: \033[0m";
        if (!(cin >> roomNumber)) {
            throw invalid_argument("\033[31mInvalid input! Please enter a valid room number (integer).\033[0m");
        }

    for (size_t i = 0; i < rooms.size(); ++i)
    {
    Room& room = rooms[i];
        if (room.roomNumber == roomNumber) {
            if (!room.isBooked) {
                cout << "\033[34mRoom " << roomNumber << " is already free!" << endl;
            } else {
                room.isBooked = false;
                room.checkOutTime = getCurrentTime();
                updateCheckOutTime("CustomerData.txt", roomNumber, room.checkOutTime);



                cout << "\033[32mRoom " << roomNumber << " has been checked out successfully!\033[0m" << endl;

            

                // Reset room details
                room.customerName = "";
                room.checkInTime = "";
                room.checkOutTime = "";
                contactNumber ="";
                emailAddress = "";
                numberOfDays="";
               
            }
            return;
        }
    }
    
      cout << "\033[31mRoom " << roomNumber << " does not exist!\033[0m" << endl;
    } catch (const invalid_argument& e) {
        cout << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}
 


// Function to generate and display the summary report of bookings and room statuses
void generateSummaryReport(const vector<Room>& rooms) {

    const string red = "\033[31m";   // Red text
    const string green = "\033[32m"; // Green text
    
    const string reset = "\033[0m";  // Reset to default color
 try {
    cout << "\n  \t  \t     \t   \t     \033[38;5;214m     Summary Report of Bookings and Room Statuses \n";
    cout << "\033[38;5;214m--------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << setw(25) << "Guest Name" 
         << setw(25) << "Room Number " 
         << setw(25) << "   Room Type " 
         << setw(25) << "  Status " 
         << setw(30) << "  Check-In Time  " << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------\033[0m\n";

    for (size_t i = 0; i < rooms.size(); ++i) 
    {
    const Room& room = rooms[i];

        string status = room.isBooked ? red + "Booked" + reset : green + "Available" + reset;
        string roomtype = "\033[34m" + room.type + "\033[0m"; // Blue for "Room Type"
        string roomcustomerName = "\033[33m" + room.customerName + "\033[0m"; // Yellow for "Guest Name"

        

        cout <<std::right
             << setw(30) << roomcustomerName 
             << setw(25) << room.roomNumber 
             << setw(36) << roomtype
             << setw(38) << status
             << setw(36) << (room.isBooked ? room.checkInTime : "") << std::flush << endl;
    }
    cout << "\033[38;5;214m--------------------------------------------------------------------------------------------------------------------------------------------\033[0m\n";
}
catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}
        
// Main menu
void displayMenu() {
    cout << "\033[1m\033[35m\nHotel Management System\033[0m\n"<< endl;
    cout << "\033[38;5;114m1. \033[38;5;17m Display Rooms" << endl;
    cout << "\033[38;5;114m2. \033[38;5;17m View Room Details" << endl;
    cout << "\033[38;5;114m3. \033[38;5;17m Book a Room" << endl;
    cout << "\033[38;5;114m4. \033[38;5;17m Check In Room" << endl;
    cout << "\033[38;5;114m5. \033[38;5;17m Display Customer Details" << endl;
    cout << "\033[38;5;114m6. \033[38;5;17m Check Out Room" << endl;
    cout << "\033[38;5;114m7. \033[38;5;17m Summary Report of all bookings" << endl;
    cout << "\033[38;5;114m8. \033[38;5;17m Exit \033[0m\n" << endl;
    cout << "\033[35mEnter your choice :\033[0m";
}

 
int main() {
    
    vector<Room> rooms;

    rooms.reserve(100); // Reserve memory for 100 rooms
    for (int i = 0; i < 100; i++) {
        string roomType = (i < 30) ? "Single" : (i < 60) ? "Double" : "Suite"; // Assigning room types based on room number
        rooms.emplace_back(i + 1, false, "", roomType);
        
        rooms[i].roomNumber = i + 1;
        rooms[i].isBooked = false;
        rooms[i].customerName = "";
        
        rooms[i].pricePerDay = (i < 5) ? 1500 : 2500;
        
         
         // Manually assign values to the amenities vectors
        rooms[i].amenities.resize(4);  // Ensure the vector has space for 4 elements
        rooms[i].amenities[0] = "\033[38;5;214mA/C";
        rooms[i].amenities[1] = "\033[38;5;214mGeyser";
        rooms[i].amenities[2] = "\033[38;5;214mTV";
        rooms[i].amenities[3] = "\033[38;5;214mFree WiFi\033[0m";
    }

    displayWelcomeScreen();
    displayHotelDescription();

    int choice;
    bool found = false;  // Declare 'found' here to make it accessible in the switch block
    do {
        displayMenu();
        
        // Handle invalid input for the menu choice
        while (true) {
            try {
                cin >> choice;
                if (cin.fail()) {
                    throw invalid_argument("\033[31m\nInvalid input! Please enter a valid menu choice (1-8).\033[0m");
                }
                break;  // Exit the loop if valid input is received
            } catch (const invalid_argument& e) {
                cout << e.what() << endl;
                cin.clear(); // Clear error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            }
        }
        
   // clearFileAndAddNewData("CustomerData.txt");

      

        switch (choice) {
            case 1:
                       
                displayRooms(rooms);
                break;
            case 2:
             // Ask for the room number again to display room details
                int roomNumber;
                cout << "\033[34mEnter Room Number to View Details:\033[0m ";
                cin >> roomNumber;
                found = false;  // Reset the 'found' flag before searching for the room
                for (size_t i = 0; i < rooms.size(); ++i) {
                    if (rooms[i].roomNumber == roomNumber) {
                        displayRoomDetails(rooms[i]); // Pass the specific room
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "\033[31mRoom " << roomNumber << " does not exist!\033[0m" << endl;
                }
                break;
            case 3:
                bookRoom(rooms);
                break;
            case 4:
            checkInRoom(rooms);
                 break;
            case 5:
                displayCustomerDetails();
                break;
            case 6:
                checkOutRoom(rooms);
                break;
            case 7:
            generateSummaryReport(rooms);  // Display the summary report
                break;
            case 8:

                cout<<"\033[38;5;225mTHANK YOU FOR VISITING OUR HOTEL"<<endl;
                cout << "Exiting program. Thank you!\033[0m" << endl;
                break;
            default:
                cout << "\033[31mInvalid choice! Please try again.\033[0m" << endl;
        }
    } while (choice != 8);

    return 0;

}
