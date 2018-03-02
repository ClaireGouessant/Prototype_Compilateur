#include "Language.h"

using namespace std;

bool Langage:: EstTerminal(char monEtat)
{
    for(unsigned int i=0; i<etats.size(); i++)
    {
        if(etats[i]==monEtat)
        {
            if(terminaux[i]== 0)
            {
                return false;
            }

            if(terminaux[i]==1)
            {
                return true;
            }
        }
    }
    return false;
}
void Langage::PremiersSuivants()
{
    int a = 0;
    int b =0;
    vector <char> DejaTraite;
    vector <char> DejaTraite2;
    for( unsigned int i=0; i<etats.size(); i++ )
    {
        if(terminaux[i]== 0)
        {
            premiers.push_back(vector<char>());
            premiers[a].push_back(etats[i]);
            Premiers(a, etats[i],DejaTraite);
            a++;
        }

    }
    for( unsigned int i=0; i<etats.size(); i++ )//On a besoin que le tab de premier soit completement remplie
    {
        if(terminaux[i]== 0)
        {
            suivants.push_back(vector<char>());
            suivants[b].push_back(etats[i]);
            DejaTraite2.push_back(etats[i]);
            Suivants(b, etats[i], DejaTraite2);// Appel de la fonction premier qui va donner la liste des premiers de l'etat[i] non terminaux

            for(unsigned int k=0;k<DejaTraite2.size();k++)
            {
                DejaTraite2.pop_back();
            }
            b++;
        }
    }
}
void Langage::Premiers(int a,char IndiceEtats,vector<char> DejaTraite)
{

    bool monEtat=false;
    bool testFin = false;
    bool present =false;
    DejaTraite.push_back(IndiceEtats);
    for(unsigned int i=0; i<sRecursivite.size(); i++)
    {
        present = false;
        if(IndiceEtats == sRecursivite[i][0])
        {
            monEtat= EstTerminal(sRecursivite[i][1]);
            for(unsigned int l=0; l<premiers[a].size(); l++)
            {
                if(premiers[a][l]==sRecursivite[i][1])
                {
                    present =true;
                }
            }
            if(monEtat==true)
            {
                if (present==false)
                {
                    premiers[a].push_back(sRecursivite[i][1]);
                }
            }
            else
            {
                do
                {
                for(unsigned int k=0; k<DejaTraite.size(); k++)
                {

                    if(sRecursivite[i][1]==DejaTraite[k])
                    {
                        testFin= true;
                    }
                }
                if(testFin == false)
                {
                    DejaTraite.push_back(sRecursivite[i][1]);
                    Premiers(a,sRecursivite[i][1],DejaTraite);
                }
            }while(testFin==false);
            }
        }
    }
}

vector<char> Langage::Suivants(int b, char IndiceEtats, vector<char>DejaTraite2)// Meme chose que premiers
   {
       bool MonEtat=true;
       bool FollowDejaTraite=false;
        if(IndiceEtats == etats[0])// Si c'est le premier etat, alors dans les follows, il possede le startSymbol
        {
              suivants[b].push_back('$');
        }
        for(unsigned int i=0;i<sRecursivite.size();i++)
       {
             for(unsigned int j=1;j<sRecursivite[i].size();j++)
             {
                 if(sRecursivite[i][j]==IndiceEtats && j+1<sRecursivite[i].size())
                 {
                     MonEtat=EstTerminal(sRecursivite[i][j+1]);
                     //Cas Follow Terminal
                     if(MonEtat == true && sRecursivite[i][j+1]!='#')
                     {
                        suivants[b].push_back(sRecursivite[i][j+1]);
                     }
                     //Cas Follow non terminal
                     else if(MonEtat==false)
                     {
                        SuivantsR2(b,i,j,IndiceEtats,DejaTraite2);
                    }
                 }

                if(sRecursivite[i][j]==IndiceEtats && j+1==sRecursivite[i].size())
                {
                    //Cas ou on effectuera un follow de sRecurvite[i][0]
                    for(unsigned int s=0; s<DejaTraite2.size();s++)
                    {
                        if(DejaTraite2[s]==sRecursivite[i][0])
                        {
                            FollowDejaTraite=true;
                        }
                    }
                    if(FollowDejaTraite==false)
                    {
                        DejaTraite2.push_back(sRecursivite[i][0]);
                        Suivants(b, sRecursivite[i][0],DejaTraite2);
                    }
                    FollowDejaTraite=false;
                }
             }
       }
        return DejaTraite2;
   }
   bool Langage::TestSPresent(char MaValeur, char IndiceEtats)
   {
       bool EstPresent=false;
       for(unsigned int h=0;h<suivants.size();h++)
        {
            for(unsigned int p=0;p<suivants[h].size();p++)
            {
                if(suivants[h][0]==IndiceEtats && suivants[h][p]==MaValeur)
                {
                    EstPresent=true;
                }
            }
        }
    return EstPresent;
   }

   vector<char> Langage::SuivantsR2(int b,int i, int j, char IndiceEtats, vector<char>DejaTraite2)
   {
       bool TestVide=false;
       bool FollowDejaTraite=false;
        for(unsigned int k=0;k<premiers.size();k++)
        {
            for(unsigned int l=1;l<premiers[k].size();l++)
            {
                if(premiers[k][0]==sRecursivite[i][j+1] && premiers[k][l]=='#')
                {
                    TestVide=true;
                }
            }
        }
        if(TestVide==false)//Cas ou dans le first du suivant il n'y a pas de mot vide
        {
            for(unsigned int r=0;r<premiers.size();r++)
            {
                for(unsigned int t=1;t<premiers[r].size();t++)
                {
                    if(premiers[r][0]==sRecursivite[i][j+1])
                    {
                        suivants[b].push_back(premiers[r][t]);
                    }
                }
            }
        }
        else
        {
            for(unsigned int r=0;r<premiers.size();r++)
            {
                for(unsigned int t=1;t<premiers[r].size();t++)
                {
                    if(premiers[r][0]==sRecursivite[i][j+1]&&premiers[r][t]!='#')
                    {
                        suivants[b].push_back(premiers[r][t]);
                    }
                }
            }
            //Le follow de sRecursivite[i][0]
            for(unsigned int s=0; s<DejaTraite2.size();s++)
            {
                if(DejaTraite2[s]==sRecursivite[i][0])
                {
                    FollowDejaTraite=true;
                }
            }
            if(FollowDejaTraite==false)
            {
                DejaTraite2.push_back(sRecursivite[i][0]);
                Suivants(b, sRecursivite[i][0],DejaTraite2);
            }
        }
        return DejaTraite2;
   }

void Langage::AffichagePremiers()
{
    cout << endl <<"\n====== Premiers =======" << endl << endl;
    for(unsigned int i=0; i<premiers.size(); i++)
    {

        cout <<"Etat : "<<premiers[i][0]<<" = [";
        for(unsigned int j=1; j<premiers[i].size(); j++)
        {
            cout<<" "<<premiers[i][j];
        }
        cout<<" ]"<<endl;
    }
     cout<<"\n\n---------------------------------------"<<endl;
}
void Langage::AffichageSuivants()
{
    cout<<"\n====== Suivants =======\n"<<endl;
    for(unsigned int i=0; i<suivants.size();i++)
    {
        cout<<"Etat "<<suivants[i][0]<<" = [";
        for(unsigned int j=1; j<suivants[i].size();j++)
        {
            cout<<" "<<suivants[i][j];
        }
        cout<<" ]"<<endl;
    }
    cout<<"\n\n---------------------------------------"<<endl;
}
