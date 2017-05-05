VERSIONS DE MFC MUTE....

----------------------------------------------------------------------------------------------------
--- version 0.0.7 -- 10-11-2005 release:------------------------------------------------------------
--- explanation of fixes/additions/alterations
----------------------------------------------------------------------------------------------------
1. Per coding help and motivation from Defnax and MCoder:
   a-> Changed tabs to XP Theme aware tabs.
   b-> Added status bar and removed old green/red bar from bottom of GUI.
   c-> Added headings above list boxes with counts.
   d-> Regrouped connections dialog controls
   e-> Added lots of nice looking button graphics
2. Increased performance for hashing by increasing chunk sizes being passed to SHA1 routines.
3. Decreased the time between automated queue searches.
4. Moved string resources out of MS Visual Studio automated resource files.  Now when new strings
   are added, the file won't get automatically modified by the compiler IDE.
5. When manually searching for a file and attempting to restart the download of a queued download,
   the remote HASH is also checked for a match against the queued file.  If the hash matches,
   then that file download is resumed immediately as long as the # of downloads from that VIP doesn't
   exceed the max downloads from 1 VIP.
   
----------------------------------------------------------------------------------------------------
--- version 0.0.6 -- 08-13-2005 mise � jour---------------------------------------------------------
--- explication des corrections/ajouts/modifications
----------------------------------------------------------------------------------------------------
1.  Incorporation du code du patch DROP TREE de Jason Rohrer.
2.  Mise � jour de l'�cran "A propos" int�grant l'adresse de sourceforge
     http://www.sourceforge.net/projects/mfc-mute-net
3.  L'utilisation du joker (wildcard) '*' permet maintenant de limiter les r�sultats. Ceux-ci sont
     randomiz�s afin d'augmenter la s�curit� et de r�duire les attaques du r�seau par des recherches
     effectu�es � partir de ce joker.
4.  Les fichiers tels que desktop.ini et Thumbs.db ne seront jamais inclus dans les r�sultats de
     recherches. Il n'y a aucune raison de pouvoir t�l�charger de tels fichiers, aussi ils sont retir�s
    des r�sultats des reherches.
5.  Les icones dynamiques sont charg�es au d�marage � partir des fichiers d'icones contenues dans
    le repertoire icones situ� sous le repertoire du programme principal. La liste des fichiers d'icones
    est donn�e ci-dessous. Pour changer une icone il suffit de remplacer le ou les fichiers ci-dessous :
          icons\searchTab.ico
          icons\downloadsTab.ico
          icons\uploadsTab.ico
          icons\connectionsTab.ico
          icons\sharedfilesTab.ico
          icons\settingsTab.ico
6.  Les statistiques de traffic r�seau figurent d�sormais sur de nombreux �crans  (en anglais seulement)


----------------------------------------------------------------------------------------------------
--- version 0.0.5 -- 03-04-2005 release:-----------------------------------------------------------------------
--- explanation of fixes/additions/alterations
----------------------------------------------------------------------------------------------------
1.  Added colored bar across bottom of GUI that shows connection status.
2.  Put the elapsed time in the caption bar format DAYS:HOURS:MINUTES:SECONDS
3.  Added some code from Nate that saves out of order downloaded chunks to help speed up D/Ls.


----------------------------------------------------------------------------------------------------
--- version 0.0.3 -- 02-09-2005-----------------------------------------------------------------------
--- Explication des corrections/ajouts/modifications
----------------------------------------------------------------------------------------------------

1.  Ajout de nouvelles icones et modifications des icones existantes(--NGLWARCRY--)
2.  Les fichiers sources du projet ont �t� modifi�s pour �tre facilement compil�s avec Visual Studio .NET.
3.  Nouveau code ajout� pour sauvergarder les IP hotes dans le fichier seedHosts.ini lors
    de la fermeture du programme.(--Nate--/TSAFA)
4.  Correction du statut du tri dans la fen�tre des t�l�chargements.
5.  Ajout d'un clic droit dans la fen�tre des t�l�chargements ce qui permet � l'utilisateur de
    de faire de l'item selectionn� le prochain � �tre t�l�charg�.(--Tony--)
6.  Augmentation du d�lai entre chaque requ�te de recherche afin de r�duire l'engorgement
    du r�seau par trop de requ�tes de recherche.
