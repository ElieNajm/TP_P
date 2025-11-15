#include "multimedia.h"
#include <iostream>
using namespace std;

Multimedia::Multimedia(){}

Multimedia::Multimedia(string nom, string nom_fichier)
{
    this->nom = nom;
    this->nom_fichier = nom_fichier;
}

string Multimedia::getnom() const {
    return nom;
}

string Multimedia::getnom_fichier() const{
    return nom_fichier;
}

void Multimedia::setnom(string nom){
    this->nom = nom;
}

void Multimedia::setnom_fichier(string nom_fichier){
    this->nom_fichier = nom_fichier;
}

void Multimedia::affichage(ostream & cout) const{
    cout<<" Nom: "<<nom<<", Nom du Fichier: "<<nom_fichier;
}

Multimedia::~Multimedia(){
    cout<<"Multimedia detruit"<<endl;
}

string Multimedia::getClassName() const{
    return "Multimedia";
}

void Multimedia::write(ostream& os) const{
    os<<getClassName()<<endl;
    os<<nom<<'\n'<<nom_fichier<<endl;
}

void Multimedia::read(istream& is){
    getline(is, nom);
    getline(is, nom_fichier);
}

