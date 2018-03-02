#include "Language.h"

using namespace std;

void Langage::recupSRecursivite()//ne fonctionne que pour la r�cursivit� directe
{
    //Parcourir les etats
    for(unsigned i=0; i<etats.size(); i++)
    {
        //Si l'etat est non terminal trouver les etats engendr�s
        if(terminaux[i] == false)
        {
            bool indicateur = false;
            //Parcourir les imports pour trouver les etats engendr�s
            for(unsigned j=0; j<imports.size(); j++)
            {
                //Trouver une ligne r�cursive commencant par l'�tat �tudi�
                if(imports[j][0]==etats[i] && imports[j][0]==imports[j][1])
                {
                    indicateur = true;

                    //Cr�er un nouvel �tat
                    char nouvEtat = trouverEtatLibre(imports[j][0]);
                    etats.push_back(nouvEtat);
                    terminaux.push_back(false);
                    sRecursivite.push_back(vector<char>(2));
                    sRecursivite[sRecursivite.size()-1][0] = nouvEtat;
                    sRecursivite[sRecursivite.size()-1][1] = '#';

                    //ajouter # dans les etats
                    bool diese = false;
                    for(unsigned k=0; k<etats.size(); k++)
                        if(etats[k] == '#') diese = true;
                    if(diese == false)
                    {
                        etats.push_back('#');
                        terminaux.push_back(true);
                    }

                    //Trouver les lignes commencant par l'�tat �tudi�
                    for(unsigned k=0; k<imports.size(); k++)
                    {
                        if(imports[k][0]==etats[i])
                        {
                            //Si la ligne est r�cursive
                            if(imports[k][0] == imports[k][1])
                            {
                                //Recopier l'ancien �tat puis la fin de la chaine et y ajouter le nouvel �tat
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
                            else//Si la ligne n'est pas r�cursive
                            {
                                //Recopier le nouvel �tat puis la chaine et y ajouter le nouvel etat
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
                    //Etat d�r�cursiv� : passage � l'�tat suivant
                    j=imports.size();
                }
            }
            //Si �tat non r�cursif
            if(indicateur==false)
            {
                //Parcourir les imports pour recopi� les �tats engendr�s
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
    cout << endl << "==== Grammaire sans recursivite ====" << endl << endl;
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