7.  Modification du code relatif au t�l�chargement en sorte que chaque fois qu'un fichier est
    annul� ou termin� le fichier Downloadqueue.ini file soit mis � jour pour refleter l'�tat de
    la file d'attente. Ceci am�liore la persistance et l'int�grit� de cette file en cas de
    de crash �ventuel ou de fermeture rapide du programme.
8.  Si un utilisateur cherche un fichier qui est dans la file d'attente et le trouve dans
    la fen�tre de recherche il peut effectuer un double clic sur ce fichier ou cliquer sur
    t�l�chargement et forcer ainsi le telechargement � redemarrer.(--Tony--)
9.  Ajout d'un onglet "fichiers partag�s" dans le GUI. Celui-ci montre les fichiers en partage
    et leurs HASH (hachage).
    -- on peut exporter pour un usage externe cette liste vers un fichier utilisant la virgule
    comme d�limiteur.
10. L'utilisateur peut d�sormais reduire la fen�tre principale � l'aide d'une poign�e barre (--Tony--)
11. Ajout de modifications dans le code source du noyau pour refleter les modifications et am�liorations
    effectu�es par Jason Rohrer's  dans le noyau de MUTE-0.4.
    -- Recherche d'h�tes am�lior�e
    -- Gestion du temps corrig�e
    -- Correction des canaux d'entr�e et de sortie
    -- Correction du StringBufferOutputStream (flux de sortie des chaines)
    -- corrections apport�es au compilateur de chiffrement crytpo++
    -- corrections apport�es a ChannelReceivingThreadManager (manager des canaux de reception)
    -- corrections apport�es au ConnectionMaintainer (maintien des connexions)
    -- corrections du d�roulant de Log
    -- corrections apport�es � formatUtils.cpp (ajout de code -GiB)
12. Modifications du code g�rant le d�compte temporel et l'abandon (--Nate--)
13. Am�liorations SIGNIFICATIVES du code de routage. Le code recherche et nettoie les modifications au fur et
    � mesure qu'elles sont d�couvertes (--NATE--).
    -- Ces changement devraient vraiment am�liorer le r�seau.
14. Ajout de code minimisant les requ�tes de duplication de fichiers partiels fourni par (--Nate--)
    -->Auparavant les noeuds recevaient des requ�tes de duplication de fichiers encombrant le r�seau de
    paquets inutiles.
15. Ajout d'un m�canisme de cache associ� au r�sultat de recherche reduisant TRES SIGNIFICATIVEMENT
    l'utilisation du processeur.La version pr�c�dente parcourait et  recr�ait la liste des fichiers
    partag�s lors de chaque requ�te de recherche. La nouvelle version met � jour p�riodiquement un
    cache qui contient le nom de fichier, le hachage associ� et la taille du fichier. Au
    d�marrage l'application met � jour ce cache � l'occasion de la premi�re requ�te de recherche. Lors
    des requ�tes suivantes l'application recherche quand le cache a �t� mis � jour pour la derni�re fois.
    Le premier d�lai entre deux mises � jour du cache est de 10 minutes,� chaque mise � jour successive
    l'intervalle augmente de 50 secondes jusqu'� atteindre un maximum de 30 minutes entre chaque mise
    � jour - Ceci non seulement reduit l'usage du processeur mais am�liore �galement la performance
    g�n�rale du r�seau car l'application dispose d�sormais de beaucoup plus de temps pour traiter les
    message du r�seau plut�t que de consacrer son temps � rechercher dans les r�pertoires et les noms
    de fichiers.
16. Augmentation du temps de saturation du syst�me de hachage. Cela signifie le temps allou� pour
    rechercher dans le r�pertoire des fichiers partag�s de nouveau fichiers qui n'ont pas encore �t�
    hach�s a �t� augment�. Ceci permet au syst�me de hachage de consommer moins de ressources processeur.
17. La fen�tre de fichiers en cours de partage se nettoie automatiquement apr�s avoir montr� 100 fichiers
    afin de limiter la consommation de m�moire ram et �galement d'acc�l�rer le fonctionnement dans la mesure
    ou chaque fois que des tron�ons de fichiers sont �mis en sortie cette liste doit �tre parcourue afin
    d'�tre mise � jour.
18. Les dimensions et l'emplacement de la fen�tre sont d�sormais persistants et m�moris�s dans un fichier
   "mfcWindowPlacement.ini". Ce fichier utilise 5 entiers d�limit�s par une virgule. Le format est :
   champs 1 : 0== montrer la fen�tre dans la barre des taches
              1== affichage normal de la fen�tre
   champs 2 : x coordonn�e du coin haut gauche de la fen�tre
   champs 3 : y coordonn�e du coin haut droite de la fen�tre
   champs 4 : x coordonn�e du coin bas gauche de la fen�tre
   champs 5 : y coordonn�e du coin bas droite de la fen�tre
