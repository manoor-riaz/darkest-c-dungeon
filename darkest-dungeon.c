#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int orJoueur = 0;

// Structure pour les classes des personnages
typedef struct {
    char nom[50];
    int att;
    int def;
    int HPmax;
    int rest;
} Classe;

// Structure pour les accessoires
typedef struct Accessoire {
    char nom[50];
    int attbonus;
    int defbonus;
    int HPbonus;
    int restbonus;
    int strred;
    int prix;
    int utilise; // Marqueur pour indiquer si l'accessoire est utilisé
    struct Accessoire *suivant; // Pointeur vers le prochain accessoire dans la liste
} *Accessoire;

// Structure pour les personnages
typedef struct Personnage {
    char nom[50];
    Classe *classe;
    int HP;
    int str;           // Stress
    int nbcomb;        // Nombre de combats effectués
    Accessoire accessoire; // Liste des accessoires
    struct Personnage *suivant; // Pointeur vers le prochain personnage dans la liste
} *Personnage;

// Structure pour les ennemis
typedef struct Ennemi {
    char nom[50];
    int niveau;
    int attenn;
    int defenn;
    int HPenn;
    int attstrenn;     // Niveau de stress infligé par l'ennemi
    struct Ennemi *suivant; // Pointeur vers le prochain ennemi dans la liste
} *Ennemi;

typedef Personnage Lieu;

// Structure pour la roulotte
typedef struct Roulotte {
    char nom[50];
    int prix;
    Accessoire *suivant; // Pointeur vers le prochain accessoire dans la liste
} Roulotte;

typedef struct Joueur {
    int or;
    Accessoire* lstaccessoire; // Liste des accessoires du joueur
} Joueur;

/*
- Initialise le champ suivant du nouveau personnage à NULL.
- Ajoute un personnage à la fin de la liste des personnages. Si la liste est vide, le nouveau personnage devient le premier élément. Sinon, il est ajouté à la fin de la liste existante.
- Paramètres : 
  - "lstpersonnage" : un pointeur vers un pointeur de type Personnage, représentant la liste des personnages.
  - "nvperso" : un objet de type Personnage à ajouter à la liste.
- Valeur de retour : aucune (void).
*/

void ajouterPersonnage(Personnage *lstpersonnage, Personnage nvperso) {
    nvperso->suivant = NULL;
    if (*lstpersonnage == NULL) {
        *lstpersonnage = nvperso;
    } else {
        Personnage tmp = *lstpersonnage;
        while (tmp->suivant != NULL) {
            tmp = tmp->suivant;
        }
        tmp->suivant = nvperso;
    }
}
/*
- Initialise le champ suivant du nouvel ennemi à NULL.
- Ajoute un ennemi à la fin de la liste des ennemis. Si la liste est vide, le nouvel ennemi devient le premier élément. Sinon, il est ajouté à la fin de la liste existante.
- Paramètres : 
  - "lstennemi" : un pointeur vers un pointeur de type Ennemi, représentant la liste des ennemis.
  - "nvEnnemi" : un objet de type Ennemi à ajouter à la liste.
- Valeur de retour : aucune (void).
*/
void ajouterEnnemi(Ennemi *lstennemi, Ennemi nvEnnemi) {
    nvEnnemi->suivant = NULL;
    if (*lstennemi == NULL) {
        *lstennemi = nvEnnemi;
    } else {
        Ennemi tmp = *lstennemi;
        while (tmp->suivant != NULL) {
            tmp = tmp->suivant;
        }
        tmp->suivant = nvEnnemi;
    }
}

/*
- Alloue dynamiquement de la mémoire pour un nouveau personnage.
- Ajoute le personnage à la fin de la liste des personnages en appelant la fonction ajouterPersonnage.
- Paramètres : 
  - "nom" : chaîne de caractères représentant le nom du personnage.
  - "classe" : un pointeur vers une structure Classe représentant la classe du personnage.
  - "lstpersonnage" : un pointeur vers un pointeur de type Personnage, représentant la liste des personnages.
- Valeur de retour : le nouveau personnage .
*/
Personnage creerPersonnage(char *nom, Classe *classe, Personnage *lstpersonnage) {
    Personnage nvperso = (Personnage)malloc(sizeof(struct Personnage));
    if (nvperso == NULL){
        printf("Erreur d'allocation de mémoire\n");
        exit(1);
    }
    strcpy(nvperso->nom, nom);
    nvperso->classe = classe;
    nvperso->HP = classe->HPmax;
    nvperso->str = 0;
    nvperso->nbcomb = 0;
    nvperso->accessoire = NULL;
    nvperso->suivant = NULL;

    ajouterPersonnage(lstpersonnage, nvperso);

    return nvperso;
}


/*
- Alloue dynamiquement de la mémoire pour un nouvel ennemi.
- Ajoute l'ennemi à la fin de la liste des ennemis en appelant la fonction ajouterEnnemi.
- Paramètres : 
  - "nom" : chaîne de caractères représentant le nom de l'ennemi.
  - "niveau" : entier représentant le niveau de l'ennemi.
  - "attenn" : entier représentant l'attaque de l'ennemi.
  - "defenn" : entier représentant la défense de l'ennemi.
  - "HPenn" : entier représentant les points de vie de l'ennemi.
  - "attstrenn" : entier représentant la force d'attaque de l'ennemi.
  - "lstennemi" : un pointeur vers un pointeur de type Ennemi, représentant la liste des ennemis.
- Valeur de retour : le nouveau ennemi.
*/

Ennemi creerEnnemi(char *nom, int niveau, int attenn, int defenn, int HPenn, int attstrenn, Ennemi *lstennemi) {
    Ennemi nvEnnemi = (Ennemi)malloc(sizeof(struct Ennemi));
    if (nvEnnemi == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        exit(1);
    }
    strcpy(nvEnnemi->nom, nom);
    nvEnnemi->niveau = niveau;
    nvEnnemi->attenn = attenn;
    nvEnnemi->defenn = defenn;
    nvEnnemi->HPenn = HPenn;
    nvEnnemi->attstrenn = attstrenn;
    nvEnnemi->suivant = NULL;

    ajouterEnnemi(lstennemi, nvEnnemi);

    return nvEnnemi;
}

/*
- Calcule le nombre d'éléments dans la liste des personnages en parcourant la liste.
- Paramètres : 
  - "lstpersonnage" : un pointeur vers un pointeur de type Personnage, représentant la liste des personnages.
- Valeur de retour : un entier représentant la taille de la liste (le nombre de personnages).
*/
int calculerTailleListe(Personnage* lstpersonnage) {
    int count = 0; 
    Personnage tmp = *lstpersonnage; 
    while (tmp != NULL) { 
        count++; 
        tmp = tmp->suivant; 
    } 
        return count; 
}

/*
- Parcourt la liste des personnages et affiche les détails de chaque personnage sous forme de tableau.
- Paramètres : 
  - "personnages" : un pointeur vers la liste des personnages à afficher (de type Personnage).
- Valeur de retour : aucune (void).
*/
void afficherperso(Personnage personnages) {
    // Afficher l'en-tête
    printf("+----+------------------+-----------+-----------+----------+----------+---------+\n");
    printf("| #  | Nom              | Classe    | Attaque   | Défense  | HP       | Stress  |\n");
    printf("+----+------------------+-----------+-----------+----------+----------+---------+\n");

    // Afficher les personnages
    int i = 1;
    for (; personnages; personnages = personnages->suivant) {
        printf("| %-2d | %-16s | %-9s | %-9d | %-8d | %-3d/%-5d| %-7d |\n",
               i, personnages->nom, personnages->classe->nom,
               personnages->classe->att, personnages->classe->def,
               personnages->HP, personnages->classe->HPmax,
               personnages->str);
        i++;
    }

    // Ligne de fin du tableau (ajustée pour ne pas déborder)
    printf("+----+------------------+-----------+-----------+----------+----------+---------+\n");
}



/*
- Parcourt la liste des classes et affiche les détails de chaque classe sous forme de tableau.
- Paramètres : 
  - "classes" : un tableau de structures Classe représentant les différentes classes à afficher.
  - "nbClasses" : un entier représentant le nombre de classes à afficher.
- Valeur de retour : aucune (void).
*/
void afficherClasses(Classe *classes, int nbClasses) {
    printf("+-----------+--------+--------+--------+--------+\n");
    printf("|  Classes  | Attaque| Défense| HPmax  |  rest  |\n");
    printf("+-----------+--------+--------+--------+--------+\n");
    for (int i = 0; i < nbClasses; i++) {
        printf("| %-9s | %-6d | %-6d | %-6d | %-6d |\n",
               classes[i].nom, classes[i].att, classes[i].def, classes[i].HPmax, classes[i].rest);
    }
    printf("+-----------+--------+--------+--------+--------+\n");
}

