#!/bin/bash

## This file updates or populates the config files from the github repo of the local user
#
## Future updates should include back ups of the most recent files before copy and testing for differences before a senseless copy

REPO_DESTINATION='$HOME/Src/Personal_Configs'
# Clone repo if not already present
if ! [[ -f $REPO_DESTINATION ]]; then
	git pull https://github.com/confusedCpu/Personal_Configs.git $HOME/Src/
	echo "Personal_Configs repository cloned to $REPO_DESTINATION"
else
	# update the repository
	cd $REPO_DESTINATION
	git pull
fi

# Copy all dot files to ~/ 
cp -ruv <(ls | grep -e [[^".git"]]) $HOME/
echo All \'.\' files have been pushed to $HOME.

# Dump every thing else into ~/.config
cp -r <(ls | egrep -E [[:alpha:]]) $HOME/.config/
echo Everything else is in $HOME/.config.

echo Done.

