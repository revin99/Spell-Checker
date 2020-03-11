# Spell-Checker
Spell Checker application written in C language

This application requires the initialisation of a Dictionary file which contains all the legal, correctly-spelt list of words.
This jumble of correctly spelt words is then sorted alphabetically and stored in a list of lists, achieved by creating an array of linked list. A particular index of the array stores all words starting from a particular letter and these words are chained to this array through linked list, words in which are arranged in sorted order lexicographically.

The input file, containing the text to be spelt-checked is extracted word by word, by ignoring the punctuations and checked if it is present in the MRU list.The MRU is a list of most recently used words with it's frequency,maintained sorted lexicographically upto 10 words. The input word's spelling is first checked in here before being checked in the dictionary, which requires constant time.

The operation of checking in the dictionary takes up O(N) time as access to the array index is done in constant time whereas searching through that linked list requires worst time complexity of N.

A list of mis-spelt words is maintained which is sorted according to it's frequency of occurrence.