/*
- Parcourt la liste des accessoires et affiche les détails de chaque accessoire sous forme de tableau.
- Paramètres : 
  - "lstaccessoire" : un pointeur vers la liste des accessoires à afficher (de type Accessoire).
- Valeur de retour : aucune (void).
*/
void afficherAccessoires(Accessoire lstaccessoire) {
    // Afficher l'en-tête du tableau
    printf("+----+---------------------+-----------+-----------+-----------+-----------+----------+\n");
    printf("| #  | Nom                 | AttBonus  | DefBonus  | HPBonus   | RestBonus | StrRed   |\n");
    printf("+----+---------------------+-----------+-----------+-----------+-----------+----------+\n");

    // Afficher les accessoires
    int i = 1;
    for (; lstaccessoire; lstaccessoire = lstaccessoire->suivant) {
        printf("| %-2d | %-19s | %-9d | %-9d | %-9d | %-9d | %-8d |\n",
               i, lstaccessoire->nom, lstaccessoire->attbonus,
               lstaccessoire->defbonus, lstaccessoire->HPbonus,
               lstaccessoire->restbonus, lstaccessoire->strred);
        i++;
    }

    // Ligne de fin du tableau
    printf("+----+---------------------+-----------+-----------+-----------+-----------+----------+\n");
}

/*
- Demande à l'utilisateur de saisir un entier en affichant un message.
- Vérifie que la saisie est un entier valide. Si ce n'est pas le cas, affiche un message d'erreur et redemande la saisie.
- Paramètres : 
  - "message" : chaîne de caractères à afficher pour inviter l'utilisateur à saisir un entier.
- Valeur de retour : l'entier saisi par l'utilisateur.
*/

int saisirEntier(char *message) {
    int valeur;
    char zoneSaisie[50];  
    int saisieValide = 0;

    while (!saisieValide) {
        printf("%s", message);
        if (fgets(zoneSaisie, sizeof(zoneSaisie), stdin) != NULL) {
            if (sscanf(zoneSaisie, "%d", &valeur) == 1) {
                saisieValide = 1;
            } else {
                printf("Saisie invalide. Veuillez entrer un entier.\n");
            }
        }
    }

    return valeur;
}

/*
- Demande à l'utilisateur de saisir un caractère parmi un ensemble d'options spécifiées.
- Vérifie que le caractère saisi est valide (c'est-à-dire qu'il fait partie des options données). Si ce n'est pas le cas, affiche un message d'erreur et redemande la saisie.
- Paramètres : 
  - "message" : chaîne de caractères à afficher pour inviter l'utilisateur à saisir un caractère.
  - "options" : chaîne de caractères contenant les options valides que l'utilisateur peut saisir.
- Valeur de retour : le caractère saisi par l'utilisateur, s'il est valide.
*/
char saisirCaractere(char *message, const char *options) {
    char zoneSaisie[50];  
    char valeur;
    int saisieValide = 0;

    while (!saisieValide) {
        printf("%s", message);
        if (fgets(zoneSaisie, sizeof(zoneSaisie), stdin) != NULL) {
            if (sscanf(zoneSaisie, " %c", &valeur) == 1 && strchr(options, valeur)) {
                saisieValide = 1;
            } else {
                printf("Saisie invalide. Veuillez entrer une des options suivantes: %s\n", options);
            }
        }
    }

    return valeur;
}

/*
- Permet à l'utilisateur de choisir des personnages pour un combat, avec un nombre de combattants dépendant de numCombat.
- Affiche les personnages disponibles, permet de les sélectionner et les retire de la liste originale.
- Si aucun combattant n'est choisi, redemande la sélection.
- Paramètres : 
  - "lstpersonnage" : liste des personnages disponibles.
  - "numCombat" : nombre de combattants à choisir.
- Valeur de retour : liste des combattants choisis.
*/
Personnage choisirPersonnagesPourCombat(Personnage *lstpersonnage, int numCombat) {
    int maxCombattants = (numCombat <= 5) ? 2 : 3;
    Personnage combattants = NULL;
    int nbCombattantsChoisis = 0;


    while (nbCombattantsChoisis < maxCombattants) {
        if (*lstpersonnage == NULL) {
            break; // Quitte la boucle si plus de personnages disponibles
        }
        printf("Personnages disponibles \n");
        afficherperso(*lstpersonnage);

         int choix =saisirEntier("Choix du combattant (entrée 0 si vous ne voulez pas de combattant supplémentaire) : ");

        if (choix == 0) {
            break;
        }

        Personnage tmp = *lstpersonnage;
        Personnage precedent = NULL;
        int j = 1;

        while (tmp != NULL && j < choix) {
            precedent = tmp;
            tmp = tmp->suivant;
            j++;
        }

        if (tmp == NULL || j != choix) { // Vérifie si le choix est valide
            printf("Choix invalide. Veuillez réessayer.\n");
            continue;
        }

        // Retirer le personnage choisi de la liste originale
        if (precedent == NULL) {
            *lstpersonnage = tmp->suivant;
        } else {
            precedent->suivant = tmp->suivant;
        }
        tmp->suivant = NULL;

        // Ajouter le personnage choisi à la liste des combattants
        ajouterPersonnage(&combattants, tmp);
        nbCombattantsChoisis++;
    }

    if (nbCombattantsChoisis == 0) {
        printf("Vous devez choisir au moins 1 combattant. Veuillez en sélectionner un.\n");
        return choisirPersonnagesPourCombat(lstpersonnage, numCombat);
    }

    return combattants;
}

/*
- Permet d'équiper un accessoire à un personnage.
- Copie l'accessoire et l'ajoute à la liste des accessoires du personnage.
- Applique les bonus de l'accessoire (HP, etc.) et ajuste les points de vie du personnage.
- Paramètres : 
  - "perso" : personnage à qui l'accessoire est équipé.
  - "acc" : accessoire à équiper.
- Valeur de retour : aucune (void).
*/
void equiperAccessoire(Personnage perso, Accessoire acc) {
    if (!perso || !acc) return;

    // Copier l'accessoire pour l'attacher au personnage
    Accessoire copie = malloc(sizeof(struct Accessoire));
    if (!copie) {
        printf("Erreur d'allocation mémoire pour équiper %s\n", acc->nom);
        return;
    }
    *copie = *acc;
    copie->suivant = perso->accessoire;
    perso->accessoire = copie;

    // Appliquer les bonus de l'accessoire
    perso->classe->HPmax += copie->HPbonus;
    perso->HP += copie->HPbonus;
    if (perso->HP > perso->classe->HPmax) perso->HP = perso->classe->HPmax;
    printf("%s a équipé l'accessoire %s.\n", perso->nom, acc->nom);

    acc->utilise = 1; // Marquer l'accessoire comme utilisé
}



/*
- Permet à chaque combattant de choisir jusqu'à deux accessoires parmi une liste d'accessoires disponibles.
- Affiche les accessoires disponibles, demande un choix, et applique l'accessoire sélectionné au combattant.
- Les accessoires choisis sont retirés de la liste globale et équipés au personnage.
- Si un accessoire est déjà utilisé ou si le choix est invalide, redemande la sélection.
- Paramètres : 
  - "combattants" : liste des combattants à équiper d'accessoires.
  - "lstaccessoire" : liste globale des accessoires disponibles.
- Valeur de retour : aucune (void).
*/
// Fonction pour choisir jusqu'à deux accessoires pour un personnage
void choisirAccessoiresPourPersonnages(Personnage combattants, Accessoire *lstaccessoire) {
    while (combattants != NULL) {
        printf("Choisissez des accessoires pour %s :\n", combattants->nom);
        afficherAccessoires(*lstaccessoire);

        int choix;
        for (int i = 0; i < 2; i++) { // Permet de choisir jusqu'à 2 accessoires
            printf("Entrez le numéro de l'accessoire à ajouter (entrée 0 si vous ne voulez pas d'accessoire) : ");
            scanf("%d", &choix);

            if (choix == 0) {
                break;
            }

            Accessoire tmp = *lstaccessoire;
            Accessoire precedent = NULL;
            int index = 1;

            while (tmp && index < choix) {
                precedent = tmp;
                tmp = tmp->suivant;
                index++;
            }

            if (!tmp || tmp->utilise) {
                printf("Choix invalide ou accessoire déjà utilisé. Veuillez réessayer.\n");
                i--;
                continue;
            }

            // Retirer l'accessoire de la liste globale
            if (precedent == NULL) {
                *lstaccessoire = tmp->suivant;
            } else {
                precedent->suivant = tmp->suivant;
            }

            equiperAccessoire(combattants, tmp);
            afficherAccessoires(*lstaccessoire);
        }

        combattants = combattants->suivant;
    }
}

