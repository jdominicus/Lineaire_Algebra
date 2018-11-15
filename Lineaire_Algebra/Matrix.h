#pragma once

#include <vector>
#include "Vector.h"

class Matrix
{
public:
	Matrix();
	~Matrix();

private:
	std::vector<std::unique_ptr<Vector>> vectors;

public:
	void addVector(std::unique_ptr<Vector> vector);
	void scale();
	void translate();
	void draw();
};

/*
Schrijf een Class Matrix die je vult met punten/vectoren op het scherm.
Maak een matrix die een aantal (hoek)punten op het scherm beschrijft/definieert.
Deze punten samen vormen jouw object.
Toon deze vorm op het scherm.
Extra: teken ook de omtrek van je figuur (lijnen tussen de punten)
Maak nu een methode waarmee je deze vorm kunt schalen
Maak ook een methode waarmee je deze vorm kunt transleren.
 */