19. Ajout de statistiques dans la fen�tre de partage sur les partages effectu�s et les tron�ons mis � jours.
    
----------------------------------------------------------------------------------------------------
--- version 0.0.2 -- 11-24-2004-----------------------------------------------------------------------
--- Description des corrections/ajouts/modifications
----------------------------------------------------------------------------------------------------

1.  *** Nouvelle file d'attente des t�l�chargements *** apr�s un red�marrage 
    du programme de nouvelles sources sont d�sormais recherch�es en vue de continuer le t�l�chargement.
    
    La reprise des t�l�chargements a �t� consid�rablement am�lior�e. Maintenant le programme
    est capable de red�marrer des t�l�chargements quand de nouvelles sources deviennent disponibles.
    
    Les donn�es de la file d'attente sont stock�es dans le fichier downloadqueue.ini dans le
    r�pertoire MUTE\Settings. Il s'agit d'un fichier texte dans lequel les lignes ont le format 
    suivant :  NOM DE FICHIER * HACHAGE.
    
    '*' est le d�limiteur. NOM DE FICHIER estle nom de la version ascii de la version locale
    du fichier dans le r�pertoire des entr�es.HACHAGE est le hachage du 
    fichier distant tel qu'enregistr� lors du d�but du t�l�chargement. Le fichier 
    Downloadqueue.ini est lu au d�marrage de l'application et mis � jour avec les nouvelles donn�es de 
    synchronisation de la file d'attente lors de sa fermeture.
    
    Si un utilisateur veut ajouter manuellement � Downloadqueue.ini des 
    fichiers pr�sents dans le r�pertoire des fichiers entrants il peut le faire m�me sans en connaitre 
    la valeur de hachage. Il suffit, alors que le logiciel est arr�t�,  d'�diter le fichier 
    Downloadqueue.ini avec un �diteur de texte standard et d'ajouter le nom des fichiers suivi par 
    un '*'.  Par exemple pour ajouter le fichier "supercoolmusic.mp3" il suffit 
    d'ouvrir le fichier
    Downloadqueue.ini et d'ajouter la ligne :
    
    supercoolmusic.mp3 *
    
2.  Francis a revu l'�cran de r�glages en le dotant � gauche d'un panneau d'options
    � partir duquel on peut appeler les �crans de r�glages, d'aide HTML ( 
    qui pointe sur la page de MUTE WIKI, une actualisation restant � faire) ainsi qu'un �cran 
    A propos.

3.  Francis a restructur� le code pour permettre de changer de langue 
    sans avoir � red�marrer le programme.
    
4.  Francis a ajout� une prise en charge de fichiers de langues qui peuvent �tre cr��s
    et plac�s dans le r�pertoire settings pour permettre la reconnaissance d'autres
    langues que celles incorpor�es dans le logiciel (Anglais-Italien-Allemand-Francais).
    voir : http://board.planetpeer.de/viewtopic.php?t=464

5.  Nouvel �cran A Propos avec un d�roulant sympa pour les cr�dits.

6.  R�solution du probl�me des instances multiples de MFC-MUTE. Lorsque deux 
    instances de MFC-MUTE utilisaient le m�me port le programme plantait.

7.  Les recherches "hash_" fonctionnent correctement dans cette version.

8.  Le programme se ferme plus rapidement, grace � un code plus �pur�.

9.  Traduction en francais

10. Nouvel �cran de fermeture qui permet de savoir quand le programme est vraiment termin�.

11. Correction de bugs internes relatifs � l'exportation des r�sultats de recherche.

12. Am�lioration du processus de t�l�chargement. Les messages sont d�sormais trait�s
    par la routine de traitement appropri�e. Plus de passage � l'aveugle.

13. Utilisation de la librairie pthreads32 pour �viter le gel des t�l�chargements. Avec
    cette version Vous ne vous trouverez plus dans la situation de ne pouvoir arr�ter un
    t�l�chargement.

14. Annulation des recherches plus rapide.

15. Correction d'un bug dans le code de hachage qui causait l'arr�t du programme quand
    l'utilisateur d�marrait avec un r�pertoire de hachage invalide.
    
