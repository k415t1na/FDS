//
//  main.cpp
//  PROJECTKM
//
//  Created by Kristina Myftaraga on 2/2/20.
//  Copyright © 2020 Kristina Myftaraga. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>



using namespace std;

class Company;
class Editor;
class User;
class VideoEditor;
class PhotoEditor;
class Simple;
class Complex;
class SocialMedia;
class VirtualReality;

vector < Company* > Companies;
vector < Company* > Promoted_Companies;
vector < Editor* > Editors;
vector < pair < Editor*, Company* > > FoundApps;
vector < User* > Users;
vector < string > OffersAvailable {"Photography","Single App", "All apps", "All package" };
vector < string > Apps {"PhotoEditor, Complex", "One out of 11 apps included in CC","PhotoEditor, Photoshop, Illustrator, InDesign, PremierPro, Dimension, InCopy, Spark, Capture, Comp, Bridge", "All apps + AdobeStock "};

void showOA() {
    cout << "Available Offers: \n";
    for (unsigned int i = 0; i < OffersAvailable.size(); i++) {
        cout << i + 1 << " - " << OffersAvailable[i] << endl;
    }
}
void showApps() {
    cout << "Apps included in the offer: \n";
    for (unsigned int i = 0; i < Apps.size(); i++) {
        cout << i + 1 << " - " << Apps[i] << endl;
    }
}

class Company {
public:
    Company() {
        cName = "";
        cAdress = "";
        cPhone = "";
        accessCode = "";
    }

    Company(string name, string adress, string phone, string ac) {
        cName = name;
        cAdress = adress;
        cPhone = phone;
        accessCode = ac;
    }

    void setname() {
        cout << "Enter the name of the company: ";
        string name;
        cin.ignore();
        getline(cin, name);
        this->cName = name;
    }

    void setadress() {
        cout << "Enter the adress: ";
        string adress;
        getline(cin, adress);
        this->cAdress = adress;
    }

    void setphone() {
        cout << "Enter phone number: ";
        string phone;
        cin >> phone;
        this->cPhone = phone;
    }

    string getCode() { return accessCode; }
    string getCname() { return cName; }
    string getCadress() { return cAdress; }
    string getCphone() { return cPhone; }


    void Info() {
        cout << "Company Overall Description\n\n";
        cout << getCname() << " is hiring\n";
        cout << "Location: " << getCadress() << endl;
        cout << "Phone: " << getCphone() << endl;
    }

private:
    string cName;
    string cAdress;
    string cPhone;
    string accessCode;
};


class Editor {
public:
    Editor() {
        cout << "Fill the Description below: \n\n ";
        setVersion();
        setFormat();
        setName();
        setID();
        setOsystem();
    }

    Editor(string NAME, string VERSION, string FORMAT, string id, string OSYSTEM) {
        eVersion = VERSION;
        eFormat = FORMAT;
        eName = NAME;
        ID = id;
        eOsystem = OSYSTEM;
    }

    void setName() {
        cout << "Name of the Editor: ";
        string n;
        cin.ignore();
        getline(cin, n);
        this->eName = n;
    }

    void setVersion() {
        cout << "Version: ";
        string a;
        getline(cin, a);
        this->eVersion = a;
    }

    void setFormat() {
        cout << "Format: ";
        string ag;
        cin >> ag;
        unsigned int w = atoi(ag.c_str());
        if (w) {
            this->eFormat = w;
        } else {
            cout << "\nEnter valid format!\n";
            setFormat(); }
    }

    void setOsystem() {
           cout << "Operating system: ";
           string os;
           cin >> os;
           unsigned int w = atoi(os.c_str());
           if (w) {
               this->eFormat = w;
           } else {
               cout << "\nEnter valid operating system!\n";
               setOsystem(); }
       }

    void setCompany(Company* object) {
        company = object;
    }

