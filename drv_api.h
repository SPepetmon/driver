/*********************************************************************************************************
*                                                                                             
*     _/_/_/    _/        _/_/_/          _/_/_/  _/    _/                                     
*    _/    _/  _/        _/    _/      _/        _/    _/    _/_/    _/_/_/  _/_/      _/_/    
*   _/_/_/    _/        _/    _/      _/  _/_/  _/_/_/_/  _/    _/  _/    _/    _/  _/_/_/_/   
*  _/        _/        _/    _/      _/    _/  _/    _/  _/    _/  _/    _/    _/  _/          
* _/        _/_/_/_/  _/_/_/          _/_/_/  _/    _/    _/_/    _/    _/    _/    _/_/_/     
*                                                                                              
*                                                                                              
*			  __   __  _   ___  _______  ____   _   ___ 
*			|  | |  || | |   ||       ||    | | | |   |
*			|  |_|  || |_|   ||___    | |   | | |_|   |
*			|       ||       | ___|   | |   | |       |
*			|       ||___    ||___    | |   | |___    |
*			|   _   |    |   | ___|   | |   |     |   |
*			|__| |__|    |___||_______| |___|     |___|
*
* API implémentée par les drivers et utilisée par le gestionnaire de drivers
**********************************************************************************************************/

#ifndef __DRV_API_H__
#define __DRV_API_H__

//#include <semaphore.h>

/**
Fonction appelée juste après le chargement de la librairie en mémoire pour initialiser le capteur en spécifiant les données de connexion.
\param:	remote_addr	Adresse IP ou DNS de l'hôte contacter
	remote_port	Port de l'hôte à contacter
\return 0 si tout est ok, > 0 si erreur
*/

int drv_init( const char* remote_addr, int remote_port );


/**
Fonction appelée par le gestionnaire de drivers pour activer l'écoute (après l'initialisation)
\param mem_sem	Semaphore protegeant les accès concurrents à la mémoire
\return 0 si tout est ok, > 0 si erreur
*/
int drv_run( sem_t mem_sem );

/**
Fonction appelée par le gestionnaire de drivers juste avant de décharger la librairie de la mémoire. L'écoute se stoppe et les ressources sont libérées
*/
void drv_stop( void );

/**
Fonction appelée par le gestionnaire de drivers pour ajouter un capteur à écouter. Peut survenir n'importe quand.
\param	id_sensor	Identifiant unique du capteur qui doit être écouté
	mem_ptr		Pointeur vers l'espace mémoire dans lequelle les données lues pour ce capteur doivent être stockées
\return 0 si tout est ok, > 0 si erreur
*/
int drv_add_sensor( unsigned int id_sensor, unsigned char* mem_ptr );

/**
Fonction appelée par le gestionnaire de drivers pour supprimer un capteur en cours d'écoute.
\param	id_sensor	Identifiant unique du capteur qui ne doit plus être écouté
*/
int drv_remove_sensor( unsigned int id_sensor );

/**
Permet de demander des informations à un capteur
\param	id_sensor	Identifiant unique du capteur à interroger
	id_trame	Identifiant de la trame à envoyer
	buffer		Buffer qui va recevoir les données de retour
	max_length	Taille maximale du buffer
\return 0 si erreur, ou la taille des données lues
*/
int drv_fetch_data( unsigned int id_sensor, unsigned int id_trame, char* buffer, int max_length );


/**
Permet d'envoyer des données à un capteur (sans retour de sa part)
\param	id_sensor	Identifiant unique du capteur à contacter
	id_trame	Identifiant de la trame à envoyer
\return 0 si tout est ok, > 0 si erreur
*/
int drv_send_data( unsigned int id_sensor, unsigned int id_trame );

/**
 Recherche la premiere place libre dans le tableau des donnees des capteurs
 \param idCapteur
\return valeur de la place du capteur recherche, -1 si le capteur n'a pas été trouve.
*/
int drv_rechercheCapteur(unsigned int idCapteur);

#endif
