#include "CCircle.h"
#include <iostream>
#include <fstream> // For file handling
#include <iomanip> // For setw()
#include "../ApplicationManager.h"
using namespace std;
CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	point1 = P1;
	point2 = P2;
	radius = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
	FigName = CIRCLE;
}

void CCircle::Draw(Output* pOut) const
{
	pOut->DrawCir(point1,point2 , FigGfxInfo, Selected);
}

bool CCircle::SearchPoint(int x, int y)
{
	if (sqrt(pow(x - point1.x, 2) + pow(y - point1.y, 2)) <= radius)
		return true;
	else
		return false;
}
CCircle* CCircle::deepcopy() {

	return new CCircle(*this);
}
void CCircle::Save(ofstream& outFile,int id) {
	outFile << left << setw(15) << "Circle" << setw(5) << id << setw(10) << 
		point1.x << setw(10) <<point1.y<< 
		setw(10)<< (int)sqrt((int)pow((point2.x - point1.x), 2) + (int)pow((point2.y - point1.y), 2)) <<
		setw(10)<<"Draw color"<<setw(10)<<"Fill color" << endl;
}
void CCircle::Load(ifstream& infile, int lineNum) {
	infile.seekg(0, ios::beg);//to start reading from the begining
	for (int i = 0; i < lineNum; i++)
		infile.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');//skip to line

	ApplicationManager pmanager;
	string line;
	getline(infile, line);

	point1.x = stoi(line.substr(20, 30));
	point1.y = stoi(line.substr(30, 40));
	point2.x = point1.x + stoi(line.substr(40, 50));
	point2.y = point1.y + stoi(line.substr(40, 50));
	//FigGfxInfo.DrawClr = line.substr(70, 80);
	//FigGfxInfo.FillClr = line.substr(70, 80);
	Output* pOut = pmanager.GetOutput();
	Draw(pOut);
}

