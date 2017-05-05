#!/usr/bin/perl -wT


#
# Modification History
#
# 2004-January-9   Jason Rohrer
# Created.
# Copied from DHB P2P fund.
# Made separate directories for public/private data.
# Fixed custom field.
# Fixed refund bug.
#
# 2004-February-26   Jason Rohrer
# Changed to format dollar amounts with two decimal places.
#
# 2004-March-7   Jason Rohrer
# Changed to match new IPN refund format.
#
# 2004-May-25   Jason Rohrer
# Fixed a bug and abstracted the allowed custom field as a setting.
# Fixed bug in dealing with new IPN refunds.
#


# This script must have write permissions to its dataDirectory
# it must be able to create files in this directory
# On most web servers, this means the directory must be world-writable.
my $pubDataDirectory = "../htdocs/donationData";
my $privDataDirectory = "../cgi-data/donationTracker";

# If this $privDataDirectory setting is changed, you must also change it below
# where the error LOG is opened



# setup a local error log
use CGI::Carp qw( carpout );
BEGIN {
    use CGI::Carp qw( carpout );
    open( LOG, ">>../cgi-data/donationTracker/errors.log" ) or
        die( "Unable to open errors.log: $!\n" );
    carpout( LOG );
}


use strict;
use CGI;                # Object-Oriented CGI library





# script settings


# the custom field that we pass through paypal to ensure that we are
# getting IPN from the right donate button
my $allowCustomField = "MUTE_donate";

my $donationFormURL =           "http://mute-net.sf.net";
my $scriptURL =   "http://mute-net.sf.net/cgi-bin/donationTracker.pl";
my $scriptFileName = "donationTracker.pl";
my $donationLogFile = "$privDataDirectory/donationLog.txt";


my $overallSumFile =            "$pubDataDirectory/overallSum.html";
my $donationCountFile =         "$pubDataDirectory/donationCount.html";

# where non-fatal errors and other information is logged
my $logFile =                   "$privDataDirectory/log.txt";



# IP of notify.paypal.com
# my $paypalNotifyIP =           "65.206.229.140";   
# New IP as of October 23, 2003
# my $paypalNotifyIP =           "64.4.241.140";
# New IP as of June 11, 2004 
my $paypalNotifyIP =           "216.113.188.202";

# end of script settings




# setup stuff, make sure our needed files are initialized
if( not doesFileExist( $overallSumFile ) ) {
    writeFile( $overallSumFile, "0" );
}
if( not doesFileExist( $donationCountFile ) ) {
    writeFile( $donationCountFile, "0" );
}





# create object to extract the CGI query elements

my $cgiQuery = CGI->new();


# always at least send an HTTP OK header
print $cgiQuery->header( -type=>'text/html', -expires=>'now',
                         -Cache_control=>'no-cache' );

my $remoteAddress = $cgiQuery->remote_host();



my $action = $cgiQuery->param( "action" ) || '';

if( $action eq "showSource" ) {
    # print the sourcecode for our script
    print "<PRE>";

    my $source = readFileValue( $scriptFileName );
    
    # replace any &'s in code with &amp;
    $source =~ s/&/&amp;/g;
    # replace HTML brackets with &lt; and &gt; 
    $source =~ s/</&lt;/g;
    $source =~ s/>/&gt;/g;

    print $source;

    print "</PRE>\n";
}
# make sure the request is coming from paypal
elsif( $remoteAddress eq $paypalNotifyIP ) {
    
    my $donorName;


    # was this paypal payment generated by us?
    my $customField = $cgiQuery->param( "custom" ) || '';
    if( $customField eq $allowCustomField ) {
        
        my $amount = $cgiQuery->param( "mc_gross" ) || '';
        
        my $currency = $cgiQuery->param( "mc_currency" ) || '';
        
        my $fee = $cgiQuery->param( "mc_fee" ) || '0';
        
        my $date = $cgiQuery->param( "payment_date" ) || '';
        
        my $transactionID = $cgiQuery->param( "txn_id" ) || '';


        # these are for our private log only, for tech support, etc.
        # this information should not be stored in a web-accessible
        # directory
        my $payerFirstName = $cgiQuery->param( "first_name" ) || '';
        my $payerLastName = $cgiQuery->param( "last_name" ) || '';
        my $payerEmail = $cgiQuery->param( "payer_email" ) || '';
            

        # only track US Dollars 
        # (can't add apples to oranges to get a final sum)
        if( $currency eq "USD" ) {

                my $status = $cgiQuery->param( "payment_status" ) || '';
                
                my $completed = $status eq "Completed";
                my $pending = $status eq "Pending";
                my $refunded = $status eq "Refunded";

                if( $completed or $pending or $refunded ) {
                    
                    # write all relevant payment info into our private log
                    addToFile( $donationLogFile,
                               "$transactionID  $date\n" . 
                               "From: $payerFirstName $payerLastName " .
                               "($payerEmail)\n" .
                               "Amount: \$$amount\n" .
                               "Fee: \$$fee\n" .
                               "Status: $status\n\n" );                    
                
                        
                    if( $refunded ) {
                        # subtract from total sum
                        
                        my $oldSum = 
                            readTrimmedFileValue( $overallSumFile );

                        # both the refund amount and the
                        # fee on the refund are now reported as negative
                        # this changed as of February 13, 2004
                        my $newSum = $oldSum + $amount - $fee;
                        
                        # format to show 2 decimal places
                        my $newSumString = sprintf( "%.2f", $newSum );

                        writeFile( $overallSumFile, $newSumString );
                        
                        
                        my $oldCount = readTrimmedFileValue( 
                                            $donationCountFile );
                        my $newCount = $oldCount - 1;
                        writeFile( $donationCountFile, 
                                   $newCount );
                              
                    }
                    
                    # This case no longer needed as of February 13, 2004
                    # since now only one IPN is sent for a refund.
                    #  
                    # ignore negative completed transactions, since
                    # they are reported for each refund (in addition to 
                    # the payment with Status: Refunded)
                    if( $completed and $amount > 0 ) {
                        # fee has not been subtracted yet
                        # (fee is not reported for Pending transactions)
                        
                        my $oldSum = 
                            readTrimmedFileValue( $overallSumFile );
                        my $newSum = $oldSum + $amount - $fee;
                        
                        # format to show 2 decimal places
                        my $newSumString = sprintf( "%.2f", $newSum );
                        
                        writeFile( $overallSumFile, $newSumString );
                        
                        my $oldCount = readTrimmedFileValue( 
                                                   $donationCountFile );
                        my $newCount = $oldCount + 1;
                        writeFile( $donationCountFile, 
                                   $newCount );
                    }
                }
                else {
                    addToFile( $logFile, "Payment status unexpected\n" );
                    addToFile( $logFile, "status = $status\n" );
                }
            }
        else {
            addToFile( $logFile, "Currency not USD\n" );
            addToFile( $logFile, "currency = $currency\n" );
        }
    }
    else {
        addToFile( $logFile, "Custom field does not contain our tag\n" );
        addToFile( $logFile, "custom = $customField\n" );
    }
}
else {
    # else not from paypal, so it might be a user accessing the script
    # URL directly for some reason

    # make sure we're not getting IPN from another address
    my $customField = $cgiQuery->param( "custom" ) || '';
    if( $customField eq $allowCustomField ) {

        my $date = $cgiQuery->param( "payment_date" ) || '';
        my $transactionID = $cgiQuery->param( "txn_id" ) || '';
        my $amount = $cgiQuery->param( "mc_gross" ) || '';
        
        my $payerFirstName = $cgiQuery->param( "first_name" ) || '';
        my $payerLastName = $cgiQuery->param( "last_name" ) || '';
        my $payerEmail = $cgiQuery->param( "payer_email" ) || '';


        my $fee = $cgiQuery->param( "mc_fee" ) || '0';
        my $status = $cgiQuery->param( "payment_status" ) || '';

        # log it
        addToFile( $donationLogFile,
                   "WARNING:  got IPN from unexpected IP address\n" .
                   "IP address:  $remoteAddress\n" .
                   "$transactionID  $date\n" . 
                   "From: $payerFirstName $payerLastName " .
                   "($payerEmail)\n" .
                   "Amount: \$$amount\n" .
                   "Fee: \$$fee\n" .
                   "Status: $status\n\n" );
    }

    # Redirect to the donation form page
    print 
        "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=$donationFormURL\">\n";
}




