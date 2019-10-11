###############################################################################
# Makefile - designed to work on windows nt and all unix variants
#
# This Makefile assumes:
#
#    (a) You are using gnu make, even if you are on windows nt
#    (b) g++ version >= 2.8.1 on unix
#    (c) MS VC++ version >= 5.0 on windows
###############################################################################

include ../../directories.inc

###############################################################################
# Debug or Release?
###############################################################################

ifeq "${RELEASE}" "1"
   MODE := release
else
   MODE := debug
endif

###############################################################################
# Determine which platform we're on ...
#
# We don't really need to know which unix platform we're on, but save off
# the result in ${PLATFORM} in case we need it for future funkiness
###############################################################################

ifeq "${OS}" "Windows_NT"
   PLATFORM := winnt
else
   PLATFORM := ${shell uname}
endif

LIBRARY := libfractal_${MODE}.a

###############################################################################
# Windows settings ...
###############################################################################

ifeq "${PLATFORM}" "winnt"

   ifeq "${MODE}" "release"
      OPTIMIZE := -O2
   else
      OPTIMIZE := -Zi
   endif

   PLATFORM_INCLUDE  := -I. -I${WINDOWS_VC_INCLUDE}
   CPP               := cl
   WARN              := -W3
   OUT1              :=
   OUT2              := -Fo
   MKLIB             := lib /out:${LIBRARY}
   PLATFORM_CPPFLAGS := -GX -TP
   RM                := del

else

###############################################################################
# Unix settings ...
###############################################################################

   ifeq "${MODE}" "release"
      OPTIMIZE := -O2
   else
      OPTIMIZE := -g
   endif

   CPP   := g++
   WARN  := -W -Wall
   OUT1  := -o
   OUT2  := ${shell echo " "}
   MKLIB := ar ruv ${LIBRARY}
   RM    := rm

endif

###############################################################################
# Platform Independent Settings
###############################################################################

INCLUDE   := ${PLATFORM_INCLUDE}
OUT       := ${OUT1}${OUT2}
CPPFLAGS  := -c ${WARN} ${INCLUDE} ${OPTIMIZE} ${PLATFORM_CPPFLAGS}
LEX       := flex
LEXFLAGS  := -ofractal.lex.c -Pfractal_yy
YACC      := bison
YACCFLAGS := --verbose --defines --output=fractal.yacc.c --name-prefix=fractal_yy

