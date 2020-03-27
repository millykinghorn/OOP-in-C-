#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

//class containing member functions to manipulate data
class galaxy
{
private:
    string hubble_type;
    double redshift;
    double mass_total;
    double mass_fraction;
    vector<string> satellites;

public:

    // Constructor
    //default constructor: object with no parameters
    galaxy() : hubble_type{}, redshift{}, mass_total{}, mass_fraction{}, satellites{} {}

    // Parameterized constructor
    //two constructors: one with satellite, one without
    galaxy(string galaxyhubble_type, double galaxyredshift, double galaxymass_total, double galaxymass_fraction, vector<string> galaxysatellites) :
        hubble_type{ galaxyhubble_type }, redshift{ galaxyredshift }, mass_total{ galaxymass_total },
        mass_fraction{ galaxymass_fraction }, satellites{ galaxysatellites }{}

    galaxy(string galaxyhubble_type, double galaxyredshift, double galaxymass_total, double galaxymass_fraction) :
        hubble_type{ galaxyhubble_type }, redshift{ galaxyredshift }, mass_total{ galaxymass_total },
        mass_fraction{ galaxymass_fraction }{}

    //prototyping the functions inside the class
    void print_data();
    void hubble_type_change();
    double stellar_mass();
    void add_satellite();

    //Destructor
    //clears space before allocating data and after
    //~galaxy() { cout << "Destroying " << hubble_type << endl; }  
    ~galaxy() { cout << "" << endl; }
};

//scope resolution operator = ::
//without this, compiler thinks its a normal function which can't operate on private data
void galaxy::print_data()
{

    //modify to print number of satellites
    //if non zero, print satellite data

    // 2 significant figures
    cout.precision(3); 
    cout << "galaxy: [hubble_type,m,p,E, no. satellites] = [" << hubble_type << "," << redshift
        << "," << mass_total << "," << mass_fraction << ","<<satellites.size()<<"]" << endl;
    
    if (satellites.size() != 0){
        cout << "Satellite Data: " << endl;
        for (int i = 0; i < satellites.size(); ++i) {
            cout << satellites[i];
            cout << "" << endl;

        }
    }
    return;
}

void galaxy::hubble_type_change()
{
    string change;

    cout << "Would you like to change hubble type? (enter y to change) " ;
    cin >> change;

    if (change == "y"){
        cout << "Enter new hubble type: " ;
        cin >> hubble_type;
        //getline(cin, hubble_type);
        cin.clear();
        print_data();
        return;
    }

    else {
        return;
    }

}

double galaxy::stellar_mass() 
{
    double stellar_mass_value = mass_fraction * mass_total;
    return stellar_mass_value;
}

void galaxy::add_satellite() {

    string add = "y";
    string satellite_data;

    cout << "Would you like to add a satellite? (press y to add) ";
    cin >> add;
    cin.clear();
    while (add == "y") {
        cout << "Please enter a satellite: ";
        cin >> satellite_data;
        cin.clear();
        satellites.push_back(satellite_data);

        cout << "Would you like to add another satellite? (press y to add) ";
        cin >> add;

    }

    print_data();
    return;

}

int main()
{
    vector<galaxy> galaxy_data;

    //Choose random values in the correct ranges
    //Galaxy 1
    galaxy_data.push_back(galaxy("E0", 2.3, 1.5e12, 0.03)); //last entry = stellar mass fraction randomly picked
    //Galaxy 2
    galaxy_data.push_back(galaxy("Sa", 3.6, 5e10, 0.01)); //last entry = stellar mass fraction randomly picked

    //print out and alter galaxy details
    for (auto galaxy_it = galaxy_data.begin();
        galaxy_it < galaxy_data.end();
        ++galaxy_it) {
        galaxy_it->print_data();
        galaxy_it->hubble_type_change();
        galaxy_it->add_satellite();

        //return stellar mass
        std::cout << "Stellar mass =" << galaxy_it->stellar_mass() << std::endl;
        cout << "" << endl;

    }
    return 0;
}