16. Pour les clients MFC-MUTE seulement, ajout de code pour permettre les recherches
    avec '*. Ceci devrait retourner tous les fichiers dans le r�pertoire des fichiers
    partag�s. A utiliser avec mod�ration parce que cela monopolise la bande passante. 
    Mais si vous avez de la chance comme avec GOOGLE, alors essayez.
    
17. Suppression de la limitation � 28 kbytes de la chaine de recherche. D�sormais les
    r�sultats d'une recherche correspondent � tous les crit�res de la requ�te.

18. Ajout d'ic�nes aux menus contextuels dans chaque fen�tre


----------------------------------------------------------------------------------------------------
--- 08-21-2004 version:-----------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
1.  Une modification substantielle de la fa�on dont les recherches entrantes sont trait�es a �t�
    effectu�e. Maintenant, en pr�sence d'une recherche entrante, s'il n'existe pas de hachage pour
    un fichier, aucun hachage n'est cr��. Un thread s�par� prend en charge la g�n�ration de fichiers
    de hachage a partir du r�pertoire des fichiers partag�s de l'utilisateur. 

    Le nouveau thread d�marre quand le programme d�marre. Ce thread parcourt tous les fichiers
    du r�pertoire des fichiers partag�s et v�rifie au cours de cette it�ration qu'� chaque fichier
    correspond bien un hachage. Si un hachage n'existe pas il en cr�e un et attend 10 secondes jusqu'�
    ce qu'il puisse cr�er le fichier de hachage suivant. De plus, la fonction qui assure concr�tement
    le hachage est d�sormais dot�e d'un limiteur, de telle sorte que les gros fichiers ne plantent pas 
    totalement l'application. Alors que le code de hachage boucle toutes les trois
    secondes, cette fonction introduit une pause d'une seconde. Ceci garantit que le hachage ne porte
    pas pr�judice aux threads d'autres applications.    
    
2.  Cr�ation d'un installateur complet avec Inno Setup 4.2.7 ISPP 1.2.1.295 et ISTool 4.2.7.
    -- Le nouvel installateur g�n�re des installations en allemand, italien et anglais.
    -- Le nouvel installateur place une icone sur le bureau et dans le groupe de programmes.
    -- Le nouvel installateur place le nouveau Seed Node Updater (qui met � jour les noeuds de d�part)
       dans le r�pertoire settings.
    -- Le nouvel installateur place les fichiers batch sur le bureau pour le seed node updater qui mettra � 
       jours les pr�f�rences de l'utilisateur s'agissant des noeuds de d�part et des caches web.
       
----------------------------------------------------------------------------------------------------       
--- 08-07-2004 version:-----------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
1.  Support pour plusieurs langues ajout� � partir de l'�diteur de ressources de MS Visual C++. Maintenant
    MUTE MFC est disponible en anglais,allemand et italien.

--- 7-29-2004 version de d�bogage : executable seulement (source disponible sur demande) -------
1.  la version 7-28 avait un bug concernant le t�l�chargement quand des fichiers en lecture seule �taient partag�s...
    Le programme plantait lors de la tentative de transf�rer les fichiers � partir du r�pertoire des fichiers entrants
    vers un r�pertoire en lecture seule (par exemple un lecteur CD) parce que les pointeurs de fichiers n'�taient pas
    pas valid�s dans le code sous-jacent du coeur MUTE. Cela a �t� r�solu rapidemment... D�sol� pour ces versions
    cons�cutives � intervalles rapproch�s.

	-- Aucune nouvelle fonctionnalit� dans cette version
  
----------------------------------------------------------------------------------------------------
--- 7-28 version de d�bogage : ex�cutable seulement (source disponible sur demande) -------
----------------------------------------------------------------------------------------------------
1. La fen�tre des pr�f�rences a chang�. Elle propose de nouveaux r�glages et des liens vers des sites web
   importants concernant MUTE
2. Les utilisateurs peuvent d�sormais choisir leurs r�pertoires de partage, t�l�chargement et entrants.
   - Cela permet de partager des fichiers stock�s sur des supports en lecture seule comme des  CDs. 
   Cependant... pour le moment, les fichiers entrants ne seront pas transf�r�s apr�s ach�vement
   vers le r�pertoire des fichiers partag�s. (Cela sera r�solu dans une prochaine version apr�s que
   l'on m'aura donn� quelques id�es pour rem�dier � cela).
3. Nouveau bouton sur la fen�tre t�l�chargement pour parcourir le r�pertoire des fichiers entrants.

