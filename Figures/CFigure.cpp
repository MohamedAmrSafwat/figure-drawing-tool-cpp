#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	IsCut = false;
	NumSelected = 0;
	ChngBrdr = false;
	ChngFill = false;
}

int CFigure::NumSelected;


void CFigure::SetSelected(bool s)
{
	Selected = s;
}

bool CFigure::IsSelected() const
{
	return Selected;
}
void CFigure::setChngBrdr(bool b) {
	ChngBrdr = b;
}

bool CFigure::getChngBrdr() {
	return ChngBrdr;
}

void CFigure::ChngDrawClr(color Dclr)
{
	FigGfxInfo.DrawClr = Dclr;
}

void CFigure::ChngFillClr(color Fclr)
{
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr;
}
bool CFigure::getChngFill() {
	return ChngFill;
}
void CFigure::setChngFill(bool b) {
	ChngFill = b;
}

CFigure::Name CFigure::getFigName() {
	return FigName;
}

GfxInfo CFigure::GetGfxInfo() {
	return FigGfxInfo;
}

