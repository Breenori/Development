//       $Id: arithmetic_parser.h 41750 2020-11-22 09:32:40Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/bin/cepheiden/pfc/trunk/scanner/arithmetic-parser/src/arithmetic_parser.h $
// $Revision: 41750 $
//     $Date: 2020-11-22 10:32:40 +0100 (Sun, 22 Nov 2020) $
//   $Author: p20068 $
//   Creator: Peter Kulczycki
//  Creation: November 6, 2020
// Copyright: (c) 2020 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg.
//            It is distributed under the Boost Software License (see
//            https://www.boost.org/users/license.html).

// Expression  = Term { AddOp Term }.
// Term        = Factor { MultOp Factor }.
// Factor      = [ AddOp ] ( Number | PExpression ).
// PExpression = "(" Expression ")" .
// AddOp       = "+" | "-" .
// MultOp      = "*" | "/" .
// Number      = Die Grammatik für Number ist im Scanner eingebaut (Integer | Real).

#pragma once

#include "pfc_scanner.h"
#include <map>

// -------------------------------------------------------------------------------------------------

struct parser_exception : std::runtime_error {
   explicit parser_exception (std::string const & m) : std::runtime_error {m} {
   }
};

// -------------------------------------------------------------------------------------------------

class arithmetic_parser final {
   public:
      auto parse (std::istream & in) {
         m_scanner.set_istream (in, true); auto const value {parse_Expression ()};
         m_scanner.set_istream ();

         return value;
      }

      auto parse (std::string const & str) {
         std::stringstream in{str}; return parse(in);
      }
      void assign_Variable(std::string const& var, int const num) {
          if (var.length() == 0)
          {
              throw parser_exception("Error. Empty Variable.");
          }
          variables.insert_or_assign(var, num);
      }


   private:
      bool is_tb_AddOp () const {
         return m_scanner.is ('+') || m_scanner.is ('-');
      }

      bool is_tb_Expression () const {
         return is_tb_Term ();
      }

      bool is_tb_Factor () const {
         return is_tb_AddOp () || is_tb_Number () || is_tb_PExpression ()||is_tb_Variable();
      }

      bool is_tb_MultOp () const {
         return m_scanner.is ('*') || m_scanner.is ('/');
      }

      bool is_tb_Number () const {
         return m_scanner.is_number ();
      }

      bool is_tb_PExpression () const {
         return m_scanner.is ('(');
      }

      bool is_tb_Term () const {
         return is_tb_Factor ();
      }

      bool is_tb_Variable()const {
          return m_scanner.is_identifier();
      }

      double parse_AddOp () {
         if (!is_tb_AddOp ())
            throw parser_exception {"Error parsing 'AddOp'."};

         auto sign {0.0};

         if (m_scanner.is ('+')) { sign =  1; m_scanner.next_symbol (); }
         else if (m_scanner.is ('-')) { sign = -1; m_scanner.next_symbol (); }

         else
            throw parser_exception {"Error parsing 'AddOp'."};

         return sign;
      }

      double parse_Expression() {
          if (!is_tb_Expression())
              throw parser_exception{ "Error parsing 'Expression'." };
          double value{ parse_Term() };
          while (is_tb_AddOp())
          {
              double const sign{ parse_AddOp() };
              value += sign * parse_Term();
          }
          return value;
      }

      double parse_Factor () {
         if (!is_tb_Factor ())
            throw parser_exception {"Error parsing 'Factor'."};

         auto const sign  {is_tb_AddOp () ? parse_AddOp () : 1.0};
         auto       value {0.0};

         if (is_tb_Number()) {
             value = m_scanner.get_number(); m_scanner.next_symbol();

         }
         else if (is_tb_PExpression())
             value = parse_PExpression();
         else if (is_tb_Variable()) {
             std::string var_name{ m_scanner.get_identifier() };
             if (variables.contains(var_name))
             {
                 value = variables.find(var_name)->second;
                 m_scanner.next_symbol();
             }
             else
             {
                 throw parser_exception("No variable found.");
             }
         }
   
         else
            throw parser_exception {"Error parsing 'Factor'."};

         return sign * value;
      }

      double parse_PExpression () {
         if (!is_tb_PExpression ())
            throw parser_exception {"Error parsing 'PExpression'."};

         m_scanner.next_symbol ('('); auto const value {parse_Expression ()};
         m_scanner.next_symbol (')');

         return value;
      }

      double parse_Term () {
         if (!is_tb_Term ())
            throw parser_exception {"Error parsing 'Term'."};

         auto value {parse_Factor ()};

         while (is_tb_MultOp ())
            if (m_scanner.is ('*')) {
               m_scanner.next_symbol (); value *= parse_Factor ();

            } else if (m_scanner.is ('/')) {
               m_scanner.next_symbol ();
               double divider = parse_Factor();
               if (divider == 0)
                   throw parser_exception("Error. Division by zero.");
               else
               value /= divider;

            } else
               throw parser_exception {"Error parsing 'Term'."};

         return value;
      }

      pfc::scanner m_scanner;//scanner
      std::map<std::string, int> variables;//namelist
};
