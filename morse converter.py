# KDWallace 2020.7.17
# basic algorithm for converting strings to morse based on the frequency of occurance
############################################################################

import math

#order of frequency of characters as well as non-existing dit/cah combinations which are replaced by #
alphabet = '##etianmsurwdkgohvf#l#pjbxcyzq##54#3###2##+####16=/#####7###8#90'

#user input
string = input('> ').lower()

#function for converting string to morse
def morse(string):
    out = ''
    #iterate through characters in the string
    for char in string:
        letter = ''
        if char in alphabet and char != '#':
            index = alphabet.index(char) + 1
            while index > 2:
                
                #if index is even, this results in a dah
                if index%2 == 0:
                    letter += '-'
                #otherwise, it is a dit
                else:
                    letter += '.'
                #half and round up
                index = math.ceil(index/2)

            #as this is working backwards on the frequency tree, the order of dits and dahs will be reversed
            letter = letter[::-1]
            out = out + letter + ' '

        #if the char is a space
        elif char == ' ':
            out += '   '
    return out

print(morse(string))
