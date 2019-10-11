/*****************************************************************************
 * C/C++ Headers
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/*****************************************************************************
 * Local Headers
 *****************************************************************************/

#include "TextIntersectNode.h"
#include "ComplexNode.h"
#include "dmemory.h"

/*****************************************************************************
 * Local Defines
 *****************************************************************************/

#define TABLE_WIDTH  (7)
#define TABLE_HEIGHT (11)

/*****************************************************************************
 * Local Typedefs
 *****************************************************************************/

typedef char CharEntry[TABLE_HEIGHT][TABLE_WIDTH + 1];

/*****************************************************************************
 * Local Functions
 *****************************************************************************/

static CharEntry *letter_space()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_A()
{
   static CharEntry entry = {
      "       ",
      "  b  c ",
      "       ",
      "       ",
      "       ",
      "  f  g ",
      "       ",
      "       ",
      "       ",
      " a    d",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_B()
{
   static CharEntry entry = {
      "       ",
      " Fi  E ",
      "      D",
      "       ",
      "      C",
      "  a  b ",
      "      c",
      "       ",
      "      d",
      " fh  e ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_C()
{
   static CharEntry entry = {
      "       ",
      "  c  b ",
      " d    a",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      " e    h",
      "  f  g ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_D()
{
   static CharEntry entry = {
      "       ",
      " dl  c ",
      "      b",
      "       ",
      "      f",
      "       ",
      "      a",
      "       ",
      "      g",
      " ik  h ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_E()
{
   static CharEntry entry = {
      "       ",
      " b    a",
      "       ",
      "       ",
      "       ",
      " f  g  ",
      "       ",
      "       ",
      "       ",
      " c    d",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_F()
{
   static CharEntry entry = {
      "       ",
      " b    c",
      "       ",
      "       ",
      "       ",
      " e  f  ",
      "       ",
      "       ",
      "       ",
      " a     ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_G()
{
   static CharEntry entry = {
      "       ",
      "  c  b ",
      " d    a",
      "       ",
      "       ",
      "       ",
      "    j i",
      "       ",
      " e    h",
      "  f  gI",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_H()
{
   static CharEntry entry = {
      "       ",
      " b    d",
      "       ",
      "       ",
      "       ",
      " g    h",
      "       ",
      "       ",
      "       ",
      " a    e",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_I()
{
   static CharEntry entry = {
      "       ",
      " a h b ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      " d g e ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_J()
{
   static CharEntry entry = {
      "       ",
      "  a d b",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      " h  e  ",
      "  gf   ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_K()
{
   static CharEntry entry = {
      "       ",
      " b    f",
      "       ",
      "       ",
      "       ",
      " de    ",
      "       ",
      "       ",
      "       ",
      " a    F",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_L()
{
   static CharEntry entry = {
      "       ",
      " a     ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      " b    c",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_M()
{
   static CharEntry entry = {
      "       ",
      " b    e",
      "       ",
      "       ",
      "   cd  ",
      "       ",
      "       ",
      "       ",
      "       ",
      " a    f",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_N()
{
   static CharEntry entry = {
      "       ",
      " b    d",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      " a    c",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_O()
{
   static CharEntry entry = {
      "       ",
      "  h  g ",
      " i    f",
      "       ",
      "       ",
      "       ",
      " a     ",
      " j     ",
      " b    e",
      "  c  d ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_P()
{
   static CharEntry entry = {
      "       ",
      " b   c ",
      "      d",
      "       ",
      "      e",
      " g   f ",
      "       ",
      "       ",
      "       ",
      " a     ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_Q()
{
   static CharEntry entry = {
      "       ",
      "  h  g ",
      " i    f",
      "       ",
      "       ",
      "       ",
      " a     ",
      " j  l e",
      " b     ",
      "  c d m",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_R()
{
   static CharEntry entry = {
      "       ",
      " b   c ",
      "      d",
      "       ",
      "      e",
      " gi  f ",
      "       ",
      "       ",
      "       ",
      " a    j",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_S()
{
   static CharEntry entry = {
      "       ",
      "  j  k ",
      " i    l",
      "       ",
      " h     ",
      "  g  f ",
      "      e",
      "       ",
      " a    d",
      "  b  c ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_T()
{
   static CharEntry entry = {
      "       ",
      "  b d a",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "    e  ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_U()
{
   static CharEntry entry = {
      "       ",
      " a    f",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      " b    e",
      "  c  d ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_V()
{
   static CharEntry entry = {
      "       ",
      " a    d",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "   bc  ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_W()
{
   static CharEntry entry = {
      "       ",
      " a    f",
      "       ",
      "       ",
      "       ",
      "   cd  ",
      "       ",
      "       ",
      "       ",
      " b    e",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_X()
{
   static CharEntry entry = {
      "       ",
      " a    e",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      " d    b",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_Y()
{
   static CharEntry entry = {
      "       ",
      "  c   C",
      "       ",
      "       ",
      "       ",
      "    b  ",
      "       ",
      "       ",
      "       ",
      "    a  ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_Z()
{
   static CharEntry entry = {
      "       ",
      " a    b",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      " c    d",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_a()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "       ",
      "  d  c ",
      "      b",
      "  g   f",
      " h    l",
      " i     ",
      "  j k a",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_b()
{
   static CharEntry entry = {
      "       ",
      " b     ",
      "       ",
      "       ",
      "   e f ",
      "      g",
      " d     ",
      " k     ",
      "      h",
      " a j i ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_c()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "       ",
      "  f  g ",
      " e    h",
      "       ",
      "       ",
      " d    a",
      "  c  b ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_d()
{
   static CharEntry entry = {
      "       ",
      "      b",
      "       ",
      "       ",
      "  i j  ",
      " h     ",
      "      k",
      "      d",
      " g     ",
      "  f e a",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_e()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "       ",
      "  f  g ",
      " e    h",
      " j    i",
      "       ",
      " d    a",
      "  c  b ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_f()
{
   static CharEntry entry = {
      "       ",
      "   c d ",
      "  b   e",
      "       ",
      "       ",
      "       ",
      " g   h ",
      "       ",
      "       ",
      "  a    ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_g()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "  n m M",
      " o   l ",
      " p   k ",
      "  i j  ",
      " h     ",
      "  ga b ",
      " f    c",
      "  e  d ",
   };

   return(&entry);
}

static CharEntry *letter_h()
{
   static CharEntry entry = {
      "       ",
      " b     ",
      "       ",
      "       ",
      "       ",
      "  e  f ",
      " d    g",
      "       ",
      "       ",
      " a    h",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_i()
{
   static CharEntry entry = {
      "       ",
      "    h  ",
      "    i  ",
      "       ",
      "   fe  ",
      "       ",
      "       ",
      "       ",
      "       ",
      "  a d b",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_j()
{
   static CharEntry entry = {
      "       ",
      "      j",
      "      i",
      "       ",
      "    g f",
      "       ",
      "       ",
      "       ",
      " a     ",
      " b    e",
      "  c  d ",
   };

   return(&entry);
}

static CharEntry *letter_k()
{
   static CharEntry entry = {
      "       ",
      "  b    ",
      "       ",
      "      f",
      "       ",
      "       ",
      "  e    ",
      "       ",
      "       ",
      "  a   d",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_l()
{
   static CharEntry entry = {
      "       ",
      "   fe  ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "       ",
      "  a d b",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_m()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "       ",
      "  bc E ",
      "    d F",
      "       ",
      "       ",
      "    e  ",
      "  a   G",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_n()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "       ",
      " b e f ",
      "  d   g",
      "       ",
      "       ",
      "       ",
      " a    h",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_o()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "  h  g ",
      " i    f",
      "       ",
      " a     ",
      " j     ",
      " b    e",
      "  c  d ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_p()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      " b e f ",
      "      g",
      " d     ",
      "  k   h",
      "   j i ",
      "       ",
      "       ",
      " a     ",
   };

   return(&entry);
}

static CharEntry *letter_q()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "  f e b",
      " g     ",
      "      d",
      " h   k ",
      "  i j  ",
      "       ",
      "       ",
      "      a",
   };

   return(&entry);
}

static CharEntry *letter_r()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      " c C D ",
      "  b   E",
      "       ",
      "       ",
      "       ",
      "       ",
      "  a    ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_s()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "       ",
      "  h  i ",
      " g    j",
      " f     ",
      "      e",
      " a    d",
      "  b  c ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_t()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "  e    ",
      " g  h  ",
      "       ",
      "       ",
      "       ",
      "       ",
      "  d   a",
      "   c b ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_u()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "       ",
      " h    b",
      "       ",
      "       ",
      "      d",
      " g     ",
      "  f e a",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_v()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "       ",
      "  a   c",
      "       ",
      "       ",
      "       ",
      "       ",
      "    b  ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_w()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "       ",
      "  a   e",
      "       ",
      "    c  ",
      "       ",
      "       ",
      "   b d ",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_x()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "       ",
      " e    b",
      "       ",
      "       ",
      "       ",
      "       ",
      " a    d",
      "       ",
   };

   return(&entry);
}

static CharEntry *letter_y()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "       ",
      " k    a",
      "       ",
      "      g",
      " j     ",
      "  i h  ",
      " e    b",
      "  d  c ",
   };

   return(&entry);
}

static CharEntry *letter_z()
{
   static CharEntry entry = {
      "       ",
      "       ",
      "       ",
      "       ",
      " d    c",
      "       ",
      "       ",
      "       ",
      "       ",
      " b    a",
      "       ",
   };

   return(&entry);
}

static CharEntry *getCharEntry(char c)
{
   CharEntry *ptr = letter_space();

   switch(c)
   {
      case 'A': ptr = letter_A(); break;
      case 'B': ptr = letter_B(); break;
      case 'C': ptr = letter_C(); break;
      case 'D': ptr = letter_D(); break;
      case 'E': ptr = letter_E(); break;
      case 'F': ptr = letter_F(); break;
      case 'G': ptr = letter_G(); break;
      case 'H': ptr = letter_H(); break;
      case 'I': ptr = letter_I(); break;
      case 'J': ptr = letter_J(); break;
      case 'K': ptr = letter_K(); break;
      case 'L': ptr = letter_L(); break;
      case 'M': ptr = letter_M(); break;
      case 'N': ptr = letter_N(); break;
      case 'O': ptr = letter_O(); break;
      case 'P': ptr = letter_P(); break;
      case 'Q': ptr = letter_Q(); break;
      case 'R': ptr = letter_R(); break;
      case 'S': ptr = letter_S(); break;
      case 'T': ptr = letter_T(); break;
      case 'U': ptr = letter_U(); break;
      case 'V': ptr = letter_V(); break;
      case 'W': ptr = letter_W(); break;
      case 'X': ptr = letter_X(); break;
      case 'Y': ptr = letter_Y(); break;
      case 'Z': ptr = letter_Z(); break;
      case 'a': ptr = letter_a(); break;
      case 'b': ptr = letter_b(); break;
      case 'c': ptr = letter_c(); break;
      case 'd': ptr = letter_d(); break;
      case 'e': ptr = letter_e(); break;
      case 'f': ptr = letter_f(); break;
      case 'g': ptr = letter_g(); break;
      case 'h': ptr = letter_h(); break;
      case 'i': ptr = letter_i(); break;
      case 'j': ptr = letter_j(); break;
      case 'k': ptr = letter_k(); break;
      case 'l': ptr = letter_l(); break;
      case 'm': ptr = letter_m(); break;
      case 'n': ptr = letter_n(); break;
      case 'o': ptr = letter_o(); break;
      case 'p': ptr = letter_p(); break;
      case 'q': ptr = letter_q(); break;
      case 'r': ptr = letter_r(); break;
      case 's': ptr = letter_s(); break;
      case 't': ptr = letter_t(); break;
      case 'u': ptr = letter_u(); break;
      case 'v': ptr = letter_v(); break;
      case 'w': ptr = letter_w(); break;
      case 'x': ptr = letter_x(); break;
      case 'y': ptr = letter_y(); break;
      case 'z': ptr = letter_z(); break;
   }

   return(ptr);
}

static int findLetter(CharEntry *ptr, char theLetter, int *row, int *column)
{
   for(int i = 0; i < TABLE_HEIGHT; i ++)
   {
      for(int j = 0; j < TABLE_WIDTH; j ++)
      {
         if((*ptr)[i][j] == theLetter)
         {
            *row    = (TABLE_HEIGHT - 1) - i;
            *column = j;

            return(1);
         }
      }
   }

   return(0);
}

static double distance(double x0, double y0, double x1, double y1)
{
   return(
      sqrt(
         (x0 - x1) * (x0 - x1) +
         (y0 - y1) * (y0 - y1)
      )
   );
}

static double lineDistance(
   double x, double y,
   double x0, double y0,
   double x1, double y1
)
{
   double m = distance(x0, y0, x1, y1);

   double u = ((x - x0) * (x1 - x0) + (y - y0) * (y1 - y0)) / (m * m);

   if(u < 0 || u > 1)
      return(-1);

   double xIntersect = x0 + u * (x1 - x0);
   double yIntersect = y0 + u * (y1 - y0);

   return(distance(x, y, xIntersect, yIntersect));
}

/*****************************************************************************
 * Local Structure Definitions
 *****************************************************************************/

struct Point
{
   double x;
   double y;
};

struct LineSegment
{
   Point start;
   Point end;
};

struct LineSegmentEntry
{
   LineSegment segment;
   LineSegmentEntry *next;
};

/*****************************************************************************
 * Declaration of class: SegmentList
 *****************************************************************************/

class SegmentList
{
   public:
      SegmentList();
      ~SegmentList();

      void append(LineSegment *entry);
      void dump() const;
      int  size() const;
      LineSegmentEntry *getHead() const;

   private:
      SegmentList(const SegmentList &);
      SegmentList &operator=(const SegmentList &);

      LineSegmentEntry *mHead;
      int mSize;
};

/*****************************************************************************
 * Definition of class: SegmentList
 *****************************************************************************/

SegmentList::SegmentList() :
   mHead(0), mSize(0)
{
}

SegmentList::~SegmentList()
{
   LineSegmentEntry *ptr = mHead;

   while(ptr)
   {
      LineSegmentEntry *p = ptr;
      ptr = ptr->next;

      DDELETE(p);
   }

   mHead = 0;
}

void SegmentList::append(LineSegment *entry)
{
   LineSegmentEntry *newEntry = 0;
   DNEW(newEntry, LineSegmentEntry());

   newEntry->next    = 0;
   newEntry->segment = *entry;

   if(!mHead)
   {
      mHead = newEntry;
   }
   else
   {
      LineSegmentEntry *ptr = mHead;

      while(ptr->next)
         ptr = ptr->next;

      ptr->next = newEntry;
   }

   mSize++;
}

void SegmentList::dump() const
{
   LineSegmentEntry *ptr = mHead;

   while(ptr)
   {
      printf(
         "[%f, %f] => [%f, %f]\n",
         ptr->segment.start.x, ptr->segment.start.y,
         ptr->segment.end.x, ptr->segment.end.y
      );

      ptr = ptr->next;
   }
}

int SegmentList::size() const
{
   return(mSize);
}

LineSegmentEntry *SegmentList::getHead() const
{
   return(mHead);
}

void getSegmentList(SegmentList &list, char letter)
{
   CharEntry *ptr   = getCharEntry(letter);
   char c           = 'a';
   int row          = 0;
   int column       = 0;
   int visited[255] = { 0 };


   // Start with the capital letters

   for(c = 'A'; c < 'Z'; c ++)
   {
      // Try to find the current letter

      if(findLetter(ptr, c, &row, &column))
      {
         LineSegment segment;

         segment.start.x = (double)column;
         segment.start.y = (double)row;

         if(findLetter(ptr, c + 1, &row, &column))
         {
            segment.end.x = (double)column;
            segment.end.y = (double)row;

            list.append(&segment);

            visited[c + 1] = 1;
         }
      }
   }

   // Now, the lowercase letters

   for(c = 'a'; c < 'z'; c ++)
   {
      // Try to find the current letter

      if(findLetter(ptr, c, &row, &column))
      {
         LineSegment segment;

         segment.start.x = (double)column;
         segment.start.y = (double)row;

         // Can we find the next letter?

         if(findLetter(ptr, c + 1, &row, &column))
         {
            // Ok, so complete the current segment

            segment.end.x = (double)column;
            segment.end.y = (double)row;

            list.append(&segment);
         }

         // Ok, how about the next letter as a capital letter?

         char cUpper = toupper(c + 1);

         if(!visited[cUpper] && findLetter(ptr, cUpper, &row, &column))
         {
            segment.end.x = (double)column;
            segment.end.y = (double)row;

            list.append(&segment);
         }
      }
   }

   // Now the capital letters

   for(c = 'A'; c < 'Z'; c ++)
   {
      // Try to find the current letter

      if(findLetter(ptr, c, &row, &column))
      {
         LineSegment segment;

         segment.start.x = (double)column;
         segment.start.y = (double)row;

         if(findLetter(ptr, c + 1, &row, &column))
         {
            segment.end.x = (double)column;
            segment.end.y = (double)row;

            list.append(&segment);
         }
      }
   }
}

/*****************************************************************************
 * Definition of class: TextIntersectNode
 *****************************************************************************/

TextIntersectNode::TextIntersectNode(
   const char *text,
   const ComplexNode *originPtr,
   const DoubleNode  *heightPtr,
   const DoubleNode  *thicknessPtr,
   const ComplexNode *pointPtr
) :
   mText(0),
   mValues(0),
   mNumValues(0),
   mOriginPtr(originPtr),
   mHeightPtr(heightPtr),
   mThicknessPtr(thicknessPtr),
   mPointPtr(pointPtr)
{
   DNEW(mText, char[strlen(text) + 1]);
   strcpy(mText, text);

   mNumValues = strlen(text);

   DNEW(mValues, SegmentList *[mNumValues]);

   for(int i = 0; i < mNumValues; i ++)
   {
      SegmentList *ptr = 0;
      DNEW(ptr, SegmentList());

      getSegmentList(*ptr, text[i]);

      mValues[i] = ptr;
   }
}

TextIntersectNode::~TextIntersectNode()
{
   DADELETE(mText);

   for(int i = 0; i < mNumValues; i ++)
      DDELETE(mValues[i]);

   DADELETE(mValues);

   DDELETE(mOriginPtr);
   DDELETE(mHeightPtr);
   DDELETE(mThicknessPtr);
   DDELETE(mPointPtr);
}

double TextIntersectNode::evaluate() const
{
   double height   = mHeightPtr->evaluate();
   dcomplex origin = mOriginPtr->evaluate();
   double scale    = height / TABLE_HEIGHT;
   double step     = scale * TABLE_WIDTH;

   double xOrigin = __REAL(origin);
   double yOrigin = __IMAG(origin);

   double thick = mThicknessPtr->evaluate();
   dcomplex point = mPointPtr->evaluate();
   double x       = __REAL(point);

   if(x < xOrigin)
      return(-1);

   if(x > xOrigin + mNumValues * step + thick)
      return(-1);

   double y = __IMAG(point);

   if(y < yOrigin - thick)
      return(-1);

   if(y > yOrigin + height + thick)
      return(-1);

   for(int i = 0; i < mNumValues; i ++)
   {
      LineSegmentEntry *entry = NULL;

      // Doing the lines first, then the joints tends
      // to look a bit better so lets do that ;-)

      for(entry = mValues[i]->getHead(); entry; entry = entry->next)
      {
         double xStart = xOrigin + scale * entry->segment.start.x;
         double yStart = yOrigin + scale * entry->segment.start.y;

         double xEnd   = xOrigin + scale * entry->segment.end.x;
         double yEnd   = yOrigin + scale * entry->segment.end.y;

         double d = lineDistance(x, y, xStart, yStart, xEnd, yEnd);

         if(d >= 0 && d <= thick)
            return(d / thick);
      }

      for(entry = mValues[i]->getHead(); entry; entry = entry->next)
      {
         double xStart = xOrigin + scale * entry->segment.start.x;
         double yStart = yOrigin + scale * entry->segment.start.y;

         double d = distance(x, y, xStart, yStart);

         if(d <= thick)
            return(d / thick);

         double xEnd = xOrigin + scale * entry->segment.end.x;
         double yEnd = yOrigin + scale * entry->segment.end.y;

         d = distance(x, y, xEnd, yEnd);

         if(d <= thick)
            return(d / thick);
      }

      xOrigin += step;
   }

   return(-1);
}

ostream &TextIntersectNode::print(ostream &out) const
{
   out << "text_intersect(" << mText << ", ";
   mOriginPtr->print(out);
   out << ", ";
   mHeightPtr->print(out);
   out << ", ";
   mThicknessPtr->print(out);
   out << ", ";
   mPointPtr->print(out);
   out << ")";

   return(out);
}
