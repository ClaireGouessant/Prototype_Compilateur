#include <iostream>
#include "Language.h"


using namespace std;

string saisieFichier()
{
    system("CLS");
    string menu;
    cout << endl;
    cout << "==== Selection du fichier ====" << endl;
    cout << "    1. fichierTest1.txt" << endl;
    cout << "    2. fichierTest2.txt" << endl;
    cout << "    3. fichierTest3.txt" << endl;
    cout << "    4. fichierTest4.txt" << endl;
    cout << "    5. fichierTest5.txt" << endl;
    cout << "    6. fichierTest6.txt" << endl;
    cout << "    7. fichierTest7.txt" << endl;
    cout << "    8. fichierTest8.txt" << endl;
    cout << "    9. fichierTest9.txt" << endl;
    cout << "    10. fichierTest10.txt" << endl;
    cout << "    11. Saississez votre propre fichier" << endl;
    cout << "    0. Quitter" << endl << endl;

    bool verif = false;

    while (!verif)
    {
        cout << " Veuillez choisir une option" << endl;
        cin >> menu;

        if (menu == "1")
        {
            menu = "fichierTest1.txt";
            verif = true;
        }
        else if (menu == "2")
        {
            menu = "fichierTest2.txt";
            verif = true;
        }
        else if (menu == "3")
        {
            menu = "fichierTest3.txt";
            verif = true;
        }
        else if (menu == "4")
        {
            menu = "fichierTest4.txt";
            verif = true;
        }
        else if (menu == "5")
        {
            menu = "fichierTest5.txt";
            verif = true;
        }
        else if (menu == "6")
        {
            menu = "fichierTest6.txt";
            verif = true;
        }
        else if (menu == "7")
        {
            menu = "fichierTest7.txt";
            verif = true;
        }
        else if (menu == "8")
        {
            menu = "fichierTest8.txt";
            verif = true;
        }
        else if (menu == "9")
        {
            menu = "fichierTest9.txt";
            verif = true;
        }
        else if (menu == "10")
        {
            menu = "fichierTest10.txt";
            verif = true;
        }
        else if (menu == "11")
        {
            menu = "fichierTest11.txt";
            verif = true;
        }
        else if (menu == "0")
        {
            cout<<"\n\n\n\nDeveloppe par Duhamel Bertrand, Gouessant Claire," << endl << "              Laversanne Vincent, Zuber Thibault."<<endl;
            exit(EXIT_SUCCESS);
        }
    }
    cout << " L'analyse va etre lance sur ce fichier" << endl;
    return menu;
}

int main()
{
    bool verif = true;
    while (verif)
    {
        Langage premier(saisieFichier());

        premier.afficherGrammaire();

        premier.recupEtats();
        premier.recupTerminal();
        premier.afficherEtatsEtTerminaux();

        premier.recupSRecursivite();
        premier.afficherGrammaireSRecursivite();
        premier.afficherEtatsEtTerminaux();

        premier.PremiersSuivants();
        premier.AffichagePremiers();
        premier.AffichageSuivants();
        premier.Analyse();

        premier.reconnaissance();

        system("PAUSE");
    }
    return 0;
}