##
# Reads file as a string.
#
# @param0 the name of the file.
#
# @return the file contents as a string.
#
# Example:
# my $value = readFileValue( "myFile.txt" );
##
sub readFileValue {
    my $fileName = $_[0];
    open( FILE, "$fileName" ) 
        or die( "Failed to open file $fileName: $!\n" );
    flock( FILE, 1 ) 
        or die( "Failed to lock file $fileName: $!\n" );

    my @lineList = <FILE>;

    my $value = join( "", @lineList );

    close FILE;
 
    return $value;
}



##
# Reads file as a string, trimming leading and trailing whitespace off.
#
# @param0 the name of the file.
#
# @return the trimmed file contents as a string.
#
# Example:
# my $value = readFileValue( "myFile.txt" );
##
sub readTrimmedFileValue {
    my $returnString = readFileValue( $_[0] );
    trimWhitespace( $returnString );

    return $returnString;
}



##
# Writes a string to a file.
#
# @param0 the name of the file.
# @param1 the string to print.
#
# Example:
# writeFile( "myFile.txt", "the new contents of this file" );
##
sub writeFile {
    my $fileName = $_[0];
    my $stringToPrint = $_[1];
    
    open( FILE, ">$fileName" ) 
        or die( "Failed to open file $fileName: $!\n" );
    flock( FILE, 2 ) 
        or die( "Failed to lock file $fileName: $!\n" );

    print FILE $stringToPrint;
        
    close FILE;
}



##
# Checks if a file exists in the filesystem.
#
# @param0 the name of the file.
#
# @return 1 if it exists, and 0 otherwise.
#
# Example:
# $exists = doesFileExist( "myFile.txt" );
##
sub doesFileExist {
    my $fileName = $_[0];
    if( -e $fileName ) {
        return 1;
    }
    else {
        return 0;
    }
}



##
# Trims any whitespace from the beginning and end of a string.
#
# @param0 the string to trim.
##
sub trimWhitespace {   
    
    # trim from front of string
    $_[0] =~ s/^\s+//;

    # trim from end of string
    $_[0] =~ s/\s+$//;
}



##
# Appends a string to a file.
#
# @param0 the name of the file.
# @param1 the string to append.
#
# Example:
# addToFile( "myFile.txt", "the new contents of this file" );
##
sub addToFile {
    my $fileName = $_[0];
    my $stringToPrint = $_[1];
        
    open( FILE, ">>$fileName" ) 
        or die( "Failed to open file $fileName: $!\n" );
    flock( FILE, 2 ) 
        or die( "Failed to lock file $fileName: $!\n" );
        
    print FILE $stringToPrint;
        
    close FILE;
}



##
# Makes a directory file.
#
# @param0 the name of the directory.
# @param1 the octal permission mask.
#
# Example:
# makeDirectory( "myDir", oct( "0777" ) );
##
sub makeDirectory {
    my $fileName = $_[0];
    my $permissionMask = $_[1];
    
    mkdir( $fileName, $permissionMask );
}
