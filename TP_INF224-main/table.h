#ifndef TABLE_H
#define TABLE_H
#include <iostream>
using namespace std;
#include <memory>
#include "multimedia.h"
#include "photo.h"
#include "video.h"
#include "film.h"
#include "groupe.h"
#include <map>
#include <fstream>

class Table
{

private:
    using objptr = shared_ptr<Multimedia>;
    using grpptr = shared_ptr<Groupe>;
    map <string, objptr> objets;
    map <string, grpptr> groupes;

public:
    Table(){};
    ~Table(){};

    shared_ptr<Photo> creerPhoto(string nom, string nom_fichier, double latitude, double longitude){
        auto p = make_shared<Photo>(nom, nom_fichier, latitude, longitude);
        if(objets.find(nom) != objets.end()){
            cerr<<"objet déjà créé ";
            return nullptr;
        }
        objets[nom] = p;
        return p;
    }

    shared_ptr<Video> creerVideo(string nom, string nom_fichier, int duree){
        auto v = make_shared<Video>(nom, nom_fichier, duree);
        if(objets.find(nom) != objets.end()){
            cerr<<"objet déjà créé ";
            return nullptr;
        }
        objets[nom] = v;
        return v;
    }

    shared_ptr<Film> creerFilm(string nom, string nom_fichier, int duree, const int* chapitre, int nbchap){
        auto f = make_shared<Film>(nom, nom_fichier, duree, chapitre, nbchap);
        if(objets.find(nom) != objets.end()){
            cerr<<"objet déjà créé ";
            return nullptr;
        }
        objets[nom] = f;
        return f;
    }

    shared_ptr<Groupe> creerGroupe(string nom){
        auto g = make_shared<Groupe>(nom);
        if(groupes.find(nom) != groupes.end()){
            cerr<<"groupe déjà créé ";
            return nullptr;
        }
        groupes[nom] = g;
        return g;
    }

    shared_ptr<Multimedia> findObjet(const string nom){
        auto it = objets.find(nom);
        if (it != objets.end()){
            return it->second;
        } else return nullptr;
    }

    shared_ptr<Groupe> findGroupe(const string nom){
        auto it = groupes.find(nom);
        if (it != groupes.end()){
            return it->second;
        } else return nullptr;
    }

    void affichage(ostream& cout, const string nom){ //on cherche et on affiche
        auto it = objets.find(nom);
        if(it != objets.end()){
            cout<<"\nobjet a les proprietes suivantes:\n";
            it->second->affichage(cout);
            return;
        } else{
            auto it2 = groupes.find(nom);
            if(it2 != groupes.end()){
                cout<<"\ngroupe a les proprietes suivantes\n";
                it2->second->affichage(cout);
                return;
            }
        }
        cout<<"\naucun objet ou groupe a le nom: "<<nom<<endl;
    }

    void Jouer(const string nom){
        auto it = objets.find(nom);
        if(it != objets.end()){
            it->second->jouer();
            return;
        }
        cout<<"\naucun objet multimedia a le nom: "<<nom<<endl;
    }

    void supprimerObjet(const string nom){
        auto it = objets.find(nom);
        if(it != objets.end()){
            objets.erase(it);
            cout<<"\nObjet de nom: "<<nom<<" à été supprimé\n";
        } else{
            cerr<<"objet n'existe pas ";
        }
    }

    void supprimerGroupe(const string nom){
        auto it = groupes.find(nom);
        if(it != groupes.end()){
            groupes.erase(it);
            cout<<"\nGroupe de nom: "<<nom<<" à été supprimé\n";
        } else{
            cerr<<"groupe n'existe pas ";
        }
    }

    shared_ptr<Multimedia> createfromClassName(const string& classname){
        if(classname == "Photo"){
            return make_shared<Photo>();
        } else if(classname == "Video"){
            return make_shared<Video>();
        } else if(classname == "Film"){
            return make_shared<Film>();
        } else return nullptr;
    }

    void save(const string& filename) const{
        ofstream file(filename);
        if(!file){
            cerr<<"fichier ne peut pas etre ouvert pour ecrire: "<<filename<<endl;
            return;
        }

        for(auto& it: objets){
            it.second->write(file);
        }
        file.close();
    }

    void load(const string& filename){
        ifstream file(filename);
        if(!file){
            cerr<<"fichier ne peut pas etre ouvert pour la lecture de: "<<filename<<endl;
        }

        while(true){
            string classname;
            if(!getline(file, classname)){ //getline appeler dans tous cas!!!
                break; //fin du fichier, on ne peut plus ecrire
            }
            auto obj = createfromClassName(classname);


            if(!obj){
                cerr<<"classe inconnue: "<<classname<<endl;
                break;
            }
            obj->read(file);
            objets[obj->getnom()] = obj;

        }
        file.close();
    }

};

#endif // TABLE_H
