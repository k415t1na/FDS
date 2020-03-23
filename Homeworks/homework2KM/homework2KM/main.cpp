//
//  main.cpp
//  homework3KM
//
//  Created by Kristina Myftaraga on 3/1/20.
//  Copyright © 2020 Kristina Myftaraga. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Division class interface
class Division {
public:
    
    //This is the default constructor for this class.
    Division() {
        this->GUID = "";
        this->name = "";
        this->description = "";
        this->phonenumber = "";
    }
   
    //entering data through the class' constructor
   Division(string GUID, string name, string phonenumber, string description, Division* parentDivision = NULL){  //Division is a custom data type
        this->GUID = GUID;
        this->name = name;
        this->phonenumber = phonenumber;
        this->description = description;
        this->parentDivision = parentDivision;
    }
    
    //getting name of the division, which is not going to change
    string getName()  { return this->name; }
    string getGUID()  { return this->GUID; }

    //checking if "GUID" is unique for this devision
    bool isUnique( vector<Division*> &Divisions,  Division & newDivision)  {
        for (int i = 0; i < Divisions.size(); ++i) {
            if (newDivision.GUID == Divisions[i]->GUID) {
                return false;
            }
        }
        return true;
    }
    

private:
    //attributes of the Division class
    string GUID, name, phonenumber;
    string description;
    //pointing to the parent Division
    Division * parentDivision;
};


//--------------------------------------------------------------------------------------------------------------------------------

class Item {   //abstract class created
public:
    Item (){};
    virtual string getName()= 0;
    virtual string getGUID()= 0;
    virtual double getTotalPrice()= 0;//virtual function
};


//--------------------------------------------------------------------------------------------------------------------------------

class Artifact : public Item {
public:
    
    //enum type, which is a user-defined data type, is used here to represent the 2 types of discounts
    enum DiscountType {
        amount, percentage
    };
    
    //this is the default constructor for the Artifact class, without parametres
    Artifact(){
        this->GUID = "";
        this->Name = "";
        this->Description = "";
        this->Price = 0.0;
        this->Discount = 0.0;
        this->Quantity = 0;
        this->discountType = amount;
        
        this->division = new Division;
    }

    //adding parametres to the default constructor
    Artifact(string GUID, string Name, string Description,string Category, double Price, double Discount, int Quantity, Division* division, DiscountType discountType) {
        
        this->GUID = GUID;
        this->Name = Name;
        this->Description = Description;
        this->Category = Category;

        //Price, Discount and Quantity can't be negative
        if (this->Price > 0) { this->Price = Price; }
        else { Price=0; }

        if (this->Discount >= 0) { this->Discount = Discount; }
        else { Discount=0; }

        if (this->Quantity >= 0) { this->Quantity = Quantity; }
        else { Quantity=0; }

        this->discountType = discountType;
        this->division = division;
    }

    //getting Artifact's name
    string getName (){return this->Name;}
    string getGUID (){return this->GUID;}
    
    //calculate the price after the discount
    double getEffectivePrice(){
        double effectivePrice = this->Price - this->Price*this->Discount / 100;
        if (this->discountType == amount) {
            effectivePrice = this->Price - this->Discount;
        }
        if (effectivePrice > 0) { //this can't be negative
            return effectivePrice;
        }
        return 0;
    }

    //calculating the total price of the Artifacts
    double getTotalPrice(){
        double totalPrice = this->Quantity * Artifact::getEffectivePrice();
        if (totalPrice > 0) { //can't be negative
            return totalPrice;
        }
        return 0;
    }

private:
    string GUID, Name, Category, Description;
    double Price, Discount;
    int Quantity;
    Division * division;
    DiscountType discountType;
};

//--------------------------------------------------------------------------------------------------------------------------------

class Service : public Artifact {
public:
    //creating a user-defined data type to represent, once again, the type of discounts offered
    enum RateDiscountType {
        amount, percentage
    };
    //the default constructor for the Service class, without parametres
    Service(){
        this->Duration = 0.0;
        this->Rate = 0.0;
        this->RateDiscount = 0.0;
        this->rateDiscountType = amount;
    }
    //the class constructor, now overriding the default constructor
    Service(string GUID, string Name, string Description,string Category,double Price, double Discount, int Quantity,Division* division,
            DiscountType discountType, double Duration, double Rate, double RateDiscount,RateDiscountType rateDiscountType):
    Artifact(GUID, Name, Description,Category,Price, Discount, Quantity,division, discountType){
       
    //RateDiscount, Duratiom and Rate can't be negative
        if (this->Duration >= 0) {this->Duration=Duration;}
        else {Duration=0.0;}
   
        if (this->Rate >=0) {this->Rate=Rate;}
        else {Rate=0.0;}
    
        if (this->RateDiscount >=0) {this->RateDiscount=RateDiscount;}
        else {RateDiscount=0.0;}
}
    double getDuration(){return Duration;}
    
