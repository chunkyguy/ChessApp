/*
 Sjeng - a chess variants playing program
 Copyright (C) 2000 Gian-Carlo Pascutto
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
 File: attacks.c                                             
 Purpose: calculate attack information                      
 
 */

#include "sjeng.h"
#include "extvars.h"

int calc_attackers (int square, int color) {
	
	/* this function calculates attack information for a square */
	
	static const int rook_o[4] = {12, -12, 1, -1};
	static const int bishop_o[4] = {11, -11, 13, -13};
	static const int knight_o[8] = {10, -10, 14, -14, 23, -23, 25, -25};
	int a_sq, i;
	
	int attackers = 0;
	
	if (board[square] == frame) return 0;
	
	/* white attacker: */
	if (color%2) {
		/* rook-style moves: */
		for (i = 0; i < 4; i++) {
			a_sq = square + rook_o[i];
			
			/* the king can attack from one square away: */
			if (board[a_sq] == wking) 
			{	  
				attackers++;
				break;
			}
			else
			{
				/* otherwise, check for sliding pieces: */
				while (board[a_sq] != frame) {
					if (board[a_sq] == wrook || board[a_sq] == wqueen) 
					{
						attackers++;
						break;
					}
					else if (board[a_sq] != npiece) break;
					a_sq += rook_o [i];
				}
			}
		}
		
		/* bishop-style moves: */
		for (i = 0; i < 4; i++) {
			a_sq = square + bishop_o[i];
			/* check for pawn attacks: */
			if (board[a_sq] == wpawn && i%2)
			{
				attackers++;
				break;
			}
			/* the king can attack from one square away: */
			else if (board[a_sq] == wking)
			{
				attackers++;
				break;
			}
			else
			{
				while (board[a_sq] != frame) {
					if (board[a_sq] == wbishop || board[a_sq] == wqueen) 
					{
						attackers++;
						break;
					}
					else if (board[a_sq] != npiece) break;
					a_sq += bishop_o [i];
				}
			}
		}
		
		/* knight-style moves: */
		for (i = 0; i < 8; i++) {
			a_sq = square + knight_o[i];
			if (board[a_sq] == wknight)
				attackers++;
			
		}
		
		/* if we haven't hit a white attacker by now, there are none: */
		
	}
	
	/* black attacker: */
	else {
		/* rook-style moves: */
		for (i = 0; i < 4; i++) {
			a_sq = square + rook_o[i];
			/* the king can attack from one square away: */
			if (board[a_sq] == bking)
			{
				attackers++;
				break;
			}
			/* otherwise, check for sliding pieces: */
			else {
				while (board[a_sq] != frame) {
					if (board[a_sq] == brook || board[a_sq] == bqueen) 
					{
						attackers++;
						break;
					};
					if (board[a_sq] != npiece) break;
					a_sq += rook_o [i];
				}
			}
		}
		
		/* bishop-style moves: */
		for (i = 0; i < 4; i++) {
			a_sq = square + bishop_o[i];
			/* check for pawn attacks: */
			if (board[a_sq] == bpawn && !(i%2))
			{
				attackers++;
				break;
			}
			/* the king can attack from one square away: */
			else if (board[a_sq] == bking)
			{
				attackers++;
				break;
			}
			else {
				while (board[a_sq] != frame) {
					if (board[a_sq] == bbishop || board[a_sq] == bqueen) 
					{
						attackers++;
						break;
					}
					else if (board[a_sq] != npiece) break;
					a_sq += bishop_o [i];
				}
			}
		}
		
		/* knight-style moves: */
		for (i = 0; i < 8; i++) {
			a_sq = square + knight_o[i];
			if (board[a_sq] == bknight) 
				attackers++;
		}
		
		/* if we haven't hit a black attacker by now, there are none: */
	}
	
	return attackers;
	
}

