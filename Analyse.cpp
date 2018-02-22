#include "Language.h"

using namespace std;

void Langage::AnalyseInit()
{
    int a=1;
     analyse.push_back(vector<char>());
     analyse[0].push_back(' ');

    for(unsigned int i=0; i<terminaux.size();i++)
    {
        if(terminaux[i]== 1 && etats[i] !='#')
        {
             analyse[0].push_back(etats[i]);
        }
    }
    analyse[0].push_back('$');
    for(unsigned int k= 0; k<terminaux.size();k++)
    {
        if(terminaux[k]==0)
        {
            analyse.push_back(vector<char>(analyse[0].size()));
            analyse[a][0]=etats[k];
            a++;
        }
    }
}


void Langage::affichageTableA()
{
    int affichage;
    cout<<"\n\n===== Table d'Analyse ====\n\n"<<endl;
    for(unsigned int i=0;i<analyse.size();i++)
    {
        cout<<analyse[i][0]<<" | ";
        for(unsigned int j=1;j<analyse[i].size();j++)
        {
            if(i!=0 && analyse[i][j]!=0)
            {
                affichage=analyse[i][j];
                cout<<affichage<<" - ";
            }
            else
            {
                  cout<<analyse[i][j]<<" - ";
            }

        }
        cout<<endl;
    }
    cout<<"\n\n---------------------------------------"<<endl;
}
void Langage::testPremiers(int i, int j, int k)
{
  bool monEtat=false;
  monEtat= EstTerminal(sRecursivite[k][1]);
  if(monEtat==true&&sRecursivite[k][1]==analyse[0][j])//Si le premier caractere de la regle est celui recherche
  {
    analyse[i][j]=k+1;//Attention la valeur devait etre k, mais conflit avec la fonction d'affichage pour recurperer la regle merci de mettre analyse[i][j]-1
  }

  else
  {
      for(unsigned int p=0;p<premiers.size();p++)
      {
          for(unsigned int e=1;e<premiers[p].size();e++)
          {
              if(premiers[p][0]== sRecursivite[k][1] &&analyse[0][j]==premiers[p][e])
              {
                  analyse[i][j]=k+1;//Attention la valeur devait etre k, mais conflit avec la fonction d'affichage pour recurperer la regle merci de mettre analyse[i][j]-1
              }
          }
      }
  }

}

void Langage::testSuivants(int i, int j, int k)
{
   // bool presenceMotVide=false;
    //Test du mot vide dans les differentes regles d un meme etat
   /* for(unsigned int f=0;f<premiers.size();f++)
    {
        for(unsigned int g=1; g<premiers[f].size();g++)
        {
            if(analyse[i][0]==premiers[f][0]&&premiers[f][g]=='#')
            {
                presenceMotVide=true;
            }
        }
    }*/

    //if(presenceMotVide==true)
    if(sRecursivite[k][1]=='#')
    {
        for (unsigned int h=0; h<suivants.size();h++)
        {
            for (unsigned int t=1; t<suivants[h].size();t++)
            {
                if(analyse[i][0]==suivants[h][0]&& analyse[0][j]==suivants[h][t] && analyse[i][j]==0)//Recherche du symbole dans les follows de l'etat
                {
                    analyse[i][j]=k+1;//Attention la valeur devait etre k, mais conflit avec la fonction d'affichage pour recurperer la regle merci de mettre analyse[i][j]-1
                }
            }
        }
    }
}

void Langage::Analyse()
{
    AnalyseInit();
    //Parcours de Analyse[][]
    for(unsigned int i=1;i<analyse.size();i++)
    {
        for(unsigned int j=1;j<analyse[i].size();j++)
        {
            //Parcours de sRecursivite[][]
            for(unsigned int k = 0;k<sRecursivite.size();k++)
            {
                  if(analyse[i][0]==sRecursivite[k][0])
                  {
                      testPremiers(i,j,k);
                      testSuivants(i,j,k);
                  }
            }
        }
    }
    affichageTableA();
}
