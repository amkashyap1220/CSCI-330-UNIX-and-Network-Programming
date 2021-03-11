#
# Alexander Kashyap
# z1926618
# CSCI 330 section 1
# Due 3/12/21
# Assignment 8 awk report
#

BEGIN {
    # Header for the report
    print "Summary of Sales 2021\n\n";
    printf("%-22s%-8s%s\n","Name", "ID", "Sales");
    print "===================================";
    # must change the field sep to : for this db
    FS = ":";
}
{
    if (NF == 3)
    {
        # This is an associate
        associatescount++;
        split($2,name, " ");
        associates[$1] = name[2] ", " name[1];
    }
    else if (NF == 4)
    {
        # This is a product
        productcount++;
        cost[$1] = $4;
    }
    else if (NF == 5)
    {
        # This is a tranaction
        transcount++;
        # Update the total sales for that associate
        sales[$3] += cost[$2] * ($5 * 1.0);
    }
}
END {
    for (i in sales)
    {
        printf ("%-22s %s %10.2f\n",associates[i],i,sales[i]) | "sort -nr -k 4";
    }
    # close before printing anymore to avoid incorrect order due to sort still being open
    close("sort -nr -k 4");

    print "===================================";
    printf ("%22d Associates\n", associatescount);
    printf ("%22d Products\n", productcount);
    printf ("%22d Transactions\n", transcount);
}
