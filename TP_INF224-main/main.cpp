//
// main.cpp
// Created on 21/10/2018
//
#include "multimedia.h"
#include "photo.h"
#include "video.h"
#include <iostream>
#include "film.h"
#include <memory>
#include "groupe.h"
#include "table.h"
#include <sstream>
#include "tcpserver.h"
#include "ccsocket.h"
#include <string>
#include<map>
using namespace std;

//#define VERSION_OLD //supprimer le commentaire de la version a compilé
#define VERSION_SERVER
//#define VERSION_SERIALISATION

#ifdef VERSION_OLD
void printjouer(Multimedia** t, unsigned int c){
    for(unsigned int i=0; i<c; i++){
        t[i]->affichage(cout);
        cout<<endl;
    }
}

int main(int argc, const char* argv[])
{
    //Multimedia * m = new Multimedia();
    //Multimedia * m2 = new Multimedia("videos", "hi");
    //m2->affichage(cout);

    //Multimedia est maintenant une classe abstraite a cause de la methode abstraite, on ne pourra plus instancer des objets de cette classe

    Multimedia** Jouer = new Multimedia* [10];
    unsigned c = 0;
    Jouer[c++] = new Photo("Pillars of Creation :-)", "Espace", 20, 30);
    Jouer[c++] = new Video("Messi Last Minute Goal", "Football", 120);
    Jouer[c++] = new Photo("Elie Najm Photo", "Student Photos", 14, 43);
    printjouer(Jouer, c);

    int duree[] = {10, 20, 38, 44, 68};
    Film f ("Intersetllar", "Sci-fi movies", 180, duree, 5);
    f.affichage(cout);

    duree[2] = 36; // on remarquera l'independence
    f.affichage(cout);

    auto p1 = make_shared<Photo>("Tour Eiffel", "Monuments en France", 42, 23);
    auto v1 = make_shared<Video>("Climbing Mount Everest Vlog", "my Vlogs", 3600);
    int duree2[] = {60, 90, 10};
    auto f1 = make_shared<Film>("Inception", "Sci-fi movies", 160, duree2,3);

    Groupe aventures("aventures");
    aventures.push_back(p1);
    aventures.push_back(v1);
    aventures.push_back(f1);

    Groupe cinema("cinema");
    cinema.push_back(f1);

    aventures.affichage(cout);
    cinema.affichage(cout);

    auto it = aventures.begin();
    advance(it, 2);
    aventures.erase(it); //on efface f1 du groupe aventures
    cout<<"\nmaintenant on verra que f1 reste dans cinema mais plus dans aventures"<<endl;
    aventures.affichage(cout);
    cinema.affichage(cout);

    Table t;
    int duree3[] = {20, 25, 30, 58};
    auto p2 = t.creerPhoto("Materazzi & Rui Costa", "Milan Derby", 38.6, 56.2);
    auto v2 = t.creerVideo("Frottements dans un système de Pendule", "Physique", 88);
    auto f2 = t.creerFilm("Catch me if you can", "Crime/Comedy movies", 133, duree3, 4);
    auto g2 = t.creerGroupe("interets");

    g2->push_back(p2);
    g2->push_back(v2);
    g2->push_back(f2);

    t.affichage(cout, "Materazzi & Rui Costa");
    t.Jouer("Frottements dans un système de Pendule");
    t.affichage(cout, "interets");
    t.affichage(cout, "Catch me if you can");
    t.affichage(cout, "Blah Blah Blah");

    cout<<"\nMaitenant on va effacer un objet, le film: Catch me if you can\n";
    t.supprimerObjet("Catch me if you can");

}
#endif

#ifdef VERSION_SERVER

int main(){
    Table t;
    auto p1 = t.creerPhoto("Gare de Massy Palaiseau", "Transport Publique à Essone", 20, 27);
    auto v1 = t.creerVideo("Me at the Zoo", "Youtube Classics", 96);
    int duree[] = {80, 40, 60};
    auto f1 = t.creerFilm("Harry Potter 1", "Harry Potter Movies", 180, duree, 3);

    auto g1 = t.creerGroupe("groupe quelconque");
    g1->push_back(p1);
    g1->push_back(v1);
    g1->push_back(f1);

    TCPServer server(
    [&](string const& request, string& response){
        cout<<"requete reçue: "<<request<<endl;
        stringstream ss(request);
        string commande, nom;
        ss >> commande;
        getline(ss, nom);
        nom.erase(0, nom.find_first_not_of(' ')); // remove leading spaces
        ostringstream oss;

        //si on veut trouver un nom
        if(commande == "trouver"){
            auto it = t.findObjet(nom);
            if(it != nullptr){
                (*it).affichage(oss);
            } else {
                auto it2 = t.findGroupe(nom);
                if(it2 != nullptr){
                    (*it2).affichage(oss);
                } else oss<<"aucun objet ou groupe a le nom: "<<nom;
            }
        }
        //si on veut jouer (à partir d'un nom)
        else if(commande == "jouer"){
            auto it = t.findObjet(nom);
            if(it != nullptr){
                (*it).jouer();
                oss<<"lecture de l'objet: "<<nom;
            } else oss<<"aucun objet a le nom: "<<nom;
        }
        //si la commande est inconnue
        else oss<<"commande inconnue: "<<commande;

        response = oss.str(); //pour stocker la reponse
        return true; //quand on rend true, c-à-dire qu'on laisse la connection ouverte
    }
);

    cout<<"\nserveur exécuté sur le port 3331...."<<endl;

    //start the server (blocking call)
    int status = server.run(3331);
    if(status<0){
        cerr<<"Erreur: impossible de démarrer le serveur sur le port 3331"<<endl;
        return 1;
    }
    return 0;
}

#endif


#ifdef VERSION_SERIALISATION

int main(){
    Table t;
    auto p1 = t.creerPhoto("chat", "animaux", 12.6, 28);
    auto v1 = t.creerVideo("d-day", "saving private ryan", 600);
    t.save("save.txt");

    Table t2;
    t2.load("save.txt");

    auto y = t2.findObjet("chat");
    y->affichage(cout);

    return 0;
}

#endif