    void setID() {
        cout << "Enter the ID: ";
        string p;
        cin >> p;
        this->ID = p;
    }
               //virtual functions
    virtual void Description() {
        cout << "Name: " << eName;
        cout << "\nVersion: " << eVersion;
        cout << "\nFormat: " << eFormat << endl;
        cout << " Operating system : " << eOsystem << endl;
    }

    virtual double getTotalPrice() = 0;

    Company* getCompany() { return company; }
    string getEversion() { return eVersion; }
    string getEformat() { return eFormat; }
    string getoSystem() { return eOsystem; }
    string getEname() { return eName; }
    string getID() { return ID; }

private:
    Company *company;
    string eVersion;
    string eFormat;
    string eOsystem;
    string eName;
    string ID;

};

class PhotoEditor : public Editor {
public:
    PhotoEditor() {
        setOriginalSaved();
        setColorMode();
        setLayers();
    }

                                //constructor to read from the file
    PhotoEditor(string NAME, string VERSION, string id, string FORMAT, string OSYSTEM, bool _OriginalSaved, string _ColorMode, int layers):
        Editor(NAME, VERSION, FORMAT, id, OSYSTEM),
                OriginalSaved(_OriginalSaved),
                ColorMode(_ColorMode),
                Layers (layers){}

    void setOriginalSaved(){
        cout << "Do you want the original version of the photo saved? ";
        char solution;
        cin>>solution;
        switch (solution){
            case 'a':
            cout<<"yes"<<endl;
            break;

                case 'b':
                cout<<"no"<<endl;
                break;

                    default:
                    cout<<"Please select a or b"<<endl;
        }

        if (solution == 'a'){
                    cout<<"The original photo cannot be saved in Simple! Try Complex \n"<<endl;
                    //Complex;
                    }
                    else if (solution == 'b'){
                        cout <<"You may proceede with Simple!" << endl;
                        //Simple;
                    }
                    else {
                        cout << "Error!"<< endl;
                    }
    }

    void setColorMode() {
        cout << "The color mode: ";
        string p;
        cin.ignore();
        getline(cin, p);
        this->ColorMode = p;

    }

    void setLayers() {
        cout<< "The number of layers: ";
        int l;
        cin >>l;
        this->Layers = l;

    }

    void Description() {
        Editor::Description();
        cout << " OriginalSaved or Not " << OriginalSaved << endl;
        cout << " Select the color mode: " << ColorMode << endl;
        cout << " The number of layers " << Layers << endl;
        }

    bool getOriginalSaved() { return OriginalSaved; }
    string getColorMode() { return ColorMode; }
    int getLayers() { return Layers; }

private:
    bool OriginalSaved;
    string ColorMode;
    int Layers;
};

class Simple : public PhotoEditor {
public:
    Simple() {
        setFilters();
        setFeatures();
        setSIZE();
    }

    Simple(string NAME, string VERSION, string id, string FORMAT, string OSYSTEM, string SIZE, bool OriginalSaved, string ColorMode, int layers, string filter, string Features) :
                PhotoEditor(NAME, VERSION, id, FORMAT, OSYSTEM, OriginalSaved, ColorMode, layers),
                Filters(filter),
                SIZE (SIZE),
                Features (Features)
        {}

    void setFilters() {
        cout << "Enter an object to be a shape: ";
        string t;
        cin >> t;
        unsigned int w = atoi(t.c_str());
        if (w) {
            this->Filters = w;
            }else {
                 cout << "\nInvalid!\n";
                 setFilters();
         }
    }

    void setFeatures() {
        cout << "Features level  ";
               string e;
               cin >> e;
               unsigned int w = atoi(e.c_str());
               if (w) {
                   this->Features = w;
                   }else {
                   cout << "\n Negative!\n";
                   setFeatures(); }
           }


    void setSIZE() {
        cout << "SIZEs available:  ";
        string t;
        cin >> t;
        unsigned int w = atoi(t.c_str());
        if (w) {
            this->SIZE = w;
            }else {
            cout << "\nInvalid!\n";
            setSIZE(); }
    }

