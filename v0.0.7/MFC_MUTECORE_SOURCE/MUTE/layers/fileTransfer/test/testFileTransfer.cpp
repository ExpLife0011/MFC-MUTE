/*
 * Modification History
 *
 * 2003-September-4   Jason Rohrer
 * Created.
 *
 * 2003-September-5   Jason Rohrer
 * Improved progress dot display.
 *
 * 2003-September-22   Jason Rohrer
 * Added timing code for file transfers.
 *
 * 2003-November-11   Jason Rohrer
 * Added b flag to fopen of binary files.
 */



#include "MUTE/layers/messageRouting/messageRouter.h"

#include "MUTE/layers/pointToPoint/pointToPointCommunicator.h"

#include "MUTE/layers/fileTransfer/fileTransmitter.h"



#include "minorGems/util/SettingsManager.h"
#include "minorGems/util/SimpleVector.h"
#include "minorGems/util/stringUtils.h"

#include "minorGems/util/printUtils.h"
#include "minorGems/io/file/File.h"
#include "minorGems/io/file/Path.h"
#include "minorGems/system/Time.h"

#include <stdio.h>



char *readUserString( char *inPrompt ) {

    int numRead = 0;

    char *buffer = new char[1000];
    
    while( numRead != 1 ) {
        printf( inPrompt );
        fflush( stdout );
        
        numRead = scanf( "%999s", buffer );
        }
    return buffer;
    }



char *readUserLine( char *inPrompt ) {
    printf( inPrompt );
    fflush( stdout );
    
    SimpleVector<char> *readChars = new SimpleVector<char>();


    
    int readInt = getc( stdin );

    // first, skip starting newlines
    while( readInt == '\n' || readInt == '\r' ) {
        readInt = getc( stdin );
        }
    
    while( readInt != '\n' && readInt != '\r' && readInt != EOF ) {
        readChars->push_back( (char)readInt );

        readInt = getc( stdin );
        }

    char *readLine = readChars->getElementString();

    delete readChars;

    return readLine;
    }



int readUserInt( char *inPrompt ) {

    int readInt;
    int numRead = 0;
    
    while( numRead != 1 ) {
        printf( inPrompt );
        fflush( stdout );
        
        numRead = scanf( "%d", &readInt );
        }
    return readInt;
    }



// callback for incoming files
void fileHandler( unsigned char *inChunk,
                  int inChunkLengthInBytes,
                  void *inExtraParam ) {

    // extra param is file stream
    FILE *outputFile = (FILE *)inExtraParam;


    fwrite( inChunk, 1, inChunkLengthInBytes, outputFile );

    printf( "." );
    fflush( stdout );    
    }