OBJECTS   := AndRegionNode_${MODE}.o                    \
             AssignmentComplexNode_${MODE}.o            \
             AssignmentDoubleNode_${MODE}.o             \
             AttributeDoubleNode_${MODE}.o              \
             BinaryComplexNode_${MODE}.o                \
             BinaryDoubleNode_${MODE}.o                 \
             BooleanNode_${MODE}.o                      \
             BooleanNodeStack_${MODE}.o                 \
             BreakStatement_${MODE}.o                   \
             CircleRegionNode_${MODE}.o                 \
             ColorNode_${MODE}.o                        \
             ColorNodeStack_${MODE}.o                   \
             ColorStack_${MODE}.o                       \
             ColorTable_${MODE}.o                       \
             ColorsColorNode_${MODE}.o                  \
             ComplexAssignmentStatement_${MODE}.o       \
             ComplexNode_${MODE}.o                      \
             ComplexNodeStack_${MODE}.o                 \
             ComplexVariables_${MODE}.o                 \
             ComplexNodePrintArg_${MODE}.o              \
             CompoundStatement_${MODE}.o                \
             CompoundStatementStack_${MODE}.o           \
             ConditionalBooleanNode_${MODE}.o           \
             ConditionalStatement_${MODE}.o             \
             ConstantDoubleNode_${MODE}.o               \
             ContinueStatement_${MODE}.o                \
             Counter_${MODE}.o                          \
             CrossRegionNode_${MODE}.o                  \
             DefineColorNode_${MODE}.o                  \
             RGBSetColorStatement_${MODE}.o             \
             HSVSetColorStatement_${MODE}.o             \
             DoubleAssignmentStatement_${MODE}.o        \
             DoubleNode_${MODE}.o                       \
             DoubleNodeStack_${MODE}.o                  \
             DoubleVariables_${MODE}.o                  \
             DoubleNodePrintArg_${MODE}.o               \
             EllipseRegionNode_${MODE}.o                \
             FalseBooleanNode_${MODE}.o                 \
             FlagStack_${MODE}.o                        \
             ForStatement_${MODE}.o                     \
             Fractal_${MODE}.o                          \
             GenericStack_${MODE}.o                     \
             GetEntryDoubleNode_${MODE}.o               \
             GradientColorNode_${MODE}.o                \
             IndexedSetColorStatement_${MODE}.o         \
             InsideBooleanNode_${MODE}.o                \
             InfiniteLoopCallback_${MODE}.o             \
             LiteralPrintArg_${MODE}.o                  \
             MapColorFunctionDoubleNode_${MODE}.o       \
             MapColorFunctionDoubleNodeStack_${MODE}.o  \
             MixedThreeArgFunctionComplexNode_${MODE}.o \
             NotBooleanNode_${MODE}.o                   \
             NotRegionNode_${MODE}.o                    \
             NullStatement_${MODE}.o                    \
             NumericComplexNode_${MODE}.o               \
             OneArgFunctionComplexNode_${MODE}.o        \
             OneArgFunctionDoubleNode_${MODE}.o         \
             OrRegionNode_${MODE}.o                     \
             PolyRegionNode_${MODE}.o                   \
             PrintArg_${MODE}.o                         \
             PrintStatement_${MODE}.o                   \
             RectRegionNode_${MODE}.o                   \
             RegionNode_${MODE}.o                       \
             RegionNodeStack_${MODE}.o                  \
             RelationalBooleanNode_${MODE}.o            \
             RepeatColorNode_${MODE}.o                  \
             SingleColorColorNode_${MODE}.o             \
             SPolyRegionNode_${MODE}.o                  \
             Statement_${MODE}.o                        \
             SwitchStatement_${MODE}.o                  \
             SwitchStatementStack_${MODE}.o             \
             TernaryComplexNode_${MODE}.o               \
             TernaryDoubleNode_${MODE}.o                \
             TextIntersectNode_${MODE}.o                \
             ThreeArgFunctionDoubleNode_${MODE}.o       \
             TrueBooleanNode_${MODE}.o                  \
             TwoArgFunctionComplexNode_${MODE}.o        \
             TwoArgFunctionDoubleNode_${MODE}.o         \
             UnaryComplexNode_${MODE}.o                 \
             UnaryDoubleNode_${MODE}.o                  \
             VariableComplexNode_${MODE}.o              \
             VariableDoubleNode_${MODE}.o               \
             XorRegionNode_${MODE}.o

COBJ := fractal.yacc_${MODE}.o fractal.lex_${MODE}.o

GENSRC := fractal.yacc.c fractal.lex.c

###############################################################################
# Add these lines to quiet gnu make's warnings about circular dependencies
# which stem from the fact that gnu make recognizes ".yacc" as an extension.
###############################################################################

.SUFFIXES:
.SUFFIXES: .yacc                           

###############################################################################
# Rules
###############################################################################

${LIBRARY}: ${OBJECTS} ${COBJ}
	${MKLIB} ${OBJECTS} ${COBJ}

release:
	${MAKE} RELEASE=1

debug:
	${MAKE}

%_${MODE}.o: %.cpp
	${CPP} ${CPPFLAGS} ${OUT}$@ $<

%_${MODE}.o:%.c
	${CPP} ${CPPFLAGS} ${OUT}$@ $<

fractal.yacc.c fractal.yacc.h: fractal.yacc
	${YACC} ${YACCFLAGS} fractal.yacc

fractal.lex.c: fractal.lex
	${LEX} ${LEXFLAGS} fractal.lex                          

clean:
	-${RM} *.a *.o *.pdb

###############################################################################
# Unix Only Rules
###############################################################################

realclean:
	-rm ${GENSRC}
	${MAKE} clean    

depend:
	@g++ -MM ${INCLUDE} *.c *.cpp | sed 's/\.o/_$${MODE}.o/'

