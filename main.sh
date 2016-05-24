#!/usr/bin/env bash

mkdir outputs
echo Time interval is selected as 2010-01-01 -- 2010-03-01
#################################################################################################
echo Authors are extracting..
git log --format='%aN' --since=2010-01-01 --before=2010-03-01 | sort -u >outputs/allauthors.log


getauthors() {
authors=() # Create array
while IFS= read -r line # Read a line
do
authors+=("$line") # Append line to the array
done < "$1"
}

getauthors "outputs/allauthors.log"
for e in "${authors[@]}"
do
git shortlog --since=2010-01-01 --before=2010-03-01 --author="$e" >>outputs/commitandauthors.log
done


#################################################################################################

echo Total commits with commit dates are extracting..
for e in "${authors[@]}"
do
echo "$e" >>outputs/commitdateandauthor.log
git log --author="$e" --since=2010-01-01 --before=2010-03-01 | grep Date | awk '{print " : "$4" "$3" "$6}' | uniq -c >>outputs/commitdateandauthor.log
done

#################################################################################################
##Extract data for a specific time interval
echo Extracting data of given time interval..
for e in "${authors[@]}"
do
git shortlog  --since=2010-01-01 --before=2010-03-01  --author="$e" >outputs/tmp.log
head -1 outputs/tmp.log  >>outputs/commitof2months.log
done

gcc calculate.c -o calculate
./calculate outputs/commitof2months.log

#################################################################################################

#find commit frequency of committers
echo Frequencies of each developer is calculating..
git shortlog -s --since=2010-01-01 --before=2010-03-01 >outputs/commitcountandauthors1.log
gcc frequency.c -o freq
./freq

#################################################################################################
#find 80% of the commits
echo Top developers are finding..
git shortlog -s -n --since=2010-01-01 --before=2010-03-01  >outputs/commitcountandauthors.log
gcc topdeveloper.c -o topdevelopers
./topdevelopers outputs/commitcountandauthors.log

#################################################################################################

#Part3: Generation of matrix
for e in "${authors[@]}"
do
echo "*"  >>outputs/allchangedfilesandauthors.log
echo "$e" >>outputs/allchangedfilesandauthors.log
git log --since=2010-01-01 --before=2010-03-01 --pretty="%H" --author="$e" | while read commit_hash; do git show --oneline --name-only $commit_hash | tail -n+2; done | sort | uniq >>outputs/allchangedfilesandauthors.log
echo "**"  >>outputs/allchangedfilesandauthors.log
done

git ls-files >outputs/allfiles.log

echo Matrix is generating...
g++ preprocess_matrix.cpp -o pre
./pre outputs/allchangedfilesandauthors.log

sort -u outputs/files.txt >outputs/uniqfiles.txt

g++ creatematrix.cpp -o matrix
./matrix outputs/allchangedfilesandauthors.log


#################################################################################################
echo Cleaning operations is doing

rm outputs/tmp.log
rm outputs/lastcommitdates.txt