    double getTotalPrice(){
        return 10;
    }
    void Description() {
        PhotoEditor::Description();
        cout << " SIZEs availbale: " << getSIZE() << endl;
        cout << " Do you want the original saved? " << getOriginalSaved() <<endl;
        cout << " Custom Shape of the product: " << getFilters() <<endl;
        cout << " Features level: " << getFeatures() << endl;
    }

    string getFilters() { return Filters; }
    string getFeatures() { return Features; }
    string getSIZE() { return SIZE; }

private:
    string Filters;
    string Features;
    string SIZE;
};

class Complex : public PhotoEditor {
public:
    Complex() {
        setMobileFormat();
        setPortraitCorrection();
        setPhotoMasking();
        setCatalog();
        setTraceImage();
        setVector();
    }

    Complex(string NAME, string VERSION, string id, string FORMAT, string OSYSTEM, bool OriginalSaved, string ColorMode, int layers, string mf,  bool PortraitCorrection, string catalog, string masking, string traceimage, string _vector):
                PhotoEditor(NAME, VERSION, id, FORMAT, OSYSTEM, OriginalSaved, ColorMode, layers),
                MobileFormat(mf),
                PortraitCorrection(PortraitCorrection),
                Catalog (catalog),
                PhotoMasking (masking),
                TraceImage (traceimage),
                Vector (_vector)
    {}


    void setMobileFormat() {
        cout << "The photos are accesible in the mobile format ";
        string c;
        cin >> c;
        unsigned int w = atoi(c.c_str());
        if (w) {
            this->MobileFormat = w;
            }else {
                cout << "\nInvalid!\n"; setMobileFormat();
                }
    }
    void setPhotoMasking() {
           cout << "Masking options: ";
           string c;
           cin >> c;
           unsigned int w = atoi(c.c_str());
           if (w) {
               this->PhotoMasking = w;
               }else {
                   cout << "\nInvalid!\n"; setPhotoMasking();
                   }
       }

    void setPortraitCorrection() {
        cout << "Do you want it to be PortraitCorrection? ";
        string b;
        cin >> b;
        unsigned int w = atoi(b.c_str());
        if (w) {
            this->PortraitCorrection = w;
            } else {
                cout << "\nInvalid!\n"; setPortraitCorrection();
                 }
    }

    void setCatalog() {
        cout << "The photos saved in the catalog: ";
        string a;
        cin >> a;
        unsigned int w = atoi(a.c_str());
        if (w) {
            this->Catalog = w;
            } else {
                cout << "\nInvalid!\n";
                setCatalog();
                }
    }
    void setTraceImage() {
           cout << "Trace image editing:  ";
           string t;
           cin >> t;
           unsigned int w = atoi(t.c_str());
           if (w) {
               this->TraceImage = w;
               }else {
                   cout << "\nInvalid!\n";
                   setTraceImage();
                   }
       }

       void setVector() {
           cout << " Vector:  ";
           string t;
           cin >> t;
           unsigned int w = atoi(t.c_str());
           if (w) {
               this-> Vector = w;
               } else {
                   cout << "\nInvalid!\n";
                   setVector();
                   }
       }
    double getTotalPrice(){
        return 10;
    }

    void Description() {
        PhotoEditor::Description();
        cout << " The app accesible in the mobile format " << getMobileFormat() << endl;
        cout << " Do you want them to be PortraitCorrection? " << getPortraitCorrection() << endl;
        cout << " You want the original to be saved: " << getTraceImage() << endl;
        cout << " Photos saved in the catalog: " << getVector() << endl;
        cout << " Photo masking options: " << getPhotoMasking() <<endl;
        cout << " Photos saved in the catalog: " << getCatalog() << endl;
    }