###############################################################################
# Dependencies - created by running: "make depend >> Makefile"
###############################################################################
fractal.lex_${MODE}.o: fractal.lex.c fractal.yacc.h FractalLexer.h dmemory.h
fractal.yacc_${MODE}.o: fractal.yacc.c dcomplex.h Fractal.h ColorEnvironment.h \
  ComplexVariables.h DoubleVariables.h ColorTable.h rowsupplier.h \
  DoubleNodeStack.h GenericStack.h DoubleNode.h BinaryDoubleNode.h \
  UnaryDoubleNode.h VariableDoubleNode.h ConstantDoubleNode.h \
  AttributeDoubleNode.h OneArgFunctionDoubleNode.h \
  TwoArgFunctionDoubleNode.h ThreeArgFunctionDoubleNode.h \
  MapColorFunctionDoubleNode.h TernaryDoubleNode.h TextIntersectNode.h \
  MapColorFunctionDoubleNodeStack.h AssignmentDoubleNode.h \
  GetEntryDoubleNode.h ComplexNodeStack.h ComplexNode.h \
  BinaryComplexNode.h UnaryComplexNode.h NumericComplexNode.h \
  VariableComplexNode.h OneArgFunctionComplexNode.h \
  TwoArgFunctionComplexNode.h MixedThreeArgFunctionComplexNode.h \
  TernaryComplexNode.h AssignmentComplexNode.h BooleanNodeStack.h \
  BooleanNode.h ConditionalBooleanNode.h RelationalBooleanNode.h \
  TrueBooleanNode.h FalseBooleanNode.h NotBooleanNode.h ColorNodeStack.h \
  ColorNode.h ColorStack.h ColorsColorNode.h Counter.h DefineColorNode.h \
  GradientColorNode.h RepeatColorNode.h SingleColorColorNode.h \
  ConditionalStatement.h Statement.h tf.h CompoundStatement.h \
  CompoundStatementStack.h ComplexAssignmentStatement.h \
  DoubleAssignmentStatement.h RGBSetColorStatement.h \
  HSVSetColorStatement.h IndexedSetColorStatement.h ForStatement.h \
  NullStatement.h PrintStatement.h BreakStatement.h ContinueStatement.h \
  ComplexNodePrintArg.h PrintArg.h DoubleNodePrintArg.h LiteralPrintArg.h \
  FlagStack.h SwitchStatement.h SwitchStatementStack.h \
  InsideBooleanNode.h RegionNodeStack.h RegionNode.h CircleRegionNode.h \
  EllipseRegionNode.h RectRegionNode.h PolyRegionNode.h SPolyRegionNode.h \
  CrossRegionNode.h NotRegionNode.h AndRegionNode.h OrRegionNode.h \
  XorRegionNode.h dmemory.h FractalLexer.h fractal_parse.h
AndRegionNode_${MODE}.o: AndRegionNode.cpp AndRegionNode.h RegionNode.h dmemory.h
AssignmentComplexNode_${MODE}.o: AssignmentComplexNode.cpp \
  AssignmentComplexNode.h ComplexNode.h dcomplex.h \
  ComplexAssignmentStatement.h Statement.h tf.h dmemory.h
AssignmentDoubleNode_${MODE}.o: AssignmentDoubleNode.cpp AssignmentDoubleNode.h \
  DoubleNode.h DoubleAssignmentStatement.h Statement.h tf.h dmemory.h
AttributeDoubleNode_${MODE}.o: AttributeDoubleNode.cpp AttributeDoubleNode.h \
  DoubleNode.h dcomplex.h ComplexNode.h dmemory.h
BinaryComplexNode_${MODE}.o: BinaryComplexNode.cpp BinaryComplexNode.h \
  ComplexNode.h dcomplex.h dmemory.h
BinaryDoubleNode_${MODE}.o: BinaryDoubleNode.cpp BinaryDoubleNode.h DoubleNode.h \
  dmemory.h
BooleanNode_${MODE}.o: BooleanNode.cpp BooleanNode.h
BooleanNodeStack_${MODE}.o: BooleanNodeStack.cpp BooleanNodeStack.h \
  GenericStack.h BooleanNode.h
