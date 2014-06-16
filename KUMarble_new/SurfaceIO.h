#ifndef SURFACEIO_H_INCLUDED
#define SURFACEIO_H_INCLUDED

#include "Var.h"

void SIO_InitConsoleSize (int y);

void SIO_InitBoard ();
void SIO_DrawBoard ();

int SIO_MovePlayerEffect(PLAYER *p, int turn, int dice);
void SIO_CalcPos(const int pos, int *x, int *y);

void SIO_PrtBuilding(int n);
void SIO_PrtCityName (int n);
void SIO_PrtPlayer(const PLAYER *p);
void SIO_PrtInfo(const PLAYER *player, const UNIV *univ);

void SIO_TurnColor(int n);

void SIO_PrintMsg(char* msg);

#endif // SURFACEIO_H_INCLUDED
