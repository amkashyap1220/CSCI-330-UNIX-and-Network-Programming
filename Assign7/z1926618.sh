#
# Alexander Kashyap
# z1926618
# CSCI 330 section 1
# Due 3/5/21
#

#!/bin/bash

new () {
    printf "%s\n" "$2" > $1 
}

insert () {
    printf "%s, %s, %s, %s\n" "$2" "$3" "$4" "$5" >> $1
}

display () {
    if [ $2 = "all" ]; then
        cat $1
    elif [ $2 = "single" ]; then
        sed -n $(($3 + 1))p $1
    elif [ $2 = "range" ]; then
        sed -n $(($3 + 1)),$(($4 + 1))p $1
    else
        printf "specify 1 of: all, single #, or range # #\n"
    fi
}

delete () {
    if [ $2 = "all" ]; then
        sed -i '' '1!d' $1
    elif [ $2 = "single" ]; then
        sed -i '' $(($3 + 1))d $1
    elif [ $2 = "range" ]; then
        sed -i '' $(($3 + 1)),$(($4 + 1))d $1
    else
        printf "specify 1 of: all, single #, or range # #\n"
    fi
}

# First check if in interactive mode
if [ ! $# = 0 ]; then # not interative 
    if [ $2 = "new" ]; then # new
        if [ $# = 2 ]; then
            # if no name specified
            new "$1" "Untitled Database"
        else
            new "$1" "$3"
        fi
    elif [ $2 = "insert" ]; then # insert
        if [ $# = 6 ]; then
            insert "$1" "$3" "$4" "$5" "$6"
        else
            # error if they dont specify all parts
            printf "Insert requires 5 parameters.\n"
        fi
    elif [ $2 = "display" ]; then # display
        display $1 $3 $4 $5
    elif [ $2 = "delete" ]; then # delete
        delete $1 $3 $4 $5
    else
        printf "Use new, insert, display, or delete. Not: %s\n" "$2"
    fi
else # interactive
    echo "hi"
fi