BreakStatement_${MODE}.o: BreakStatement.cpp BreakStatement.h Statement.h tf.h
CircleRegionNode_${MODE}.o: CircleRegionNode.cpp CircleRegionNode.h RegionNode.h \
  ComplexNode.h dcomplex.h DoubleNode.h dmemory.h
ColorNode_${MODE}.o: ColorNode.cpp ColorNode.h
ColorNodeStack_${MODE}.o: ColorNodeStack.cpp ColorNodeStack.h GenericStack.h \
  ColorNode.h
ColorsColorNode_${MODE}.o: ColorsColorNode.cpp ColorsColorNode.h ColorNode.h \
  ColorNodeStack.h GenericStack.h dmemory.h
ColorStack_${MODE}.o: ColorStack.cpp ColorStack.h GenericStack.h
ColorTable_${MODE}.o: ColorTable.cpp ColorTable.h dmemory.h
ComplexAssignmentStatement_${MODE}.o: ComplexAssignmentStatement.cpp \
  ComplexAssignmentStatement.h Statement.h tf.h dcomplex.h ComplexNode.h \
  dmemory.h
ComplexNode_${MODE}.o: ComplexNode.cpp ComplexNode.h dcomplex.h
ComplexNodePrintArg_${MODE}.o: ComplexNodePrintArg.cpp ComplexNodePrintArg.h \
  PrintArg.h ComplexNode.h dcomplex.h dmemory.h
ComplexNodeStack_${MODE}.o: ComplexNodeStack.cpp ComplexNodeStack.h \
  GenericStack.h ComplexNode.h dcomplex.h
ComplexVariables_${MODE}.o: ComplexVariables.cpp ComplexVariables.h dcomplex.h \
  tf.h dmemory.h
CompoundStatement_${MODE}.o: CompoundStatement.cpp CompoundStatement.h \
  Statement.h tf.h dmemory.h
CompoundStatementStack_${MODE}.o: CompoundStatementStack.cpp \
  CompoundStatementStack.h GenericStack.h
ConditionalBooleanNode_${MODE}.o: ConditionalBooleanNode.cpp \
  ConditionalBooleanNode.h BooleanNode.h dmemory.h
ConditionalStatement_${MODE}.o: ConditionalStatement.cpp ConditionalStatement.h \
  Statement.h tf.h BooleanNode.h dmemory.h
ConstantDoubleNode_${MODE}.o: ConstantDoubleNode.cpp ConstantDoubleNode.h \
  DoubleNode.h
ContinueStatement_${MODE}.o: ContinueStatement.cpp ContinueStatement.h \
  Statement.h tf.h
Counter_${MODE}.o: Counter.cpp Counter.h GenericStack.h dmemory.h
CrossRegionNode_${MODE}.o: CrossRegionNode.cpp CrossRegionNode.h RegionNode.h \
  ComplexNode.h dcomplex.h DoubleNode.h tf.h dmemory.h
DefineColorNode_${MODE}.o: DefineColorNode.cpp DefineColorNode.h ColorNode.h \
  ColorNodeStack.h GenericStack.h ColorTable.h dmemory.h
DoubleAssignmentStatement_${MODE}.o: DoubleAssignmentStatement.cpp \
  DoubleAssignmentStatement.h Statement.h tf.h DoubleVariables.h \
  DoubleNode.h dmemory.h
DoubleNode_${MODE}.o: DoubleNode.cpp DoubleNode.h
DoubleNodePrintArg_${MODE}.o: DoubleNodePrintArg.cpp DoubleNodePrintArg.h \
  PrintArg.h DoubleNode.h dmemory.h
DoubleNodeStack_${MODE}.o: DoubleNodeStack.cpp DoubleNodeStack.h GenericStack.h \
  DoubleNode.h
DoubleVariables_${MODE}.o: DoubleVariables.cpp DoubleVariables.h tf.h dmemory.h
EllipseRegionNode_${MODE}.o: EllipseRegionNode.cpp EllipseRegionNode.h \
  RegionNode.h ComplexNode.h dcomplex.h DoubleNode.h tf.h dmemory.h
FalseBooleanNode_${MODE}.o: FalseBooleanNode.cpp FalseBooleanNode.h BooleanNode.h
FlagStack_${MODE}.o: FlagStack.cpp FlagStack.h GenericStack.h dmemory.h
ForStatement_${MODE}.o: ForStatement.cpp ForStatement.h Statement.h tf.h \
  BooleanNode.h InfiniteLoopCallback.h dmemory.h
