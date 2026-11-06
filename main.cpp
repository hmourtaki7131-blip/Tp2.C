
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

class Filiere;

class Etudiant {
private:
    string nom;
    Filiere* filiere;

public:
    Etudiant(string n) {
        if (n.empty())
            throw invalid_argument("Nom vide !");
        nom = n;
        filiere = nullptr;
    }

    string getNom() const {
        return nom;
    }

    Filiere* getFiliere() const {
        return filiere;
    }

    void setFiliere(Filiere* f) {
        filiere = f;
    }

    void changerDeFiliere(Filiere* nouvelle);
};

class Filiere {
private:
    string nomFiliere;
    vector<Etudiant*> etudiants;

public:
    Filiere(string nom) {
        if (nom.empty())
            throw invalid_argument("Nom de filiere vide !");
        nomFiliere = nom;
    }

    // Destructeur
    ~Filiere() {
        for (Etudiant* e : etudiants) {
            if (e != nullptr) {
                e->setFiliere(nullptr);
            }
        }

        etudiants.clear();

        cout << "Destruction de la filiere : "
             << nomFiliere << endl;
    }

    void inscrireEtudiant(Etudiant* e) {
        if (e == nullptr)
            throw invalid_argument("Etudiant invalide !");

        if (e->getFiliere() != nullptr)
            throw runtime_error("Etudiant deja inscrit !");

        etudiants.push_back(e);
        e->setFiliere(this);
    }

    void retirerEtudiant(Etudiant* e) {
        auto it = find(etudiants.begin(), etudiants.end(), e);

        if (it == etudiants.end())
            throw runtime_error("Etudiant introuvable !");

        e->setFiliere(nullptr);
        etudiants.erase(it);
    }

    void afficherEtudiants() const {
        cout << "\nFiliere : " << nomFiliere << endl;

        for (Etudiant* e : etudiants) {
            cout << "- " << e->getNom() << endl;
        }
    }
};

void Etudiant::changerDeFiliere(Filiere* nouvelle) {
    if (nouvelle == nullptr)
        throw invalid_argument("Nouvelle filiere invalide !");

    if (filiere == nouvelle)
        throw runtime_error("Meme filiere !");

    if (filiere != nullptr)
        filiere->retirerEtudiant(this);

    nouvelle->inscrireEtudiant(this);
}

int main() {
    try {
        Etudiant e1("Alice");

        Filiere f1("Informatique");
        Filiere f2("Mathematiques");

        f1.inscrireEtudiant(&e1);

        cout << "Avant le changement :";
        f1.afficherEtudiants();

        e1.changerDeFiliere(&f2);

        cout << "\nApres le changement :";
        f1.afficherEtudiants();
        f2.afficherEtudiants();

    }
    catch (const exception& e) {
        cout << "Erreur : " << e.what() << endl;
    }

    return 0;
}




