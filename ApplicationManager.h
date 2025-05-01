#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "Actions\AddSquareAction.h"
#include"Actions\AddTriangleAction.h"
#include"Actions\AddHexAction.h"
#include"Actions\AddCircleAction.h"
#include"Actions\SelectAction.h"
#include "GUI\input.h"
#include "GUI\output.h"

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)

	int SelectedCount;
	CFigure* SelectedFig; //Pointer to the selected figure


	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

	CFigure* Clipboard;  //Pointer to copied/cut figure

public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList
	void DeleteFigure(CFigure* pFig);       //Delete figures from fig list
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	void SaveAll(ofstream& outFile);
	CFigure* IntersectFigure(CFigure* shape);
	void SetSelectedFig(CFigure* pFig);
	CFigure* GetSelectedFig();
	void DeselectAll();
	void ClearFigures();
	CFigure::Name GetFigName();
	bool ChngBrdr();
	void CopytoClipboard(CFigure* pFig);
	CFigure* GetClipboard();
	CFigure* Selectedarr[MaxFigCount];
	CFigure** GetFigList();

	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window	

};

#endif