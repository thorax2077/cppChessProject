#pragma once
#include <Windows.h>
#include <string>
#include <array>
#include <optional>
using namespace std;

class ChessPiece
{
	enum class ChessFigure;
	enum class Alignment;
	enum class Direction;
	
public:
	
	int Y;
	int X;
	LPCWSTR name;
	ChessFigure chessFigure;
	Alignment alignment;
	bool directionIsUp;

	enum class ChessFigure {
		Pawn,
		Rook,
		Horse,
		Bishop,
		King,
		Queen,
		None
	};
	enum class Alignment {
		White,
		Black,
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
		case ChessFigure::Pawn:
			if (toBeX == curX + 1 * dirMult && toBeY == curY + 1 * dirMult) {
				return true;
			}
			if (enX != -1 && enY != -1) {
				if ((enX == curX + 1 || enX == curX - 1) && enY == curY + 1 * dirMult) return true;
			}
			break;
		case ChessFigure::Rook:
			break;
		case ChessFigure::Horse:
			break;
		case ChessFigure::Bishop:
			break;
		case ChessFigure::King:
			break;
		case ChessFigure::Queen:
			break;
		case ChessFigure::None:
			break;
		default:
			break;
		}
		return false;
	}
};

