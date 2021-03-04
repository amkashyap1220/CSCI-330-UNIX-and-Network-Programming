#
# Alexander Kashyap
# z1926618
# CSCI 330 section 1
# Due 3/5/21
#

#!/bin/bash

# create a new database file
new() {
    printf "%s\n" "$2" > "$1"
    printf "New Database created\n"
}

# add a record to an existing database file
insert() {
    # Check to see if the arguments are all value before appending to database
    if [[ "$4" -gt 1921 && "$4" -lt 2029 ]]; then
        if [[ ! -z "$2" && ! -z "$3" && ! -z "$5" ]]; then
            printf "%s, %s, %s, %s\n" "$2" "$3" "$4" "$5" >> "$1"
            printf "Successfully added a record to the database\n"

        else
            printf "ERROR: The make, model, and color must be strings with length >0\n"
            exit 1

        fi

    else
        printf "ERROR: The year of the car must be >1921 and <2029\n"
        exit 1

    fi

}

# show record(s) found in an existing database
display() {
    # check if they dont specify
    if [ $# = 1 ]; then
        printf "ERROR: specify all, single #, or range # #\n"
        exit 1

    fi

    # check against all, single, and range and cat or sed depepending on which
    if [ "$2" = "all" ]; then
        cat "$1"

    elif [ "$2" = "single" ]; then
        sed -n $(($3 + 1))p "$1"

    elif [ "$2" = "range" ]; then
        sed -n $(($3 + 1)),$(($4 + 1))p "$1"
        printf "\n"

    else
        # Catching error if they dont input correct
        printf "ERROR: invalid display argument: %s\n" "$2"
        exit 1

    fi

}

# delete records from an existing database.
delete() {
    # check if they dont specify
    if [ $# = 1 ]; then
        printf "ERROR: specify all, single #, or range # #\n"
        exit 1

    fi

    # check against all, single, and range and sed to delete lines
    if [ "$2" = "all" ]; then
        sed -i '' '1!d' "$1"
        printf "All records deleted\n"

    elif [ "$2" = "single" ]; then
        sed -i '' $(($3 + 1))d "$1"
        printf "1 record deleted\n"

    elif [ "$2" = "range" ]; then
        sed -i '' $(($3 + 1)),$(($4 + 1))d "$1"
        printf "$(($4 - $3 + 1)) record(s) deleted\n"

    else
        # catching if they have an incorrect arg
        printf "ERROR: invalid delete argument: %s\n" "$2"
        exit 1

    fi

}

# count and print the number of rows in an existing database
count() {
    if [[ -f "$1" && -r "$1" ]]; then
        # using WC -l and piping it into awk to get just the number and then subtracting 1 for the header
        awks='{ print $1 }'
        temp=$(wc -l $1 | awk "$awks")
        printf "$((temp - 1))\n"
        
    else
        # the file they enter must be a readable file
        printf "ERROR: %s is NOT a readable file...\n" "$1"

    fi

}

# First check if in interactive mode
if [ ! $# = 0 ]; then   # not interative
    if [ $# = 1 ]; then # no cmd specified
        printf "ERROR: please specify a command and a database\n"
        exit 1

    fi

    if [ $2 = "new" ]; then # new
        if [ $# = 2 ]; then
            # if no name specified
            new "$1" "Untitled Database"

        else
            new "$1" "$3"

        fi
    elif [[ $2 = "insert" || $2 = "add" ]]; then # insert
        # if they have all of the params
        if [ $# = 6 ]; then
            insert "$1" "$3" "$4" "$5" "$6"

        else
            # error if they dont specify all parts
            printf "ERROR: Insert requires 5 parameters.\n"
            exit 1

        fi

    elif [ "$2" = "display" ]; then # display
        display "$1" "$3" "$4" "$5"

    elif [ "$2" = "delete" ]; then # delete
        delete "$1" "$3" "$4" "$5"

    elif [ "$2" = "count" ]; then # count
        count "$1"

    else
        # if the enter a incorrect cmd
        printf "ERROR: invalid command. Not: %s\n" "$2"
        exit 1

    fi

else # interactive mode
    # looping until cont != y
    cont="y"
    while [ $cont = "y" ]; do
        # get the database name MUST BE SPECIFIED!
        read -p "filename of database to use: " dbname
        while [ -z "$dbname" ]; do
            read -p "You must specify the name of a database... : " dbname

        done

        # now get the cmd
        read -p "command? new, insert, display, delete, count: " cmd

        if [ "$cmd" = "new" ]; then # new
            # read the params needed for new
            read -p "Header for the db: " header
            # check if they specified a header or just hit enter
            if [ -z "$header" ]; then
                header="Untitled Database"

            fi

            new "$dbname" "$header"

        elif [[ $cmd = "insert" || $cmd = "add" ]]; then # insert
            # read in all of the params
            read -p "Make: " make
            read -p "Model: " model
            read -p "Year (1922-2028): " year
            read -p "Color: " color
            # call insert with params
            insert "$dbname" "$make" "$model" "$year" "$color"

        elif [ $cmd = "display" ]; then # display
            # read in the display param
            read -p "How many to show (one of all, single, or range): " howm
            # check which display mode they want, for each mode read the needed params and call display
            if [ $howm = "single" ]; then
                read -p "Which single: " single
                display "$dbname" "$howm" "$single"

            elif [ $howm = "range" ]; then
                read -p "Begining of range: " beg
                read -p "End of range: " end
                display "$dbname" "$howm" "$beg" "$end"

            elif [ $howm = "all" ]; then
                display "$dbname" "$howm"

            else
                # invalid mode
                printf "ERROR: %s  is not valid\n" "$howm"

            fi

        elif [ $cmd = "count" ]; then # count
            count "$dbname"

        elif [ $cmd = "delete" ]; then # delete
            # read the params for delete
            read -p "How many to delete (one of all, single, or range): " howm
            # same logic as display but calling delte with the params gotten instead
            if [ $howm = "single" ]; then
                read -p "Which single: " single
                delete "$dbname" "$howm" "$single"

            elif [ $howm = "range" ]; then
                read -p "Begining of range: " beg
                read -p "End of range: " end
                delete "$dbname" "$howm" "$beg" "$end"

            elif [ $howm = "all" ]; then
                delete "$dbname" "$howm"

            else
                printf "ERROR: %s  is not valid\n" "$howm"

            fi

        else
            printf "ERROR: invalid command. Not: %s\n" "$cmd"
            exit 1       

        fi

        # try and keep looping
        read -p "More? (y/n): " cont

    done

fi

exit 0 # sucess