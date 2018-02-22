#include <iostream>
#include <vector>
#include "Language.h"


using namespace std;


void Langage:: Creation()
{

   // sRecursivite = imports;
   // sRecursivite.resize(imports.size());
    cout<<"\n\n==== Sans la Recursivite Gauche ===\n"<<endl;
    DeterminerNbRegles();

   for(unsigned int i=0; i<imports.size(); i++)
   {
       for(unsigned int j = 0; j< imports[i].size(); j++ )
       {
             if(imports[i][0] == imports[i][1])//Test recursivité
            {
                //testRecur(i,j);
            }

       }
    }
        /*for(unsigned int i=0; i<sRecursivite.size(); i++)
        {
            for(unsigned int j = 0; j< sRecursivite[i].size(); j++ )
            {
                cout<<" " <<sRecursivite[i][j]<<" "<<endl;
            }
            cout<<endl;
        }*/
}

void Langage::DeterminerNbRegles()
{
     int current = 0;
     bool test = true;
    vector <char> nbReglesC(term);
    vector <int> nbReglesI(term);
    cout<<"Taille1 "<<  nbReglesC.size()<<endl;
     cout<<"Taille2 "<<  nbReglesI.size()<<endl;

    for(unsigned int j=0;j<terminaux.size();j++)
    {
        if(terminaux[j] == 0)
        {
            if(j==0)
            {
                nbReglesC[current]=etats[j];
                nbReglesI[current]=1;
                current++;
            }

            else
            {
                 for(unsigned int i=0; i<nbReglesC.size();i++)
                {
                    if(nbReglesC[i]==etats[j])
                    {
                        test=true;//L'etat existe deja dans le tab
                        nbReglesI[i]+=1;
                    }
                }
                if(test==false)
                {
                    nbReglesC[current]=etats[j];
                    nbReglesI[current]=1;
                    current++;
                }
            }
        }

        test=false;
    }

    for(unsigned int k=0;k<nbReglesC.size();k++)
    {
        cout<<" "<<nbReglesC[k]<<" ";
    }
    cout<<endl;
    for(unsigned int k=0;k<nbReglesI.size();k++)
    {
        cout<<" "<<nbReglesI[k]<<" ";
    }
}