#if 0
bool_c is_attacked (int square, int color)
{
	int a, j, dir, i, l;
	
	for (a = 1, j = 1; (a <= piece_count); j++)
	{
		i = pieces[j];
		
		if (!i)
			continue;
		else
			a++;
		
		if ((color&1) != (board[i]&1)) continue;
		
		if (color & 1)
		{
			switch (board[i])
			{
				case (wpawn):
					if ((i+13) == square || (i+11) == square) return TRUE_C;
					break;
				case (wknight):
					if ((i - 25) == square || (i-23) == square || (i-14) == square
						|| (i-10) == square || (i+10) == square || (i+14) == square
						|| (i+23) == square || (i+25) == square) return TRUE_C;
					break;
				case (wbishop):
					dir = abs(i - square);
					if ((dir % 13) == 0)
					{
						dir = (i - square > 0) ? 13 : -13;
						for (l = square+dir;(board[l] == npiece) && (l != i);l += dir);
						if (i == l) return TRUE_C;
					}
					else if ((dir % 11) == 0)
					{
						dir = (i - square > 0) ? 11 : -11;
						for (l = square+dir;(board[l] == npiece) && (l != i);l += dir);
						if (i == l) return TRUE_C;
					}
					break;
				case (wrook):
					if (file(i) == file(square))
					{
						dir = (i - square > 0) ? 12 : -12;
						for (l = square+dir;(board[l] == npiece) && (l != i); l += dir);
						if (i == l) return TRUE_C;
					}
					else if (rank(i) == rank(square))
					{
						dir = (i - square > 0) ? 1 : -1;
						for (l = square+dir;(board[l] == npiece) && (l != i); l += dir);
						if (i == l) return TRUE_C;
					}
					break;
				case (wqueen):
					dir = abs(i - square);
					if ((dir % 13) == 0)
					{
						dir = (i - square > 0) ? 13 : -13;
						for (l = square+dir;(board[l] == npiece) && (l != i);l += dir);
						if (i == l) return TRUE_C;
					}
					else if ((dir % 11) == 0)
					{
						dir = (i - square > 0) ? 11 : -11;
						for (l = square+dir;(board[l] == npiece) && (l != i);l += dir);
						if (i == l) return TRUE_C;
					}
					else if (file(i) == file(square))
					{
						dir = (i - square > 0) ? 12 : -12;
						for (l = square+dir;(board[l] == npiece) && (l != i); l += dir);
						if (i == j) return TRUE_C;
					}
					else if (rank(i) == rank(square))
					{
						dir = (i - square > 0) ? 1 : -1;
						for (l = square+dir;(board[l] == npiece) && (l != i); l += dir);
						if (i == l) return TRUE_C;
					}
					break;
				case (wking):
					if (   (abs(rank(i) - rank(square)) <= 1) 
						&& (abs(file(i) - file(square)) <= 1)) 
						return TRUE_C;
					break;
			}
		}
		else 
		{
			switch(board[i])
			{
				case (bpawn):
					if ((i-13) == square || (i-11) == square) return TRUE_C;
					break;
				case (bknight):
					if ((i - 25) == square || (i-23) == square || (i-14) == square
						|| (i-10) == square || (i+10) == square || (i+14) == square
						|| (i+23) == square || (i+25) == square) return TRUE_C;
					break;
				case (bbishop):
					dir = abs(i - square);
					if ((dir % 13) == 0)
					{
						dir = (i - square > 0) ? 13 : -13;
						for (l = square+dir;(board[l] == npiece) && (l != i);l += dir);
						if (i == l) return TRUE_C;
					}
					else if ((dir % 11) == 0)
					{
						dir = (i - square > 0) ? 11 : -11;
						for (l = square+dir;(board[l] == npiece) && (l != i);l += dir);
						if (i == l) return TRUE_C;
					}
					break;
				case (brook):
					if (file(i) == file(square))
					{
						dir = (i - square > 0) ? 12 : -12;
						for (l = square+dir;(board[l] == npiece) && (l != i); l += dir);
						if (i == l) return TRUE_C;
					}
					else if (rank(i) == rank(square))
					{
						dir = (i - square > 0) ? 1 : -1;
						for (l = square+dir;(board[l] == npiece) && (l != i); l += dir);
						if (i == l) return TRUE_C;
					}
					break;
				case (bqueen):
					dir = abs(i - square);
					if ((dir % 13) == 0)
					{
						dir = (i - square > 0) ? 13 : -13;
						for (l = square+dir;(board[l] == npiece) && (l != i);l += dir);
						if (i == l) return TRUE_C;
					}
					else if ((dir % 11) == 0)
					{
						dir = (i - square > 0) ? 11 : -11;
						for (l = square+dir;(board[l] == npiece) && (l != i);l += dir);
						if (i == l) return TRUE_C;
					}
					else if (file(i) == file(square))
					{
						dir = (i - square > 0) ? 12 : -12;
						for (l = square+dir;(board[l] == npiece) && (l != i); l += dir);
						if (i == l) return TRUE_C;
					}
					else if (rank(i) == rank(square))
					{
						dir = (i - square > 0) ? 1 : -1;
						for (l = square+dir;(board[l] == npiece) && (l != i); l += dir);
						if (i == l) return TRUE_C;
					}
					break;
				case (bking):
					if (   (abs(rank(i) - rank(square)) <= 1) 
						&& (abs(file(i) - file(square)) <= 1)) 
						return TRUE_C;
					break;
			}
		}
	}
	return FALSE_C;
}
#endif

