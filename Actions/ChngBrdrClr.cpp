#include "ChngBrdrClr.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

ChngBrdrClr::ChngBrdrClr(ApplicationManager* pApp): Action(pApp){}

void ChngBrdrClr::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Pick new border color");
}

void ChngBrdrClr::Execute() {
	Output* pOut = pManager->GetOutput();
	if (pManager->GetSelectedFig()->NumSelected == 1)
	{
		ReadActionParameters();
		pManager->GetSelectedFig()->setChngBrdr(true);
	}
	else if (pManager->GetSelectedFig()->NumSelected > 1)
		pOut->PrintMessage("Select only one figure");
	else
		pOut->PrintMessage("No figure is selected");
}