    string getMobileFormat() { return MobileFormat; }
    bool getPortraitCorrection() { return  PortraitCorrection; }
    string getCatalog() { return Catalog; }
    string getPhotoMasking() { return PhotoMasking;}
    string getTraceImage() { return TraceImage; }
    string getVector() { return Vector; }

private:
    string MobileFormat;
    bool PortraitCorrection;
    string Catalog;
    string PhotoMasking;
    string TraceImage;
    string Vector;
};


class VideoEditor : public Editor {
public:
    VideoEditor() {
        setaudioformats();
        setMontage();
        seteffects();
    }

    VideoEditor(string NAME, string VERSION, string id, string FORMAT, string OSYSTEM, string am, string montage, string effects):
        Editor(NAME, VERSION, id, FORMAT, OSYSTEM),
        audioformats(am),
        Montage(montage),
        effects(effects)
        {}


    void setMontage() {
        cout << "Montage ";
        string t;
        cin >> t;
        unsigned int w = atoi(t.c_str());
        if (w) {
            this->Montage = w;
             }else {
                 cout << "\nInvalid!\n";
                 setMontage();
                 }
    }

    void seteffects() {
        cout << "effects ";
        string tim;
        cin >> tim;
        unsigned int w = atoi(tim.c_str());
        if (w) {
            this->effects = w;
            }else {
                cout << "\nInvalid\n";
                seteffects();
                }
    }

    void setaudioformats(){
        cout << "Audio Formats ";
            string af;
            cin >> af;
            unsigned int w = atoi(af.c_str());
            if (w) {
                this->effects = w;
                }else {
                    cout << "\nInvalid\n";
                    setaudioformats();
                    }
        }
       

    void Description() {
        Editor::Description();
        cout << "montage " << getMontage() << endl;
        cout << "effects " << geteffects() << endl;
         cout << "What format you want to use? " << getaudioformats() <<endl;
    }

    string getMontage() { return Montage; }
    string geteffects() { return effects; }
    string getaudioformats() { return audioformats; }

private:
    string Montage;
    string effects;
    string audioformats;
};


class SocialMedia : public VideoEditor {
public:
    SocialMedia() {
        setMotionGraphics();
        setproperties();
    }

    SocialMedia(string NAME, string VERSION, string id, string FORMAT, string OSYSTEM, string af, string montage, string effects, string motiongraphics, string properties):
                VideoEditor(NAME, VERSION, id, FORMAT, OSYSTEM, af, montage, effects),
                MotionGraphics (motiongraphics),
                properties (properties)
    {}

    void setMotionGraphics() {
        cout << "Motion Graphics ";
        string t;
        cin >> t;
        unsigned int w = atoi(t.c_str());
        if (w) {
            this->MotionGraphics = w;
            }else {
                cout << "\nInvalid!\n";
                setMotionGraphics();
                }
    }

    void setproperties() {
        cout << "Visual Effects";
        string tim;
        cin >> tim;
        unsigned int w = atoi(tim.c_str());
        if (w) {
             this->properties = w;
             }else {
                  cout << "\nInvalid\n";
                  setproperties();
                  }
    }

    double getTotalPrice(){
          return 10;
      }

    void Description() {
        Editor::Description();
        cout << "motion grapgics " << getMotionGraphics() << endl;
        cout << "Visual Effects " << getproperties() << endl;

    }

    string getMotionGraphics() { return MotionGraphics; }
    string getproperties() { return properties; }


private:
    string MotionGraphics;
    string properties;

};

class VirtualReality : public VideoEditor {
public:
    VirtualReality() {
        setPlatforms();
        setTransitions();
        setTimeline();
        setStory();
    }

    VirtualReality(string NAME, string VERSION, string id, string FORMAT, string OSYSTEM, string af, string montage, string effects,string platforms, string transitions, string story, string timeline):
                VideoEditor(NAME, VERSION, id, FORMAT, OSYSTEM, af, montage, effects),
                Platforms (platforms),
                Transitions (transitions),
                timeline (timeline),
                story (story)

    {}

