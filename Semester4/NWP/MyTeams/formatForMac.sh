#!/bin/zsh

# Remove uuid library linking to make it work with MacOS
if [ ! -z $1 ]
then
    if [ $1 = "apple" ]
    then
        find ./src/server/ -type f -name "CMakeLists*.txt" -exec sed -i '' 's/myteams_common uuid/myteams_common/g' {} \;
        find ./src/client/ -type f -name "CMakeLists*.txt" -exec sed -i '' 's/myteams_common uuid/myteams_common/g' {} \;
        find ./src/server/packet_handlers/ -type f -name "login.c" -exec sed -i '' 's/server_event_user_created(unparsed, name);/\/\/server_event_user_created(unparsed, name);/g' {} \;
        exit 0
    fi
fi
find ./src/server/ -type f -name "CMakeLists*.txt" -exec sed -i '' 's/myteams_common/myteams_common uuid/g' {} \;
find ./src/client/ -type f -name "CMakeLists*.txt" -exec sed -i '' 's/myteams_common/myteams_common uuid/g' {} \;
find ./src/server/packet_handlers/ -type f -name "login.c" -exec sed -i '' 's/\/\/server_event_user_created(unparsed, name);/server_event_user_created(unparsed, name);/g' {} \;
