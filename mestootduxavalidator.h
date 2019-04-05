#ifndef MESTOOTDUXAVALIDATOR_H
#define MESTOOTDUXAVALIDATOR_H

#include <QValidator>
#include <QRegExp>


class mestoOtduxaValidator : public QValidator
{
    public:
        mestoOtduxaValidator(QObject *parent) {}
        ~mestoOtduxaValidator() {}
        QValidator::State validate(QString & input, int & pos ) const;
};
#endif // MESTOOTDUXAVALIDATOR_H
