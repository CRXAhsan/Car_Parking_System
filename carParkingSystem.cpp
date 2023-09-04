#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void addVehicle(ofstream &outfile)
{
    string regNumber, ownerName, mobilenumber, vehicleType;
    cout << "Enter Vehicle Number: ";
    cin >> regNumber;

    cin.ignore();
    cout << "Enter Owner Name: ";
    getline(cin, ownerName);

    cout << "Enter Mobile Number: ";
    cin >> mobilenumber;
    cout << "Enter Vehicle Type: ";
    cin >> vehicleType;

    outfile << regNumber << "," << ownerName << "," << mobilenumber << "," << vehicleType << "\n";

    cout << "Vehicle add successfully...\n";
}

void removeVehicle(const string &regNumber, const string &filename)
{
    ifstream infile(filename);
    ofstream tempfile("temp.txt");

    string line;
    bool found = false;

    while (getline(infile, line))
    {
        size_t commaPos = line.find(',');
        if (commaPos != string::npos && line.substr(0, commaPos) == regNumber)
        {
            found = true;
            continue;
        }
        tempfile << line << "\n";
    }

    infile.close();
    tempfile.close();

    if (found)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        cout << "Vehicle Removed Successfully...\n";
    }
    else
    {
        cout << "Vehicle Not Found...\n";
        remove("temp.txt");
    }
}

void viewVehicle(const string &filename)
{
    ifstream infile(filename);
    string line;

    cout << "######           Vehicles Present in the Parking Plot          ######" << endl;
    int countVehicle = 1;
    while (getline(infile, line))
    {

        size_t commaPos1 = line.find(',');
        size_t commaPos2 = line.find(',', commaPos1 + 1);
        size_t commaPos3 = line.find(',', commaPos2 + 1);

        string regNumber = line.substr(0, commaPos1);
        string ownerName = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
        string mobileNumber = line.substr(commaPos2 + 1, commaPos3 - commaPos2 - 1);
        string vehicleType = line.substr(commaPos3 + 1);

        cout << "             Vehicle: " << countVehicle << endl;
        cout << " Registration Number: " << regNumber << endl;
        cout << "          Owner Name: " << ownerName << endl;
        cout << "       Mobile Number: " << mobileNumber << endl;
        cout << "        Vehicle Type: " << vehicleType << endl;
        countVehicle++;
    }

    infile.close();
}

int main()
{
    while (true)
    {
        system("cls");
        int choice;
        cout << "######################################################\n";
        cout << "#        Welcome to Car Parking System               #\n";
        cout << "#     1.  Add Vehicle                                #\n";
        cout << "#     2.  Delete Vehicle                             #\n";
        cout << "#     3.  View Vehicle                               #\n";
        cout << "#     4.  Exit                                       #\n";
        cout << "######################################################\n";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            ofstream outFile("Parking.txt", ios_base::app);
            addVehicle(outFile);
            outFile.close();
            break;
        }

        case 2:
        {
            string regNumber;
            cout << "Enter Vehicle Number: ";
            cin >> regNumber;
            removeVehicle(regNumber, "Parking.txt");
            break;
        }

        case 3:
        {
            viewVehicle("Parking.txt");
            break;
        }

        case 4:
        {
            return 0;
        }
        default:
        {
            cout << "Invalid Choice...\n";
        }
        }
        system("pause");
    }
    return 0;
}