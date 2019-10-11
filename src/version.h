/*****************************************************************************
 * Revision History
 *
 * August 12, 1999 - Version 1.0 - initial coding
 *
 * August 22, 1999 - Version 1.1
 *                 - When a new window is opened (via "new" or by zooming)
 *                   the sizes of the text and image portions of our splitter
 *                   now match the corresponding sizes in the original window
 *                 - Zooming is now allowed on an incompletely drawn image.
 *                   (zooming is now only disallowed while the image is
 *                   actively being drawn)
 *                 - Replaced "Stop Drawing" button at the bottom with a
 *                   button on our tool bar
 *                 - Area formerly occupied by the "Stop Drawing" now
 *                   displays the line and column number of the cursor
 *                   in the text window
 *                 - When saving an image, if the selected name does not
 *                   end in 'IMAGE_EXTENSION', the extension is now
 *                   automatically appended
 *
 * August 22, 1999 - Version 1.1.1
 *                 - Implemented persistent state for directory used when
 *                   opening a .jfd file
 *                 - Implemented persistent state for the application
 *                   width and height
 *
 * August 23, 1999 - Version 1.1.2
 *                 - Revamped persistence, moved state information into
 *                   its own class "State", also added the zoom color
 *                   and the sizes of the 2 splitter windows to the list
 *                   of things we store persistently
 *
 * August 24, 1999 - Version 1.1.3
 *                 - Change filename/caption when user does a 'saveText'
 *                 - When saving text, if the selected name does not end in
 *                   'TEXT_EXTENSION',  the extension is now automatically
 *                   appended
 *                 - Fixed a bug that caused the program to dump core
 *                   (sometimes) when 'repeat' was used within the
 *                   'COLOR' section
 *
 * August 30, 1999 - Version 1.1.4
 *                 - Implemented zoom out functionality
 *
 * September 6, 1999 - Version 1.1.5
 *                     Reworked persistence implementation to save all
 *                     attributes as they change.
 *
 * September 8, 1999 - Version 1.1.6
 *                     Added zoom in options, removed the 'show this dialog'
 *                     option from the zoom out options dialog
 *
 * September 11, 1999 - Version 1.1.7
 *                      Fixed bug in zoom in options, added shortcuts to
 *                      all menu options, added 'edit' menu
 *
 * September 12, 1999 - Version 1.1.8
 *                      Added ability to select font size
 *
 * September 12, 1999 - Version 1.1.9
 *                      Disabled draw hot key when image is already being
 *                      drawn
 *
 * September 14, 1999 - Version 1.2.0
 *                      Previously, the mapping section's pixel size fields
 *                      only allowed: a * b or a / b, we now allow any
 *                      number of terms using * or /.
 *                      Allow both 'abs' and 'fabs',
 *                      allow both 'mod' and 'fmod'
 *
 * September 19, 1999 - Version 1.2.1
 *                      If drawing was already being done and you
 *                      changed the text (or opened a new .jfd file)
 *                      the draw button would (wrongly) become enabled
 *                      allowing drawing.  Fixed this bug.
 *
 * September 21, 1999 - Version 1.2.2
 *                      Fixed bug in persist.cpp that caused g++ 2.9.5 to
 *                      not compile that module (casting const char * to
 *                      char *, around line 595)
 *
 * October 10, 1999   - Version 1.2.3
 *                      Fixed bug where the mouse was pressed while drawing
 *                      and released after drawing causing the rectangle to
 *                      be drawn in unconstrained zoom mode (even though
 *                      constrained zoom mode had been selected)
 * 
 * October 22, 1999   - Version 1.2.4
 *                      Added 'sum_of_squares' attribute (identical to
 *                      magnitude but without the sqrt).
 *
 * October 23, 1999   - Version 1.3.0
 *                      Change all attributes into functions
 *                      (so we now do: real(z) instead of z.real).
 *                      Allow complex and real to be used in places where
 *                      there were previously disallowed (we can now
 *                      do [z.real, c.complex].
 *                      Add 'complex' operator for disambiguation when
 *                      the result is a double, that change allows things
 *                      like this: z = c + complex(fmod($count, 2));
 *                      Added if/else logic to the formula and color
 *                      selection sections.
 *                      Arbitrary mathematical expressions are now allowed 
 *                      in the mapping sections (no function calls, but
 *                      any combination of +, -, *, /, () are allowed)
 *                      Changed from timer-based drawing to
 *                      qApp->processEvents as this allows us to always
 *                      be able to break out when the formula has an
 *                      an infinite loop.
 * October 26, 1999   - Version 1.3.1 - Attempt to fix bug where the
 *                      program crashes if a window is closed while drawing
 *                      is active.
 *
 * October 30, 1999   - Version 1.4.0
 *                      Changed grammar to allow the 'colors' section
 *                      to be optional, color assignment now done via
 *                      set_color(index) or set_color(r, g, b).  Also
 *                      introduced second type of variable (a double)
 *                      that is designated by a '$' before its name, this
 *                      means that '$current' became just 'current' while
 *                      $count (being a double) stayed $count.  Also added
 *                      the ability for any statement to appear before, during
 *                      or after the while loop.  Lastly, shorter variants
 *                      of the complex attributes (imaginary, magnitude, etc.)
 *                      are now allowed.  The shortened forms are listed
 *                      in: lib/fractal/AttributeDoubleNode.cpp
 *
 * November 13, 1999 - Version 1.4.1
 *                     Added support for tan, cot, sec, csc
 *                     (complex functions) and cot, sec, csc (double functions)
 * 
 * November 15, 1999 - Version 1.4.2
 *                     Split 'save image' into:
 *                        (a) generate from text and
 *                        (b) use current image
 *                     to allow the tif file to be optionally generated from
 *                     the onscreen image.  Fixed bug where program would
 *                     incorrectly believe the text still needed saving
 *                     despite the fact that the text had been saved.
 *
 * November 15, 1999 - Version 1.4.3
 *                     When a window is being closed (via 'close' or 'quit')
 *                     and the 'text has not been saved' dialog appears, it
 *                     now contains a 'cancel' option to allow the user to
 *                     abort the close altogether.  Also, previously on unix
 *                     when you drew a smaller image on top of a larger one
 *                     the background wasn't properly erased (it is now).
 *                     Lastly, previously the quality of the saved image
 *                     when using the 'use current image' option under
 *                     'save image' was dependent upon the depth of the
 *                     monitor - this has been fixed, the output is now
 *                     always based upon the full 24 bit data.
 *
 * November 23, 1999 - Version 1.4.4
 *                     Fixed some documentation bugs, fixed bug related
 *                     to random horizontal bars when the supplied color
 *                     index (or rgb value) was out of bounds (thanks
 *                     to Morgan Larch, mlarch@ix.netcom.com for this fix).
 *                     Moved local class 'Settings' (application.cpp) from
 *                     inside ApplicationWindow::zoomOut to outside that
 *                     function as egcs-2.91.66 apparently doesn't care for
 *                     classes defined within methods., thanks to Arne
 *                     Schmitz (arne.schmitz@gmx.net) for the heads up
 *                     on this one.
 *
 * December 14, 2000 - Version 1.4.5
 *                     Added support for: +=, -=, *=, /= for both complex
 *                     and double variables.  Added support for a general
 *                     looping construct 'loop' (exactly like 'while' except
 *                     that you can use it anywhere and it doesn't set
 *                     $count)
 *
 * January 14, 2001 - Version 1.4.6
 *                    Added support for 'get_sin_color' function which
 *                    generates a value between 0 and 255 using steve
 *                    ferguson's sin coloring algorithm.
 *
 * January 15, 2001 - Version 1.4.7
 *                    - Removed 'loop' construct (added in 1.4.5) and
 *                      replaced it with a much more general 'for' loop
 *                      construct.  This isn't a compatibility issue
 *                      since the last public version was 1.4.4
 *                    - Added two now boolean constructs: true and false
 *                      to allow things like: if(true) { ... }.
 *                    - Added a null statement allowing things like:
 *                      for(null;true;null) { null; } (assuming you
 *                      want an infinite loop ;-)
 *                    - Added support for undo and redo
 *                    - Added a 'mapping reset' feature to reset the
 *                      mapping section to sensible defaults
 *                    - Added double size and half size menu options
 *
 * January 16, 2001 - Version 1.4.8
 *                    - added 'elseif' construct
 *                    - added hot keys for Yes/No/Cancel dialogs
 *
 * January 17, 2001 - Version 1.4.9
 *                    - added support for ++ and --
 *                    - fixed a few small memory leaks
 *                    - added check for a condition that sometimes occurs
 *                      on windows when fractorama has been associated with
 *                      the .jfd extension but when opened, argv[0] does
 *                      contain the path to fractorama (this crashed the
 *                      program).
 *                    - now allow '%' to be used as an alternative to
 *                      mod/fmod (doubles only) and '^' as an alternative
 *                      to pow (doubles and complex)
 *                    - added tanh(complex)
 *                    - fixed a problem where when [0, 0] was raised to
 *                      a power [nan, nan] resulted (for details see the notes
 *                      in TwoArgFunctionComplexNode.cpp)
 *                    - added support for a 'print' function which can write
 *                      literals/double variables/complex variables to a log
 *                      file or stdout
 *                    - fixed sporadic black horizontal lines in drawing
 *                      area problem.
 *                    - added menu option for 10% smaller / 10% larger
 *                    - changed command-line generation option to output
 *                      percentage complete after each scanline rather
 *                      than '.'
 * January 24, 2001 - Version 1.5.0
 *                    - added support for "regions" which allow for very
 *                      sophisticated orbit trap areas to be constructed
 *                      and used.  The region can be used with the 'inside'
 *                      function to see if a point is within the trap.
 *                    - added support for '!' with boolean expressions
 * January 30, 2001 - Version 1.5.1
 *                    - added support for 'rotate' function
 *                    - added a new region 'r_spoly' (simple polygon).
 *                    - fixed a (long present) bug in
 *                      AttributeDoubleNode::radians and
 *                      AttributeDoubleNode::degrees (angles were offset
 *                      by pi).  Since this bug has been around for so long
 *                      I added attributes: 'old_deg/old_degrees' and
 *                     'old_rad/old_radians' to allow old .jfd files to be
 *                      quickly repaired
 *                    - added search and replace capabilities
 *                    - added 'showMatch' capabilities so that you can
 *                      quickly locate the matching '(', '{' or '[' when
 *                      your cursor is on a ')', '}', ']' (and vice versa)
 * February 6, 2001   - Version 1.5.1-A, fixed bug in r_spoly where
 *                      rotated polygons would end up being distorted
 * February 19, 2001  - Version 1.5.1-B, added setprecision(10) to
 *                      ComplexVariablePrintArg.cpp and
 *                      DoubleVariablePrintArg.cpp for improved output
 *                      precision.  Also added 6 new pseudo variables:
 *                      $mapping_x_start,  $mapping_y_start,
 *                      $mapping_x_end,    $mapping_y_end,
 *                      $mapping_x_pixels, $mapping_y_pixels
 *                      to allow formula files to access the
 *                      values in their 'mapping' section
 * February 23, 2001  - Version 1.5.1-C, moved the mapping stuff to
 *                      its own pulldown menu - also while we already had
 *                      the ability to change the image size (1/2 size,
 *                      double size, 10% larger/smaller), I've now added 
 *                      equivalent behavior for the complex coordinates
 *                      portion of the mapping section.  Also added
 *                      ability to indent/unindent current line.
 * February 24, 2001  - Version 1.5.1-D, fixed bug in view mapping code
 *                      also added 'factorial' double function and 
 *                      csch, sech, coth double and complex function.
 *                      Also changed 'print' to default to stdout if
 *                      no filename is given (and removed the reserved
 *                      word 'stdout')
 * March 6, 2001      - Version 1.5.1-E, put in check for 'isnan'
 *                      into DoubleVariables.cpp to cause the program to
 *                      produce the same results on linux as it does on
 *                      win32.  Also added 'println' function (just like
 *                      'print' except it automatically appends a newline)
 * June 3, 2001       - Version 1.5.2
 *                      - added support for the following
 *                        complex functions:
 *                           asin, acos, atan, asec, acsc, acot,
 *                           asinh, acosh, atanh, asech, acsch, acoth
 *                      - added a double function 'gamma' to perform
 *                        gamma correction:
 *                           double gamma(color, gammaValue)
 *                        where 0 <= color <= 255 and gammaValue > 0
 *                      - added a new coloring function 'map_color':
 *                           double map_color(value : colors : percentages)
 *                        where 0 <= value <= 1
 *                        colors: a comma separated list of color values
 *                           where 0 <= colorValue <= 255
 *                        percentages: a comma separated list of percentages
 *                           where 0 <= percentage <= 100
 * June 9, 2001       - Version 1.5.3
 *                      - added support for a number of predefined useful
 *                        math constants:
 *                           $m_e        e
 *                           $m_log2e    log_2 e
 *                           $m_log10e   log_10 e
 *                           $m_ln2      log_e 2
 *                           $m_ln10     log_e 10
 *                           $m_pi       pi
 *                           $m_pi_2     pi/2
 *                           $m_pi_4     pi/4
 *                           $m_1_pi     1/pi
 *                           $m_2_pi     2/pi
 *                           $m_2_sqrtpi 2/sqrt(pi)
 *                           $m_sqrt2    sqrt(2)
 *                           $m_sqrt1_2  1/sqrt(2)
 *                      - added support for a similar construct to C's
 *                        ternary operator (condition ? value1 : value2)
 *                        In Fractorama's scripting language the ternary
 *                        construct must be surrounded with '{}'.  The new
 *                        construct works both doubles and complex types
 *                        as in:
 *                           z  = {$count % 2 == 0 ? z ^ 2 : z ^ 3 };
 *                           $x = sin(10 * {$a > $b ? $a : $b});
 * June 14, 2001       - Version 1.5.4
 *                      - fixed bug where spurious '\n' would be added to
 *                        the formula file each time the mapping section
 *                        is programmatically altered (i.e. all the options
 *                        under the 'Mapping' pulldown)
 *                      - fixed bug where cursor jumped to the first line
 *                        whenever the mapping section is programmatically
 *                        altered
 *                      - added support for (previously missing) double
 *                        functions:
 *                           asec, acsc, acot, acosh, asinh, atanh,
 *                           asech, acsch, acoth
 *                      - fixed incorrect formula for (complex) atan
 * June 16, 2001       - Version 1.5.5
 *                      - implemented html help browser
 * June 22, 2001       - Version 1.5.6
 *                      - implemented chained assignment for both double
 *                        and complex variables so you can now do:
 *                           $a = $b  = $c = 0;
 *                           a =   b *= [1, 2];
 *                      - implemented 'break' and 'continue' statements
 *                      - fixed up the grammar in fractal.yacc to handle
 *                        all double => complex automatic conversions
 *                        (there were a few that didn't work such as
 *                        z = 2 % 3).  Additionally, the grammar
 *                        cleanup confers some efficiency benefits as
 *                        well as:
 *                           z = 1 + 2
 *                        is now parsed as:
 *                           z = 1 + 2
 *                        rather than
 *                           z = [1, 0] + [2, 0]
 *                        as was the case in previous versions.
 *                      - made the surrounding '{' '}' optional for both
 *                        double and complex ternary expressions so you
 *                        can now do:
 *                           z = $count % 2 ? sin(z) : cos(z)
 *                        as well as
 *                           z = { $count % 2 ? sin(z) : cos(z) }
 *                      - made the "before statements" (those before while)
 *                        and that "after statements"  (those after while)
 *                        optional so this is now a valid formula section:
 *                           formula
 *                           {
 *                              while($count < 20)
 *                              {
 *                                 z = z ^ 2 + c;
 *                              }
 *                           }
 *                      - made it possible for the body of a: for, while,
 *                        if, elseif, else statement to have zero statements
 *                        so these are now legal:
 *                           for($i = 0; $i < 10; $i ++) {}
 *                           while($count < 10) {}
 *                           if($i < 10) {} elseif($i < 20) {} else {}
 *                        The '{}' are still required since they allow us
 *                        to avoid the "dangling else" problem entirely.
 * June 23, 2001       - Version 1.5.7
 *                      - Added mapping menu options to allow panning
 *                        the view left/right/up/down 10%/50%/100%.
 *                        (including associated hot keys)
 *                      - Fixed some problems with chained assignment:
 *                        when the rightmost term was one of:
 *                           ++x, x++, --x, x--,
 *                           x += value, x -= value, x *= value, x /= value
 *                        in these cases the non rightmost terms would
 *                        be incorrectly given the value 1 (for ++/--)
 *                        or 'value" (x += value, x -= value, etc.).
 *                        Also, made sure that assignment (chained or
 *                        otherwise) works properly in all places where
 *                        a double_expression or complex_expression
 *                        is allowed such as:
 *                           $x = sin($y = $z = 0);
 *                           if(ssq(z = [1, 2]) > 4) { // ... }
 *                      - Fixed up the help browser to do a "page down"
 *                        when the space bar is pressed.
 *                      - Removed dependency on QALE, there were only two
 *                        (fairly simple) dialogs that used it and
 *                        reworking them to use Qt's layout managers
 *                        trimmed 80kb off the binary.
 *                      - Made it legal for the initization and increment
 *                        statements in a for statement to be empty
 *                        as in:
 *                           for(;true;) {}
 *                        The condition portion of a for statement, however
 *                        is still required to be non-empty.
 * July 5, 2001        - Version 1.5.8
 *                      - Implemented xmirror/ymirror options (mapping
 *                        pulldown menu)
 *                      - Added double functions: deg2rad(degrees) and
 *                        rad2deg(radians)
 *                      - Fixed problem where program would exit if unable
 *                        to open the tiff file to which it was attempting
 *                        to save the image
 *                      - support "elif" in addition to "elseif"
 *                      - fixed bug in handling of the ternary operator:
 *                           (condition ? first : second)
 *                        was being interpreted as:
 *                           (condition ? second : first) [doh!]
 *                      - revamped chained assignment (again) to
 *                        address scenarios like:
 *                           if(($a = $b) < 0 || ($a = $c) < 0) {}
 *                        which were being handled wrongly before
 *                      - added support for antialiased output including
 *                        a command-line switch '-a' and an option
 *                        dialog to set/store the choice persistently
 *                      - added support for having the program remember
 *                        the most recent directory to which a file was
 *                        saved
 *                      - added support for three functions:
 *                           get_entry_red(index)
 *                           get_entry_green(index)
 *                           get_entry_blue(index)
 *                        these functions return the red, green or blue
 *                        component of a selected color table entry (index)
 * Aug 18, 2001        - Version 1.5.9 - a
 *                       - fixed bug related to use of 'continue' within
 *                         the main while or within a for loop.  Basically
 *                         if a continue statement was ever executed the
 *                         'doContinue' flag would remain wrongly set for
 *                         all subsequent passes through the loop rather
 *                         than being reset for each pass.
 * Aug 21, 2001        - Version 1.5.9 - b
 *                       - fixed bug where ^Z (the hot key) would allow
 *                         zooming even though there wasn't a zoom rectangle
 *                         currently active
 * Jan 18, 2002        - Version 1.6.0
 *                       - changed VERSION in this file to include
 *                         program name added support for set_color_hsv
 * Jan 24, 2002        - Version 1.6.1
 *                       - added support for new predefined variables
 *                         $current_row and $current_column
 * Feb 17, 2002        - Version 1.6.2
 *                       - ported code to Qt 3.0.1 and g++ 2.96
 * Feb 19, 2002        - Version 1.6.3
 *                       - ported code to Qt 3.0.2, only change involved
 *                         changing the mechanism in Application::loadFile
 *                         used to read the .jfd file and put it into
 *                         the QMultiLineEdit, we now use 'theStream.read()'
 *                         as that method preserves empty lines whereas
 *                         the original line-by-line/append method caused
 *                         them to disappear with Qt-3.0.x
 * Jun 18, 2002        - Version 1.6.4
 *                       - added support for new functions:
 *                         double bernoulli(double), double euler(double)
 *                         the return the Nth bernoulli and euler numbers
 *                         respectively
 *                       - built under Qt 3.0.4 (no porting required)
 * Feb 1, 2003         - Version 1.6.5
 *                       - added support for new functions:
 *                         double bit_and(double, double)
 *                         double bit_or(double, double)
 *                         double bit_xor(double, double)
 *                         double bit_shl(double, double)
 *                         double bit_shr(double, double)
 *                         double bit_not(double)
 *                       - added support for hex integers
 *                         0x{value} or 0X{value}
 *                       - changed 'print' and 'println' to use '.' instead
 *                         of '+' for chaining items to print.  This allows
 *                         us to mix string literals with any double or
 *                         complex expression to print.
 * Mar 27, 2003         - Version 1.6.6
 *                        - Fixed bug in set_color_hsv, the parameters
 *                          were being interpreted backwards (i.e. when
 *                          you passed h, s, v they were being processed
 *                          as v, s, h)
 *                        - Added support for new functions:
 *                          double get_hsv_red(h, s, v)
 *                          double get_hsv_green(h, s, v)
 *                          double get_hsv_blue(h, s, v)
 * Oct 23, 2003         - Version 1.6.7
 *                        - added function text_intersect
 *                        - added function get_cos_color
 *                        - fixed bug involving 'continue' inside for loops,
 *                          previously use of continue prevented the for
 *                          loop's increment statement from being executed
 *                        - implemented 'switch' statement
 *                        - try to make syntax errors move you to
 *                          the correct column for the error instead
 *                          of just positioning the cursor at the start
 *                          of the line
 *                        - Reworked the way complex and double variables
 *                          are get and set to use direct pointers rather
 *                          than requiring method calls.  This has
 *                          produced speed improvements of up to 25%
 *                          in some of my tests of the command-line
 *                          version.  The gui version has also benefitted
 *                          but not to such a dramatic extent.
 *                        - fixed bug in TiffWriter where anti-aliased output
 *                          could produce Segmentation Faults when the
 *                          width of the image was an odd number of pixels
 *                        - added --size=WxH command-line option for
 *                          the non-gui version to allow image size to
 *                          be specified when the program is invoked.
 * Oct 11, 2007         - Version 1.7.0
 *                        - switched to using ostringstream instead
 *                          of strstream
 *                        - implemented dmemory.h for all new/delete calls
 * Dec 12, 2007         - Version 1.7.1
 *                        - implemented gradient editor
 *                        - added ability to save/load gradients to editor
 *****************************************************************************/

#define AUTHOR       "John F. Dumas"
#define VERSION      "Fract-O-Rama! - Version 1.7.0, Oct 11, 2007"