bool_c is_attacked (int square, int color) {
	
	/* this function will return TRUE_C if square "square" is attacked by a piece
     of color "color", and return FALSE_C otherwise */
	
	static const int rook_o[4] = {12, -12, 1, -1};
	static const int bishop_o[4] = {11, -11, 13, -13};
	static const int knight_o[8] = {10, -10, 14, -14, 23, -23, 25, -25};
	register int ndir, a_sq;
	register int basq, i;
	
	/* white attacker: */
	if (color&1) {
		
		/* bishop-style moves: */
		for (i = 0; i < 4; i++) {
			ndir = bishop_o[i];
			a_sq = square+ndir;
			basq = board[a_sq];
			/* check for pawn attacks: */
			if (basq == wpawn && (i&1)) return TRUE_C;
			/* the king can attack from one square away: */
			if (basq == wking) return TRUE_C;
			while (basq != frame) {
				if (basq == wbishop || basq == wqueen) return TRUE_C;
				if (basq != npiece) break;
				a_sq += ndir;
				basq = board[a_sq];
			}
		}
		/* knight-style moves: */
		for (i = 0; i < 8; i++) {
			if (board[square + knight_o[i]] == wknight) return TRUE_C;
		}
		/* rook-style moves: */
		for (i = 0; i < 4; i++) {
			ndir = rook_o[i];
			a_sq = square + ndir;
			basq = board[a_sq];
			/* the king can attack from one square away: */
			if (basq == wking) return TRUE_C;
			/* otherwise, check for sliding pieces: */
			while (basq != frame) {
				if (basq == wrook || basq == wqueen) return TRUE_C;
				if (basq != npiece) break;
				a_sq += ndir;
				basq = board[a_sq];
			}
		}
		
		/* if we haven't hit a white attacker by now, there are none: */
		return FALSE_C;
		
	}
	
	/* black attacker: */
	else {
		/* bishop-style moves: */
		for (i = 0; i < 4; i++) {
			ndir = bishop_o[i];
			a_sq = square + ndir;
			basq = board[a_sq];
			/* check for pawn attacks: */
			if (basq == bpawn && !(i&1)) return TRUE_C;
			/* the king can attack from one square away: */
			if (basq == bking) return TRUE_C;
			while (basq != frame) {
				if (basq == bbishop || basq == bqueen) return TRUE_C;
				if (basq != npiece) break;
				a_sq += ndir;
				basq = board[a_sq];
			}
		}
		
		/* knight-style moves: */
		for (i = 0; i < 8; i++) {
			if (board[square + knight_o[i]] == bknight) return TRUE_C;
		}
		
		/* rook-style moves: */
		for (i = 0; i < 4; i++) {
			ndir = rook_o[i];
			a_sq = square + rook_o[i];
			basq = board[a_sq];
			/* the king can attack from one square away: */
			if (basq == bking) return TRUE_C;
			/* otherwise, check for sliding pieces: */
			while (basq != frame) {
				if (basq == brook || basq == bqueen) return TRUE_C;
				if (basq != npiece) break;
				a_sq += ndir;
				basq = board[a_sq];
			}
		}
		
		/* if we haven't hit a black attacker by now, there are none: */
		return FALSE_C;
		
	}
	
}