/*
- Réintègre les accessoires utilisés par les personnages dans la liste des accessoires disponibles.
- Marque chaque accessoire comme non utilisé et le place en tête de la liste globale des accessoires.
- Vide la liste d'accessoires du personnage après réintégration.
- Paramètres : 
  - "lstaccessoire" : liste des accessoires disponibles à réintégrer.
  - "combattants" : liste des personnages dont les accessoires doivent être réintégrés.
- Valeur de retour : aucune (void).
*/
void reintegrerAccessoires(Accessoire *lstaccessoire, Personnage combattants) {
    Personnage tmp = combattants;

    // Réintégrer les accessoires utilisés par les personnages
    while (tmp != NULL) {
        Accessoire acc = tmp->accessoire;
        while (acc != NULL) {
            Accessoire suivant = acc->suivant;

            // Réintégrer l'accessoire dans la liste des accessoires disponibles
            acc->utilise = 0;  // Marquer l'accessoire comme non utilisé
            acc->suivant = *lstaccessoire;  // Le mettre en tête de la liste des accessoires disponibles
            *lstaccessoire = acc;  // Réassigner la tête de liste

            acc = suivant;
        }
        tmp->accessoire = NULL; // Vider la liste d'accessoires du personnage
        tmp = tmp->suivant;
    }
}

/*
- Ajoute un personnage disponible à la liste des personnages.
- Crée un personnage avec le nom et la classe spécifiés, puis l'ajoute à la liste.
- Paramètres : 
  - "lstpersonnage" : liste des personnages disponibles.
  - "nom" : nom du personnage à ajouter.
  - "classe" : classe du personnage à ajouter.
- Valeur de retour : aucune (void).
*/
void ajouterPersonnageDisponible(Personnage *lstpersonnage, char *nom, Classe *classe) {
    creerPersonnage(nom, classe, lstpersonnage);
}

/*
- Ajoute un accessoire à la liste des accessoires disponibles.
- Si la liste est vide, l'accessoire devient le premier élément. Sinon, il est ajouté à la fin de la liste.
- Paramètres : 
  - "lstaccessoire" : liste des accessoires disponibles.
  - "nvAccessoire" : accessoire à ajouter à la liste.
- Valeur de retour : aucune (void).
*/
void ajouterAccessoire(Accessoire *lstaccessoire, Accessoire nvAccessoire) {
    nvAccessoire->suivant = NULL;
    if (*lstaccessoire == NULL) {
        *lstaccessoire = nvAccessoire;
    } else {
        Accessoire tmp = *lstaccessoire;
        while (tmp->suivant != NULL) {
            tmp = tmp->suivant;
        }
        tmp->suivant = nvAccessoire;
    }
}

/*
- Réintègre les personnages du combat dans la liste globale des personnages disponibles.
- Pour chaque personnage, réintègre ses accessoires et, si ses points de vie sont positifs, le réajoute à la liste globale.
- Si un personnage a des points de vie nuls ou inférieurs, il est supprimé.
- Paramètres : 
  - "lstpersonnage" : liste des personnages disponibles.
  - "combattants" : liste des personnages ayant participé au combat.
  - "lstaccessoire" : liste des accessoires à réintégrer.
- Valeur de retour : aucune (void).
*/
void reintegrerPersonnages(Personnage *lstpersonnage, Personnage *combattants, Accessoire *lstaccessoire) {
    Personnage tmp = *combattants;
    while (tmp) {
        Personnage persosuivant = tmp->suivant;

        // Réintégrer les accessoires du personnage
        reintegrerAccessoires(lstaccessoire, tmp);

        // Réintégrer le personnage dans la liste globale
        if (tmp->HP > 0) {
            ajouterPersonnage(lstpersonnage, tmp);
        } else {
            free(tmp);
        }

        tmp = persosuivant;
    }
    *combattants = NULL;
}



/*
- Crée un nouvel accessoire avec les caractéristiques spécifiées (nom, bonus d'attaque, de défense, de HP, etc.).
- L'accessoire est ajouté à la liste des accessoires disponibles.
- Paramètres : 
  - "nom" : nom de l'accessoire.
  - "attbonus" : bonus d'attaque de l'accessoire.
  - "defbonus" : bonus de défense de l'accessoire.
  - "HPbonus" : bonus de points de vie de l'accessoire.
  - "restbonus" : bonus de récupération de l'accessoire.
  - "strred" : réduction du stress de l'accessoire.
  - "lstaccessoire" : liste des accessoires disponibles.
- Valeur de retour : le nouvel accessoire créé.
*/
Accessoire creerAccessoire(char *nom, int attbonus, int defbonus, int HPbonus, int restbonus, int strred, Accessoire *lstaccessoire) {
    Accessoire nvAccessoire = (Accessoire)malloc(sizeof(struct Accessoire));
    if (nvAccessoire == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        exit(1);
    }
    strcpy(nvAccessoire->nom, nom);
    nvAccessoire->attbonus = attbonus;
    nvAccessoire->defbonus = defbonus;
    nvAccessoire->HPbonus = HPbonus;
    nvAccessoire->restbonus = restbonus;
    nvAccessoire->strred = strred;
    nvAccessoire->utilise = 0;
    nvAccessoire->suivant = NULL;

    ajouterAccessoire(lstaccessoire, nvAccessoire);
    return nvAccessoire;
}


/*
- Calcule les dommages d'une attaque en fonction de l'attaque de l'attaquant et de la défense de la cible.
- Si les dommages calculés sont inférieurs ou égaux à 0, retourne 1 (dommages minimum).
- Paramètres :
  - "att" : valeur de l'attaque de l'attaquant.
  - "def" : valeur de la défense de la cible.
- Valeur de retour : dommages infligés (valeur entière).
*/
int calculerDommagesAttaque(int att, int def) {
    float roll = ((float)rand() / RAND_MAX) * (1.2 - 0.8) + 0.8;
    int dommages = (int)((att - def) * roll);
    if (dommages > 0) return dommages;
    return 1;
}

/*
- Effectue une attaque d'un personnage (attaquant) sur un ennemi (cible).
- Calcule les dommages en fonction de l'attaque de l'attaquant et de la défense de la cible.
- Réduit les points de vie de la cible en fonction des dommages subis.
- Paramètres :
  - "attaquant" : personnage qui attaque.
  - "cible" : ennemi qui est attaqué.
*/
void attaquer(Personnage attaquant, Ennemi cible) {
    int dommages = calculerDommagesAttaque(attaquant->classe->att, cible->defenn);
    cible->HPenn -= dommages;
    if (cible->HPenn <= 0) {
        cible->HPenn = 0;
    }

    printf("%s attaque %s pour %d dégâts. HP restant de l'ennemi : %d\n",
           attaquant->nom, cible->nom, dommages, cible->HPenn);

    if (cible->HPenn <= 0) {
        printf("%s est vaincu !\n", cible->nom);
    }
}


/*
- Restaure des points de vie à un personnage cible, en utilisant le pouvoir de soin du soigneur.
- La quantité de soin est égale à la récupération de points de vie (rest) du soigneur.
- Si les points de vie de la cible dépassent le maximum, ils sont limités à ce maximum.
- Affiche un message indiquant le nombre de points restaurés et les points de vie actuels de la cible.
- Paramètres :
  - "soigneur" : personnage qui effectue la restauration des points de vie.
  - "cible" : personnage qui reçoit les points de vie restaurés.
*/
void restaurerPoints(Personnage soigneur, Personnage cible) {
    int soin = soigneur->classe->rest;
    cible->HP += soin;

    // Ne pas dépasser le maximum de points de vie
    if (cible->HP > cible->classe->HPmax) {
        cible->HP = cible->classe->HPmax;
    }

    printf("%s restaure %d points de vie à %s. HP actuel : %d/%d\n",
           soigneur->nom, soin, cible->nom, cible->HP, cible->classe->HPmax);
}

