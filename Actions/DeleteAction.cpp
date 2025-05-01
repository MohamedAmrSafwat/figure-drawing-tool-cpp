#include "DeleteAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\Actions\SelectAction.h"
DeleteAction::DeleteAction(ApplicationManager* pApp) : Action(pApp) {}

void DeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->GetSelectedFig() == NULL)
		pOut->PrintMessage("No figure is selected");
	else
		pOut->PrintMessage("Figure deleted successfully");
}

void DeleteAction::Execute()
{	
	ReadActionParameters();
	for (int i = 0; i < 200; i++)
	{
		if (pManager->Selectedarr[i] != NULL) {
			pManager->DeleteFigure(pManager->Selectedarr[i]);
		}
	}
}
	