    void setStory() {
        cout << "Time to finish a task: ";
        string tim;
        cin >> tim;
        unsigned int w = atoi(tim.c_str());
        if (w) { this->story = w; }
        else { cout << "\nInvalid\n"; setStory(); }
    }

    void setPlatforms() {
        cout << "Platforms";
        string t;
        cin >> t;
        unsigned int w = atoi(t.c_str());
        if (w) {
            this->Platforms = w;
        }else {
            cout << "\nInvalid!\n";
            setPlatforms(); }
    }

    void setTransitions() {
        cout << "Transitions";
        string tim;
        cin >> tim;
        unsigned int w = atoi(tim.c_str());
        if (w) {
            this->Transitions = w;
        }else {
            cout << "\nInvalid\n";
            setTransitions(); }
    }

    void setTimeline() {
        cout << "The timeline: ";
        string t;
        cin >> t;
        unsigned int w = atoi(t.c_str());
        if (w) { this->timeline = w; }
        else { cout << "\nInvalid!\n"; setTimeline(); }
    }

    double getTotalPrice(){
          return 10;
      }

    void Description() {
        Editor::Description();
        cout << "Platforms available on: " << getPlatforms() << endl;
        cout << "Transitions " << getTransitions() << endl;
        cout << "Story of the virtual relaity" << getStory() << endl;
        cout << "The timeline" << getTimeline() << endl;
    }

    string getPlatforms() { return Platforms; }
    string getTransitions() { return Transitions; }
    string getStory() { return story; }
    string getTimeline() { return timeline; }

private:
    string Platforms;
    string Transitions;
    string story;
    string timeline;

};

class User {

public:

    User() {
        setName();
        setID();
        setPhone();
        setAdress();
        setBudget();
        }


    User(string n, string id, double budget, string ad, string phone) {
        Budget = budget;
        Adress = ad;
        Phone = phone;
        Name = n;
        ID = id;
    }


    void setName() {
        cout << "Name: ";
        string n;
        cin.ignore();
        getline(cin, n);
        this->Name = n;
    }

    void setAdress() {
        cout << "Adress: ";
        string a;
        cin.ignore();
        getline(cin, a);
        this->Adress = a;
    }

    void setPhone() {
        cout << "Phone Number: ";
        string p;
        cin >> p;
        this->Phone = p;
    }

    void CreateEditors(){

        cout<<"Photo (1) or Video (2) \n";
        string choice;
        cin>>choice;
        if(choice=="1"){
           CreatedEditors.push_back(new Complex());
        }
        else if (choice=="2"){

        }
        else{
            cout<<"Invalid input!\n";
            CreateEditors();
        }

    }

    void setBudget() {
        cout << "Budget: ";
        string b;
        cin >> b;
        unsigned int w = atoi(b.c_str());
        if (w) { this->Budget = w; }
        else { cout << "\nInvalid!\n"; setBudget(); }
    }

    void reduceBudget(int b) {
        Budget -= b;
    }

    void setCompany(Company *C) {
        comp = C;
        hasComp = true;
    }

    void setID() {
        cout << "ID: ";
        string id;
        cin >> id;
        this->ID = id;
    }

    bool getStatus(){return hasComp;}

    vector<Editor*> getCreatedEditors() { return CreatedEditors; }
    vector<Editor*> getBoughtEditors() { return BoughtEditors; }
    string getAdress() { return Adress; }
    double getBudget() { return Budget; }
    string getPhone() { return Phone; }
    string getName() { return Name; }
    string getID() { return ID; }
    Company* getCompany() { return comp; }
    bool has() { return hasComp; }

private:
    vector<Editor*> CreatedEditors;
    vector<Editor*> BoughtEditors;

    double Budget = 0;
    string Adress = "";
    string Phone = "";
    string Name = "";
    string ID = "";

    Company *comp;
    bool hasComp = false;
};




//------------------------------------------------------------Functions------------------------------------------Functions----------------------------------------------

