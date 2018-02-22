#include "Language.h"

using namespace std;

/*void Langage::recupSRecursivite()
{
    // Tableau "sRecursivite" codé directement pour les tests.
    sRecursivite.push_back(vector<char>(4));
    sRecursivite.push_back(vector<char>(2));
    sRecursivite.push_back(vector<char>(3));
    sRecursivite.push_back(vector<char>(4));
    sRecursivite.push_back(vector<char>(2));
    sRecursivite[0][0]='S';
    sRecursivite[0][1]='(';
    sRecursivite[0][2]='L';
    sRecursivite[0][3]=')';
    sRecursivite[1][0]='S';
    sRecursivite[1][1]='a';
    sRecursivite[2][0]='L';
    sRecursivite[2][1]='S';
    sRecursivite[2][2]='l';
    sRecursivite[3][0]='l';
    sRecursivite[3][1]=',';
    sRecursivite[3][2]='S';
    sRecursivite[3][3]='l';
    sRecursivite[4][0]='l';
    sRecursivite[4][1]='#';

    etats.push_back('l');
    etats.push_back('#');
    terminaux.push_back(false);
    terminaux.push_back(true);
}*/


/*void Langage::recupSRecursivite()///ne fonctionne que pour la récursivité directe
{
    //Parcourir tout le vecteur imports
    for(unsigned i=0; i<imports.size(); i++)
    {
        //Ajouter une ligne et copier la ligne dans le vecteur sRecursitite
        sRecursivite.push_back(vector<char>(1));//sRecursivite.push_back(vector<char>imports[i])
        sRecursivite[sRecursivite.size()-1] = imports[i];
        //S'il y a une récursivité à gauche
        if(sRecursivite[sRecursivite.size()-1][0] == sRecursivite[sRecursivite.size()-1][1])
        {
            //Chercher une ligne commençant par le même état mais pas récursive
            for(unsigned j=0; j<imports.size(); j++)
            {
                if((imports[j][0] == sRecursivite[sRecursivite.size()-1][0]) && (imports[j][0] == imports[j][1]))
                {
                    //vérifier si la règle est déjà dans le vecteur sRecursivite (< ou >)
                    if(j < i)//Si oui
                    {
                        //Modifier la ligne en ajoutant un nouvel état
                        //Si ça a déjà été changé ça marche pas
                    }
                    else//Si non
                    {

                        //Ajouter une ligne et inscrire la règle

                    }
                    //Ajouter deux lignes et écrire les règles du nouvel état
                    //Mettre à jour les vecteurs etat et terminaux
                    //sortir du si et du pour
                }//fin si
            }//fin pour
            //add etat terminal
        }//fin si
    }//fin pour
}*/

void Langage::recupSRecursivite()//ne fonctionne que pour la récursivité directe
{
    //Parcourir les etats
    for(unsigned i=0; i<etats.size(); i++)
    {
        //Si l'etat est non terminal trouver les etats engendrés
        if(terminaux[i] == false)
        {
            bool indicateur = false;
            //Parcourir les imports pour trouver les etats engendrés
            for(unsigned j=0; j<imports.size(); j++)
            {
                //Trouver une ligne récursive commencant par l'état étudié
                if(imports[j][0]==etats[i] && imports[j][0]==imports[j][1])
                {
                    indicateur = true;

                    //Créer un nouvel état
                    char nouvEtat = trouverEtatLibre(imports[j][0]);
                    etats.push_back(nouvEtat);
                    terminaux.push_back(false);
                    sRecursivite.push_back(vector<char>(2));
                    sRecursivite[sRecursivite.size()-1][0] = nouvEtat;
                    sRecursivite[sRecursivite.size()-1][1] = '#';


                    //sRecursivité[sRecursivite.size()].push_back('#');

                    //ajouter # dans les etats
                    bool diese = false;
                    for(unsigned k=0; k<etats.size(); k++)
                        if(etats[k] == '#') diese = true;
                    if(diese == false)
                    {
                        etats.push_back('#');
                        terminaux.push_back(true);
                    }

                    //Trouver les lignes commencant par l'état étudié
                    for(unsigned k=0; k<imports.size(); k++)
                    {
                        if(imports[k][0]==etats[i])
                        {
                            //Si la ligne est récursive
                            if(imports[k][0] == imports[k][1])
                            {
                                //Recopier l'ancien état puis la fin de la chaine et y ajouter le nouvel état
                                unsigned l = 2;
                                vector<char> tmp;
                                tmp.push_back(nouvEtat);
                                while(l < imports[k].size())
                                {
                                    tmp.push_back(imports[k][l++]);
                                }
                                tmp.push_back(nouvEtat);

                                sRecursivite.push_back(tmp);
                            }
                            else//Si la ligne n'est pas récursive
                            {
                                //Recopier le nouvel état puis la chaine et y ajouter le nouvel etat
                                unsigned l = 1;
                                vector<char> tmp;
                                tmp.push_back(etats[i]);
                                while(l < imports[k].size())
                                {
                                    tmp.push_back(imports[k][l++]);
                                }
                                tmp.push_back(nouvEtat);

                                sRecursivite.push_back(tmp);
                            }
                        }
                    }
                    //Etat dérécursivé : passage à l'état suivant
                    j=imports.size();
                }
            }
            //Si état non récursif
            if(indicateur==false)
            {
                //Parcourir les imports pour recopié les états engendrés
                for(unsigned j=0; j<imports.size(); j++)
                {
                    if(imports[j][0]==etats[i])
                    {
                        sRecursivite.push_back(imports[j]);
                    }
                }
            }
        }
    }
}

char Langage::trouverEtatLibre()
{
    char lettre;
    bool continuer = true;

    while(continuer)
    {
        srand(time(NULL));
        lettre = (char) (rand()%26) + 'a';
        continuer = false;
        for(unsigned i=0; i<etats.size(); i++)
        {
            if(etats[i] == lettre)
            {
                continuer = true;
                i = etats.size();
            }
        }
    }
    return lettre;
}

char Langage::trouverEtatLibre(char ancLettre)
{
    char nouvLettre = ancLettre - 'A' + 'a';
    bool continuer = false;

    for(unsigned i=0; i<etats.size(); i++)
    {
        if(etats[i] == nouvLettre)
        {
            continuer = true;
            i = etats.size();
        }
    }

    while(continuer)
    {
        srand(time(NULL));
        nouvLettre = (char) (rand()%26) + 'a';
        continuer = false;
        for(unsigned i=0; i<etats.size(); i++)
        {
            if(etats[i] == nouvLettre)
            {
                continuer = true;
                i = etats.size();
            }
        }
    }
    return nouvLettre;
}

void Langage::afficherGrammaireSRecursivite()
{
    cout << "\n\n==== Grammaire sans recursivite ====\n" << endl;
    for (unsigned int x=0; x<sRecursivite.size(); x++)
    {
        cout << " " << sRecursivite[x][0] << " ->";;
        for (unsigned int y=1; y<sRecursivite[x].size(); y++)
        {
            cout << " " << sRecursivite[x][y];
        }
        cout << endl;
    }
    cout << endl;
}
