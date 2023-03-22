/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
Vector<string> printAminos(string protein, Map<char, Set<string> >& codons);
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
    
    Map<char, Set<string> > codons = loadCodonMap();
	

    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons)
{
	printAminos(protein,codons).toString();
}
Vector<string> printAminos(string protein, Map<char, Set<string> >& codons)
{
	Vector<string> result;
	if(protein.empty())
	{
		result.add("");
	}
	char amino = protein[0];
	foreach(string str in codons[amino])
	{
		foreach(string str1 in printAminos(protein.substr(1,protein.length()-1),codons))
		{
		str1 = str+str1;	
		result.add(str1);
		}
	}
	return result;
}