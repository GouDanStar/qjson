/* This file is part of QJson
 *
 * Copyright (C) 2008 Flavio Castelli <flavio.castelli@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef _JSON_DRIVER
#define _JSON_DRIVER

#include "json_parser.hh"
#include "json_scanner.h"
#include "qjson_export.h"

#include <QtCore/QIODevice>
#include <QtCore/QVariant>

namespace yy {
  class json_parser;
  class location;
}

/**
* @brief Main class used for converting JSON data to QVariant objects
*/
class QJSON_EXPORT JSonDriver
{
  friend int yy::yylex(YYSTYPE *yylval, yy::location *yylloc, JSonDriver* driver);
  friend class yy::json_parser;

  public:
    JSonDriver();
    virtual ~JSonDriver();

    /**
    * Read JSON string from the I/O Device and converts it to a QVariant object
    * @param io Input output device
    * @param ok if a conversion error occurs, *ok is set to false; otherwise *ok is set to true.
    * @returns a QVariant object generated from the JSON string
    */
    QVariant parse(QIODevice* io, bool* ok = 0);

    /**
    * This is a method provided for convenience.
    * @param jsonString string containing the JSON object representation
    * @param ok if a conversion error occurs, *ok is set to false; otherwise *ok is set to true.
    * @returns a QVariant object generated from the JSON string
    * /sa error
    */
    QVariant parse(const QString& jsonString, bool* ok = 0);

    /**
      * This method generates a textual JSON representation and outputs it to the
      * passed in I/O Device.
      * @param v The JSON document in its in-memory representation as generated by the
      * parser side of this.
      * @param out Input output device
      * @param ok if a conversion error occurs, *ok is set to false; otherwise *ok is set to true
      */
    void serialize( const QVariant& v, QIODevice* out, bool* ok = 0 );

    /**
      * This is a method provided for convenience. It turns the passed in in-memory
      * representation of the JSON document into a textual one, which is returned.
      * If the returned string is empty, the document was empty. If it was null, there
      * was a parsing error.
      */
    const QString serialize( const QVariant& v );

    /**
    * This method returns the error message
    * @returns a QString object containing the error message of the last parse operation
    */
    QString error() const { return m_errorMsg; }

    /**
    * This method returns line number where the error occurred
    * @returns the line number where the error occurred
    */
    int errorLine() const { return m_errorLine; }


  private:
    void setError(QString errorMsg, int line);
    JSonScanner* scanner() { return m_scanner; };

    JSonScanner* m_scanner;
    bool m_negate;
    bool m_error;
    int m_errorLine;
    QString m_errorMsg;
    QVariant m_result;
};

#endif
