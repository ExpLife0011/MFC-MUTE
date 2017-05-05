MFC MUTE VERSIONER....

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
--- version 0.0.6 -- 08-13-2005 release:------------------------------------------------------------
--- forklaring af fixes/tilf�jelser/�ndringer
----------------------------------------------------------------------------------------------------
1. Jason Rohrer's DROP TREE sikkerhedspatch er blevet integreret.
2. Om Mute side (under indstillinger) er blevet opdateret med 
http://www.sourceforge.net/projects/mfc-mute-net adressen.
3. Der er blevet lagt begr�nsning af antallet af resultater som 
kan modtages p� baggrund af wildcard s�gninger '*'. Antallet af 
resultater som kan modtages er bestemt af en tilf�ldighed funktion.
Dette er gjordt for at �ge sikkerheden og  reducere antallet 
af 'Network search attacks'.
4. Forbedret s�gefunktion. Desktop.ini og Thumbs.db filer vil ikke 
l�ngere blive vist som s�ge resultater, da der ikke er nogen fornuftig 
grund til at downloade dem.
5. Dynamiske faneblads ikoner. Nu er det mulig tilf�je egne faneblads-
ikoner. Kopier dine ikoner ned i 'icons'-mappen, filnavnene skal matche
underst�ende:
    icons\searchTab.ico
    icons\downloadsTab.ico
    icons\uploadsTab.ico
    icons\connectionsTab.ico
    icons\sharedfilesTab.ico
    icons\settingsTab.ico

6. Netv�rks traffik statistik p� relevate faneblade (Download, upload, 
forbindelser).


----------------------------------------------------------------------------------------------------
--- version 0.0.5 -- 03-04-2005 release:-----------------------------------------------------------------------
--- forklaring af fixes/tilf�jelser/�ndringer
----------------------------------------------------------------------------------------------------
1. Tilf�jet en farvet status-bar i bunden af GUI'en over forbindelse 
status.
2. Sat timer (over forl�ben tid) i caption-baren med formatet 
DAGE:TIMER:MINUTER:SEKUNDER.
3. Tilf�jet noget kode som holder styr p� download r�kkef�lgen af
hentede blokke. Dette �ger download hastigheden.

----------------------------------------------------------------------------------------------------
--- version 0.0.4 -- 02-24-2005 release:-----------------------------------------------------------------------
--- forklaring af fixes/tilf�jelser/�ndringer
----------------------------------------------------------------------------------------------------
1.  �ndret den gule tips tekst, som h�re til MUTE MFC, i proceslinien fra 
    "MFC_MUTE_0.3" til "MFC MUTE".
2.  Har ordnet 2 fejl i "Download k�"-koden.
    -1-->   Har ordet en fejl som opst�r n�r en download fra Downloadqueue.ini 
    genoptages. I ver. 0.0.3 blev ikke alle af downloads'ene genoptaget korrekt
    efter genstart, dette er nu rettet.
     -2-->  Fik rettet en fejl hvor en download i k�en blev genoptaget. Processen
     s�gte efter og fandt emnet, og fors�gte p� at begynde download
     ogs� selvom der allerede var 4 aktive downloads i gang fra denne VIP. 
     Da 4 er det max. antal downloads som m� v�re aktive fra en VIP, skal download's
     fors�get l�gges tilbage i k�'en. Fejlen var at selvom downloadet blive lagt
     tilbage i k�en, s� blev status teksten ved med at v�re den samme (forkerte).
3.  For�get semaphore timeout v�rdier i "Download-K�"-koden.
4.  Rettet den program-kode som tilf�jer downloads fra s�ge-vinduet. Fejlen var
    at program-koden tilf�jede downloads som allerede var valgt og at der derfor kom dubletter.
5.  I Download-vinduet kan valgte filer nu afbrydes/fjernes med DELETE tasten.
6.  For�get semaphore timeout v�rdier in "Download Dialog"-koden.
7.  Har tilf�jet 1 millisekunds hvile for at tage alt CPU kraften fra andre tr�de.
8.  I upload-vinduet kan valgte filer nu afbrydes/fjernes med DELETE tasten.
9.  Har rettet fejl I den program-kode som styre filblok-forsp�rgselernes timeout/retries. 
    Denne rettelse skulle forbedre netv�rksydelsen ved at begr�nse antallet af filblok-forsp�rgseler
    som genudsendes fordi der ikke er nok tid til at klienten kan n� at f� et svar.
10. Der er blevet rettet nogle fejl i den danske sprog pakke. (TOBIAS)