void UserMenu() {
    cout<< "\tUser Menu\n";
    cout<<" 1) Login \t\t 2) Register";
    cout<<"\nChoice: ";
    char choice;
    cin>>choice;
    if(choice=='1'){
        cout<<"First Name: ";
        string name,id;
        cin.ignore();
        getline(cin,name);

        cout<<"ID: ";
        cin>>id;
        bool loggedIn = false;
        for(auto currUser : Users){
            if( currUser->getName() == name && currUser->getID()==id){
                cout<<"Successfully logged in as "<<name<<endl;
                loggedIn = true;

                if(currUser->getStatus()){
                    cout<<"  > Current company: " << currUser->getCompany()->getCname()<<"\n";
                }
                else{
                    cout<<"  > User not part of our partner Companies!\n";
                }
                cout << "Please make a choice...";
                cout << "\n\n 1) Apply to Company \n 2) Buy Editor\n";
                char choice;
                cout<<" > ";
                cin>>choice;
                if(choice=='1'){ // list companies and apply
                    int it=1;
                    for(auto currCompany: Companies){
                        cout<<it<<") "<<currCompany->getCname()<<endl;
                        it++;
                    }
                    if(it==1){
                        cout<<"Not promoted Companies!\n\n";
                    }
                }
                else if(choice=='2'){ // list Editors and buy (compare price and budget)
                    int it=1;
                    for(auto currEditor: Editors){
                        cout<<it<<") "<<currEditor->getEname()<<endl;
                        it++;
                    }
                    if(it==1){
                        cout<<"No Editors for sale!\n\n";
                    }
                }

            }
        }
        if(loggedIn==false){
            cout<<" Incorrect name or ID!\n\n";
        }


    }
    else if( choice=='2'){
        User* curr = new User();
        Users.push_back(curr);
        cout<<" Successfully registered!\n\n";
        UserMenu();
    }
}

void addCompany() {
    cout << "Number of featured Companies: ";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        Companies.push_back(new Company());
        cout << Companies[i]->getCname() << " successfully added\n";
    }
}

//MergeSort Algorithm to be used in the main function
void merges(vector<Editor*>&collection, int start, int mid, int ends) {
// temp vector of items
    vector<Editor*>temp(ends - start + 1);

// iterators of intervals
    int i = start, j = mid+1, k = 0;

// here we compare and add smaller  to temp  (when comparing doubles use 0.0001 for precision)
    while(i <= mid && j <= ends) {

    if( collection[i]->getTotalPrice() <= collection[j]->getTotalPrice()) {
            temp[k] = collection[i];
            k += 1; i += 1;
        }
        else {
            temp[k] = collection[j];
            k += 1; j += 1;
        }
    }
    while(i <= mid) {
        temp[k] = collection[i];
        k += 1; i += 1;
    }
    // Copy the remaining elements of vector<Item*> ends , if there are any
    while(j <= ends) {
        temp[k] = collection[j];
        k += 1; j += 1;
    }
    // Copy the remaining elements of vector<Item*> starts , if there are any
    for(i = start; i <= ends; i += 1) {
        collection[i] = temp[i - start];
    }
}

void mergeSort( vector<Editor*>&collection, int start, int ends) {
    if(start < ends) {
          //Sort the first and second halves
        int mid = (start + ends) / 2;
         //Recursion of mergeSort function
        mergeSort(collection, start, mid);
        mergeSort(collection, mid+1, ends);
         //merge the two halves together
        merges(collection, start, mid, ends);
    }
}

void EditorsInfo() {
    if (Editors.size() == 0) { cout << "\n  Not available Editors\n\n"; }
    else {
       // quickSort(PhotoEditors, 0, PhotoEditors.size() - 1);
        cout << "The Editor, sorted based on their price, are:\n " << endl;
        mergeSort(Editors,0,(int)Editors.size()-1);//calling the function
        cout << "Select an Editor to get Description:\n";
        for (unsigned int q = 0; q < Editors.size(); q++) {
            cout << endl << q + 1 << " - " << Editors[q]->getEname() << endl;
        }
        cout << "Choice: ";

        string c;
        cin >> c;

        unsigned int w = atoi(c.c_str());

        if (w && w <= Editors.size()) {

            cout << "\n\nDisplaying Description...\n\n";
            Editors[w - 1]->Description();
        }

        else { cout << "\nInvalid command!\n\n"; EditorsInfo(); }
    }
}

