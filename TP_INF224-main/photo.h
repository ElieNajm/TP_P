#ifndef PHOTO_H
#define PHOTO_H
#include<iostream>
#include"multimedia.h"
#include<string.h>
using namespace std;

class Photo : public Multimedia
{

private:
    double latitude{};
    double longitude{};

public:
    Photo(){
        latitude=0;
        longitude=0;
    }

    Photo(string nom, string nom_fichier, double latitude, double longitude):
        Multimedia(nom, nom_fichier)
    {
        this->latitude = latitude;
        this->longitude = longitude;
    }

    ~Photo(){
        cout<<"Photo detruite"<<endl;
    }
    double getlatitude() const{return latitude;};
    double getlongitude() const{return longitude;};
    void setlatitude(double latitude){this->latitude = latitude;};
    void setlongitude(double longitude){this->longitude = longitude;};
    void affichage(ostream & cout) const override {
        Multimedia::affichage(cout);
        cout<<", la latitude est: "<<latitude<<", la longitude est: "<<longitude;
    }
    void jouer() const override{
        string cmd = "imagej "+ getnom_fichier();
        system(cmd.c_str());
    }

    string getClassName() const override{
        return "Photo";
    }

    void write(ostream& os) const override{
        Multimedia::write(os);
        os<<latitude<<endl<<longitude<<endl;
    }

    void read(istream& is) override{
        Multimedia::read(is);
        string lat;
        getline(is, lat);
        latitude = stod(lat);
        string longi;
        getline(is, longi);
        latitude = stod(longi);
    }

};

#endif // PHOTO_H
