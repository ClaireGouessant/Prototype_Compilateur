#include <iostream>
#include "Language.h"
#include <fstream>
using namespace std;

Langage::Langage(string menu)
{
    ifstream fichier (menu.c_str(), ios::in);

    if (fichier)
    {
        fichier >> term;
        for (int i=0; i<term; i++)
        {
            imports.push_back(vector<char>(1)); // Rajout d'une ligne par état

            char etat; // Le premier terme de la ligne qui devrait etre l'etat
            string droite; // Ce qui se trouve a droite de l'etat

            fichier >> etat;
            imports[i][0]=etat; // Mise de l'etat au debut de la ligne du tableau d'import
            etats.push_back(etat);

            fichier >> droite;
            for (int unsigned y=0; y<droite.size(); y++) // Pour chaque symbole a droite, rajout d'une case et du symbole dans le tableau imports[][]
            {
                char symb=droite[y];
                if (symb=='|')    // detection si l'etat a plusieurs parties a droite par le symbole | dan sle fichier
                {
                    term++;
                    i++;
                    imports.push_back(vector<char>(1));
                    imports[i][0]=etat;
                }
                else
                {
                    imports[i].push_back(symb);
                }
            }
        }
    }
    else
    {
        cout << " Erreur lors de l'ouverture du fichier, fermeture du programme" << endl;
        exit(EXIT_FAILURE);
    }
    fichier.close();
}

Langage::~Langage()
{

}

void Langage::recupTerminal()
{
    for (unsigned int x=0; x<etats.size(); x++) // les ints sont en unsigned simplement pour éviter un warning avec la comparaison de vector<>::size()
    {
        terminaux.push_back(true);
    }
    for (unsigned int x=0; x<etats.size(); x++)
    {
        for (unsigned int y=0; y<imports.size(); y++)
        {
            if (etats[x]==imports[y][0])
            {
                terminaux[x] = false;
            }
        }
    }
}

void Langage::recupEtats()
{
    for (unsigned int x=0; x<imports.size(); x++)
    {
        for (unsigned int y=0; y<imports[x].size(); y++)
        {
            for (unsigned int z=0; z<etats.size(); z++)
            {
                if (imports[x][y] == etats[z])
                {
                    z = etats.size();
                }
                else if (z==etats.size()-1)
                {
                    etats.push_back(imports[x][y]);
                }
            }
        }
    }
}

void Langage::afficherGrammaire()
{
    cout << endl;
    for (unsigned int x=0; x<imports.size(); x++) // les ints sont en unsigned simplement pour éviter un warning avec la comparaison de vector<>::size()
    {
        for (unsigned int y=0; y<imports[x].size(); y++)
        {
            cout << " " << imports[x][y];
            if (y==0)
            {
                cout << " -> ";
            }
            if (y==imports[x].size()-1)
            {
                cout << endl;
            }
        }
    }
    cout << endl;
}

void Langage::afficherEtatsEtTerminaux()
{
    cout<<endl<<endl<<"==== Caracteristiques des etats ==="<<endl<<endl;

    cout << "Les etats  terminaux sont: ";
    for (unsigned int i=0; i<etats.size(); i++)
    {
        if( terminaux[i]== 1)
        {
            cout <<"  "<<etats[i] <<" ";
        }
    }

    cout << endl << endl << "Les etats  non terminaux sont: ";
    for (unsigned int i=0; i<etats.size(); i++)
    {
        if( terminaux[i]!= 1)
        {
            cout <<"  "<<etats[i] <<" ";
            term++;

        }
    }
    cout << endl;
}

