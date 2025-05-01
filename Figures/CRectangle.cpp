#include "CRectangle.h"
#include <iostream>
#include <fstream> // For file handling
#include <iomanip> // For setw()
#include "../ApplicationManager.h"
CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	FigName = RECTANGLE;
	dx = abs(Corner1.x - Corner2.x); dy = abs(Corner1.y - Corner2.y);
}
	

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}
bool CRectangle::SearchPoint(int x, int y)
{
	if (x <= Corner2.x && x >= Corner1.x && y <= Corner2.y && y >= Corner1.y) {
		return true;
	}
	else {
		return false;
	}
}

void CRectangle::Save(ofstream& outFile,int id) {
	outFile << left << setw(15) << "Rectangle" << setw(5) << id << setw(10) 
		<< Corner1.x<< setw(10) << Corner1.y<<setw(10) <<
		Corner2.x << setw(10) << Corner2.y << 
		setw(10) << "Draw color" << setw(10) << "Fill color" << endl;
}
CRectangle* CRectangle::deepcopy() {

	return new CRectangle(*this);
}
void CRectangle::Load(ifstream& infile, int lineNum) {
	infile.seekg(0, ios::beg);//to start reading from the begining
	for (int i = 0; i < lineNum; i++)
		infile.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');//skip to line
	ApplicationManager pmanager;
	string line;
	getline(infile, line);
	Corner1.x = stoi(line.substr(20, 30));
	Corner1.y = stoi(line.substr(30, 40));
	Corner2.x = stoi(line.substr(40, 50));
	Corner2.y = stoi(line.substr(50, 60));
	//FigGfxInfo.DrawClr = line.substr(70, 80);
	//FigGfxInfo.FillClr = line.substr(70, 80);
	Output* pOut = pmanager.GetOutput();
	Draw(pOut);
}
