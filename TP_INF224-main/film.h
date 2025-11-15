#ifndef FILM_H
#define FILM_H
#include<iostream>
#include"video.h"
#include"multimedia.h"
#include<string.h>
using namespace std;

class Film : public Video
{

private:
    int* chapitre =  nullptr;
    int nbchap = 0;

public:
    Film(){};

    ~Film(){
        delete[] chapitre;
        cout<<"Film detruit"<<endl;
    }

    Film( string nom, string nom_fichier, int duree, const int* chapitre, int nbchap):
        Video(nom, nom_fichier, duree)
    {
        //afin de copier le tableau donnee en input dans mon nouveau tableau
        if(nbchap > 0 && chapitre != nullptr){
            this->nbchap = nbchap;
            this->chapitre = new int[nbchap];
            for(int i = 0; i<nbchap; i++){this->chapitre[i] = chapitre[i];};
        }
    }

    Film& operator=(const Film &other){ //utiliser quand on veut remplacer le contenu d'un objet deja existant
        if(this != &other){ //pour verifier qu'il n' y a pas de "self-assignment"
             Video::operator=(other); //pour aussi copier les elements de la classe mere
             delete[] chapitre; //setfilm
             nbchap = other.nbchap;
             if(nbchap>0 && other.chapitre != nullptr){
                 chapitre = new int[nbchap];
                 for(int i=0; i<nbchap; i++){
                     chapitre[i]=other.chapitre[i];
                 }
             } else chapitre = nullptr;
        }
        return *this;
    }

    Film(const Film &other) :
        Video(other) //pour copier les elements de la classe mere aussi
    { //utiliser quand on veut copier le contenu d'un objet dans un nouvel objet (objet qui n'existait pas au prealable)
        nbchap = other.nbchap; //setfilm
        if(nbchap>0 && other.chapitre != nullptr){
            chapitre = new int[nbchap];
            for(int i=0; i<nbchap; i++){
                chapitre[i] = other.chapitre[i];
            }
        } else chapitre = nullptr;
    }

    void setfilm(const int* chapitre, int nbchap){
        delete[] this->chapitre;
        if(nbchap > 0 && chapitre != nullptr){
            this->nbchap = nbchap;
            this->chapitre = new int[nbchap];
            for(int i = 0; i<nbchap; i++){this->chapitre[i] = chapitre[i];};
        } else {
            this->chapitre = nullptr;
            this->nbchap = 0;
        }
    }

    const int* getchapitre() const{return chapitre;}

    int getnbchap() const{return nbchap;}

    void affichage(ostream& cout) const override{
        Multimedia::affichage(cout);
        for(int i=0; i<nbchap; i++){
            cout<<", chapitre numero: "<<i+1<<", duree du chapitre: "<<(getchapitre())[i];
        }
    }

    string getClassName() const override{
        return "Film";
    }

    void write(ostream& os) const override{
        Video::write(os);
        os<<" nombre de chapitres: "<<nbchap;

        for(int i=0; i<nbchap; i++){
            os<<endl<<"chapitre numero: "<<i+1<<", duree du chapitre: "<<(getchapitre())[i];
        }
    }

    void read(istream& is) override{
        Video::read(is);
        string nbc;
        getline(is, nbc);
        nbchap = stod(nbc);

        delete[] chapitre;
        chapitre = new int[nbchap];
        for(int i=0; i<nbchap; i++){
            is>>chapitre[i];
        }
    }

};

#endif // FILM_H
