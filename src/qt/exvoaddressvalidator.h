// Copyright (c) 2017-2018 EXVO developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef EXVO_QT_EXVOADDRESSVALIDATOR_H
#define EXVO_QT_EXVOADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class ExvoAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit ExvoAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Exvo address widget validator, checks for a valid exvo address.
 */
class ExvoAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit ExvoAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // EXVO_QT_EXVOADDRESSVALIDATOR_H
