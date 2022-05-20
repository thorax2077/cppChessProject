#pragma once
#include <string>
#include <array>
using namespace std;

class ChessPiece
{
	enum ChessFigure;
	enum Alignment;
	enum Direction;
	
public:
	bool checkIfStepValid(ChessPiece arr[32], int curX, int curY, int toBeX, int toBeY);
	int Y;
	int X;
	string name;
	ChessFigure chessFigure;
	Alignment alignment;
	bool directionIsUp;

	enum ChessFigure {
		Pawn,
		Rook,
		Horse,
		Bishop,
		King,
		Queen,
		None
	};
	enum Alignment {
		White,
		Black,
		None
	};

	bool checkIfStepValid(ChessPiece arr[32], int curX, int curY, int toBeX, int toBeY) {
		ChessFigure ownType;
		Alignment ownAlign;
		bool ownDirectionIsUp;
		int enX = -1;
		int enY = -1;

		for (int i = 0; i < 32; i++)
		{
			if (arr[i].X == curX && arr[i].Y == curY) {
				ownType = arr[i].chessFigure;
				ownAlign = arr[i].alignment;
				ownDirectionIsUp = arr[i].directionIsUp;
				break;
			}
		}
		for (int i = 0; i < 32; i++) {
			if (arr[i].X == toBeX && arr[i].Y == toBeY) {
				if (arr[i].alignment == ownAlign) return false;
				enX = arr[i].X;
				enY = arr[i].Y;
			}
		}
		int dirMult = ownDirectionIsUp ? -1 : 1;
		switch (ownType) {
		case Pawn:
			if (toBeX == curX + 1 * dirMult && toBeY == curY + 1 * dirMult) {
				return true;
			}
			if (enX != -1 && enY != -1) {
				if ((enX == curX + 1 || enX == curX - 1) && enY == curY + 1 * dirMult) return true;
			}
			break;
		case Rook:
			break;
		case Horse:
			break;
		case Bishop:
			break;
		case King:
			break;
		case Queen:
			break;
		case None:
			break;
		default:
			break;
		}
		return false;
	}
};

