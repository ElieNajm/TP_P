#ifndef VIDEO_H
#define VIDEO_H
#include<iostream>
#include"multimedia.h"
#include<string.h>
using namespace std;

class Video : public Multimedia
{

private:
    int duree{};

public:
    Video(){duree = 0;};
    Video(string nom, string nom_fichier, int duree) :
        Multimedia(nom, nom_fichier)
    {
        this->duree = duree;

    }
    ~Video(){
        cout<<"Video detruite"<<endl;
    }
    int getduree() const{return duree;};
    void setduree(int duree){this->duree = duree;};
    void affichage(ostream & cout) const override {
        Multimedia::affichage(cout);
        cout<<", la duree est: "<<duree;
    }
    void jouer() const override{
        string cmd = "mpv "+ getnom_fichier();
        system(cmd.c_str());
    }

    string getClassName() const override{
        return "Video";
    }

    void write(ostream& os) const override{
        Multimedia::write(os);
        os<<duree<<endl;
    }

    void read(istream& is) override{
        Multimedia::read(is);
        string dur;
        getline(is, dur);
        duree = stoi(dur);
    }

};

#endif // VIDEO_H