Fractal_${MODE}.o: Fractal.cpp Fractal.h ColorEnvironment.h ComplexVariables.h \
  dcomplex.h DoubleVariables.h ColorTable.h rowsupplier.h \
  InfiniteLoopCallback.h Statement.h tf.h BooleanNode.h dmemory.h
GenericStack_${MODE}.o: GenericStack.cpp GenericStack.h cpp_assert.h dmemory.h
GetEntryDoubleNode_${MODE}.o: GetEntryDoubleNode.cpp GetEntryDoubleNode.h \
  DoubleNode.h ColorEnvironment.h dmemory.h
GradientColorNode_${MODE}.o: GradientColorNode.cpp GradientColorNode.h \
  ColorNode.h ColorStack.h GenericStack.h ColorTable.h dmemory.h
HSVSetColorStatement_${MODE}.o: HSVSetColorStatement.cpp HSVSetColorStatement.h \
  Statement.h tf.h DoubleNode.h ColorEnvironment.h dmemory.h
IndexedSetColorStatement_${MODE}.o: IndexedSetColorStatement.cpp \
  IndexedSetColorStatement.h Statement.h tf.h DoubleNode.h \
  ColorEnvironment.h dmemory.h
InfiniteLoopCallback_${MODE}.o: InfiniteLoopCallback.cpp InfiniteLoopCallback.h
InsideBooleanNode_${MODE}.o: InsideBooleanNode.cpp InsideBooleanNode.h \
  BooleanNode.h ComplexNode.h dcomplex.h RegionNode.h dmemory.h
LiteralPrintArg_${MODE}.o: LiteralPrintArg.cpp LiteralPrintArg.h PrintArg.h \
  dmemory.h
MapColorFunctionDoubleNode_${MODE}.o: MapColorFunctionDoubleNode.cpp \
  MapColorFunctionDoubleNode.h DoubleNode.h TwoArgFunctionDoubleNode.h \
  dmemory.h
MapColorFunctionDoubleNodeStack_${MODE}.o: MapColorFunctionDoubleNodeStack.cpp \
  MapColorFunctionDoubleNodeStack.h GenericStack.h \
  MapColorFunctionDoubleNode.h DoubleNode.h
MixedThreeArgFunctionComplexNode_${MODE}.o: MixedThreeArgFunctionComplexNode.cpp \
  MixedThreeArgFunctionComplexNode.h ComplexNode.h dcomplex.h \
  AttributeDoubleNode.h DoubleNode.h dmemory.h
NotBooleanNode_${MODE}.o: NotBooleanNode.cpp NotBooleanNode.h BooleanNode.h \
  dmemory.h
NotRegionNode_${MODE}.o: NotRegionNode.cpp NotRegionNode.h RegionNode.h dmemory.h
NullStatement_${MODE}.o: NullStatement.cpp NullStatement.h Statement.h tf.h \
  BooleanNode.h
NumericComplexNode_${MODE}.o: NumericComplexNode.cpp NumericComplexNode.h \
  ComplexNode.h dcomplex.h ConstantDoubleNode.h DoubleNode.h dmemory.h
OneArgFunctionComplexNode_${MODE}.o: OneArgFunctionComplexNode.cpp \
  OneArgFunctionComplexNode.h ComplexNode.h dcomplex.h dmemory.h
OneArgFunctionDoubleNode_${MODE}.o: OneArgFunctionDoubleNode.cpp \
  OneArgFunctionDoubleNode.h DoubleNode.h AttributeDoubleNode.h \
  dcomplex.h dmemory.h
OrRegionNode_${MODE}.o: OrRegionNode.cpp OrRegionNode.h RegionNode.h dmemory.h
PolyRegionNode_${MODE}.o: PolyRegionNode.cpp PolyRegionNode.h RegionNode.h \
  ComplexNode.h dcomplex.h DoubleNode.h tf.h dmemory.h
