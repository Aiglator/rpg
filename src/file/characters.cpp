#include <iostream>
#include <vector>

// Classe de base pour les personnages
class Personnage {
public:
    std::string nom;
    int pointsDeVie;
    float vitesse;

    Personnage(std::string n, int pv, float v) : nom(n), pointsDeVie(pv), vitesse(v) {}

    virtual void afficherInfos() {
        std::cout << "Nom: " << nom << "\nPoints de Vie: " << pointsDeVie << "\nVitesse: " << vitesse << "\n";
    }
};

// Classe Hero qui hérite de Personnage
class Hero : public Personnage {
public:
    int puissanceAttaque;

    Hero(std::string n, int pv, float v, int pa) : Personnage(n, pv, v), puissanceAttaque(pa) {}

    void afficherInfos() override {
        std::cout << "HERO -> " << nom << " | PV: " << pointsDeVie << " | Vitesse: " << vitesse << " | Attaque: " << puissanceAttaque << "\n";
    }
};

// Classe Ennemi qui hérite de Personnage
class Ennemi : public Personnage {
public:
    std::string type;

    Ennemi(std::string n, int pv, float v, std::string t) : Personnage(n, pv, v), type(t) {}

    void afficherInfos() override {
        std::cout << "ENNEMI (" << type << ") -> " << nom << " | PV: " << pointsDeVie << " | Vitesse: " << vitesse << "\n";
    }
};

int main() {
    Hero hero("Mario", 100, 5.5, 30);
    Ennemi champignon("Goomba", 20, 2.0, "Champignon");
    Ennemi tortueVerte("Koopa Vert", 40, 3.0, "Tortue Verte");
    Ennemi tortueRouge("Koopa Rouge", 50, 3.5, "Tortue Rouge");

    std::vector<Personnage*> personnages = {&hero, &champignon, &tortueVerte, &tortueRouge};

    for (Personnage* p : personnages) {
        p->afficherInfos();
    }

    return 0;
}