/*
- Supprime un personnage spécifique de la liste de personnages.
- Libère la mémoire allouée pour le personnage supprimé.
- Si le personnage à supprimer est le premier de la liste, la tête de liste est mise à jour.
- Si le personnage est au milieu ou à la fin, il est retiré de la liste sans affecter les autres éléments.
- Paramètres :
  - "lstpersonnage" : pointeur vers la liste de personnages.
  - "persoASupprimer" : personnage à supprimer de la liste.
  - "lstaccessoire" : liste des accessoires, à vérifier si nécessaire pour les actions liées (non utilisée dans cette fonction).
*/
void supprimerPersonnage(Personnage *lstpersonnage, Personnage persoASupprimer, Accessoire *lstaccessoire) {
    Personnage current = *lstpersonnage;
    Personnage precedent = NULL;
    
    while (current != NULL) {
        if (current == persoASupprimer) {
            if (precedent == NULL) {
                *lstpersonnage = current->suivant; 
            } else {
                precedent->suivant = current->suivant;
            }
            free(current); 
        }
        precedent = current;
        current = current->suivant;
    }
}

/*
- Cette fonction gère le déroulement d'un combat entre des personnages et un ennemi.
- Paramètres :
    - lstpersonnage : pointeur vers la liste des personnages disponibles.
    - combattants : liste des personnages actuellement dans le combat.
    - ennemi : structure représentant l'ennemi à combattre.
    - lstaccessoire : liste des accessoires disponibles pour les personnages.
    - lstaccessoireagagner : liste des accessoires pouvant être gagnés après la victoire.
    - joueur : pointeur vers la structure du joueur (pour gérer l'or gagné).
    - numCombat : numéro du combat (utile pour suivre le déroulement des différents combats).
- Fonctionnement :
    - Le combat alterne entre les tours des personnages et celui de l'ennemi.
    - Lors du tour des personnages, chaque personnage peut choisir d'attaquer, de se défendre ou de restaurer des points de vie à un autre personnage.
    - Lors du tour de l'ennemi, l'ennemi choisit aléatoirement un personnage à attaquer et effectue une attaque physique ou une attaque de stress.
    - Le combat continue jusqu'à ce que l'ennemi ou tous les personnages soient vaincus.
    - En cas de victoire, le joueur reçoit de l'or et un accessoire aléatoire.
    - Les personnages morts sont retirés de la liste des combattants et leur équipement est mis à jour en conséquence.
*/
void deroulerCombat(Personnage *lstpersonnage, Personnage combattants, Ennemi ennemi, Accessoire *lstaccessoire, Accessoire *lstaccessoireagagner, Joueur* joueur, int numCombat) {
    int tour = rand() % 2; // 0 pour les personnages, 1 pour l'ennemi
    Personnage tmp;
    int nbperso = 0;

    printf("État des personnages :\n");
    tmp = combattants;
    while (tmp != NULL) {
        printf("%s : %d HP, %d str\n", tmp->nom, tmp->HP, tmp->str);
        nbperso++;
        tmp = tmp->suivant;
    }
    printf("L'ennemi que vous allez combattre est: %s\n", ennemi->nom);

    while (ennemi->HPenn > 0 && combattants != NULL) {
        if (tour == 0) {
            // Tour des perso
            tmp = combattants;
            while (tmp != NULL) {
                if (tmp->str >= 100) {
                    printf("%s est trop stressé pour agir.\n", tmp->nom);
                } else {
                    printf("Action de %s (A, D, R) : ", tmp->nom);
                    char action = saisirCaractere("", "ADRadr");
                    if (action == 'A' || action == 'a') {
                        attaquer(tmp, ennemi);
                    } else if (action == 'D' || action == 'd') {
                        printf("%s se défend.\n", tmp->nom);
                    } else if (action == 'R' || action == 'r') {
                        printf("Quel personnage voulez-vous restaurer ?\n");
                        afficherperso(combattants);
                        int choix = saisirEntier("");
                        Personnage cible = combattants;
                        for (int i = 1; i < choix && cible != NULL; i++) {
                            cible = cible->suivant;
                        }
                        if (cible != NULL) {
                            printf("%s restaure des points de vie à %s.\n", tmp->nom, cible->nom);
                            restaurerPoints(tmp, cible);
                        } else {
                            printf("Choix invalide.\n");
                        }
                    } else {
                        printf("Action invalide.\n");
                    }
                }
                if (ennemi->HPenn <= 0) break;
                tmp = tmp->suivant;
            }
            tour = 1; // On passe au tour de l'ennemi
        } else {
            // Tour de l'ennemi
            Personnage cible = combattants;
            int cibleIndex = rand() % nbperso;
            for (int i = 0; i < cibleIndex && cible != NULL; i++) {
                cible = cible->suivant;
            }
            if (cible != NULL) {
                int actionEnnemi = rand() % 2;
                if (actionEnnemi == 0) {
                    // Attaque physique
                    int defTotal = cible->classe->def;
                    int dommages = calculerDommagesAttaque(ennemi->attenn, defTotal);
                    cible->HP -= dommages;
                    if (cible->HP <= 0) cible->HP = 0;
                    printf("L'ennemi attaque %s pour %d dégâts. HP restants de %s : %d\n", cible->nom, dommages, cible->nom, cible->HP);
                } else {
                    // Attaque de stress
                    if (cible->str < 100) {
                        int strredTotal = 0;
                        Accessoire acc = cible->accessoire;
                        while (acc != NULL) {
                            strredTotal += acc->strred;
                            acc = acc->suivant;
                        }
                        int stress = (int)((ennemi->attstrenn - strredTotal) * (((float)rand() / RAND_MAX) * (1.2 - 0.8) + 0.8));
                        if (stress < 0) stress = 0;
                        cible->str += stress;
                        if (cible->str > 100) cible->str = 100;
                        printf("L'ennemi attaque %s pour %d stress. Stress actuel de %s : %d\n", cible->nom, stress, cible->nom, cible->str);
                    }
                }
                if (cible->HP <= 0) {
                    printf("%s est mort...\n", cible->nom);
                    supprimerPersonnage(&combattants, cible, lstaccessoire);
                    nbperso--;
                }
            }
            tour = 0; // On passe au tour des perso
        }
    }

    if (ennemi->HPenn <= 0) {
        joueur->or += 10;
        printf("Vous avez gagné 10 or. Or total : %d\n", joueur->or);

        // On choisi un accessoire aléatoire de lstaccessoireagagner
        Accessoire accGagne = *lstaccessoireagagner;
        int accIndex = rand() % 6;
        Accessoire precedent = NULL;
        for (int i = 0; i < accIndex && accGagne != NULL; i++) {
            precedent = accGagne;
            accGagne = accGagne->suivant;
        }
        if (accGagne != NULL) {
            printf("Vous avez gagné un accessoire : %s\n", accGagne->nom);
            printf("Caractéristiques : AttBonus = %d, DefBonus = %d, HPBonus = %d, RestBonus = %d, StrRed = %d\n",
                   accGagne->attbonus, accGagne->defbonus, accGagne->HPbonus, accGagne->restbonus, accGagne->strred);
            accGagne->utilise = 0; // On s'assure que l'accessoire gagné n'est pas utilisé

            // On ajoute l'accessoire à la liste des accessoires disponibles (lstaccessoire)
            accGagne->suivant = *lstaccessoire;
            *lstaccessoire = accGagne;

            // Après on supprime l'accessoire gagné de lstaccessoireagagner
            if (precedent == NULL) {
                *lstaccessoireagagner = accGagne->suivant;
            } else {
                precedent->suivant = accGagne->suivant;
            }
        }
    } else {
        printf("Tous les personnages sont vaincus...\n");
    }

}

/*
- Cette fonction permet de récupérer des points de vie (HP) pour les personnages présents dans le sanitarium.
- Paramètres :
    - sanitarium : un pointeur vers la liste des personnages dans le sanitarium.
- Fonctionnement :
    - Parcourt la liste des personnages dans le sanitarium.
    - Ajoute 7 points de vie (HP) à chaque personnage, à condition qu'ils n'aient pas atteint leur maximum de points de vie (défini par 'HPmax' dans leur classe).
    - Si les points de vie dépassent 'HPmax', ils sont limités à la valeur maximale de la classe.
*/
void recupererHP(Lieu sanitarium) {
    // On accéde à la liste des personnages dans le sanitarium
    Personnage temp = sanitarium; // 'sanitarium' c'est déjà un pointeur vers un Perso
    
    while (temp != NULL) {
        if (temp->HP != temp->classe->HPmax) temp->HP += 7;  // Ajouter 7 HP à chaque personnage dans le sanitarium
        if (temp->HP > temp->classe->HPmax) temp->HP = temp->classe->HPmax; // On vérifie que ça dépasse pas les HPmax
        temp = temp->suivant;
    }
}