PrintArg_${MODE}.o: PrintArg.cpp PrintArg.h
PrintStatement_${MODE}.o: PrintStatement.cpp PrintStatement.h Statement.h tf.h \
  PrintArg.h dmemory.h
RectRegionNode_${MODE}.o: RectRegionNode.cpp RectRegionNode.h RegionNode.h \
  ComplexNode.h dcomplex.h DoubleNode.h tf.h dmemory.h
RegionNode_${MODE}.o: RegionNode.cpp RegionNode.h
RegionNodeStack_${MODE}.o: RegionNodeStack.cpp RegionNodeStack.h GenericStack.h \
  RegionNode.h
RelationalBooleanNode_${MODE}.o: RelationalBooleanNode.cpp \
  RelationalBooleanNode.h BooleanNode.h DoubleNode.h dmemory.h
RepeatColorNode_${MODE}.o: RepeatColorNode.cpp RepeatColorNode.h ColorNode.h \
  ColorNodeStack.h GenericStack.h dmemory.h
RGBSetColorStatement_${MODE}.o: RGBSetColorStatement.cpp RGBSetColorStatement.h \
  Statement.h tf.h DoubleNode.h ColorEnvironment.h dmemory.h
SingleColorColorNode_${MODE}.o: SingleColorColorNode.cpp SingleColorColorNode.h \
  ColorNode.h ColorTable.h
SPolyRegionNode_${MODE}.o: SPolyRegionNode.cpp SPolyRegionNode.h RegionNode.h \
  ComplexNode.h dcomplex.h AttributeDoubleNode.h DoubleNode.h tf.h \
  dmemory.h
Statement_${MODE}.o: Statement.cpp Statement.h tf.h
SwitchStatement_${MODE}.o: SwitchStatement.cpp SwitchStatement.h Statement.h tf.h \
  DoubleNode.h CompoundStatement.h dmemory.h
SwitchStatementStack_${MODE}.o: SwitchStatementStack.cpp SwitchStatementStack.h \
  GenericStack.h
TernaryComplexNode_${MODE}.o: TernaryComplexNode.cpp TernaryComplexNode.h \
  ComplexNode.h dcomplex.h BooleanNode.h dmemory.h
TernaryDoubleNode_${MODE}.o: TernaryDoubleNode.cpp TernaryDoubleNode.h \
  DoubleNode.h BooleanNode.h dmemory.h
TextIntersectNode_${MODE}.o: TextIntersectNode.cpp TextIntersectNode.h \
  DoubleNode.h ComplexNode.h dcomplex.h dmemory.h
ThreeArgFunctionDoubleNode_${MODE}.o: ThreeArgFunctionDoubleNode.cpp \
  ThreeArgFunctionDoubleNode.h DoubleNode.h AttributeDoubleNode.h \
  dcomplex.h HSVSetColorStatement.h Statement.h tf.h dmemory.h
TrueBooleanNode_${MODE}.o: TrueBooleanNode.cpp TrueBooleanNode.h BooleanNode.h \
  DoubleNode.h
TwoArgFunctionComplexNode_${MODE}.o: TwoArgFunctionComplexNode.cpp \
  TwoArgFunctionComplexNode.h ComplexNode.h dcomplex.h \
  TwoArgFunctionDoubleNode.h DoubleNode.h ComplexVariables.h dmemory.h
TwoArgFunctionDoubleNode_${MODE}.o: TwoArgFunctionDoubleNode.cpp \
  TwoArgFunctionDoubleNode.h DoubleNode.h dmemory.h
UnaryComplexNode_${MODE}.o: UnaryComplexNode.cpp UnaryComplexNode.h ComplexNode.h \
  dcomplex.h dmemory.h
UnaryDoubleNode_${MODE}.o: UnaryDoubleNode.cpp UnaryDoubleNode.h DoubleNode.h \
  dmemory.h
VariableComplexNode_${MODE}.o: VariableComplexNode.cpp VariableComplexNode.h \
  ComplexNode.h dcomplex.h dmemory.h
VariableDoubleNode_${MODE}.o: VariableDoubleNode.cpp VariableDoubleNode.h \
  DoubleNode.h dmemory.h
XorRegionNode_${MODE}.o: XorRegionNode.cpp XorRegionNode.h RegionNode.h dmemory.h