    //using accessor to get the service's name
    double getEffectiveRate() {
        double effectiveRate;
        if (this->rateDiscountType == amount) {
            effectiveRate = this->Rate - this->RateDiscount;
        }
        else {
            effectiveRate = this->Rate - this->Rate * this->RateDiscount / 100;
        }
        //this method can't return a negative value
        if (effectiveRate > 0) {
            return effectiveRate;
        }
        return 0;
    }

     double getTotalPrice() {
        double totalPrice = Artifact::getTotalPrice() + getEffectiveRate()* getDuration(); // check
        //this function can't return a negative value
        if (totalPrice > 0) {
            return totalPrice;
        }
        return 0;
    }

private:
    double Duration, Rate, RateDiscount;
    RateDiscountType rateDiscountType;

};
//-----------------------------------------------------------------------------------------------------------------------
class BM {
public:
    //This is the default constructor for this class.
     BM() {
         this->pattern = "";
         this->text = "";
         this->pos = 0;
     }
    
     //entering data through the class' constructor
     BM(string p, string t){  //Division is a custom data type
         this->pattern = p;
         this->text =t;
         this->pos = 0;
         {
             patlen = (int) pattern.length();
         
             for (int i = 0; i < 256; i++)  // empty the positions array
                 positions[i] = 0;
         
             for (int i = 0; pattern[i]; i++)  // record the positions of characters
                 positions[pattern[i]] = i;
         }
     }
    
    int operator++ (){
        //pos += 1;
    
        int lastpos = (int)text.length() - patlen;  // last possible starting position
    
        while (pos <= lastpos) {
            int j = patlen - 1;
    
            // loop over pattern from right side
            while ((j >= 0) && (text[pos + j] == pattern[j]))
                j--;
    
                if (j < 0)
                    return 1;  // found a match
    
                pos += max(1, j - positions[text[pos + j]]);  // else advance position
            
            }
    
        pos = -1;
        return 0;
    }

    
private:
    string pattern;
    short int positions[256];
    string text;
    int pos;
    unsigned int patlen;
};

//---------------------------------------------------------------------------------------------------------------------------------

