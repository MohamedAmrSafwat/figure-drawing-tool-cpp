#include "CSquare.h"
#include <iostream>
#include <fstream> // For file handling
#include <iomanip> // For setw()
#include "../ApplicationManager.h"
CSquare::CSquare(Point P1, int l , GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Center = P1;
	L = l;
	FigName = SQUARE;
}

void CSquare::Draw(Output* pOut) const
{
	pOut->DrawSqu(Center, L , FigGfxInfo, Selected);
}

bool CSquare::SearchPoint(int x, int y)
{
	if (x > Center.x - L && x< Center.x + L && y>Center.y - L && y < Center.y + L)
		return true;
	else
		return false;
}
CSquare* CSquare::deepcopy() {

	return new CSquare(*this);
}
void CSquare::Save(ofstream& outFile, int id) {
	outFile << left << setw(15) << "Square" << setw(5) << id << setw(10) <<
		Center.x << setw(10) << Center.y <<
		setw(10) << L <<setw(10) << "Draw color" << setw(10) << "Fill color" << endl;
}
void CSquare::Load(ifstream& infile, int lineNum) {
	infile.seekg(0, ios::beg);//to start reading from the begining
	for (int i = 0; i < lineNum; i++)
		infile.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');//skip to line
	ApplicationManager pmanager;
	string line;
	getline(infile, line);
	Center.x = stoi(line.substr(20, 30));
	Center.y = stoi(line.substr(30, 40));
	L = stoi(line.substr(40, 50));
	//FigGfxInfo.DrawClr = line.substr(70, 80);
	//FigGfxInfo.FillClr = line.substr(70, 80);
	Output* pOut = pmanager.GetOutput();
	Draw(pOut);
}