int main() {

    char *randomSeed = SettingsManager::getStringSetting( "randomSeed" );

    if( randomSeed == NULL ) {
        randomSeed = readUserString( "Enter some randomness: " );
        }
    else {
        printf( "Using randomness saved from last time\n" );
        }

    muteSeedRandomGenerator( randomSeed );
    delete [] randomSeed;


    char valueFound;

    int portNumber = SettingsManager::getIntSetting( "port", &valueFound );

    if( ! valueFound ) {

        portNumber = readUserInt( "Enter port number to listen on: " );

        SettingsManager::setSetting( "port", portNumber );
        }


    char *localName = SettingsManager::getStringSetting( "localContactName" );

    if( localName == NULL ) {
        localName = readUserString( "Enter nickname: " );

        int keyLength =
            readUserInt( "Enter key size [512, 1024, 1536, 2048, 4096]: " );

        printf( "Generating %d-bit RSA key pair...\n", keyLength ); 
        muteGenerateLocalContactInformation( localName, keyLength );

        printf( "...done\n" );
        }
    else {
        printf( "Using keys for local nickname \"%s\"\n", localName ); 
        }

    delete [] localName;

    
    printf( "Listening for connections on port %d\n", portNumber );
    muteStart( portNumber );
        
    mutePointToPointStart();

    muteFileTransferStart();
    
    
    char quitting = false;
    char *readCharBuffer = new char[2];
    // print the prompt 
    printf( "> " );
    fflush( stdout );

    while( !quitting ) {


        scanf( "%1s", readCharBuffer );

        switch( readCharBuffer[0] ) {
            case '?':
                printf( "Commands:\n" );
                printf( "? -- print this help message\n" );
                printf( "p -- print contact list\n" );
                printf( "f -- list a contact's files\n" );
                printf( "d -- download a file\n" );

                printf( "l -- lookup contact info for virtual address\n" );

                printf( "i -- push our contact info to a contact\n" );
                printf( "u -- print list of unknown contacts waiting "
                        "for approval\n" ); 
                printf( "a -- approve an unknown contact\n" );
                printf( "t -- toggle unknown contact auto-approve " );

                if( muteGetUnknownContactAutoApprove() ) {
                    printf( "[currently on]\n" );
                    }
                else {
                    printf( "[currently off]\n" );
                    }
                
                printf( "q -- quit\n" );
                break;
            case 'p':
            case 'P': {
                int contactCount;
                char **contactList = muteGetContactList( &contactCount );
                if( contactCount > 0 ) {
                    printf( "Contacts:\n" );
                    for( int i=0; i<contactCount; i++ ) {
                        // check if online
                        unsigned long seconds;
                        unsigned long ms;
                        Time::getCurrentTime( &seconds, &ms );
                        
                        char online = mutePingContact( contactList[i] );

                        unsigned long deltaMS
                            = Time::getMillisecondsSince( seconds, ms );
                        
                        if( online ) {
                            printf( "[online, ping: %d]  ", (int)deltaMS );
                            }
                        else {
                                printf( "[offline] " );
                            }
                        
                        printf( "%s\n", contactList[i] );
                        delete [] contactList[i];
                            }
                    }
                else {
                    printf(
                        "No contacts.\n"
                        "Add contact (.mc) files to "
                        "your \"contacts\" folder\n" );
                    }
                delete [] contactList;
                break;
                }
            case 'u':
            case 'U': {
                int contactCount;
                char **contactList =
                    muteGetUnknownContactList( &contactCount );
                if( contactCount > 0 ) {
                    printf( "Unknown contacts (waiting for approval):\n" );
                    for( int i=0; i<contactCount; i++ ) {
                        
                        printf( "%s\n", contactList[i] );
                        delete [] contactList[i];
                        }
                    }
                    else {
                        printf( "No unknown contacts.\n" );
                        }
                delete [] contactList;
                break;
                }
            case 'a':
            case 'A': {
                char *contactName = readUserString( "Enter contact name: " );

                char approved = muteApproveUnknownContact( contactName );

                if( approved ) {
                    printf( "%s added to contact list\n",
                            contactName );
                    }
                else {
                    printf( "Failed to approve %s\n",
                            contactName );
                    }
                delete [] contactName;
                break;
                }
            case 'i':
            case 'I': {
                char *contactName = readUserString( "Enter contact name: " );

                char sent = mutePushLocalContactInfoToContact( contactName );

                if( ! sent ) {
                    printf( "Failed to sent our contact info to %s\n",
                            contactName );
                    }
                delete [] contactName;
                break;
                }
            case 't':
            case 'T': {

                char oldValue = muteGetUnknownContactAutoApprove();

                muteSetUnknownContactAutoApprove( !oldValue );

                char newValue = muteGetUnknownContactAutoApprove();
                
                printf( "Auto-approve is " );

                if( newValue ) {
                    printf( "on\n" );
                    }
                else {
                    printf( "off\n" );
                    }
                break;
                }
            case 'f':
            case 'F': {
                char* name = readUserString( "Enter contact name: " );

                printf( "Fetching folder listing...\n" );
                int numEntries;
                char **dirList = muteGetDirectoryListing( name,
                                                          "/",
                                                          &numEntries );

                if( dirList == NULL ) {
                    printf( "failed to fetch list\n" );
                    }
                else {
                    printf( "List:\n" );

                    for( int i=0; i<numEntries; i++ ) {
                        printf( "%s\n", dirList[i] );
                        delete [] dirList[i];
                        }
                    delete [] dirList;
                    if( numEntries == 0 ) {
                        printf( "[empty folder]\n" );
                        }
                    }
                
                delete [] name;
                break;
                }
            case 'd':
            case 'D': {
                char* name = readUserString( "Enter contact name: " );
                char* fileName = readUserString( "Enter file name: " );

                printf( "Fetching file into \"files\" folder...\n" );

                Path *filesPath = new Path( "files" );
                File *file = new File( filesPath, fileName );
                char *fullFileName = file->getFullFileName();
                
                
                FILE *outputFile = fopen( fullFileName, "wb" );

                if( outputFile == NULL ) {
                    printf( "Failed to open file %s for writing\n",
                            fullFileName );
                    }
                else {
                    unsigned long seconds;
                    unsigned long ms;
                    Time::getCurrentTime( &seconds, &ms );
                    
                    
                    char fetched = muteGetFile( name, fileName,
                                                fileHandler,
                                                (void *)outputFile );

                    unsigned long deltaMS
                        = Time::getMillisecondsSince( seconds, ms );
                    
                    fclose( outputFile );

                    if( fetched ) {
                        printf( "\nFile transfer complete in %d ms\n",
                                (int)deltaMS );
                        }
                    else {
                        printf( "\nFile transfer failed\n" );

                        if( file->exists() ) {
                            // remove partial file
                            file->remove();
                            }
                        }
                    
                    }

                delete file;
                delete [] fullFileName;
                delete [] fileName;
                delete [] name;
                break;
                }
            case 'l':
            case 'L': {
                char *address = readUserString( "Enter virtual address: " );
                printf( "Fetching contact information...\n" );
                char *contactName =
                    muteFetchContactInfoForVirtualAddress( address );
                delete [] address;
                if( contactName != NULL ) {
                    printf(
                        "Found contact: %s\n"
                        "Contact information saved into contacts directory\n",
                        contactName );
                    delete [] contactName;
                    }
                else {
                    printf(
                        "Failed to fetch contact info (contact offline?)\n" );
                    }
                break;
                }
            case 'q':
            case 'Q':
                quitting = true;
                break;
            default:
                printf( "Unknown command: %c\n", readCharBuffer[0] );
                break;
            }

        // print the next prompt 
        printf( "> " );
        fflush( stdout );
        }
    delete [] readCharBuffer;

    threadPrintF( "Qutting...\n" );



    
    threadPrintF( "Stopping file transfer layer\n" );
    muteFileTransferStop();


    threadPrintF( "Stopping point-to-point communications layer\n" );
    mutePointToPointStop();
    

    threadPrintF( "Saving randomness for use at next startup\n" );
    char *randState = muteGetRandomGeneratorState();

    SettingsManager::setSetting( "randomSeed", randState );
    delete [] randState;


    threadPrintF( "Stopping message routing layer\n" );
    muteStop();

    threadPrintF( "All layers are stopped, exiting.\n" );
    }