void readCompanies() {
    ifstream Database("Companies.txt");

    if (Database.fail()) { cout << "\nFailed accessing Companies"; }
    else {


        while (!Database.eof()) {
            string name;
            string adress;
            string phone;
            string ac;

            Database >> name >> adress >> phone >> ac;
     if (!Database.eof()) { Companies.push_back(new Company(name, adress, phone, ac));
     }
        }
        Database.close();
    }
}


void readUsers() {

    ifstream O;
    O.open("Users.txt");
    if (!O) { cout << "\nProblem importing User data!"; }

    string line;

    while (getline(O, line)) {
        string name, adress, budget, id, phone;
        istringstream ss(line);
        while (getline(ss, name, ',')) {
            getline(ss, adress, ',');
            getline(ss, id, ',');  //User(string n,string ad,string id,string phone, int budget)
            getline(ss, phone, ',');

            getline(ss, budget);

            int budgets = atoi(budget.c_str());

            Users.push_back(new User(name, id, budgets, adress, phone));
                }
    }
    O.close();

}


void readEditors() {

    ifstream C;
    C.open("Editors.txt");

    if (C.fail()) { cout << "\nFailed accessing Editors!\n"; }

    string line;
    while (getline(C, line)) {

        string name,VERSION,id,type, rate, FORMAT,  OSYSTEM, _OriginalSaved, _ColorMode,layers, mf,PortraitCorrection,catalog, masking, traceimage,_vector,SIZE,filter, features,AD, audioformats, montage, effects, motiongraphics, properties, platforms, transitions, story, timeline;
        istringstream qs(line);

        while (getline(qs, type, ',')) {

            if (type == "Complex") {
                getline(qs, name, ',');
                getline(qs, VERSION, ',');
                getline(qs, id, ',');
                getline(qs, FORMAT, ',');
                getline(qs, OSYSTEM, ',');
                getline(qs, _OriginalSaved, ',');
                getline(qs, _ColorMode, ',');
                getline(qs, layers, ',');
                getline(qs, mf, ',');
                getline(qs, PortraitCorrection, ',');
                getline(qs, catalog, ',');
                getline(qs, masking, ',');
                getline(qs, traceimage, ',');
                getline(qs, _vector);
                int Layers = atoi(layers.c_str());
                bool OS=0,PC=0;
                if(_OriginalSaved=="Yes")OS=1;
                if(PortraitCorrection=="Yes")PC=1;

                Editors.push_back(new Complex(name, VERSION, id, FORMAT, OSYSTEM,OS,_ColorMode,Layers, mf, PC, catalog, masking, traceimage,_vector));

            }

            else if (type == "Simple") {
                getline(qs, name, ',');
                getline(qs, VERSION, ',');
                getline(qs, id, ',');
                getline(qs, FORMAT, ',');
                getline(qs, OSYSTEM, ',');
                getline(qs, SIZE, ',');
                getline(qs, _OriginalSaved, ',');
                getline(qs, _ColorMode, ',');
                getline(qs, layers, ',');
                getline(qs, filter, ',');
                getline(qs, features);
               int Layers = atoi(layers.c_str());
                bool OS=0;
               if(_OriginalSaved=="Yes")OS=1;


                Editors.push_back(new Simple(name, VERSION, id, FORMAT, OSYSTEM,SIZE,OS,_ColorMode,Layers,filter,features));
            }

            else if (type == "Social Media") {

                getline(qs, name, ',');
                getline(qs, VERSION, ',');
                getline(qs, id, ',');
                getline(qs, FORMAT, ',');
                getline(qs, OSYSTEM, ',');
                getline(qs, AD, ',');
                getline(qs, audioformats, ',');
                getline(qs, montage);
                getline(qs, effects);
                getline(qs, motiongraphics);
                getline(qs, properties);

                Editors.push_back(new SocialMedia(name, VERSION, id, FORMAT, OSYSTEM, audioformats, montage, effects, motiongraphics, properties));

        }

        else if (type == "Virtual Reality") {
                       getline(qs, name, ',');
                       getline(qs, VERSION, ',');
                       getline(qs, id, ',');
                       getline(qs, FORMAT, ',');
                       getline(qs, OSYSTEM, ',');
                       getline(qs, audioformats, ',');
                       getline(qs, montage);
                       getline(qs, effects);
                       getline(qs, platforms, ',');
                       getline(qs, transitions, ',');
                       getline(qs, story, ',');
                       getline(qs, timeline);

                Editors.push_back(new VirtualReality(name, VERSION, id, FORMAT, OSYSTEM, audioformats, montage, effects, platforms, transitions, story, timeline));

                   }

               }
    }
    C.close();

}

