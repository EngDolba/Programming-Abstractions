/*
* File: UniversalHealthCoverage.cpp
* ----------------------
* Name: [TODO: enter name here]
* Section: [TODO: enter section leader here]
* This file is the starter project for the UniversalHealthCoverage problem
* on Assignment #3.
* [TODO: extend the documentation]
*/
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

bool isGood(Set<string>& cities,Vector< Set<string> > hospitals,Set<string> coveredCities);
void generateAllCombination(Vector<Set<string> > remaining,Vector<Set<string> > soFar,Vector<Vector<Set<string> > >& goodVariations,int numHosp);
Vector<Set<string> > checkSets(Set<string>& cities,Vector<Vector<Set<string> > > checkableSets);
bool goodVariation(Vector<Set<string> > &variation,int numHosp);
void generateAllCombination(Vector<Set<string> > remaining,Vector<Set<string> > soFar,Vector<Vector<Set<string> > >& goodVariations,int numHosp);
bool canOfferUniversalCoverage(Set<string>& cities,
							   Vector< Set<string> >& locations,
							   int numHospitals,
							   Vector< Set<string> >& result);


int main() {

	Set<string> cities;
	cities.add("A");
	cities.add("B");
	cities.add("C");
	cities.add("D");
	cities.add("E");
	cities.add("F");
	cities.add("K");
	Vector<Set<string> > locations;
	Set<string> bla;
	bla.add("A");
	bla.add("B"); 
	bla.add("C");
	locations.add(bla);
	Set<string> bla1;
	bla1.add("A");
	bla1.add("C");
	bla1.add("D");
	locations.add(bla1);
	Set<string> bla2;
	bla2.add("B");
	bla2.add("F");
	locations.add(bla2);
	Set<string> bla3;
	bla3.add("C");
	bla3.add("E");
	bla3.add("F");
	locations.add(bla3);
	Set<string> bla4;
	bla4.add("K");
	locations.add(bla4);
	Vector< Set<string> > result;
	cout << canOfferUniversalCoverage(cities,locations,4,result) << endl;
	cout << result.toString() << endl;
	return 0;
}
bool canOfferUniversalCoverage(Set<string>& cities,
							   Vector< Set<string> >& locations,
							   int numHospitals,
							   Vector< Set<string> >& result)
{
	Vector<Vector<Set<string> > > checkableSets;
	generateAllCombination(locations,result,checkableSets,numHospitals);
	result = checkSets(cities,checkableSets);
	if(result.size()==0) return false;
	return true;

}
//Vector<string> generateAllSubsetsLessThanN(int n,Vector< Set<string> >& locations)

void generateAllCombination(Vector<Set<string> > remaining,Vector<Set<string> > soFar,Vector<Vector<Set<string> > >& goodVariations,int numHosp) 
{
	if(remaining.size()==0)
	{
		if(goodVariation(soFar,numHosp)) goodVariations.add(soFar);
		return;
	}
	else
	{
		Set<string> bla = remaining[0];
		remaining.remove(0);
		generateAllCombination(remaining,soFar,goodVariations,numHosp);
		soFar.add(bla);
		generateAllCombination(remaining,soFar,goodVariations,numHosp);
		return;
	}
}

bool goodVariation(Vector<Set<string> > &variation,int numHosp)
{
	if(variation.size()> numHosp)
	{
		return false;
	}
	return true;
}
Vector<Set<string> > checkSets(Set<string>& cities,Vector<Vector<Set<string> > > checkableSets)
{
	for(int i = 0;i<checkableSets.size();i++)
	{
		Set<string> bla;
		if(isGood(cities,checkableSets[i],bla))
		{

			return checkableSets[i];
		}
	}
	Vector<Set<string> > empty;
	return empty;

}
bool isGood(Set<string>& cities,
			Vector< Set<string> > hospitals,Set<string> coveredCities)
{
	if(coveredCities.size()==cities.size())
	{	
		return true;
	}
	if(hospitals.size()==0) return false;
	Set<string> hospital = hospitals[0];
	hospitals.remove(0);
	return isGood(cities,hospitals,coveredCities+=hospital);


}