/*
- Cette fonction réduit le stress des personnages présents dans la taverne en diminuant leur niveau de stress.
- Paramètres :
    - taverne : un pointeur vers la liste des personnages dans la taverne.
- Fonctionnement :
    - Parcourt la liste des personnages dans la taverne.
    - Réduit le stress de chaque personnage de 25, sans descendre en dessous de 0.
    - Le stress de chaque personnage est représenté par l'attribut 'str'.
*/
void reduireStress(Lieu taverne) {
    // On accede à la liste des personnages dans la taverne
    Personnage temp = taverne; // la 'taverne' c'est un pointeur vers un Perso
    
    while (temp != NULL) {
        if (temp->str > 0) temp->str -= 25;  // On réduit le stress de chaque personnage dans la taverne
        if (temp->str < 0) temp->str = 0; // On vérifie que ça descend pas en dessous de 0
        temp = temp->suivant;
    }
}

/*
- Cette fonction retourne le nombre de personnages actuellement disponibles dans la liste des personnages.
- Paramètres :
    - lstpersonnage : pointeur vers la liste des personnages disponibles.
- Valeur de retour :
    - Le nombre de personnages dans la liste.
- Effets de bord : Aucune modification n'est apportée à la liste des personnages.
*/
int nombrePersonnagesDisponibles(Personnage* lstpersonnage) {
    int res = 0;
    Personnage temp = *lstpersonnage;
    while (temp != NULL) {
        res++;
        temp = temp->suivant;
    }
    return res;
}