----------------------------------------------------------------------------------------------------
--- version 0.0.3 -- 01-09-2005 release:-----------------------------------------------------------------------
--- forklaring af fixes/tilf�jelser/�ndringer
----------------------------------------------------------------------------------------------------
1.  Har tilf�jet nye Ikoner og �ndret nogen af de gamle (tak til --NGLWARCRY--).
2.  Har opgraderet projekt filer, s� det bliver nemmere at kompile under Visual Studio .NET.
3.  Tilf�jet noget kode som saver host IP adresser i seedhost.ini filen n�r Mute lukkes 
    ned (Tak til --Nate--/TSAFA).
4.  Fixer Status sorteringen in download dialog sk�rmen.
5.  Har tilf�jen en funktion, s� man ,ved at h�jre klikke p� et i downloads sk�rmen, kan bestemme 
    hvilket emne i download-k�en man vil downloade n�ste gang (tak til --Tony--).
6.  Har �get tiden mellem s�gningerne for automatiske download for at ung� overbelastning af netv�rket
7.  Tilrettet download-k�-koden s� hver gang en fil blive afbrudt eller f�rdig downloadet, s� opdateres
    indholdet af Downloadqueue.ini filen. Dette forbedre download-k�-funktionen i tilf�lde af et crash
    eller en hurtig afslutning af programmet.
8.  En bruger kan nu dobbelt-klikke (eller trykke p� download-knappen) p� en fil i s�ge-vinduet for at
    starte en download. Hvis downloaden g�r i st� eller programet lukkes kan man s�ge efter filen og
    klikke p� den igen for at genstarte download processen (tak til --Tony--).
9.  Der er blevet tilf�jet et Delte Filer fag. Her kan man se filen samt HASH-data for filen. Her ud 
    over kan du eksporter listen til en koma delt fil til ekstren brug. 
10. Brugerne kan nu formindste GUI til en mindre st�rrelse med resizer-gripbar. (tak til --Tony--)
11. Der er blevet lavet nogle �ndringer af kernen samt blevet rettet nogle bugs i kernen. Disse kommer
    fra Jason Rohrer's MUTE-0.4 core code.
    -- Host Catcher fixes
    -- Time fixes
    -- Inbound/Outbound Channel fixes
    -- StringBufferOutputStream fixes
    -- crytpo++ compiler related fixes
    -- ChannelReceivingThreadManager fixes
    -- ConnectionMaintainer fixes
    -- Log rollover fixes
    -- formatUtils.cpp fix (added -GiB code)
12. Koden som tager sig af netforbindelsen time out/dropping er blevet �ndret (tak til --Nate--)
13. S� er der blevet lavet betydelige forbedringer af routing koden. (Mange tak til --Nate--)
14. Der er blevet tilf�jet kode som forhindre duplet blokke i at overs�mme netv�rket. Dette har
    tidligere v�ret et problem.
15. Har tilf�jet en cache mekanisme til Search Result sending kode som dramatisk redukser 
    programmets CPU belastning. Tidligere versioner gens�gte mappen Delte Filer hver gang der kom
    og en foresp�rgsel og lavede hver gang en ny list af mappen. Den nye version laver periodiske
    s�gninger og gemmer resultatet i en cache som indeholder filnavn, filhash, and filest�rrelse.
    Ved program opstart opdateres cachen ved f�rste s�ge foresp�rgsel. Herefter opdateres cachen
    hver 10 minut, der ligges dog 50 sekunder til denne periode for hvert gang en s�geforesp�rgsel
    lykkes, Dog max. 30 minuter. Dette giver ikke bare en forbedret CPU udnyttelse, men ogs� en
    bedre udnyttelse af netv�rket fordi der s� er mere CPU kraft til at tage sig af netv�rks fore-
    sp�rgsler.
16. For�get hash genereringstid  -- Dette betyder programmet giver mere tid til at unders�ge 
    Delte Filer mappen for filer som ikke har f�et lavet hash-data, lave disse hash-data. Dette for
    programmet til at bruge mindre CPU kraft.   
17. Upload sk�rmen vil automatisk blive t�mt efter 100 uploads. Dette s�ge for at der ikke bliver 
    brugt s� meget ram og at programmet vil blive afviklet hurtigere fordi der ikke skal bruges 
    resurser p� opdatering af Uploadlisten.
18. Program vinduets position vil nu v�re den samme ved opstart som den var da det blev lukket 
    sidst. N�r programmet lukkes gemmes positions data i filen "mfcWindowPlacement.ini". Filen er
    koma delt og indeholder 5 integer v�rdier. Formatet er:
    
    field 1:    0 == show window in tray
                1 == show window normal
    field 2: x coordinate top left of window
    field 3: y coordinate top left of window
    field 4: x coordinate bottom right of window
    field 5: y coordinate bottom right of window
19. Tilf�jet fuktioner : Visning af antal uploads og statistik over m�ngden af blokke hver enkelt
    upload har sendt.