----------------------------------------------------------------------------------------------------
--- 7-24 version de d�bogage : ex�cutable seulement (source disponible sur demande) -------
----------------------------------------------------------------------------------------------------
1. R�glages du partage d�sormais possibles � partir de la fen�tre de pr�f�rences.
2. Bouton de purge du hachage sur la fen�tre de recherche.
3. En cas de t�l�chargement d�j� pr�sent et en cours, le m�me fichier ne peut plus �tre ajout� pour �tre t�l�charg�
   une deuxi�me fois.
4. R�solution du probl�me de la touche Alt-XXX dans la fen�tre de recherche de telle sorte qu'en appuyant sur 
   Alt-T lors d'une recherche cela sera r�ellement �quivalent � appuyer sur le bouton stop, tandis qu'avant cela ne
   fonctionnait pas.

----------------------------------------------------------------------------------------------------
--- 7-14 version de d�bogage : ex�cutable seulement (source disponible sur demande) -------
----------------------------------------------------------------------------------------------------
1. Fen�tre des pref�rences : nouveau bouton pour effacer les fichiers annul�s.
   Permet d'�viter la suppression des t�l�chargements annul�s/en echec du r�pertoire entrant de Mute.
2. Fen�tre des pref�rences : plus de message demandant de red�marrer le programme apr�s avoir enregistr� les pr�f�rences.
3. Fen�tre de recherche : nouvelle boite de filtre.
   Maintenant vous pouvez chercher sans avoir � �liminer les d�bris des recherches pr�c�dentes.
4. Fen�tre de t�l�chargement : maintenant il est possible reprendre le cours des t�l�chargements
5. Fen�tre de t�l�chargement : bouton pour purger le r�pertoire des fichiers entrants de Mute.
   Il n'est plus n�cessaire de l'ouvrir pour supprimer les fichiers -- vais peut-�tre faire de m�me pour le
   r�pertoire de hachage.

----------------------------------------------------------------------------------------------------
--- 6-15 version release: code source disponible -------
----------------------------------------------------------------------------------------------------
0. Icones en couleurs (Cela met un peu de piment dans la vie)
1. Le programme d�marre sur la fen�tre de connection
2. R�solution du bug �cran de connection invalide (en cas de saisie d'une mauvaise adresse IP)
3. Boite de liste avec possibilit� de tri et ent�tes d�pla�ables
4. Fen�tre de recherche avec fichiers color�es (selon le type...audio en rouge,vid�o en vert, documents en bleu,
   noir en cas de type inconnu)
5. Fen�tre de recherche : ajout d'icones syst�me et du type de fichier dans la boite de liste (quand disponible)
6. Fen�tre de recherche : toutes les colonnes supportent le tri et les ent�tes sont d�sormais mobiles
7. Fen�tre de recherche : menu contextuel proposant le t�l�chargement (click droit sur la souris)
8. Les fichiers ajout�s aux t�l�chargements sont surlign�es en jaune et marqu�s comme ajout�s aux t�l�chargements.
9. Fen�tre de recherche : possibilit� d'exporter les r�sultats dans un fichier utilisant la virgule comme d�limiteur
10. Fen�tre de recherche : bouton pour effacer les r�sultats de la recherche
11. Fen�tre de recherche : possibilit� de naviguer dans la liste de recherche avec les touches de d�placement et de selectionner
    les fichiers � t�l�charger en appuyant sur la touche entr�e.
12. Fen�tre de t�l�chargement : sur click droit menu contextuel : �ffac�, termin�, annul�, en attente, etc... 
13. Fen�tre de t�l�chargement : toutes les colonnes supportent le tri et les ent�tes sont d�sormais mobiles
14. Fen�tre de t�l�chargement : bouton pour parcourir les fichiers partag�s
15. Fen�tre de t�l�chargement : boutons pour effacement termin�, en attente et annulation...
16. Fen�tre de t�l�chargement : items color�s... bleu == termin�, rouge == en attente/�chec/en cours d'annulation/annul�,
    vert == t�l�chargement en cours
17. Fen�tre de partage : effacement des selections dans le  menu contextuel accessible par un click droit
18. Fen�tre de partage : toutes les colonnes supportent le tri et les ent�tes sont d�sormais mobiles
19. Fen�tre de partage : boutons pour retirer et effacer (efface seulement si termin� ou bloqu�) les partages en cours
    r�apparaitront lors de la prochaine requ�te de tron�on.
20. Fen�tre de partage : items color�s... bleu == termin�, rouge == en attente/�chec,vert == en cours
21. Info-bulles avec informations faciles � lire