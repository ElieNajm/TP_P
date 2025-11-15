#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H
#include<iostream>
#include <string.h>
using namespace std;

class Multimedia
{

private:
    string nom{};
    string nom_fichier{};

public:
    Multimedia();
    Multimedia(string nom, string nom_fichier);
    ~Multimedia();
    string getnom() const;
    string getnom_fichier() const;
    void setnom(string nom);
    void setnom_fichier(string nom_fichier);
    virtual void affichage(ostream & cout) const;
    virtual void jouer() const = 0; //methode abstraite
    virtual string getClassName() const;
    virtual void write(ostream& os) const;
    virtual void read(istream& is);
};

#endif // MULTIMEDIA_H
