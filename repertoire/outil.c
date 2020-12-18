#include <stdio.h>   /* pour les entrées-sorties */
#include <string.h>  /* pour les manipulations de chaînes de caractères */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compléter votre nom ici                                                */
/*   Nom : DIALLO                   Prénom : Ibrahima                     */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le répertoire stocké en mémoire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire *rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compléter code ici pour tableau
	int idx = MAX_SAISIE;
	int i = rep->nb_elts;
	if (rep->nb_elts < MAX_ENREG)
	{
		rep->tab[i] = enr;
		rep->nb_elts += 1;
	}
	else {
		return(ERROR);
	}

	
#else
#ifdef IMPL_LIST

	bool inserted = false;
	if (rep->nb_elts == 0) {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}

	}
	else {
		int i = 0;
		while ((i < rep->nb_elts) && (est_sup(enr, (GetElementAt(rep->liste, i)->pers)))) {
			i++; // on incremente i tant qu'on est dans la liste et que enr est superieur à l'element compteur de la liste
		}
		InsertElementAt(rep->liste, i, enr); //on insere le conctact a l'indice i
		rep->nb_elts++; // on incremente le nombre d'elements
		modif = true;
		rep->est_trie = true; // la liste est triee
	}


#endif
	
#endif


	return(OK);

} /* fin ajout */
  /**********************************************************************/
  /* supprime du répertoire l'enregistrement dont l'indice est donné en */
  /*   paramètre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire *rep, int indice) {

	// compléter code ici pour tableau
	if (rep->nb_elts >= 1)		/* s'il y a au moins un element ds le tableau */
	{						/* et que l'indice pointe a l'interieur */
		for (int i = indice; i < MAX_SAISIE; i++) { // on parcourt les contacts
			*(rep->tab + i) = *(rep->tab + (i + 1));
		}
		rep->nb_elts -= 1;		/* ds ts les cas, il y a un element en moins */
		modif = true;
	}

	return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du répertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif à vrai                              */
  /************************************************************************/
  // complet

	int supprimer_un_contact_dans_rep_liste(Repertoire *rep, SingleLinkedListElem *elem) {
	
	int ret=DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0); 
	}
#endif
#endif


  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement sur une ligne à l'écran  */
  /* ex Dupont, Jean                 0320304050                         */
  /**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	// code à compléter ici
	printf("%-30s,%-30s,%-30s", enr.nom, enr.prenom, enr.tel);

} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	// code à compléter ici
	// comme fonction affichage_enreg, mais avec présentation alignées des infos
	printf("| %-30s|%-30s|%-30s\n", enr.nom, enr.prenom, enr.tel);

} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	// code à compléter ici
	if (_stricmp(enr1.nom, enr2.nom) < 0) { // stricmp compare chaque lettre des deux variables entre en parametre. Elle compare en convertissant les lettre majuscule en minuscule
										  //on retourne false si le premier nom est plus petit que le deuxieme
		return false;
	}

	if (_stricmp(enr1.nom, enr2.nom) == 0) { //Si on a le meme nom, on va comparer les prenoms
		if (_stricmp(enr1.prenom, enr2.prenom) > 0) { //retourne vrai si le premier est plus grand que le deuxieme
			return true;
		}
		else { // retourne false sinon
			return false;
		}
	}
	else { // retourne vrai sinon
		return true;
	}
	return(false);
}
 
/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire *rep)
{

#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	int cpt = 1; // compteur qui va stocker le nombre de permutations
	while (cpt != 0) {// on continue jusqu'à ce que le tableau soit trié
		cpt = 0;
		for (int i = 0; i < rep->nb_elts - 1; i++) { //on parcourt tous les contacts
			if (est_sup(*(rep->tab + i), *(rep->tab + i + 1))) { // si un element est supérieur à celui qui le suit
				Enregistrement tmp = *(rep->tab + i); 
				*(rep->tab + i) = *(rep->tab + i + 1); // on les permute
				*(rep->tab + i + 1) = tmp;
				cpt++; // on incremente le compteur
			}
		}
	}


	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien à faire !
	// la liste est toujours triée
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le répertoire d'un enregistrement correspondant au  */
  /*   nom à partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au critère ou*/
  /*   un entier négatif si la recherche est négative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire *rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de début de recherche dans tableau/liste rep */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;		


#ifdef IMPL_TAB
							// ajouter code ici pour tableau
	strcpy_s(tmp_nom, MAX_NOM, nom); // on copie le nom dans tmp_nom
	_strupr_s(tmp_nom, _countof(tmp_nom)); // puis on le met en majuscule pour eviter certains problemes avec la casse
	ind_fin = rep->nb_elts; // pour pouvoir s'arreter a la fin de la boucle on donne a ind_fin nb_elts
	for (int i = ind; i < ind_fin; i++) {
		strcpy_s(tmp_nom2, MAX_NOM, rep->tab + i); // on recopie chaque element du tableau dans tmp_nom2
		_strupr_s(tmp_nom2, _countof(tmp_nom2));
		if (strcmp(tmp_nom, tmp_nom2) == 0) { // si on a le meme nom
			return i; // on retourne l'indice
		}
	}
	
