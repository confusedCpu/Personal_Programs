# This script is designed to automate the setup process for new machines. 
# It will change the hostname, join a domain, and run the required installers
# UPDATED: 07/18/17

# [ namespace ] 

[System.Reflection.Assembly]::LoadWithPartialName('Microsoft.VisualBasic') | Out-Null

# [ global variables ] 

$LOG = "c:\SETUP_LOG.txt"

$INSTALLERS = "c:\Installers"

$NAME = (Get-WmiObject Win32_ComputerSystem).Name
$DOMAIN_NAME = "Some.Domain"

# [ functions ] 

function changeHostname { 	# Promts the user for a host name then restarts the machine to set the change

        $HOST_INFO = Get-WmiObject Win32_ComputerSystem 		# Stores current computer information
	$HOST_OLD = $HOST_INFO.Name
        $HOST_NEW = [Microsoft.VisualBasic.Interaction]::InputBox("Enter Desired Computer Name ") 	# prompts the user for a new name
        $HOST_INFO.Rename( $HOST_NEW ) | Out-Null 	# changes the hostname of the device

	log "Host name ( ${HOST_OLD} ) changed to ( ${HOST_NEW} )" 

	$RESPONSE = [Microsoft.VisualBasic.Interaction]::InputBox("Do you want to restart now? [y/n]")

	if ( ( $RESPONSE -eq 'y' ) -or ( $RESPONSE -eq 'Y' ) ) {
        	shutdown /r /t 0 /c "Shutting down to change the hostname."
		}
}


function log( $EVENT ) { 	# Timestamps and records and event to a specified log file

	if ( ! $EVENT ) { echo "$(Get-Date -Format d)" >> $LOG }
	else { echo  "`t$(Get-Date -Format t)  ->  ${EVENT}" >> $LOG }
}


function joinDomain { 	# Joins the domain

	while ( -not ( (Get-WmiObject Win32_ComputerSystem).Domain -eq $DOMAIN_NAME ) ) {
                Add-Computer -DomainName $DOMAIN_NAME 	# prompts for domain admin creds, then joins the domain
                }

        log "Hostname ( ${HOST_NAME} ) has been joined to ( ${DOMAIN_NAME} )"
}


function operations_prompt { 	# determines the operations to run

	# 0. Resize
	# 1. Change Hostname
	# 2. Join Domain
	# 3. Run Installers

	$EXIT = 'false'
	$OPT = '1. Resize the disk', '2. Change the hostname', '3. Join the domain', '4. Run the installers', '5. View Log', '6. Exit'

	do { 
		echo $OPT
		$RESPONSE = Read-Host 'Press the number that corralates'

		switch ( $RESPONSE ) {
			'1'	{ log "Resizing the disk."; resizeDisk }
			'2'	{ log "Changing the hostname"; changeHostname }
			'3'	{ log "Joining the domain"; joinDomain }
			'4'	{ log  "Runing installer group"; runInstallers "$INSTALLERS" }
			'5'	{ viewLog }
			'6'	{ log  "***Script exiting***"; $EXIT = 'true' }
			Default	{ echo "Invalid Response! ( ${RESPONSE} )`n`n" }
		}
	} until ( $EXIT -eq 'true' ) 
}


function resizeDisk { 	# Resizes the disk

	$MAX_SIZE = (Get-PartitionSupportedSize -DriveLetter c).sizeMax 	# determine the free space on the disk
    	Resize-Partition -DriveLetter c -Size $MAX_SIZE 	# extends root to the max size available

    	log "Partition resized to the maximum available ( ${MAX_SIZE} )" 
}


function runInstallers ( $INSTALL_DIR ) { 	# locate installers in the given dir then executes them

	$CMD = dir $INSTALL_DIR | Select-String -Pattern '*.CMD$', '*.bat' 	# search for .cmd and .bat files to exec
	log ".CMD + .bat files found ($(@(CMD.length)): `n ${CMD}" 
	for ( $i = 0; $i -lt $CMD.length; $i++ ) {
		&( $INTSALL_DIR + $CMD[$i] ) 
		log "${CMD[$i]} ran" 
	}

	$MSI = dir $INSTALL_DIR | Select-String -Pattern '*.msi$' 	# search for .msi files to exec
	for ( $i = 0; $i -lt $MSI.length; $i++ ) {
		&( $INSTALL_DIR + $MSI[$i] + " /qn") 	
		log "${MSI[$i]} installed" 
	}

	$EXE = dir $INSTALL_DIR | Select-String -Pattern '*.exe$' 	# search for .exe files to exec
	for ( $i = 0; $i -lt $EXE.length; $i++ ) {
		&( $INSTALL_DIR + $EXE[$i] )
		log "${EXE[$i]} installed"
	}
}


function viewLog { cat "${LOG}" | out-host -paging }


# [ main ] 

log
operations_prompt

echo "`n`nLog can be found at ${LOG}"

exit
