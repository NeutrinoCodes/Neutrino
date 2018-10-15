/// @file

#ifndef font_hpp
#define font_hpp

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "FONT" CLASS ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  /// Font (Hershey simplex vector font) vertex coordinates.
  /// Format: {x1, y1, x2, y2, x3, y3, ... , xn, yn}
  /// xn, yn = 2D coordinates of each single font vertex.
  /// Later on, in OpenGL implementation, each two consecutive verteces are
  /// connected by a line segment.
  /// If two consecutive segments have to be joined together, the coordinates of
  /// the second vertex of the first segment are equal to the coordinates of the
  /// first vertex of the second segment.
  /// All Ascii characters from 33 to 126 have been represented in the single
  /// "font_vertex" array.
  /// The "font_index" array gives the offset at which the first vertex
  /// coordinates of each Ascii character in the "font_vertex" array starts.
  /// The "font_numdata" array contains the total number of integer data
  /// describing each Ascii character in the font.
  /// The "font_width" array contains the width of each Ascii character in the
  /// font.

  #define ASCII_33 33
  #define ASCII_126 126
  #define ASCII_SCALE 0.01
  #define ASCII_SPACE_LITTLE 4
  #define ASCII_SPACE_BIG 16

  class font
  {
    private:

    public:
      int font_vertex[3646];                                                    // Font vertex coordinates.
      int font_index[94];                                                       // Font vertex indexes.
      int font_numdata[94];                                                     // Font vertex # of data.
      int font_width[94];                                                       // Font glyph width.

            font();
      void  init();                                                             // Font initialization.
            ~font();
  };

#endif