//BM Algorithm
void HelperMethod( string str, int size,  int tempArr[256])
{
    int i;
    // Initialize all occurrences as -1
    for (i = 0; i < 256; i++)tempArr[i] = -1;
    for (i = 0; i < size; i++)tempArr[(int) str[i]] = i;
}

/* A pattern searching function that uses BadCharacter Heuristic of Boyer Moore Algorithm */
int  CurrOccurances=0;
void searchBM( string txt, string pat)
{
    int m = (int)pat.size();
    int n = (int)txt.size();
    int tempArr[256];
    HelperMethod(pat, m, tempArr);
    int s = 0; // s is shift of the pattern withrespect to text
    while(s <= (n - m))
    {
        int j = m - 1;
        while(j >= 0 && pat[j] == txt[s + j])j--;
        if (j < 0)
        {
            CurrOccurances+=1;//this keeps track of the number of occurancies of the word and then sort those in decreasing order.
            if(s+m < n) s+= m-tempArr[txt[s + m]];
            else s+=1;
        }
        else s += max(1, j - tempArr[txt[s + j]]);
    }
}


string lowerWord(string temp){
    string toReturn ="";
    for(char x: temp)
    {
        toReturn += tolower(x);

    }
    return toReturn;
}

void importData() {

    readUsers();
    readCompanies();
    readEditors();
}


void OnlineStoreMenu() {
    cout << "\n\n\t\t  * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n";
    cout << "\t\t *            Welcome to our online store                *\n";
    cout << "\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n ";
    string choice;


       do {
          // cout << "\n\n" << setw(70) << "[:] Current Web Earnings: $" << WebEarnings << endl;
           cout << setw(40) << "\n \t\t  1-User Menu"<< setw(32) << "3-List Editors"
               << "\n\t\t  2-Close" << setw(47) << "4-List Promoted Companies";
           cout << "\n\t    *                                                       *";
           cout << "\n\t\t * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n ";
           cout<<"\n\nChoice: ";
           cin >> choice;



           if (choice == "2") {
               cout<<"\n\n Goodbye!\n\n";
               }

           else if (choice == "1") { UserMenu(); cout << "\nENTER to continue..."; cin.ignore(); cin.ignore(); }
           else if (choice == "3") {

               EditorsInfo();
               OnlineStoreMenu(); cout << "\nENTER to continue..."; cin.ignore(); cin.ignore(); }

           else if (choice == "4") { OnlineStoreMenu(); cout << "\nENTER to continue..."; cin.ignore(); cin.ignore();}

           else { cout << "\nInvalid\n"; }

       } while (choice != "0");

}

//-----------------------------------------------Main------------------------------------------------------------Main-------------------------------------------------------------------------------------


int main()
{

    cout << "\n\t\t\t\tPress ENTER to continue\n";
    cin.ignore();

    importData();
    OnlineStoreMenu();

}
