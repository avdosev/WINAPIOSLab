#include "mestootduxavalidator.h"

QValidator::State mestoOtduxaValidator::validate(QString & input, int & pos )const {
   QRegExp inter("[А-Я]?[а-я]*"), accept("[А-Я][а-я]+");
   if (!inter.exactMatch(input))
       return QValidator::Invalid;
   else if (!accept.exactMatch(input))
       return QValidator::Intermediate;
   else
       return QValidator::Acceptable;
}
