#include "minesweeper.h"
#include <assert.h>

const char UNREVEALED = ' ' ;
const char REVEALED[9] = "012345678";
const char FLAG = 'F';
const char MINE = '*';

bool asseration(struct ms_board *b, int x, int y){
  return ((1 <= x && x <= b->width) && (1 <= y && y <= b->height));
}
bool flag(struct ms_board *b, int x, int y) {
  assert(asseration);
  if(b->board[(y - 1) * b->width + x - 1] == FLAG){
    b->board[(y - 1) * b->width + x - 1] = UNREVEALED;
    return true;
  } else if (b->board[(y - 1) * b->width + x - 1] == UNREVEALED){
    b->board[(y - 1) * b->width + x - 1] = FLAG;
    return true;
  } else {
    return false;
  }
}


bool is_mine(const struct ms_board *b, int x, int y){
  assert(asseration);
  for(int i = 0; i < b->num_mines; ++i){
    if(x >= 1 && x <= b->width && y >= 1 && y <= b->height &&
       (y == b->mines[i].y) && (x == b->mines[i].x)){
      return true;
    } 
  }
  return false;
}

int mines_around(struct ms_board *b, int x, int y){
  int around = 0;
  for (int x_offset = -1; x_offset <= +1; ++x_offset) {
    for (int y_offset = -1; y_offset <= +1; ++y_offset) {
      if ((x + x_offset >= 1 )&&
          (x + x_offset <= b->width) &&
          (y + y_offset >= 1)&&
          (y + y_offset <= b->height) &&
          (is_mine(b, x + x_offset, y + y_offset))){
        ++around;
      } 
    }
  }
  return around;
}

bool reveal(struct ms_board *b, int x, int y) {
  assert(asseration);
  if(b->board[(y - 1) * b->width + x - 1] == UNREVEALED){
    if(is_mine(b, x, y)){
      b->board[(y - 1) * b->width + x - 1] = MINE;
    } else {
      int around = mines_around(b, x, y);
      b->board[(y - 1) * b->width + x - 1] = REVEALED[around];
      if(around == 0){
        for (int x_offset = -1; x_offset <= +1; ++x_offset) {
          for (int y_offset = -1; y_offset <= +1; ++y_offset) {
            if((x + x_offset >= 1)&&
               (x + x_offset <= b->width) &&
               (y + y_offset >= 1)&&
               (y + y_offset <= b->height)){
              reveal(b, x + x_offset, y + y_offset);
            }
          }
        }
      }
    }
    return true;
  } else {
    return false;
  }
}

bool game_won(const struct ms_board *b) {
  assert(b->width > 0);
  assert(b->height > 0);
  for (int x = 1; x <= b->width; ++x) {
    for (int y = 1; y <= b->height; ++y) {
     
      if((is_mine(b, x, y) && (b->board[(y - 1) * b->width + x - 1] == MINE)) ||
         (!is_mine(b, x, y) &&
          ((b->board[(y - 1) * b->width + x - 1] ==
            UNREVEALED) || (b->board[(y - 1) * b->width + x - 1] == FLAG)))){
        return false;
      } 
    }
  }
  return true;
}

bool game_lost(const struct ms_board *b) {
  assert(b->width > 0);
  assert(b->height > 0);

  for (int x = 1; x <= b->width; ++x) {
    for (int y = 1; y <= b->height; ++y) {
      
      if(b->board[(y - 1) * b->width + x - 1] == MINE) {
        return true;
      }
    }
  }
  return false;
}
