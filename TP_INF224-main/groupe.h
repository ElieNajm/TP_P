#ifndef GROUPE_H
#define GROUPE_H
#include<iostream>
using namespace std;
#include<list>
#include"multimedia.h"
#include<memory>

class Groupe :public list<shared_ptr<Multimedia>>
{
private:
    string nom{};

public:
    Groupe();

    Groupe(const string& nom){
        this->nom = nom;
    }

    string getnom() const{ return nom;}

    void affichage(ostream& cout) const{ //pas besoin d'override car elle n'herite pas de Multimedia
        cout<<" Nom du Groupe: "<<nom;
        for(auto it = this->begin(); it != this->end(); it++){
            (*it)->affichage(cout); //chaque objet va appeler sa propre methode d'affichage, ce n'est donc pas une recurrence
        }
    }

    ~Groupe(){
        cout<<"Groupe detruit"<<endl;
    }
};

#endif // GROUPE_H
