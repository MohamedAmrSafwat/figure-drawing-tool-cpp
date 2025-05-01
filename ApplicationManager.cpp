#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddSquareAction.h"
#include"Actions\AddTriangleAction.h"
#include"Actions\AddHexAction.h"
#include"Actions\AddCircleAction.h"
#include"Actions\SelectAction.h"
#include"Figures\CFigure.h"
#include "Actions\ChngBrdrClr.h"
#include "Actions\ChngFillClr.h"
#include "Actions\ChngtoBlack.h"
#include "Actions\ChngtoBlue.h"
#include "Actions\ChngtoGreen.h"
#include "Actions\ChngtoOrange.h"
#include "Actions\ChngtoRed.h"
#include "Actions\ChngtoYellow.h"
#include "Actions\Copy.h"
#include "Actions/Cut.h"
#include "Actions\Paste.h"
#include"Actions/SaveAction.h"
#include "Actions/LoadAction.h"
#include"Actions/SendBackAction.h"
#include"Actions/BringFrontAction.h"
#include "Actions\DeleteAction.h"
#include "Actions\ClearAll.h"
#include <fstream>
#include <iostream>

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FigCount = 0;
	SelectedCount = 0;

	SelectedFig = NULL;

	Clipboard = NULL;
	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
	{
		FigList[i] = NULL;
		Selectedarr[i] = NULL;
	}
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT :
		pAct = new AddRectAction(this);
		break;

	case DRAW_SQU:
		pAct = new AddSquareAction(this);
		break;

	case DRAW_TRI:
		pAct = new AddTriangleAction(this);
		break;

	case DRAW_HEX:
		pAct = new AddHexAction(this);
		break;

	case DRAW_CIR:
		pAct = new AddCircleAction(this);
		break;

	case SELECT:
		pAct = new SelectAction(this);
		break;

	case BORDER:
		pAct = new ChngBrdrClr(this);
		break;

	case FILLING:
		pAct = new ChngFillClr(this);
		break;

	case CHANGETOBLACK:
		pAct = new ChngtoBlack(this);
		break;

	case CHANGETOBLUE:
		pAct = new ChngtoBlue(this);
		break;

	case CHANGETOGREEN:
		pAct = new ChngtoGreen(this);
		break;

	case CHANGETOORANGE:
		pAct = new ChngtoOrange(this);
		break;

	case CHANGETORED:
		pAct = new ChngtoRed(this);
		break;

	case CHANGETOYELLOW:
		pAct = new ChngtoYellow(this);
		break;

	case COPY:
		pAct = new Copy(this);
		break;

	case CUT:
		pAct = new Cut(this);
		break;

	case PASTE:
		pAct = new Paste(this);
		break;

	case SAVEGRAPH:
		pAct = new SaveAction(this);
		break;

	case LOADGRAPH:
		pAct = new LoadAction(this);
		break;

	case BRINGFRONT:
		pAct = new BringFrontAction(this);
		break;

	case SENDTOBACK:
		pAct = new SendBackAction(this);
		break;

	case DELET:
		pAct = new DeleteAction(this);
		break;

	case CLEARALL:
		pAct = new ClearAll(this);
		break;

	case EXIT:
		///create ExitAction here

		break;

	case STATUS:	//a click on the status bar ==> no action
		return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//You may need to change this line depending to your implementation
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
//////////////////////////////////////////////////////////////////////////
void ApplicationManager::DeleteFigure(CFigure* pFig)
{
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i] == pFig) {
			FigList[i] = FigList[FigCount - 1];
			FigList[FigCount - 1] = NULL;
			FigCount--;
		}
		if (Selectedarr[i] == pFig) {
			Selectedarr[i] = FigList[pFig->NumSelected - 1];
			Selectedarr[pFig->NumSelected - 1] = NULL;
			pFig->NumSelected--;
		}
		if (SelectedFig == pFig)
			SelectedFig = NULL;
	}
}
////////////////////////////////////////////////////////////////////////////////////
CFigure** ApplicationManager::GetFigList() {
	return FigList;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL

	for (int i = MaxFigCount - 1; i >= 0; i--) {
		if (FigList[i] != NULL && FigList[i]->SearchPoint(x, y)) {
			return FigList[i];
		}
	}
	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.

	return NULL;
}
CFigure* ApplicationManager::IntersectFigure(CFigure* shape) {
	for (int x = 0; x < 1250; x++) {
		for (int y = 0; y < 650; y++) {
			for (int i = MaxFigCount - 1; i >= 0; i--) {
				if (FigList[i] != NULL&& FigList[i] != shape&&shape->SearchPoint(x,y) && FigList[i]->SearchPoint(x, y)) {
					return FigList[i];
				}
			}
		}
	}
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::SetSelectedFig(CFigure* pFig) {
	if (pFig == NULL)
	{
		for (int i = 0; i < MaxFigCount; i++)
		{
			if (Selectedarr[i] != NULL && Selectedarr[i]->IsSelected() == false) {
				if (Selectedarr[i] == SelectedFig)
					SelectedFig = NULL;
				Selectedarr[i] = Selectedarr[Selectedarr[i]->NumSelected - 1];
				Selectedarr[Selectedarr[i]->NumSelected - 1] = NULL;
				Selectedarr[i]->NumSelected--;
				break;
			}
		}
		std::cout << Selectedarr[0]->NumSelected << endl;
	}
	else
	{
		SelectedFig = pFig;
		Selectedarr[pFig->NumSelected] = SelectedFig;
		pFig->NumSelected++;
		std::cout << pFig->NumSelected << endl;
	}
}
///////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetSelectedFig() {
	if (SelectedFig != NULL)
		return SelectedFig;
	else
		return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::DeselectAll()
{
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i] != NULL)
			FigList[i]->SetSelected(false);
		Selectedarr[i] = NULL;
	}
	SelectedFig = NULL;
	SelectedCount = 0;
}

///////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::ClearFigures()
{
	for (int i = 0; i < MaxFigCount; i++) {
		FigList[i] = NULL;
		Selectedarr[i] = NULL;
	}
	FigCount = 0;
	SelectedCount = 0;
}
//////////////////////////////////////////////////////////////////////////////////
CFigure::Name ApplicationManager::GetFigName() {
	return SelectedFig->getFigName();
}
//////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::CopytoClipboard(CFigure* pFig) {
	Clipboard = pFig;
}
//////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetClipboard() {
	return Clipboard;
}
void ApplicationManager::SaveAll(ofstream& outFile) {
	outFile << "Draw Color" << "    " << "Fill Color" << endl;
	outFile << FigCount << endl;
	for (int i = 0; i < FigCount; i++) {
		FigList[i]->Save(outFile, i);
	}
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();
	for (int i = 0; i < FigCount; i++)
	{
			FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn
	}
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
	
}