#else
#ifdef IMPL_LIST
							// ajouter code ici pour Liste
	/*On opere comme l'implementation pour les tableau sauf que pour recuperer l'element on va utiliser la fonction "GetElementAt"*/
	strcpy_s(tmp_nom, MAX_NOM, nom); 
	_strupr_s(tmp_nom, _countof(tmp_nom));
	ind_fin = rep->nb_elts; // 
	for (int i = ind; i < ind_fin; i++) {
		strcpy_s(tmp_nom2, MAX_NOM, GetElementAt(rep->liste, i)->pers.nom); 
		_strupr_s(tmp_nom2, _countof(tmp_nom2));
		if (strcmp(tmp_nom, tmp_nom2) == 0) { 
			return i; 
		}
	}

	
#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non numériques de la chaines        */
  /*********************************************************************/
void compact(char *s)
{
	// compléter code ici
	char tabCompact[MAX_TEL]; // creatin d'un tableau qui va recevoir le compacte
	int j = 0; //indice pour la copie
	for (int i = 0; i < MAX_TEL; i++) {
		if (s[i] >= '0' && s[i] <= '9') {// si on a un element numerique
			tabCompact[j] = s[i]; // on le recopie dans tabCompact
			j++; // on incremente j pour pouvoir passer au suivant
		}
	}
	tabCompact[j] = '\0'; // on place le cartactere de ifn de chaine pour montrer au compilateur qu'on a fini la copie
	return;
}

/**********************************************************************/
/* sauvegarde le répertoire dans le fichier dont le nom est passé en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionné ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	errno_t err = fopen_s(&fic_rep, nom_fichier, "w"); // on ouvre le fichier pour ecrire dedans
	if (err != 0) { // gestion de l'erreur
		return(ERROR);
	}
	char tmp[MAX_NOM + MAX_NOM + MAX_TEL + 2]; // on cree un tableau avec assez de taille pour pouvoir contenir le nom,prenom et numero telephone
	for (int i = 0; i < rep->nb_elts; i++) {// on reecrit tout le fichier dans tmp
		sprintf_s(tmp, MAX_NOM + MAX_NOM + MAX_TEL + 2, "%s%c%s%c%s\n", (rep->tab + i)->nom, SEPARATEUR, (rep->tab + i)->prenom, SEPARATEUR, (rep->tab + i)->tel);
		fputs(tmp, fic_rep); // on ecrit le tout sur la ligne
	}
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	/*on fait comme l'implemmentation du tableau mais pour recuperer les element on utuilise GetElementAt*/
	errno_t err = fopen_s(&fic_rep,"nom_fichier.txt", "w"); // on ouvre le fichier pour ecrire dedans
	if (err != 0) { // gestion de l'erreur
		return (ERROR);
	}
	char tmp[MAX_NOM + MAX_NOM + MAX_TEL + 2]; 
	for (int i = 0; i < rep->nb_elts; i++) {
		sprintf_s(tmp, MAX_NOM + MAX_NOM + MAX_TEL + 2, "%s%c%s%c%s\n", GetElementAt(rep.liste, i)->pers.nom, SEPARATEUR, GetElementAt(rep.liste, i)->pers.prenom, SEPARATEUR, GetElementAt(rep.liste, i)->pers.tel);
		fputs(tmp, fic_rep);
	}
#endif
#endif
	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le répertoire le contenu du fichier dont le nom est  */
  /*   passé en argument                                                */
  /*   retourne OK si le chargement a fonctionné et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char *char_nw_line;
	
	_set_errno(0);
	if ( ((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL) )
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element à priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
														// ajouter code implemention liste
				Enregistrement tmp; // Maillon qui va nous permettre de verifier nos conditions suivantes
				if (lire_champ_suivant(buffer, &idx, tmp.nom, MAX_NOM, SEPARATEUR) == OK) {
					idx++; // on saute le separateur
					if (lire_champ_suivant(buffer, &idx, tmp.prenom, MAX_NOM, SEPARATEUR) == OK) {
						idx++;
						if (lire_champ_suivant(buffer, &idx, tmp.tel, MAX_NOM, SEPARATEUR) == OK) {
							num_rec++; // element a priori correct, on le comptabilise
						}
					}
			    }
				InsertElementAt(rep->liste, rep->liste->size, tmp); // on ajoute l'element a la liste
#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */