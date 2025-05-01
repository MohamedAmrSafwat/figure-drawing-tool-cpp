#include "SendBackAction.h"
#include "../Figures/CFigure.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../Figures/CFigure.h"

SendBackAction::SendBackAction(ApplicationManager* pApp) :Action(pApp)
{}

void SendBackAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->GetSelectedFig() != NULL)
		pOut->PrintMessage("Figure is send back");
	else
		pOut->PrintMessage("No figure is selected");
}

//Execute the action
void SendBackAction::Execute()
{
	CFigure* overlappedShape = NULL;
	ReadActionParameters();
	overlappedShape = pManager->IntersectFigure(shape);
	if (overlappedShape!=NULL)
		pManager->GetOutput()->PrintMessage("figure overlapped");
		overlappedShape->Draw(pManager->GetOutput());
}
