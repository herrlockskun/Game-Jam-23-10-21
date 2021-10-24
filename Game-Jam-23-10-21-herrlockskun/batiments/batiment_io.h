#ifndef BATIMENT_IO_H
#define BATIMENT_IO_H

#define C_MAX 20

/****************************************************************************************/
/*La structure de batiment contient :   -sa position                                    */
/*                                      -son type (ex : usine_Brique)                   */
/*                                      -son rang (lié au type)                         */
/*                                      -son niveau actuel                              */
/*                                      -un tableau stock_entree des stocks d'entree    */
/*                                      -un stock de sortie, avec le nombre de tuyaux   */
/*                                          en sortie et l'idication du tuyau suivant   */
/*                                      -un tableau door_T du type de connectique sur   */
/*                                          chaque port (N , E , S , O)                 */
/****************************************************************************************/
typedef struct batiment_io
{
    int pos_x;
    int pos_y;
    int type;
    int rang;
    int niveau;

    int * stock_entree;
    int stock_sortie;
    int nb_sortie;
    int next_s;

    int door_T[4];          //-1 = pas de tuyau ; 0 = entree ; 1 = sortie
}batiment_io_t;             //door_T[0] = top ; door_T[1] = right ; door_T[2] = bottom ; door_T[3] = left

/****************************************************************************************/
/*initBatiment : fonction qui alloue l'espace memoire a la creation d'un batiment       */
/*                                                                                      */
/*Uniquement utilisee par newBatiment a la creation du batiment                         */
/****************************************************************************************/
int initBatiment(batiment_io_t ** batiment , int nb_s_entree);

/****************************************************************************************/
/*newBatiment : fonction qui cree la base d'un batiment aux coordonnees (x,y)           */
/*                                                                                      */
/*Uniquement utilisee par les fonctions de creation des sous-types de batiments         */
/****************************************************************************************/
void newBatiment(batiment_io_t ** batiment , int pos_x , int pos_y , int nb_s_entree , int rang);

/****************************************************************************************/
/*deleteBatiment : fonction qui supprime un batiment                                    */
/****************************************************************************************/
void deleteBatiment(batiment_io_t * batiment);

/****************************************************************************************/
/*newDoor : cree une nouvelle conectique, du cote "side" avec le type "type"            */
/*                                                                                      */
/*Appele par un tuyau lors de son racordement a un batiment                             */
/****************************************************************************************/
int newDoor(batiment_io_t * batiment , int side , int type);

/****************************************************************************************/
/*deleteDoor : retire une connectique du batiment                                       */
/*                                                                                      */
/*Appelee par un tuyau lors de sa destruction                                           */
/****************************************************************************************/
int deleteDoor(batiment_io_t * batiment , int side);

/****************************************************************************************/
/*stockEntreePlein : fonction qui renseigne si le stock d'entree est plein              */
/****************************************************************************************/
int stockEntreePlein(batiment_io_t * batiment , int stock , int max);

/****************************************************************************************/
/*stockEntreePlein : fonction qui renseigne si le stock de sortie est vide              */
/****************************************************************************************/
int stockSortieVide(batiment_io_t * batiment);

/****************************************************************************************/
/*destRessource : fonction qui donne le prochain tuyau auquel envoyer une ressource     */
/*                                                                                      */
/*Renvoie le code d'erreur -1 si aucune sortie de connectee                             */
/*Renvoie le code d'erreur -2 si probleme d'execussion                                  */
/*Renvoie l'indice (et donc le cote) de la connectique dans le tableau des connectiques */
int destRessource(batiment_io_t * batiment);

#endif