bool_c nk_attacked (int square, int color) {
	
	/* this function will return TRUE_C if square "square" is attacked by a piece
     of color "color", and return FALSE_C otherwise */
	
	static const int rook_o[4] = {12, -12, 1, -1};
	static const int bishop_o[4] = {11, -11, 13, -13};
	static const int knight_o[8] = {10, -10, 14, -14, 23, -23, 25, -25};
	register int ndir, a_sq;
	register int basq, i;
	
	/* white attacker: */
	if (color&1) {
		
		/* bishop-style moves: */
		for (i = 0; i < 4; i++) {
			ndir = bishop_o[i];
			a_sq = square+ndir;
			basq = board[a_sq];
			/* check for pawn attacks: */
			if (basq == wpawn && (i&1)) return TRUE_C;
			/* the king can attack from one square away: */
			while (basq != frame) {
				if (basq == wbishop || basq == wqueen) return TRUE_C;
				if (basq != npiece) break;
				a_sq += ndir;
				basq = board[a_sq];
			}
		}
		/* knight-style moves: */
		for (i = 0; i < 8; i++) {
			if (board[square + knight_o[i]] == wknight) return TRUE_C;
		}
		/* rook-style moves: */
		for (i = 0; i < 4; i++) {
			ndir = rook_o[i];
			a_sq = square + ndir;
			basq = board[a_sq];
			/* otherwise, check for sliding pieces: */
			while (basq != frame) {
				if (basq == wrook || basq == wqueen) return TRUE_C;
				if (basq != npiece) break;
				a_sq += ndir;
				basq = board[a_sq];
			}
		}
		
		/* if we haven't hit a white attacker by now, there are none: */
		return FALSE_C;
		
	}
	
	/* black attacker: */
	else {
		/* bishop-style moves: */
		for (i = 0; i < 4; i++) {
			ndir = bishop_o[i];
			a_sq = square + ndir;
			basq = board[a_sq];
			/* check for pawn attacks: */
			if (basq == bpawn && !(i&1)) return TRUE_C;
			/* the king can attack from one square away: */
			while (basq != frame) {
				if (basq == bbishop || basq == bqueen) return TRUE_C;
				if (basq != npiece) break;
				a_sq += ndir;
				basq = board[a_sq];
			}
		}
		
		/* knight-style moves: */
		for (i = 0; i < 8; i++) {
			if (board[square + knight_o[i]] == bknight) return TRUE_C;
		}
		
		/* rook-style moves: */
		for (i = 0; i < 4; i++) {
			ndir = rook_o[i];
			a_sq = square + rook_o[i];
			basq = board[a_sq];
			/* otherwise, check for sliding pieces: */
			while (basq != frame) {
				if (basq == brook || basq == bqueen) return TRUE_C;
				if (basq != npiece) break;
				a_sq += ndir;
				basq = board[a_sq];
			}
		}
		
		/* if we haven't hit a black attacker by now, there are none: */
		return FALSE_C;
		
	}
	
}

