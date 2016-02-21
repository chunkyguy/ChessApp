//
//  sjeng.h
//  SjengChess
//
//  Created by Sid on 21/02/16.
//  Copyright © 2016 whackylabs. All rights reserved.
//

#ifndef sjeng_engine_h
#define sjeng_engine_h

extern int board[144];

typedef void(^render_callback)(int color);

int start_chess();
void loop(char *input, render_callback render_board);

#endif /* sjeng_engine_h */
