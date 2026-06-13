#ifndef GENERATEDOT_H
#define GENERATEDOT_H

#include <QTextStream>

#include "../models/exprnode.h"


void generateDOT(ExprNode* root, QTextStream& out);
void generateDOTRecursive(ExprNode* node, QTextStream& out, int& nodeId);

#endif // GENERATEDOT_H
