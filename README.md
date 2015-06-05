The Compiler reads a list of words with frequencies and generates an optimized
trie sturctured which only consumes 8bytes per nodes and which are stored in a
vector.  The compiler then stores the structure in the specified output file as
shown below:
./TextMiningCompiler /path/to/words.txt /path/to/dict.bin

words is of the form:
hello 42
tomato 100

Then the Application can be lauched with the generated binary file to indicate
all the words that match with a certain distance for instance the command:
$ echo "approx 1 test" | ./TextMiningApp /path/to/dict.bin

will return all the words with have a distance of 1 to test. The results and
returned in a Json format.

Note only the following alphabet is currently supported:
'#', '&', '+', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_', 'a',
'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',

The Trie was optimised to given an answer in milliseconds.