/*
- Permet de gérer l'envoi de personnages au Sanitarium, en retirant d'abord les personnages déjà présents si nécessaire et en ajoutant de nouveaux personnages disponibles, tout en garantissant que le joueur conserve au moins un personnage pour les combats.
- Paramètres :
    - lstpersonnage : pointeur vers la liste des personnages disponibles pour les combats.
    - sanitarium : pointeur vers la liste des personnages présents au Sanitarium.
- Valeur de retour : aucune.
- Effets de bord :
    - Modifie la liste des personnages disponibles et celle du Sanitarium.
    - Si le Sanitarium contient déjà des personnages, l'utilisateur peut en retirer certains avant d'y ajouter de nouveaux personnages.
    - Si la liste des personnages disponibles contient moins de 2 personnages, l'utilisateur ne peut pas ajouter plus de personnages au Sanitarium.
    - Vérifie que le joueur conserve au moins un personnage disponible pour les combats.
*/
void envoyerPersonnageAuSanitarium(Personnage* lstpersonnage, Lieu* sanitarium) {

    printf("Sanitarium :\n");

    // Étape 1 : On retire les perso déjà ds le Sanitarium
    while (*sanitarium != NULL) {
        afficherperso(*sanitarium);
        printf("Voulez-vous retirer %s du Sanitarium ? (Oui=1 / Non=0) : ", (*sanitarium)->nom);
        int choix = saisirEntier("");

        if (choix == 1) {
            Personnage tmp = *sanitarium;
            *sanitarium = tmp->suivant;
            tmp->suivant = *lstpersonnage;
            *lstpersonnage = tmp;
            printf("%s a été retiré du Sanitarium.\n", tmp->nom);
        } else if (choix == 0) {
            break;
        } else {
            printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

    if (nombrePersonnagesDisponibles(lstpersonnage) <= 1) {
        printf("Erreur : Vous devez conserver au moins un personnage disponible pour les combats.\n");
        return;
    }

    // Étape 2 : On ajoute des nouveaux perso si y'a de la place
    int placeSanitarium = 0;
    Personnage temp = *sanitarium;
    while (temp != NULL) {
        placeSanitarium++;
        temp = temp->suivant;
    }

    while (placeSanitarium < 2) {
        printf("Personnages disponibles :\n");
        afficherperso(*lstpersonnage);

        int choix = saisirEntier("Indiquez les numéros des personnages que vous souhaitez envoyer au Sanitarium (0 pour quitter) : ");

        if (choix == 0) {
            break;
        }

        Personnage tmp = *lstpersonnage;
        Personnage precedent = NULL;
        int j = 1;

        while (tmp != NULL && j < choix) {
            precedent = tmp;
            tmp = tmp->suivant;
            j++;
        }

        if (tmp == NULL || j != choix) {
            printf("Choix invalide. Veuillez réessayer.\n");
            continue;
        }

        if (nombrePersonnagesDisponibles(lstpersonnage) <= 1) {
            printf("Erreur : Vous devez conserver au moins un personnage disponible pour les combats.\n");
            break;
        }

        if (precedent == NULL) {
            *lstpersonnage = tmp->suivant;
        } else {
            precedent->suivant = tmp->suivant;
        }

        tmp->suivant = *sanitarium;
        *sanitarium = tmp;
        printf("%s a été envoyé au Sanitarium.\n", tmp->nom);
        placeSanitarium++;
    }
}

/*
- Permet de gérer l'envoi de personnages à la Taverne, en retirant d'abord les personnages déjà présents si nécessaire et en ajoutant de nouveaux personnages disponibles, tout en garantissant que le joueur conserve au moins un personnage pour les combats.
- Paramètres :
    - lstpersonnage : pointeur vers la liste des personnages disponibles pour les combats.
    - taverne : pointeur vers la liste des personnages présents à la Taverne.
- Valeur de retour : aucune.
- Effets de bord :
    - Modifie la liste des personnages disponibles et celle de la Taverne.
    - Si la Taverne contient déjà des personnages, l'utilisateur peut en retirer certains avant d'y ajouter de nouveaux personnages.
    - Si la liste des personnages disponibles contient moins de 2 personnages, l'utilisateur ne peut pas ajouter plus de personnages à la Taverne.
    - Vérifie que le joueur conserve au moins un personnage disponible pour les combats.
*/
void envoyerPersonnageATaverne(Personnage* lstpersonnage, Lieu* taverne) {

    printf("Taverne :\n");

    // Étape 1 : On retire les perso déjà dans la Taverne
    while (*taverne != NULL) {
        afficherperso(*taverne);
        printf("Voulez-vous retirer %s de la Taverne ? (Oui=1 / Non=0) : ", (*taverne)->nom);
        int choix = saisirEntier("");

        if (choix == 1) {
            Personnage tmp = *taverne;
            *taverne = tmp->suivant;
            tmp->suivant = *lstpersonnage;
            *lstpersonnage = tmp;
            printf("%s a été retiré de la Taverne.\n", tmp->nom);
        } else if (choix == 0) {
            break;
        } else {
            printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

    if (nombrePersonnagesDisponibles(lstpersonnage) <= 1) {
        printf("Erreur : Vous devez conserver au moins un personnage disponible pour les combats.\n");
        return;
    }

    // Étape 2 : On ajoute des nouveaux perso si y'a de la place
    int placeTaverne = 0;
    Personnage temp = *taverne;
    while (temp != NULL) {
        placeTaverne++;
        temp = temp->suivant;
    }

    while (placeTaverne < 2) {
        printf("Personnages disponibles :\n");
        afficherperso(*lstpersonnage);

        int choix = saisirEntier("Indiquez les numéros des personnages que vous souhaitez envoyer à la Taverne (0 pour quitter) : ");

        if (choix == 0) {
            break;
        }

        Personnage tmp = *lstpersonnage;
        Personnage precedent = NULL;
        int j = 1;

        while (tmp != NULL && j < choix) {
            precedent = tmp;
            tmp = tmp->suivant;
            j++;
        }

        if (tmp == NULL || j != choix) {
            printf("Choix invalide. Veuillez réessayer.\n");
            continue;
        }

        if (nombrePersonnagesDisponibles(lstpersonnage) <= 1) {
            printf("Erreur : Vous devez conserver au moins un personnage disponible pour les combats.\n");
            break;
        }

        if (precedent == NULL) {
            *lstpersonnage = tmp->suivant;
        } else {
            precedent->suivant = tmp->suivant;
        }

        tmp->suivant = *taverne;
        *taverne = tmp;
        printf("%s a été envoyé à la Taverne.\n", tmp->nom);
        placeTaverne++;
    }
}

/*
- Affiche la liste des accessoires disponibles à la vente dans la roulotte sous forme de tableau, avec les caractéristiques et le prix de chaque accessoire.
- Paramètres :
    - lstaccessoireRoulotte : liste des accessoires disponibles dans la roulotte.
- Valeur de retour : aucune.
- Effets de bord :
    - Affiche un tableau formaté avec les informations des accessoires disponibles : 
      - Le numéro de l'accessoire.
      - Le nom de l'accessoire.
      - Les bonus d'attaque, de défense, de points de vie, de récupération et de réduction de stress.
      - Le prix de l'accessoire.
    - Affiche une ligne d'en-tête pour structurer les informations et une ligne de fin pour conclure le tableau.
*/
void afficherAccessoiresRoulotte(Accessoire lstaccessoireRoulotte) {
    // Afficher l'en-tête du tableau avec la nouvelle colonne Prix
    printf("+----+--------------------------+-----------+-----------+-----------+-----------+----------+----------+\n");
    printf("| #  | Nom                      | AttBonus  | DefBonus  | HPBonus   | RestBonus | StrRed   | Prix     |\n");
    printf("+----+--------------------------+-----------+-----------+-----------+-----------+----------+----------+\n");

    // Afficher les accessoires
    int i = 1;
    for (; lstaccessoireRoulotte; lstaccessoireRoulotte = lstaccessoireRoulotte->suivant) {
        printf("| %-2d | %-24s | %-9d | %-9d | %-9d | %-9d | %-8d | %-8d |\n",
               i, lstaccessoireRoulotte->nom, lstaccessoireRoulotte->attbonus,
               lstaccessoireRoulotte->defbonus, lstaccessoireRoulotte->HPbonus,
               lstaccessoireRoulotte->restbonus, lstaccessoireRoulotte->strred, lstaccessoireRoulotte->prix);
        i++;
    }

    // Ligne de fin du tableau
    printf("+----+--------------------------+-----------+-----------+-----------+-----------+----------+----------+\n");
}

/*
- Permet de gérer la roulotte, en affichant les accessoires disponibles à la vente et en permettant l'achat d'un accessoire avec de l'or.
- Paramètres :
    - joueur : pointeur vers la structure représentant le joueur, permettant d'accéder à l'or disponible.
    - lstaccessoireRoulotte : pointeur vers la liste des accessoires disponibles à la vente dans la roulotte.
    - lstaccessoire : pointeur vers la liste des accessoires du joueur, qui sera mise à jour avec les achats effectués.
- Valeur de retour : aucune.
- Effets de bord :
    - Affiche l'or disponible du joueur.
    - Affiche les accessoires disponibles dans la roulotte.
    - Permet au joueur de sélectionner un accessoire à acheter, ou de quitter la roulotte.
    - Si l'achat est validé (le joueur a suffisamment d'or), l'accessoire est retiré de la roulotte et ajouté à la liste des accessoires du joueur.
    - Si le joueur choisit de quitter, la boucle se termine et la fonction se termine.
    - Affiche un message informant du succès ou de l'échec de l'achat.
*/
void gererRoulotte(Joueur* joueur, Accessoire* lstaccessoireRoulotte, Accessoire* lstaccessoire) {
    char choix[10];
    int acc = 0; 

    while (acc == 0) {
        printf("Or disponible: %d\n", joueur->or);

        afficherAccessoiresRoulotte(*lstaccessoireRoulotte);

        printf("Entrez le numéro de l'accessoire à acheter ou 'Q' pour quitter : ");
        fgets(choix, sizeof(choix), stdin);
        choix[strcspn(choix, "\n")] = 0;  // On enleve le '\n' de fgets

        if (choix[0] == 'Q' || choix[0] == 'q') {
            printf("Vous quittez la roulotte.\n");
            acc = 1; // sort de la boucle
        } else {
            int indexChoisi = atoi(choix);
            int index = 1;
            Accessoire precedent = NULL;
            Accessoire tmp = *lstaccessoireRoulotte;
            while (index < indexChoisi && tmp != NULL) {
                precedent = tmp;
                tmp = tmp->suivant;
                index++;
            }

            if (tmp != NULL && joueur->or >= tmp->prix) {
                joueur->or -= tmp->prix;
                printf("Achat réussi : %s pour %d or. Or restant : %d\n", tmp->nom, tmp->prix, joueur->or);

                // Retirer l'accessoire de la roulotte
                if (precedent == NULL) {
                    *lstaccessoireRoulotte = tmp->suivant;
                } else {
                    precedent->suivant = tmp->suivant;
                }

                // Ajouter l'accessoire acheté à la liste des accessoires disponibles pour les combats suivants
                tmp->suivant = *lstaccessoire;
                *lstaccessoire = tmp;

            } else {
                printf("Vous n'avez pas assez d'or pour cet achat ou choix invalide.\n");
            }
        }
    }
}

/*
- Crée un nouvel accessoire et l'ajoute à la liste des accessoires en vente à la roulotte.
- Paramètres :
    - nom : nom de l'accessoire (chaîne de caractères).
    - attbonus : bonus d'attaque conféré par l'accessoire.
    - defbonus : bonus de défense conféré par l'accessoire.
    - HPbonus : bonus de points de vie conféré par l'accessoire.
    - restbonus : bonus de récupération conféré par l'accessoire.
    - strred : réduction de stress offerte par l'accessoire.
    - prix : coût de l'accessoire en or.
    - lstaccessoire : pointeur vers la liste des accessoires en vente à la roulotte (modifiée pour inclure le nouvel accessoire).
- Valeur de retour : aucune.
- Effets de bord :
    - Alloue dynamiquement de la mémoire pour le nouvel accessoire.
    - Ajoute le nouvel accessoire en tête de la liste des accessoires.
    - Modifie la liste des accessoires passée en paramètre.
*/
void creerAccessoireRoulotte(char* nom, int attbonus, int defbonus, int HPbonus, int restbonus, int strred, int prix, Accessoire* lstaccessoire) {
    // Allocation mémoire pour le nouvel accessoire
    Accessoire nouvelAccessoire = malloc(sizeof(struct Accessoire));
    strcpy(nouvelAccessoire->nom, nom);
    nouvelAccessoire->attbonus = attbonus;
    nouvelAccessoire->defbonus = defbonus;
    nouvelAccessoire->HPbonus = HPbonus;
    nouvelAccessoire->restbonus = restbonus;
    nouvelAccessoire->strred = strred;
    nouvelAccessoire->prix = prix; // Ajout du prix
    nouvelAccessoire->suivant = *lstaccessoire;

    // Ajout du nouvel accessoire à la liste
    *lstaccessoire = nouvelAccessoire;
}

/*
- Force le joueur à faire sortir au moins un personnage du Sanitarium ou de la Taverne lorsque la liste des personnages disponibles est vide.
- Paramètres :
    - lstpersonnage : pointeur vers la liste des personnages disponibles (mise à jour après qu'un personnage soit sorti).
    - sanitarium : pointeur vers la liste des personnages présents au Sanitarium.
    - taverne : pointeur vers la liste des personnages présents à la Taverne.
- Valeur de retour : aucune.
- Effets de bord :
    - Modifie la liste des personnages disponibles en y ajoutant un personnage qui était dans le Sanitarium ou la Taverne.
    - Modifie les listes du Sanitarium ou de la Taverne en retirant un personnage choisi par le joueur.
    - Affiche les listes de personnages disponibles dans le Sanitarium et la Taverne pour guider le choix du joueur.
*/
void forcerSortiePersonnage(Personnage *lstpersonnage, Personnage *sanitarium, Personnage *taverne) {
    printf("Tous vos personnages disponibles sont morts ou indisponibles. Vous devez en faire sortir un du Sanitarium ou de la Taverne.\n");

    while (*lstpersonnage == NULL) {
        // Afficher les personnages dans le Sanitarium
        printf("\nPersonnages dans le Sanitarium :\n");
        afficherperso(*sanitarium);

        // Afficher les personnages dans la Taverne
        printf("\nPersonnages dans la Taverne :\n");
        afficherperso(*taverne);

        int choix;
        printf("\nIndiquez le numéro du personnage que vous voulez faire sortir (Sanitarium = 1, Taverne = 2) : ");
        scanf("%d", &choix);

        if (choix == 1 && *sanitarium != NULL) {
            // Sortir un personnage du Sanitarium
            Personnage tmp = *sanitarium;
            *sanitarium = tmp->suivant;
            tmp->suivant = *lstpersonnage;
            *lstpersonnage = tmp;
            printf("%s est sorti du Sanitarium et est maintenant disponible.\n", tmp->nom);
        } else if (choix == 2 && *taverne != NULL) {
            // Sortir un personnage de la Taverne
            Personnage tmp = *taverne;
            *taverne = tmp->suivant;
            tmp->suivant = *lstpersonnage;
            *lstpersonnage = tmp;
            printf("%s est sorti de la Taverne et est maintenant disponible.\n", tmp->nom);
        } else {
            printf("Choix invalide ou aucune option disponible. Veuillez réessayer.\n");
        }
    }
}

/*
- Sauvegarde l'état actuel de la partie dans un fichier texte, y compris le niveau, les personnages, les accessoires et l'or du joueur.
- Paramètres :
    - nomFichier : chemin du fichier où les données seront sauvegardées.
    - niveau : entier représentant le niveau actuel du jeu.
    - lstpersonnage : liste des personnages disponibles à sauvegarder (chaîne de caractères et statistiques).
    - sanitarium : liste des personnages présents au Sanitarium.
    - taverne : liste des personnages présents à la Taverne.
    - lstaccessoire : liste des accessoires disponibles du joueur.
    - roulotte : liste des accessoires en vente à la roulotte.
    - orJoueur : entier représentant l'or actuel du joueur.
- Valeur de retour : aucune.
- Effets de bord :
    - Écrit les informations sur le niveau, les personnages et les accessoires dans le fichier spécifié.
    - Crée un fichier texte ou écrase un fichier existant.
    - Formate les données de manière lisible pour pouvoir être rechargées ultérieurement.
*/
void sauvegarderPartie(const char *nomFichier, int niveau, Personnage lstpersonnage, Personnage sanitarium, Personnage taverne, Accessoire lstaccessoire, Accessoire roulotte, int orJoueur) {
    FILE *fichier = fopen(nomFichier, "w");
    if (!fichier) {
        printf("Erreur : impossible de créer le fichier de sauvegarde.\n");
        return;
    }

    // Sauvegarder le niveau
    fprintf(fichier, "Niveau: %d\n", niveau);

    // Sauvegarder les personnages disponibles
    fprintf(fichier, "PersonnagesDisponibles:\n");
    for (Personnage p = lstpersonnage; p != NULL; p = p->suivant) {
        fprintf(fichier, "%s %s %d %d %d %d %d\n", p->nom, p->classe->nom, p->HP, p->classe->HPmax, p->str, p->classe->att, p->classe->def);
    }

    // Sauvegarder les personnages au sanitarium
    fprintf(fichier, "Sanitarium:\n");
    for (Personnage p = sanitarium; p != NULL; p = p->suivant) {
        fprintf(fichier, "%s\n", p->nom);
    }

    // Sauvegarder les personnages à la taverne
    fprintf(fichier, "Taverne:\n");
    for (Personnage p = taverne; p != NULL; p = p->suivant) {
        fprintf(fichier, "%s\n", p->nom);
    }

    // Sauvegarder les accessoires disponibles
    fprintf(fichier, "AccessoiresDisponibles:\n");
    for (Accessoire a = lstaccessoire; a != NULL; a = a->suivant) {
        fprintf(fichier, "%s %d %d %d %d %d\n", a->nom, a->attbonus, a->defbonus, a->HPbonus, a->restbonus, a->strred);
    }

    // Sauvegarder les accessoires en vente à la roulotte
    fprintf(fichier, "Roulotte:\n");
    for (Accessoire a = roulotte; a != NULL; a = a->suivant) {
        fprintf(fichier, "%s %d\n", a->nom, a->prix);
    }

    // Sauvegarder l'or du joueur
    fprintf(fichier, "Or: %d\n", orJoueur);

    fclose(fichier);
    printf("Partie sauvegardée dans le fichier %s.\n", nomFichier);
}

// Fonction pour charger une partie
/*
- Charge l'état d'une partie depuis un fichier de sauvegarde et restaure les données dans les structures correspondantes.
- Paramètres :
    - nomFichier : chemin du fichier de sauvegarde à lire.
    - niveau : pointeur vers un entier qui contiendra le niveau du jeu après chargement.
    - lstpersonnage : pointeur vers la liste des personnages disponibles (mise à jour à partir du fichier).
    - sanitarium : pointeur vers la liste des personnages au Sanitarium.
    - taverne : pointeur vers la liste des personnages à la Taverne.
    - lstaccessoire : pointeur vers la liste des accessoires disponibles.
    - roulotte : pointeur vers la liste des accessoires en vente à la roulotte.
    - orJoueur : pointeur vers un entier représentant l'or du joueur (mis à jour à partir du fichier).
- Valeur de retour : aucune.
- Effets de bord :
    - Modifie les structures `lstpersonnage`, `sanitarium`, `taverne`, `lstaccessoire`, et `roulotte` pour refléter l'état sauvegardé.
    - Met à jour `niveau` et `orJoueur` en fonction des données du fichier.
    - Alloue dynamiquement des structures pour les personnages et accessoires si nécessaire.
*/
void chargerPartie(const char *nomFichier, int *niveau, Personnage *lstpersonnage, Personnage *sanitarium, Personnage *taverne, Accessoire *lstaccessoire, Accessoire *roulotte, int *orJoueur) {
    FILE *fichier = fopen(nomFichier, "r");
    if (!fichier) {
        printf("Erreur : impossible de lire le fichier de sauvegarde.\\n");
        return;
    }

    char ligne[256];
    char section[50] = "";  // Pour suivre la section en cours

    while (fgets(ligne, sizeof(ligne), fichier)) {
        if (strncmp(ligne, "Niveau:", 7) == 0) {
            sscanf(ligne + 7, "%d", niveau);
        } else if (strncmp(ligne, "PersonnagesDisponibles:", 23) == 0) {
            strcpy(section, "PersonnagesDisponibles");
        } else if (strncmp(ligne, "Sanitarium:", 11) == 0) {
            strcpy(section, "Sanitarium");
        } else if (strncmp(ligne, "Taverne:", 8) == 0) {
            strcpy(section, "Taverne");
        } else if (strncmp(ligne, "AccessoiresDisponibles:", 23) == 0) {
            strcpy(section, "AccessoiresDisponibles");
        } else if (strncmp(ligne, "Roulotte:", 9) == 0) {
            strcpy(section, "Roulotte");
        } else if (strncmp(ligne, "Or:", 3) == 0) {
            sscanf(ligne + 3, "%d", orJoueur);
        } else if (strlen(section) > 0) {

            if (strcmp(section, "PersonnagesDisponibles") == 0) {
                char nom[50], classeNom[50];
                int HP, HPmax, str, att, def;
                sscanf(ligne, "%s %s %d %d %d %d %d", nom, classeNom, &HP, &HPmax, &str, &att, &def);

                Classe *classe = malloc(sizeof(Classe));
                strcpy(classe->nom, classeNom);
                classe->HPmax = HPmax;
                classe->att = att;
                classe->def = def;
                classe->rest = 0; 

                creerPersonnage(nom, classe, lstpersonnage);
            } else if (strcmp(section, "Sanitarium") == 0) {
                char nom[50];
                sscanf(ligne, "%s", nom);
                Personnage p = *lstpersonnage;
                while (p && strcmp(p->nom, nom) != 0) {
                    p = p->suivant;
                }
                if (p) {
                    ajouterPersonnage(sanitarium, p);
                }
            } else if (strcmp(section, "Taverne") == 0) {
                char nom[50];
                sscanf(ligne, "%s", nom);
                Personnage p = *lstpersonnage;
                while (p && strcmp(p->nom, nom) != 0) {
                    p = p->suivant;
                }
                if (p) {
                    ajouterPersonnage(taverne, p);
                }
            } else if (strcmp(section, "AccessoiresDisponibles") == 0) {
                char nom[50];
                int attbonus, defbonus, HPbonus, restbonus, strred;
                sscanf(ligne, "%s %d %d %d %d %d", nom, &attbonus, &defbonus, &HPbonus, &restbonus, &strred);
                creerAccessoire(nom, attbonus, defbonus, HPbonus, restbonus, strred, lstaccessoire);
            } else if (strcmp(section, "Roulotte") == 0) {
                char nom[50];
                int prix;
                sscanf(ligne, "%s %d", nom, &prix);
                Accessoire acc = malloc(sizeof(struct Accessoire));
                strcpy(acc->nom, nom);
                acc->prix = prix;
                acc->suivant = NULL;
                ajouterAccessoire(roulotte, acc);
            }
        }
    }

    fclose(fichier);
    printf("Partie chargée depuis le fichier %s.\n", nomFichier);
}

int main(void) {
    // Initialisation des classes, personnages, ennemis et accessoires...
    Classe classes[] = { {"Furie", 13, 0, 20, 0}, {"Vestale", 3, 0, 20, 10}, {"Chasseur", 7, 3, 25, 3}, {"Maître", 10, 6, 17, 5} };
    int nbClasses = sizeof(classes) / sizeof(classes[0]);

    Personnage lstpersonnage = NULL;
    Ennemi lstennemi = NULL;
    Accessoire lstaccessoire = NULL;
    Accessoire lstaccessoireagagner = NULL;
    Accessoire lstaccessoireRoulotte = NULL;
    Joueur joueur;
    joueur.or = 0;  // Initialiser l'or du joueur à 0 au début du jeu
  
    // Initialiser la taverne et le sanitarium
    Lieu taverne = NULL;
    Lieu sanitarium = NULL;

    // Initialiser le nombre de combats
    int numCombat = 1;

    char choix;
    printf("Voulez-vous charger une partie ? (o/n) : ");
    scanf(" %c", &choix);
    if (choix == 'o' || choix == 'O') {
        chargerPartie("sauvegarde.txt", &numCombat, &lstpersonnage, &sanitarium, &taverne, &lstaccessoire, &lstaccessoireRoulotte, &orJoueur);
    }

    // Afficher les classes et leurs statistiques
    afficherClasses(classes, nbClasses);

    // Initialiser avec seulement deux personnages
    ajouterPersonnageDisponible(&lstpersonnage, "Boudicca", &classes[0]);
    ajouterPersonnageDisponible(&lstpersonnage, "Junia", &classes[1]);

    // Créer les ennemis
    creerEnnemi("Brigand", 1, 3, 3, 9, 10, &lstennemi);
    creerEnnemi("Squelette", 2, 6, 4, 13, 10, &lstennemi);
    creerEnnemi("Goule", 3, 8, 8, 16, 20, &lstennemi);
    creerEnnemi("Gargouille", 4, 10, 10, 20, 25, &lstennemi);
    creerEnnemi("Loup-Garou", 5, 12, 12, 25, 30, &lstennemi);
    creerEnnemi("Goule", 6, 15, 15, 30, 35, &lstennemi);
    creerEnnemi("Vampire", 7, 18, 18, 35, 40, &lstennemi);
    creerEnnemi("Mage", 8, 20, 20, 40, 45, &lstennemi);
    creerEnnemi("Dragon", 9, 25, 25, 50, 50, &lstennemi);
    creerEnnemi("Le fanatique", 10, 30, 30, 60, 60, &lstennemi);

    // Initialiser et ajouter les accessoires
    creerAccessoire("Pendentif magique", 5, 1, 0, 0, 0, &lstaccessoire);
    creerAccessoire("Bouclier de fer", 0, 5, 0, 0, 0, &lstaccessoire);
    creerAccessoire("Potion de guérison", 0, 0, 10, 0, 0, &lstaccessoire);
    creerAccessoire("Bottes de vitesse", 0, 0, 0, 10, 0, &lstaccessoire);

    // Initialiser et ajouter les accessoires à gagner à la liste
    creerAccessoire("Amulette de force", 7, 0, 0, 0, 0, &lstaccessoireagagner);
    creerAccessoire("Casque de protection", 0, 7, 0, 0, 0, &lstaccessoireagagner);
    creerAccessoire("Élixir de vie", 0, 0, 15, 0, 0, &lstaccessoireagagner);
    creerAccessoire("Gants de guérison", 0, 0, 0, 15, 0, &lstaccessoireagagner);
    creerAccessoire("Cape d'invisibilité", 3, 3, 0, 0, 0, &lstaccessoireagagner);
    creerAccessoire("Anneau de sagesse", 2, 2, 5, 5, 0, &lstaccessoireagagner);


    // Création des accessoires pour la roulotte (ajoutés dans une liste séparée)
    creerAccessoireRoulotte("Bottes de vitesse", 0, 2, 0, 0, 20, 7, &lstaccessoireRoulotte);   // Prix 7 or
    creerAccessoireRoulotte("Garde-épaule ", 0, 15, 0, 0, 50, 16, &lstaccessoireRoulotte);   // Prix 16 or
    creerAccessoireRoulotte("Pendentif du sage", 0, 0, 30, 0, 40, 35, &lstaccessoireRoulotte);      // Prix 35 or
    creerAccessoireRoulotte("Bouclier magique ", 0, 10, 10, 5, 35, 50, &lstaccessoireRoulotte);  // Prix 50 or
    creerAccessoireRoulotte("Anneau de magie", 0, 0, 5, 0, 30, 20, &lstaccessoireRoulotte);   // Prix 20 or
    creerAccessoireRoulotte("Cape de camouflage", 0, 3, 0, 0, 25, 15, &lstaccessoireRoulotte);       // Prix 15 or
    creerAccessoireRoulotte("Gants de combat", 8, 0, 0, 0, 45, 40, &lstaccessoireRoulotte);   // Prix 40 or
    creerAccessoireRoulotte("Horloge magique", 0, 0, 0, -5, 50, 60, &lstaccessoireRoulotte);         // Prix 60 or
    creerAccessoireRoulotte("Bouclier solaire", 5, 15, 0, 0, 55, 70, &lstaccessoireRoulotte);        // Prix 70 or
    creerAccessoireRoulotte("Lanterne eternelle", 0, 0, 10, 5, 15, 25, &lstaccessoireRoulotte); // Prix 25 or


    while (numCombat <= 10 && lstpersonnage != NULL && lstennemi != NULL) {

        printf("\n----- Combat %d -----\n", numCombat);

        // Ajouter un personnage aux niveaux 2, 4, 6, et 8
        if (numCombat == 2) {
            ajouterPersonnageDisponible(&lstpersonnage, "William", &classes[3]);
            printf("Nouveau personnage disponible : William\n");
        } else if (numCombat == 4) {
            ajouterPersonnageDisponible(&lstpersonnage, "Tardif", &classes[2]);
            printf("Nouveau personnage disponible : Tardif\n");
        } else if (numCombat == 6) {
            ajouterPersonnageDisponible(&lstpersonnage, "Alhazred", &classes[0]);
            printf("Nouveau personnage disponible : Alhazred\n");
        } else if (numCombat == 8) {
            ajouterPersonnageDisponible(&lstpersonnage, "Reynauld", &classes[1]);
            printf("Nouveau personnage disponible : Reynauld\n");
        }

        // Sélection des combattants
        Personnage combattants = choisirPersonnagesPourCombat(&lstpersonnage, numCombat);

        // Sélection des accessoires pour les combattants
        choisirAccessoiresPourPersonnages(combattants, &lstaccessoire);

        // Choisir l'ennemi pour le combat en fonction du niveau
        Ennemi ennemi = lstennemi;
        for (int i = 1; i < numCombat && ennemi != NULL; i++) {
            ennemi = ennemi->suivant;
        }

        // Vérifiez l'état des ennemis avant le combat
        if (ennemi == NULL) {
            printf("Plus d'ennemis disponibles. Vous avez gagner !! Félicitation !!\n");
            break;
        }


        deroulerCombat(&lstpersonnage, combattants, ennemi, &lstaccessoire, &lstaccessoireagagner,&joueur, numCombat);

        // Réintégrer les personnages du combat à la liste des personnages disponibles
        reintegrerPersonnages(&lstpersonnage, &combattants, &lstaccessoire);

       
        // Appel du sanitarium pour les personnages blessés
        envoyerPersonnageAuSanitarium(&lstpersonnage, &sanitarium);
        if(calculerTailleListe(&lstpersonnage)>=2){
        envoyerPersonnageATaverne(&lstpersonnage, &taverne);}
        
        // Appel au sanitarium pour augmenter les HP des personnages
        recupererHP(sanitarium);
        // Appel à la taverne pour réduire le stress des personnages
        reduireStress(taverne);

        gererRoulotte(&joueur,&lstaccessoireRoulotte, &lstaccessoire);

        /*if (lstpersonnage == NULL) {
            if (sanitarium == NULL && taverne == NULL) {
                printf("Tous vos personnages sont morts. La partie est terminée.\n");
                break;
            } else {
                // Forcer le joueur à sortir un personnage du Sanitarium ou de la Taverne
                forcerSortiePersonnage(&lstpersonnage, &sanitarium, &taverne);
            }
        }*/

        numCombat++;

        sauvegarderPartie("sauvegarde.txt", numCombat, lstpersonnage, sanitarium, taverne, lstaccessoire, lstaccessoireRoulotte, orJoueur);
    }


    while (lstpersonnage) {
        Personnage tmp = lstpersonnage;
        lstpersonnage = lstpersonnage->suivant;
        free(tmp);
    }
    while (lstennemi) {
        Ennemi tmp = lstennemi;
        lstennemi = lstennemi->suivant;
        free(tmp);
    }
    
    return 0;
}