int main() {

    vector<Division*>Divisions;
    //vector<Artifact*>Artifacts; deleted
    //vector<Service*>Services; deleted
    vector<Item*> items;

    //Adding three new divisions to the Division collection
    Division * homeAppliance = new Division("ABCD-EFGH-0001", "Home Appliances", "069 899 223","Home appliances are electrical / mechanical machines which accomplish some household functions, such as cooking, cleaning, or food preservation");
    Division * transportationVehicles = new Division("ABCD-EFGH-0002", "Transportation Vehicle", "344 555 666","A vehicle is a machine that transports people or cargo. Vehicles include wagons, bicycles, motor vehicles (motorcycles, cars, trucks, buses), railed vehicles (trains, trams), watercraft (ships, boats), amphibious vehicles (screw-propelled vehicle, hovercraft), aircraft (airplanes, helicopters) and spacecraft.");
    Division * maintenance = new Division("ABCD-EFGH-0003", "Maintenance","123 4567 890", "The technical meaning of maintenance involves functional checks, servicing, repairing or replacing of necessary devices, equipment, machinery, building infrastructure, and supporting utilities in industrial, business, governmental, and residential installations.");

    //Checking if the division has an unique GUID
    if (homeAppliance->isUnique(Divisions, *homeAppliance)) {
        Divisions.push_back(homeAppliance);
    }
    else {
        cout << "GUID is not unique for this product: " << homeAppliance->getName() << endl;
    }
    //Checking if the division has an unique GUID
    if (transportationVehicles->isUnique(Divisions, *transportationVehicles)) {
        Divisions.push_back(transportationVehicles);
    }
    else {
        cout << "GUID is not unique for this product: " << transportationVehicles->getName() << endl;
    }
    //Checking if the category has an unique GUID
    if (maintenance->isUnique(Divisions, *maintenance)) {
        Divisions.push_back(maintenance);
    }
    else {
        cout << "GUID is not unique for this product: " << maintenance->getName() << endl;
    }


    //Adding  three products to the Artifacts list, which have a correct Division from the list of available and instantiated divisions in the previous step
    Artifact *Toyota = new Artifact ("001-ABCD", "2020 Toyota RAV4 XLE FWD X", "Hands-Free Access Power\n, Tailgate Wireless Phone Charger\n, 19-Inch Alloy Wheels\n,Heated Steering Wheel\n,LED Headlights with Auto-On/Off\n,Honda Satellite-Linked Navigation System™\n,Turn-By-Turn Directions\n,Roof Rails\n,330-Watt Premium Audio System with 9 Speakers\n,Dual Chrome Exhaust Finishers\n,Ambient Lighting\n, Rain-Sensing Windshield Wipers", "Compact crossover SUV",33250.22, 5.3,2, transportationVehicles, Artifact::amount);
    Artifact *RangeRover = new Artifact("002-ABCD", "Range Rover (P38A)", "The new model offered more equipment and premium trims, positioning the vehicle above the Land Rover Discovery to face the increased competition in the SUV marketplace. It is usually known as the Range Rover P38 or P38A outside of Land Rover, after the office building in which the vehicle development team was based..", "Full-size luxury SUV", 5509.9, 1.0, 2, transportationVehicles, Artifact::amount);
    Artifact  *BissellVacuumCleaner = new Artifact("003-ABCD", "Bissell Vacuum Cleaner", "Lightweight, yet powerful\n,On-board tools\n,Filter replacement: Febreze Spring & Renewal BISSELL Style 1214 Replacement Vacuum Filter, model 12141rs, handheld cleaners and cordless vacuum cleaners for your home. Available from Bosch now.","vacuum Cleaner", 2.2, 3.9, 5, homeAppliance, Artifact::percentage);
    
    // adding the new products to the Artifact vector
        items.push_back(Toyota);
        items.push_back(RangeRover);
        items.push_back(BissellVacuumCleaner);
    /*Artifacts.push_back(Toyota);
    Artifacts.push_back(RangeRover);
    Artifacts.push_back(BissellVacuumCleaner);*/
    
    //Adding at least three services to the Services list, having a valid Division
    Service *repairVehicles = new Service("001-ABCD", "Repair Vehicle", "An auto repair shop performs regular maintenance and repairs moving parts.", "Compact crossover SUV",33250.22, 5.3,2, transportationVehicles,Artifact::amount,11.1, 12, 2, Service::amount);
    Service *Convergence = new Service( "002-ABCD", "Convergence ", "Convergence is the coming together of two different entities, and in the contexts of computing and technology, is the integration of two or more different technologies in a single device or system.", "Full-size luxury SUV", 5509.9, 1.0, 2, transportationVehicles, Artifact::amount, 4.0, 13.0, 25.0, Service::amount);
    Service *repairHomeAppliances = new Service("003-ABCD", "Repair Home Appliances", "Restoration, checks for electricity etc. ","Vacuum Cleaner", 2.2, 3.9, 5, homeAppliance, Artifact::percentage, 3.0, 14.0, 25.0, Service::percentage);
    
     // adding the new services to the services vector
        items.push_back(repairVehicles);
        items.push_back(Convergence);
        items.push_back(repairHomeAppliances);
       /* Services.push_back(repairVehicles);
        //Services.push_back(Convergence);
        //Services.push_back(repairHomeAppliances);*/

    
/*
    //Using two loops to show the Name and Total Price of each artifact and service in the store
    for (int i = 0; i < Artifacts.size(); ++i) {
        cout << "Artifact name: " << Artifacts[i]->getName() << endl;
        cout << "Total Price: " << Artifacts[i]->getTotalPrice() << endl;
        cout << endl;
    }

    for (int i = 0; i < Services.size(); ++i) {
        cout << "Service name: " << Services[i]->getName() << endl;
        cout << "Total Price: " << Services[i]->getTotalPrice() << endl;
        cout << endl;
    }
    return 0;
}
*/
    string finder1;
    cout << "Enter the word you want to search: \b";
    cin >> finder1;
    

    //a loop to calculate and display the total prices of all elements in the Items collection
    for (Item * i : items) {
            
            BM finder(finder1, i->getName());
                   if (++finder) {cout << i->getName() << endl;
           // cout << "Total price: " << i->getTotalPrice() <<"$"<< endl;
                      cout << "      GUID: " << i->getGUID() << endl;
        }
    }
}
